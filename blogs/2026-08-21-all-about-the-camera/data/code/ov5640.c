/**
  ******************************************************************************
  * @file    ov5640.c
  * @brief   OmniVision OV5640 driver for STM32H7R7, MIPI CSI-2. Implementation.
  *
  * Register references in comments are to:
  *   OV5640 datasheet, product specification version 2.03, may 2011.
  *
  * See README.md for the procedure this implements and NOTES.md for the pin
  * tables and the derivations behind the numbers in the mode tables.
  ******************************************************************************
  */

#include "ov5640.h"

/*============================================================================*/
/* Local helpers                                                              */
/*============================================================================*/

#define OV5640_I2C_TIMEOUT_MS   100U

/** @brief One entry of a register script. */
typedef struct
{
    uint16_t reg;
    uint8_t  val;
} OV5640_RegVal_t;

/** @brief Sentinel: a delay in milliseconds rather than a register write. */
#define OV5640_REG_DELAY        0xFFFFU

/** @brief One output mode: sensor window, subsampling, timing, PLL. */
typedef struct
{
    uint16_t x_start;   /*!< 0x3800/0x3801                                    */
    uint16_t y_start;   /*!< 0x3802/0x3803                                    */
    uint16_t x_end;     /*!< 0x3804/0x3805                                    */
    uint16_t y_end;     /*!< 0x3806/0x3807                                    */
    uint16_t width;     /*!< 0x3808/0x3809, after the scaler                  */
    uint16_t height;    /*!< 0x380A/0x380B                                    */
    uint16_t hts;       /*!< 0x380C/0x380D, in PIXEL periods                  */
    uint16_t vts;       /*!< 0x380E/0x380F                                    */
    uint16_t x_offset;  /*!< 0x3810/0x3811                                    */
    uint16_t y_offset;  /*!< 0x3812/0x3813                                    */
    uint8_t  x_inc;     /*!< 0x3814, {odd[7:4], even[3:0]}                    */
    uint8_t  y_inc;     /*!< 0x3815                                           */
    bool     binning;   /*!< 0x3821[0] and 0x5003[2]                          */
    bool     scaler;    /*!< 0x5001[5]                                        */
    uint8_t  pll_mult;  /*!< 0x3036: the only PLL term that varies by mode    */
    uint8_t  pll_pre;   /*!< 0x3037[3:0]                                      */
    uint8_t  sys_div;   /*!< 0x3035[7:4]                                      */
} OV5640_Mode_t;

static uint32_t ov5640_xvclk(const OV5640_Ctx_t *ctx)
{
    return (ctx->xvclk_hz != 0U) ? ctx->xvclk_hz : OV5640_XVCLK_DEFAULT_HZ;
}

static uint16_t ov5640_addr(const OV5640_Ctx_t *ctx)
{
    return (ctx->i2c_addr != 0U) ? (uint16_t)ctx->i2c_addr : (uint16_t)OV5640_I2C_ADDR;
}

static OV5640_Lanes_t ov5640_lanes(const OV5640_Ctx_t *ctx)
{
    return (ctx->lanes == OV5640_LANES_1) ? OV5640_LANES_1 : OV5640_LANES_2;
}

/*============================================================================*/
/* Mode tables                                                                */
/*============================================================================*/

/*
 * These are OmniVision's reference tables, used verbatim.
 *
 * That is worth a sentence, because the DVP version of this driver could not do
 * it. HTS and VTS are counted in PIXEL periods. On an 8-bit parallel bus one
 * clock carries one BYTE, so a 2-bytes-per-pixel format needs twice the line
 * budget and the published tables do not fit - every HTS/VTS had to be
 * re-derived for the byte domain. CSI-2 serialises pixels, so the pixel-domain
 * tables are correct as written and one whole class of bug disappears.
 *
 * The constraints each row satisfies:
 *
 *     HTS >= readout width  (ISP input width after subsampling) + h blanking
 *     VTS >= readout height + v blanking
 *     pre-scale size >= output size          (the scaler only downscales)
 *     fps = PCLK / (HTS x VTS)
 *
 * The subsampled family (x_inc = y_inc = 0x31) reads the full array at 2x
 * subsample: 2624 x 1944 becomes 1312 x 972, and after the 16/6 offsets the
 * pre-scaling size is exactly 1280 x 960. Every output up to that is the ISP
 * scaler on the same frame, so the field of view never changes.
 *
 * Only three PLL terms vary by mode; everything else in the clock tree is
 * constant and lives in ov5640_clock_defaults(). Two settings cover all nine
 * modes: mult=56 gives VCO 448 MHz / PCLK 56 MHz / 448 Mbps per lane, and
 * mult=84 gives VCO 672 MHz / PCLK 84 MHz / 672 Mbps per lane. The frame rates
 * in the comments are for 2 lanes; one lane halves them (see README section 3).
 */
static const OV5640_Mode_t ov5640_modes[OV5640_RES_COUNT] =
{
    /* QQVGA 160x120 - scaled from 1280x960. 56e6/(1896*984) = 30.0 fps */
    [OV5640_RES_QQVGA] = {
        .x_start = 0U, .y_start = 4U, .x_end = 2623U, .y_end = 1947U,
        .width = 160U, .height = 120U, .hts = 1896U, .vts = 984U,
        .x_offset = 16U, .y_offset = 6U, .x_inc = 0x31U, .y_inc = 0x31U,
        .binning = true, .scaler = true,
        .pll_mult = 56U, .pll_pre = 3U, .sys_div = 1U,
    },
    /* QVGA 320x240 - scaled from 1280x960. 30.0 fps */
    [OV5640_RES_QVGA] = {
        .x_start = 0U, .y_start = 4U, .x_end = 2623U, .y_end = 1947U,
        .width = 320U, .height = 240U, .hts = 1896U, .vts = 984U,
        .x_offset = 16U, .y_offset = 6U, .x_inc = 0x31U, .y_inc = 0x31U,
        .binning = true, .scaler = true,
        .pll_mult = 56U, .pll_pre = 3U, .sys_div = 1U,
    },
    /* VGA 640x480 - scaled from 1280x960. 30.0 fps */
    [OV5640_RES_VGA] = {
        .x_start = 0U, .y_start = 4U, .x_end = 2623U, .y_end = 1947U,
        .width = 640U, .height = 480U, .hts = 1896U, .vts = 984U,
        .x_offset = 16U, .y_offset = 6U, .x_inc = 0x31U, .y_inc = 0x31U,
        .binning = true, .scaler = true,
        .pll_mult = 56U, .pll_pre = 3U, .sys_div = 1U,
    },
    /* SVGA 800x600 - scaled from 1280x960. 30.0 fps */
    [OV5640_RES_SVGA] = {
        .x_start = 0U, .y_start = 4U, .x_end = 2623U, .y_end = 1947U,
        .width = 800U, .height = 600U, .hts = 1896U, .vts = 984U,
        .x_offset = 16U, .y_offset = 6U, .x_inc = 0x31U, .y_inc = 0x31U,
        .binning = true, .scaler = true,
        .pll_mult = 56U, .pll_pre = 3U, .sys_div = 1U,
    },
    /* XGA 1024x768 - scaled from 1280x960. 30.0 fps */
    [OV5640_RES_XGA] = {
        .x_start = 0U, .y_start = 4U, .x_end = 2623U, .y_end = 1947U,
        .width = 1024U, .height = 768U, .hts = 1896U, .vts = 984U,
        .x_offset = 16U, .y_offset = 6U, .x_inc = 0x31U, .y_inc = 0x31U,
        .binning = true, .scaler = true,
        .pll_mult = 56U, .pll_pre = 3U, .sys_div = 1U,
    },
    /* SXGA 1280x960 - the full pre-scaled frame, scaler 1:1. 30.0 fps */
    [OV5640_RES_SXGA] = {
        .x_start = 0U, .y_start = 4U, .x_end = 2623U, .y_end = 1947U,
        .width = 1280U, .height = 960U, .hts = 1896U, .vts = 984U,
        .x_offset = 16U, .y_offset = 6U, .x_inc = 0x31U, .y_inc = 0x31U,
        .binning = true, .scaler = false,
        .pll_mult = 56U, .pll_pre = 3U, .sys_div = 1U,
    },
    /* 720p 1280x720 - cropped to 2624x1456, subsampled to 1312x728,
       pre-scale 1280x720 so the scaler is 1:1. 84e6/(1892*740) = 60.0 fps */
    [OV5640_RES_720P] = {
        .x_start = 0U, .y_start = 250U, .x_end = 2623U, .y_end = 1705U,
        .width = 1280U, .height = 720U, .hts = 1892U, .vts = 740U,
        .x_offset = 16U, .y_offset = 4U, .x_inc = 0x31U, .y_inc = 0x31U,
        .binning = true, .scaler = false,
        .pll_mult = 84U, .pll_pre = 3U, .sys_div = 1U,
    },
    /* 1080p 1920x1080 - cropped from full resolution, no subsampling.
       84e6/(2500*1120) = 30.0 fps */
    [OV5640_RES_1080P] = {
        .x_start = 336U, .y_start = 434U, .x_end = 2287U, .y_end = 1521U,
        .width = 1920U, .height = 1080U, .hts = 2500U, .vts = 1120U,
        .x_offset = 16U, .y_offset = 4U, .x_inc = 0x11U, .y_inc = 0x11U,
        .binning = false, .scaler = false,
        .pll_mult = 84U, .pll_pre = 3U, .sys_div = 1U,
    },
    /* 5 MP 2592x1944 - full resolution. 84e6/(2844*1968) = 15.0 fps.
       This is the case the datasheet says needs MIPI (8.4, table 8-5
       footnote e): over DVP it would want 168 MHz of byte clock. */
    [OV5640_RES_5MP] = {
        .x_start = 0U, .y_start = 0U, .x_end = 2623U, .y_end = 1951U,
        .width = 2592U, .height = 1944U, .hts = 2844U, .vts = 1968U,
        .x_offset = 16U, .y_offset = 4U, .x_inc = 0x11U, .y_inc = 0x11U,
        .binning = false, .scaler = false,
        .pll_mult = 84U, .pll_pre = 3U, .sys_div = 1U,
    },
};

/*============================================================================*/
/* Format table                                                               */
/*============================================================================*/

typedef struct
{
    uint8_t format_ctrl00;  /*!< 0x4300                                       */
    uint8_t format_mux;     /*!< 0x501F                                       */
    uint8_t isp_control00;  /*!< 0x5000                                       */
    uint8_t bit_mode;       /*!< 0x3034[3:0]: 0x8 = 8-bit, 0xA = 10-bit       */
    uint8_t bits_per_pixel; /*!< on the CSI-2 wire                            */
    uint8_t csi_data_type;  /*!< what the receiver must be told to expect     */
} OV5640_FormatCfg_t;

static const OV5640_FormatCfg_t ov5640_formats[OV5640_FORMAT_COUNT] =
{
    /* RGB565 {b[4:0],g[5:3]},{g[2:0],r[4:0]} - sequence 0xF */
    [OV5640_FORMAT_RGB565_BGR] = {
        0x6FU, 0x01U, 0xA7U, 0x08U, 16U, OV5640_CSI_DT_RGB565 },
    /* RGB565 {r[4:0],g[5:3]},{g[2:0],b[4:0]} - sequence 0x1 */
    [OV5640_FORMAT_RGB565_RGB] = {
        0x61U, 0x01U, 0xA7U, 0x08U, 16U, OV5640_CSI_DT_RGB565 },
    [OV5640_FORMAT_YUV422_YUYV] = {
        0x30U, 0x00U, 0xA7U, 0x08U, 16U, OV5640_CSI_DT_YUV422_8B },
    [OV5640_FORMAT_YUV422_UYVY] = {
        0x32U, 0x00U, 0xA7U, 0x08U, 16U, OV5640_CSI_DT_YUV422_8B },
    /* RAW: demosaic and RAW gamma off so the Bayer mosaic reaches you intact.
       Halves the lane rate versus RGB565 - see NOTES.md section 3.6. */
    [OV5640_FORMAT_RAW8_BGGR] = {
        0x00U, 0x03U, 0x06U, 0x08U,  8U, OV5640_CSI_DT_RAW8 },
    /* RAW10 forces 10-bit mode, which moves bit_div from 2 to 2.5 and so
       changes PCLK for the same PLL. The clock computation handles it. */
    [OV5640_FORMAT_RAW10_BGGR] = {
        0x00U, 0x03U, 0x06U, 0x0AU, 10U, OV5640_CSI_DT_RAW10 },
};

/*============================================================================*/
/* Common initialisation table                                                */
/*============================================================================*/

/*
 * OmniVision's reference initialisation, trimmed to the MIPI case and
 * annotated. Three kinds of entry live in here:
 *
 *   1. Things you can look up in the datasheet - block resets, clock gates,
 *      ISP enables, AEC/AGC limits, BLC, MIPI control.
 *   2. ISP tuning - AWB (0x5180+), colour matrix (0x5381+), CIP (0x5300+),
 *      gamma (0x5480+), SDE (0x5580+), lens correction (0x5800+). These are
 *      OmniVision's reference values, tuned for a reference lens. A working
 *      starting point, not tuning for YOUR module.
 *   3. Registers the datasheet marks "Debug mode" - 0x3630, 0x3631, 0x3703,
 *      0x3715, 0x3731, 0x3905 and friends. Undocumented analog trim. Not
 *      optional, and they must not be changed.
 *
 * Timing, clocks, MIPI lane count, D-PHY timing and format are deliberately
 * NOT here: OV5640_SetResolution(), OV5640_ClockApply(), OV5640_SetLanes(),
 * OV5640_ApplyDphyTiming() and OV5640_SetFormat() own those.
 */
static const OV5640_RegVal_t ov5640_init_common[] =
{
    { 0x3103, 0x11 },   /* system input clock from pad, so we can talk pre-PLL */
    { 0x3008, 0x82 },   /* software reset                                      */
    { OV5640_REG_DELAY, 5 },
    { 0x3008, 0x42 },   /* software power down while we configure              */
    { 0x3103, 0x03 },   /* system input clock from PLL                         */

    /* --- pad direction. The DVP data pads stay inputs: in MIPI mode they are
           either MIPI differential pins or unconnected, and driving the
           unconnected ones wastes power for nothing. --------------------- */
    { 0x3017, 0x00 },
    { 0x3018, 0x00 },

    /* --- undocumented analog trim (datasheet: "Debug mode") -------------- */
    { 0x3630, 0x36 },
    { 0x3631, 0x0E },
    { 0x3632, 0xE2 },
    { 0x3633, 0x12 },
    { 0x3621, 0xE0 },
    { 0x3704, 0xA0 },
    { 0x3703, 0x5A },
    { 0x3715, 0x78 },
    { 0x3717, 0x01 },
    { 0x370B, 0x60 },
    { 0x3705, 0x1A },
    { 0x3905, 0x02 },
    { 0x3906, 0x10 },
    { 0x3901, 0x0A },
    { 0x3731, 0x12 },
    { 0x3600, 0x08 },   /* VCM control, safe idle value                        */
    { 0x3601, 0x33 },
    { 0x302D, 0x60 },
    { 0x3620, 0x52 },
    { 0x371B, 0x20 },
    { 0x471C, 0x50 },
    { 0x3635, 0x13 },
    { 0x3636, 0x03 },
    { 0x3634, 0x40 },
    { 0x3622, 0x01 },
    { 0x3618, 0x00 },
    { 0x3612, 0x29 },
    { 0x3708, 0x64 },
    { 0x3709, 0x52 },
    { 0x370C, 0x03 },

    /* --- AEC/AGC, datasheet 7.8 ------------------------------------------ */
    { 0x3A13, 0x43 },   /* AEC pre-gain 1.047x                                 */
    { 0x3A18, 0x00 },   /* gain ceiling [9:8]                                  */
    { 0x3A19, 0xF8 },   /* gain ceiling = 0x0F8 / 16 = 15.5x                   */
    { 0x3A0F, 0x30 },   /* stable range high                                   */
    { 0x3A10, 0x28 },   /* stable range low                                    */
    { 0x3A1B, 0x30 },   /* stable range high, wide                             */
    { 0x3A1E, 0x26 },   /* stable range low, wide                              */
    { 0x3A11, 0x60 },   /* fast zone high                                      */
    { 0x3A1F, 0x14 },   /* fast zone low                                       */

    /* --- 50/60 Hz flicker detector, datasheet 7.10 ----------------------- */
    { 0x3C01, 0x34 },   /* detector on, manual mode off                        */
    { 0x3C04, 0x28 },
    { 0x3C05, 0x98 },
    { 0x3C06, 0x00 },
    { 0x3C07, 0x08 },
    { 0x3C08, 0x00 },
    { 0x3C09, 0x1C },
    { 0x3C0A, 0x9C },
    { 0x3C0B, 0x40 },

    /* --- black level calibration, datasheet 4.7 -------------------------- */
    { 0x4001, 0x02 },   /* BLC start line 2                                    */
    { 0x4004, 0x02 },   /* BLC line count 2                                    */
    { 0x4005, 0x1A },   /* BLC always update                                   */

    /* --- release blocks from reset, enable clocks, datasheet 6.2 --------- */
    { 0x3000, 0x00 },
    { 0x3002, 0x1C },
    { 0x3004, 0xFF },
    { 0x3006, 0xC3 },

    /* --- MIPI transmitter, datasheet 7.19 --------------------------------
       0x4800 = 0x04: clock lane free running (bit[5]=0), no per-line short
       packets (bit[4]=0), idle state LP11 (bit[2]=1). Continuous clock is the
       safer default for bring-up - see NOTES.md section 5.               */
    { 0x4800, 0x04 },
    { 0x4801, 0x04 },   /* packet header order for ECC, reset value            */
    { 0x4805, 0x10 },   /* both lanes enabled, LPX timing auto                 */

    /* D-PHY global timing floors, 0x4818..0x4832. These defaults ARE the MIPI
       D-PHY specification minimums and are correct at any line rate the
       OV5640 can produce. Listed rather than skipped so a future reader can
       see they were considered, not forgotten. Only 0x4837 needs computing,
       and OV5640_ApplyDphyTiming() does that. */
    { 0x4818, 0x00 }, { 0x4819, 0x96 },   /* hs_zero     150 ns              */
    { 0x481A, 0x00 }, { 0x481B, 0x3C },   /* hs_trail     60 ns              */
    { 0x481C, 0x01 }, { 0x481D, 0x86 },   /* clk_zero    390 ns              */
    { 0x481E, 0x00 }, { 0x481F, 0x3C },   /* clk_prepare  60 ns              */
    { 0x4820, 0x00 }, { 0x4821, 0x56 },   /* clk_post     86 ns              */
    { 0x4822, 0x00 }, { 0x4823, 0x3C },   /* clk_trail    60 ns              */
    { 0x4824, 0x00 }, { 0x4825, 0x32 },   /* lpx_p        50 ns              */
    { 0x4826, 0x00 }, { 0x4827, 0x32 },   /* hs_prepare   50 ns              */
    { 0x4828, 0x00 }, { 0x4829, 0x64 },   /* hs_exit     100 ns              */
    { 0x482A, 0x05 },                     /* hs_zero       5 UI              */
    { 0x482B, 0x04 },                     /* hs_trail      4 UI              */
    { 0x482C, 0x00 },                     /* clk_zero      0 UI              */
    { 0x482D, 0x00 },                     /* clk_prepare   0 UI              */
    { 0x482E, 0x34 },                     /* clk_post     52 UI              */
    { 0x482F, 0x00 },                     /* clk_trail     0 UI              */
    { 0x4830, 0x00 },                     /* lpx_p         0 UI              */
    { 0x4831, 0x04 },                     /* hs_prepare    4 UI              */
    { 0x4832, 0x00 },                     /* hs_exit       0 UI              */

    /* --- ISP block enables, datasheet 7.21 ------------------------------- */
    { 0x5000, 0xA7 },   /* LENC, RAW gamma, black/white pixel cancel, demosaic */
    { 0x5001, 0xA3 },   /* SDE, scaler, UV average, colour matrix, AWB         */

    /* --- AWB reference tuning, datasheet 7.22 ---------------------------- */
    { 0x5180, 0xFF }, { 0x5181, 0xF2 }, { 0x5182, 0x00 }, { 0x5183, 0x14 },
    { 0x5184, 0x25 }, { 0x5185, 0x24 }, { 0x5186, 0x09 }, { 0x5187, 0x09 },
    { 0x5188, 0x09 }, { 0x5189, 0x75 }, { 0x518A, 0x54 }, { 0x518B, 0xE0 },
    { 0x518C, 0xB2 }, { 0x518D, 0x42 }, { 0x518E, 0x3D }, { 0x518F, 0x56 },
    { 0x5190, 0x46 }, { 0x5191, 0xF8 }, { 0x5192, 0x04 }, { 0x5193, 0x70 },
    { 0x5194, 0xF0 }, { 0x5195, 0xF0 }, { 0x5196, 0x03 }, { 0x5197, 0x01 },
    { 0x5198, 0x04 }, { 0x5199, 0x12 }, { 0x519A, 0x04 }, { 0x519B, 0x00 },
    { 0x519C, 0x06 }, { 0x519D, 0x82 }, { 0x519E, 0x38 },

    /* --- colour matrix, datasheet 7.24 ----------------------------------- */
    { 0x5381, 0x1E }, { 0x5382, 0x5B }, { 0x5383, 0x08 },
    { 0x5384, 0x0A }, { 0x5385, 0x7E }, { 0x5386, 0x88 },
    { 0x5387, 0x7C }, { 0x5388, 0x6C }, { 0x5389, 0x10 },
    { 0x538A, 0x01 }, { 0x538B, 0x98 },

    /* --- colour interpolation / sharpening, datasheet 7.23 --------------- */
    { 0x5300, 0x08 }, { 0x5301, 0x30 }, { 0x5302, 0x10 }, { 0x5303, 0x00 },
    { 0x5304, 0x08 }, { 0x5305, 0x30 }, { 0x5306, 0x08 }, { 0x5307, 0x16 },
    { 0x5309, 0x08 }, { 0x530A, 0x30 }, { 0x530B, 0x04 }, { 0x530C, 0x06 },

    /* --- gamma curve, datasheet 7.25 ------------------------------------- */
    { 0x5480, 0x01 },
    { 0x5481, 0x08 }, { 0x5482, 0x14 }, { 0x5483, 0x28 }, { 0x5484, 0x51 },
    { 0x5485, 0x65 }, { 0x5486, 0x71 }, { 0x5487, 0x7D }, { 0x5488, 0x87 },
    { 0x5489, 0x91 }, { 0x548A, 0x9A }, { 0x548B, 0xAA }, { 0x548C, 0xB8 },
    { 0x548D, 0xCD }, { 0x548E, 0xDD }, { 0x548F, 0xEA }, { 0x5490, 0x1D },

    /* --- special digital effects: neutral, datasheet 7.26 ---------------- */
    { 0x5580, 0x02 },   /* contrast path enabled, hue and saturation off       */
    { 0x5583, 0x40 },   /* saturation U                                        */
    { 0x5584, 0x10 },   /* saturation V                                        */
    { 0x5586, 0x20 },   /* Y gain, 0x20 = unity                                */
    { 0x5587, 0x00 },   /* Y bright                                            */
    { 0x5588, 0x00 },
    { 0x5589, 0x10 },   /* UV adjust threshold 1                               */
    { 0x558A, 0x00 },
    { 0x558B, 0xF8 },   /* UV adjust threshold 2                               */
    { 0x501D, 0x40 },

    /* --- lens correction, datasheet 7.29 --------------------------------- */
    { 0x5800, 0x23 }, { 0x5801, 0x14 }, { 0x5802, 0x0F }, { 0x5803, 0x0F },
    { 0x5804, 0x12 }, { 0x5805, 0x26 }, { 0x5806, 0x0C }, { 0x5807, 0x08 },
    { 0x5808, 0x05 }, { 0x5809, 0x05 }, { 0x580A, 0x08 }, { 0x580B, 0x0D },
    { 0x580C, 0x08 }, { 0x580D, 0x03 }, { 0x580E, 0x00 }, { 0x580F, 0x00 },
    { 0x5810, 0x03 }, { 0x5811, 0x09 }, { 0x5812, 0x07 }, { 0x5813, 0x03 },
    { 0x5814, 0x00 }, { 0x5815, 0x01 }, { 0x5816, 0x03 }, { 0x5817, 0x08 },
    { 0x5818, 0x0D }, { 0x5819, 0x08 }, { 0x581A, 0x05 }, { 0x581B, 0x06 },
    { 0x581C, 0x08 }, { 0x581D, 0x0E }, { 0x581E, 0x29 }, { 0x581F, 0x17 },
    { 0x5820, 0x11 }, { 0x5821, 0x11 }, { 0x5822, 0x15 }, { 0x5823, 0x28 },
    { 0x5824, 0x46 }, { 0x5825, 0x26 }, { 0x5826, 0x08 }, { 0x5827, 0x26 },
    { 0x5828, 0x64 }, { 0x5829, 0x26 }, { 0x582A, 0x24 }, { 0x582B, 0x22 },
    { 0x582C, 0x24 }, { 0x582D, 0x24 }, { 0x582E, 0x06 }, { 0x582F, 0x22 },
    { 0x5830, 0x40 }, { 0x5831, 0x42 }, { 0x5832, 0x24 }, { 0x5833, 0x26 },
    { 0x5834, 0x24 }, { 0x5835, 0x22 }, { 0x5836, 0x22 }, { 0x5837, 0x26 },
    { 0x5838, 0x44 }, { 0x5839, 0x24 }, { 0x583A, 0x26 }, { 0x583B, 0x28 },
    { 0x583C, 0x42 }, { 0x583D, 0xCE },

    { 0x3008, 0x02 },   /* leave software power down                           */
};

/*============================================================================*/
/* SCCB register access                                                       */
/*============================================================================*/

HAL_StatusTypeDef OV5640_WriteReg(OV5640_Ctx_t *ctx, uint16_t reg, uint8_t val)
{
    if ((ctx == NULL) || (ctx->hi2c == NULL))
    {
        return HAL_ERROR;
    }

    return HAL_I2C_Mem_Write(ctx->hi2c, ov5640_addr(ctx), reg,
                             I2C_MEMADD_SIZE_16BIT, &val, 1U,
                             OV5640_I2C_TIMEOUT_MS);
}

HAL_StatusTypeDef OV5640_ReadReg(OV5640_Ctx_t *ctx, uint16_t reg, uint8_t *val)
{
    if ((ctx == NULL) || (ctx->hi2c == NULL) || (val == NULL))
    {
        return HAL_ERROR;
    }

    return HAL_I2C_Mem_Read(ctx->hi2c, ov5640_addr(ctx), reg,
                            I2C_MEMADD_SIZE_16BIT, val, 1U,
                            OV5640_I2C_TIMEOUT_MS);
}

HAL_StatusTypeDef OV5640_ModifyReg(OV5640_Ctx_t *ctx, uint16_t reg,
                                   uint8_t mask, uint8_t val)
{
    uint8_t           cur;
    HAL_StatusTypeDef st = OV5640_ReadReg(ctx, reg, &cur);

    if (st != HAL_OK)
    {
        return st;
    }

    cur = (uint8_t)((cur & (uint8_t)~mask) | (val & mask));

    return OV5640_WriteReg(ctx, reg, cur);
}

HAL_StatusTypeDef OV5640_WriteReg16(OV5640_Ctx_t *ctx, uint16_t reg_h, uint16_t val)
{
    HAL_StatusTypeDef st = OV5640_WriteReg(ctx, reg_h, (uint8_t)(val >> 8));

    if (st != HAL_OK)
    {
        return st;
    }

    return OV5640_WriteReg(ctx, (uint16_t)(reg_h + 1U), (uint8_t)(val & 0xFFU));
}

HAL_StatusTypeDef OV5640_ReadReg16(OV5640_Ctx_t *ctx, uint16_t reg_h, uint16_t *val)
{
    uint8_t           hi;
    uint8_t           lo;
    HAL_StatusTypeDef st;

    if (val == NULL)
    {
        return HAL_ERROR;
    }

    st = OV5640_ReadReg(ctx, reg_h, &hi);
    if (st != HAL_OK)
    {
        return st;
    }

    st = OV5640_ReadReg(ctx, (uint16_t)(reg_h + 1U), &lo);
    if (st != HAL_OK)
    {
        return st;
    }

    *val = (uint16_t)(((uint16_t)hi << 8) | lo);

    return HAL_OK;
}

/** @brief Play a register script, honouring OV5640_REG_DELAY entries. */
static HAL_StatusTypeDef ov5640_write_list(OV5640_Ctx_t *ctx,
                                           const OV5640_RegVal_t *list,
                                           uint32_t count)
{
    for (uint32_t i = 0U; i < count; i++)
    {
        if (list[i].reg == OV5640_REG_DELAY)
        {
            HAL_Delay(list[i].val);
        }
        else
        {
            HAL_StatusTypeDef st = OV5640_WriteReg(ctx, list[i].reg, list[i].val);

            if (st != HAL_OK)
            {
                return st;
            }
        }
    }

    return HAL_OK;
}

/*============================================================================*/
/* Clocking                                                                   */
/*============================================================================*/

/**
  * @brief  Fill in the clock terms that never vary by mode.
  *
  * root_div is always 2 and bit_mode comes from the format. sclk_root_div is
  * the one-lane knob: see the ratio argument in README section 3 - a one-lane
  * shortfall cannot be fixed by retuning the PLL, because VCO cancels out of
  * (available / required). Halving PCLK here is what makes one lane work, at
  * half the frame rate.
  */
static void ov5640_clock_defaults(OV5640_Clock_t *clk, uint8_t bit_mode,
                                  OV5640_Lanes_t lanes)
{
    clk->root_div      = 2U;
    clk->bit_mode      = bit_mode;
    clk->sclk_root_div = (lanes == OV5640_LANES_2) ? 2U : 4U;
}

HAL_StatusTypeDef OV5640_ClockCompute(uint32_t xvclk_hz, OV5640_Clock_t *clk,
                                      uint8_t bpp, OV5640_Lanes_t lanes)
{
    uint64_t vco;
    uint64_t pclk;
    uint64_t serclk_max;
    uint32_t twice_bit_div;   /* 2 x bit_div, so /2.5 stays integer */
    uint32_t num_lanes = (lanes == OV5640_LANES_1) ? 1U : 2U;
    uint32_t mipi_div;

    if ((clk == NULL) || (bpp == 0U) ||
        (clk->pre_div == 0U) || (clk->mult == 0U) ||
        (clk->root_div == 0U) || (clk->sys_div == 0U) ||
        (clk->sclk_root_div == 0U))
    {
        return HAL_ERROR;
    }

    /* Datasheet 7.1: pre-divider is one of 1, 2, 3, 4, 6, 8. */
    if ((clk->pre_div > 8U) || (clk->pre_div == 5U) || (clk->pre_div == 7U))
    {
        return HAL_ERROR;
    }

    /* Datasheet 7.1: multiplier 4..127 free, 128..252 even only. */
    if ((clk->mult < 4U) || ((clk->mult > 127U) && ((clk->mult & 1U) != 0U)))
    {
        return HAL_ERROR;
    }

    switch (clk->bit_mode)
    {
        case 0x08U: twice_bit_div = 4U; break;   /* 8-bit mode  -> /2   */
        case 0x0AU: twice_bit_div = 5U; break;   /* 10-bit mode -> /2.5 */
        default:    return HAL_ERROR;
    }

    vco = ((uint64_t)xvclk_hz * clk->mult) / clk->pre_div;

    if (vco > (uint64_t)OV5640_VCO_MAX_HZ)
    {
        return HAL_ERROR;
    }

    /* PCLK = VCO / sys_div / root_div / bit_div / sclk_root_div,
       rearranged so the /2.5 is exact. */
    pclk = (vco * 2U) / twice_bit_div;
    pclk /= clk->sys_div;
    pclk /= clk->root_div;
    pclk /= clk->sclk_root_div;

    if (pclk == 0U)
    {
        return HAL_ERROR;
    }

    /* The CSI-2 bandwidth constraint. The transmitter serialises pixels as
       they leave the pipeline, at the pixel clock, so this is a PEAK rate -
       VTS and frame rate do not appear, and lowering the frame rate does not
       relax it. Only lowering PCLK does. */
    clk->required_bps = (uint32_t)((pclk * bpp) / num_lanes);

    /* Available at mipi_div = 1, then divided down to the smallest setting
       that still carries the requirement. */
    serclk_max = (vco * 2U) / clk->sys_div / clk->root_div;

    mipi_div = (clk->required_bps != 0U)
                   ? (uint32_t)(serclk_max / clk->required_bps)
                   : 1U;

    if (mipi_div < 1U)  { mipi_div = 1U;  }
    if (mipi_div > 15U) { mipi_div = 15U; }   /* 0x3035[3:0] is 4 bits */

    clk->mipi_div      = (uint8_t)mipi_div;
    clk->vco_hz        = (uint32_t)vco;
    clk->pclk_hz       = (uint32_t)pclk;
    clk->lane_rate_bps = (uint32_t)(serclk_max / mipi_div);

    /* The check worth having: this turns "the image is torn and I don't know
       why" into a return code at init. */
    if (clk->lane_rate_bps < clk->required_bps)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/** @brief Encode 0x3108[1:0]: 1 -> 00, 2 -> 01, 4 -> 10, 8 -> 11. */
static uint8_t ov5640_root_code(uint8_t div)
{
    switch (div)
    {
        case 1U:  return 0U;
        case 2U:  return 1U;
        case 4U:  return 2U;
        case 8U:  return 3U;
        default:  return 1U;
    }
}

HAL_StatusTypeDef OV5640_ClockApply(OV5640_Ctx_t *ctx, const OV5640_Clock_t *clk)
{
    HAL_StatusTypeDef st;
    uint8_t           v;

    if ((ctx == NULL) || (clk == NULL) || (clk->pclk_hz == 0U))
    {
        return HAL_ERROR;   /* not computed, or computed and rejected */
    }

    /* 0x3034: [6:4] charge pump = 1, [3:0] MIPI bit mode. */
    st = OV5640_WriteReg(ctx, OV5640_SC_PLL_CTRL0,
                         (uint8_t)(0x10U | (clk->bit_mode & 0x0FU)));
    if (st != HAL_OK) { return st; }

    /* 0x3035: [7:4] system divider, [3:0] MIPI scale divider. */
    v = (uint8_t)(((clk->sys_div & 0x0FU) << 4) | (clk->mipi_div & 0x0FU));
    st = OV5640_WriteReg(ctx, OV5640_SC_PLL_CTRL1, v);
    if (st != HAL_OK) { return st; }

    /* 0x3036: PLL multiplier. */
    st = OV5640_WriteReg(ctx, OV5640_SC_PLL_CTRL2, clk->mult);
    if (st != HAL_OK) { return st; }

    /* 0x3037: [4] root divider (0 = /1, 1 = /2), [3:0] pre-divider. */
    v = (uint8_t)(((clk->root_div == 2U) ? 0x10U : 0x00U) | (clk->pre_div & 0x0FU));
    st = OV5640_WriteReg(ctx, OV5640_SC_PLL_CTRL3, v);
    if (st != HAL_OK) { return st; }

    /* 0x3108: [5:4] PCLK root (DVP only, leave /1), [3:2] SCLK2x root /1,
                [1:0] SCLK root divider - the one-lane knob. */
    v = (uint8_t)(ov5640_root_code(clk->sclk_root_div) & 0x03U);
    st = OV5640_WriteReg(ctx, OV5640_SYSTEM_ROOT_DIVIDER, v);
    if (st != HAL_OK) { return st; }

    ctx->clock = *clk;

    /* The D-PHY global timing follows from the lane rate, so recompute it here
       rather than leaving it to the caller to remember. */
    return OV5640_ApplyDphyTiming(ctx);
}

uint32_t OV5640_GetPclk(const OV5640_Ctx_t *ctx)
{
    return (ctx != NULL) ? ctx->clock.pclk_hz : 0U;
}

uint32_t OV5640_GetLaneRate(const OV5640_Ctx_t *ctx)
{
    return (ctx != NULL) ? ctx->clock.lane_rate_bps : 0U;
}

HAL_StatusTypeDef OV5640_GetTiming(OV5640_Ctx_t *ctx, OV5640_Timing_t *t)
{
    OV5640_Timing_t   tmp;
    HAL_StatusTypeDef st;

    st = OV5640_ReadReg16(ctx, OV5640_TIMING_HTS_H, &tmp.hts);
    if (st != HAL_OK) { return st; }

    st = OV5640_ReadReg16(ctx, OV5640_TIMING_VTS_H, &tmp.vts);
    if (st != HAL_OK) { return st; }

    st = OV5640_ReadReg16(ctx, OV5640_TIMING_DVPHO_H, &tmp.width);
    if (st != HAL_OK) { return st; }

    st = OV5640_ReadReg16(ctx, OV5640_TIMING_DVPVO_H, &tmp.height);
    if (st != HAL_OK) { return st; }

    /* Both high bytes carry debug bits above the field. Datasheet 7.7. */
    tmp.hts    &= 0x1FFFU;
    tmp.width  &= 0x0FFFU;
    tmp.height &= 0x07FFU;

    ctx->timing = tmp;

    if (t != NULL)
    {
        *t = tmp;
    }

    return HAL_OK;
}

uint32_t OV5640_GetFrameRate_mfps(OV5640_Ctx_t *ctx)
{
    OV5640_Timing_t t;
    uint64_t        denom;

    if ((ctx == NULL) || (ctx->clock.pclk_hz == 0U))
    {
        return 0U;
    }

    if (OV5640_GetTiming(ctx, &t) != HAL_OK)
    {
        return 0U;
    }

    denom = (uint64_t)t.hts * t.vts;
    if (denom == 0U)
    {
        return 0U;
    }

    return (uint32_t)(((uint64_t)ctx->clock.pclk_hz * 1000U) / denom);
}

HAL_StatusTypeDef OV5640_SetFrameRate(OV5640_Ctx_t *ctx, uint32_t fps)
{
    OV5640_Timing_t t;
    uint32_t        vts;
    uint16_t        vts_min;

    if ((ctx == NULL) || (fps == 0U) || (ctx->clock.pclk_hz == 0U))
    {
        return HAL_ERROR;
    }

    if (OV5640_GetTiming(ctx, &t) != HAL_OK)
    {
        return HAL_ERROR;
    }
    if (t.hts == 0U)
    {
        return HAL_ERROR;
    }

    /* Stretching VTS adds blank lines: the frame period grows while PCLK and
       line timing stay put. Note this does NOT change the lane rate the link
       needs - see OV5640_ClockCompute(). */
    vts = ctx->clock.pclk_hz / ((uint32_t)t.hts * fps);

    /* Never go below the mode's native VTS: the readout cannot finish sooner
       than it physically can. */
    vts_min = (ctx->resolution < OV5640_RES_COUNT)
                  ? ov5640_modes[ctx->resolution].vts
                  : t.vts;

    if (vts < vts_min)  { vts = vts_min;  }
    if (vts > 0xFFFFU)  { vts = 0xFFFFU;  }

    return OV5640_WriteReg16(ctx, OV5640_TIMING_VTS_H, (uint16_t)vts);
}

/*============================================================================*/
/* MIPI CSI-2 configuration                                                   */
/*============================================================================*/

HAL_StatusTypeDef OV5640_SetLanes(OV5640_Ctx_t *ctx, OV5640_Lanes_t lanes)
{
    uint8_t v;

    if (ctx == NULL)
    {
        return HAL_ERROR;
    }

    /* Built from the documented 0x300E fields (datasheet 7.1):
         [7:5] lane mode: 000 one lane, 001 two lane
         [4]   MIPI TX PHY power down - 0, we need it alive
         [3]   MIPI RX PHY power down - 0
         [2]   mipi_en = 1
       If the receiver never sees the lanes leave LP-11, write
       OV5640_MIPI_CTRL00_STREAM_ON instead. See README section 0. */
    v = (uint8_t)(((lanes == OV5640_LANES_2) ? 0x20U : 0x00U) | 0x04U);

    ctx->lanes = lanes;

    return OV5640_WriteReg(ctx, OV5640_IO_MIPI_CTRL00, v);
}

HAL_StatusTypeDef OV5640_SetClockLaneMode(OV5640_Ctx_t *ctx, bool continuous)
{
    /* 0x4800[5]: 0 = clock lane free running, 1 = gate when idle. */
    return OV5640_ModifyReg(ctx, OV5640_MIPI_CTRL00, 0x20U,
                            continuous ? 0x00U : 0x20U);
}

HAL_StatusTypeDef OV5640_ApplyDphyTiming(OV5640_Ctx_t *ctx)
{
    uint32_t serclk_mhz;
    uint32_t period;

    if ((ctx == NULL) || (ctx->clock.lane_rate_bps == 0U))
    {
        return HAL_ERROR;
    }

    /* 0x4837 is the SERCLK period in HALF-nanosecond units ("1-bit decimal",
       datasheet 7.19), and it is how the sensor converts the nanosecond floors
       in 0x4818..0x4832 into internal cycles:

           0x4837 = round(2000 / SERCLK_MHz)

       SERCLK is half the lane rate because the link is DDR. Get this wrong and
       the ns floors are met at the wrong scale: the link still runs and packets
       still arrive, but the receiver logs SoT or ECC errors. */
    serclk_mhz = (ctx->clock.lane_rate_bps / 2U) / 1000000U;

    if (serclk_mhz == 0U)
    {
        return HAL_ERROR;
    }

    period = (2000U + (serclk_mhz / 2U)) / serclk_mhz;    /* rounded */

    if (period == 0U)   { period = 1U;    }
    if (period > 0xFFU) { period = 0xFFU; }

    return OV5640_WriteReg(ctx, OV5640_MIPI_PCLK_PERIOD, (uint8_t)period);
}

uint8_t OV5640_GetCsiDataType(OV5640_Format_t fmt)
{
    return (fmt < OV5640_FORMAT_COUNT) ? ov5640_formats[fmt].csi_data_type : 0U;
}

HAL_StatusTypeDef OV5640_SetStreaming(OV5640_Ctx_t *ctx, bool on)
{
    HAL_StatusTypeDef st;

    if (ctx == NULL)
    {
        return HAL_ERROR;
    }

    if (on)
    {
        /* Re-assert the MIPI configuration, then leave software power down. */
        st = OV5640_SetLanes(ctx, ov5640_lanes(ctx));
        if (st != HAL_OK) { return st; }

        st = OV5640_WriteReg(ctx, OV5640_SYSTEM_CTRL0, 0x02U);
    }
    else
    {
        /* Software power down first, then park the PHY. */
        st = OV5640_WriteReg(ctx, OV5640_SYSTEM_CTRL0, 0x42U);
        if (st != HAL_OK) { return st; }

        st = OV5640_WriteReg(ctx, OV5640_IO_MIPI_CTRL00,
                             OV5640_MIPI_CTRL00_STREAM_OFF);
    }

    if (st == HAL_OK)
    {
        ctx->streaming = on;
    }

    return st;
}

/*============================================================================*/
/* Lifecycle                                                                  */
/*============================================================================*/

void OV5640_HwReset(OV5640_Ctx_t *ctx)
{
    /* Datasheet 2.7 / 2.8. Assumes the supplies and XVCLK are already up:
       t2 (AVDD stable to PWDN low) is the board's job, not ours. */

    if (ctx->pwdn_port != NULL)
    {
        HAL_GPIO_WritePin(ctx->pwdn_port, ctx->pwdn_pin, GPIO_PIN_SET);
    }

    if (ctx->reset_port != NULL)
    {
        HAL_GPIO_WritePin(ctx->reset_port, ctx->reset_pin, GPIO_PIN_RESET);
    }

    HAL_Delay(5U);      /* PWDN high and RESETB low together                   */

    if (ctx->pwdn_port != NULL)
    {
        HAL_GPIO_WritePin(ctx->pwdn_port, ctx->pwdn_pin, GPIO_PIN_RESET);
    }

    HAL_Delay(5U);      /* t3 >= 1 ms, with margin                             */

    if (ctx->reset_port != NULL)
    {
        HAL_GPIO_WritePin(ctx->reset_port, ctx->reset_pin, GPIO_PIN_SET);
    }

    HAL_Delay(25U);     /* t4 >= 20 ms before the first SCCB access            */
}

void OV5640_HwPowerDown(OV5640_Ctx_t *ctx, bool down)
{
    if (ctx->pwdn_port != NULL)
    {
        HAL_GPIO_WritePin(ctx->pwdn_port, ctx->pwdn_pin,
                          down ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

HAL_StatusTypeDef OV5640_SwPowerDown(OV5640_Ctx_t *ctx, bool down)
{
    /* 0x3008[6]. Register content survives; the clock keeps running. */
    return OV5640_ModifyReg(ctx, OV5640_SYSTEM_CTRL0, 0x40U, down ? 0x40U : 0x00U);
}

HAL_StatusTypeDef OV5640_SwReset(OV5640_Ctx_t *ctx)
{
    HAL_StatusTypeDef st = OV5640_WriteReg(ctx, OV5640_SYSTEM_CTRL0, 0x82U);

    if (st != HAL_OK)
    {
        return st;
    }

    HAL_Delay(5U);      /* settling time for software reset < 1 ms, 8.4        */

    return HAL_OK;
}

HAL_StatusTypeDef OV5640_ReadID(OV5640_Ctx_t *ctx, uint16_t *id)
{
    return OV5640_ReadReg16(ctx, OV5640_CHIP_ID_HIGH, id);
}

HAL_StatusTypeDef OV5640_Init(OV5640_Ctx_t *ctx,
                              OV5640_Resolution_t res,
                              OV5640_Format_t fmt)
{
    HAL_StatusTypeDef st;
    uint16_t          id = 0U;

    if ((ctx == NULL) || (ctx->hi2c == NULL) ||
        (res >= OV5640_RES_COUNT) || (fmt >= OV5640_FORMAT_COUNT))
    {
        return HAL_ERROR;
    }

    ctx->lanes     = ov5640_lanes(ctx);
    ctx->streaming = false;

    OV5640_HwReset(ctx);

    /* Step 4 of the bring-up order: nothing downstream is meaningful until
       this passes. See README section 10. */
    st = OV5640_ReadID(ctx, &id);
    if (st != HAL_OK)
    {
        return st;
    }
    if (id != OV5640_CHIP_ID)
    {
        return HAL_ERROR;
    }

    st = ov5640_write_list(ctx, ov5640_init_common,
                           sizeof(ov5640_init_common) / sizeof(ov5640_init_common[0]));
    if (st != HAL_OK)
    {
        return st;
    }

    /* MIPI first: lane count and clock lane mode before anything starts. */
    st = OV5640_SetLanes(ctx, ctx->lanes);
    if (st != HAL_OK) { return st; }

    st = OV5640_SetClockLaneMode(ctx, true);   /* continuous, safer to bring up */
    if (st != HAL_OK) { return st; }

    /* Format before resolution: it sets bits-per-pixel and bit_mode, both of
       which the resolution's clock computation needs. */
    ctx->format = fmt;

    st = OV5640_SetResolution(ctx, res);
    if (st != HAL_OK) { return st; }         /* includes the lane budget check */

    st = OV5640_SetFormat(ctx, fmt);
    if (st != HAL_OK) { return st; }

    st = OV5640_SetBandingFilter(ctx, OV5640_BANDING_AUTO);
    if (st != HAL_OK) { return st; }

    /* Settling time for a register setting can be up to 300 ms (8.4, table
       8-4). Discard the first frames after streaming starts. */
    HAL_Delay(300U);

    /* Deliberately NOT streaming: bring the receiver up, check the lanes are
       at LP-11, then call OV5640_SetStreaming(ctx, true). */
    return HAL_OK;
}

/*============================================================================*/
/* Format, resolution, orientation                                            */
/*============================================================================*/

/**
  * @brief  Recompute and apply the clock tree for the current mode and format.
  *
  * Both a resolution change and a format change can invalidate the clocks -
  * resolution because the PLL multiplier differs, format because bits per pixel
  * and bit_div do - so both funnel through here.
  */
static HAL_StatusTypeDef ov5640_refresh_clocks(OV5640_Ctx_t *ctx)
{
    const OV5640_Mode_t      *m;
    const OV5640_FormatCfg_t *f;
    OV5640_Clock_t            clk = {0};
    HAL_StatusTypeDef         st;

    if ((ctx->resolution >= OV5640_RES_COUNT) || (ctx->format >= OV5640_FORMAT_COUNT))
    {
        return HAL_ERROR;
    }

    m = &ov5640_modes[ctx->resolution];
    f = &ov5640_formats[ctx->format];

    clk.pre_div = m->pll_pre;
    clk.mult    = m->pll_mult;
    clk.sys_div = m->sys_div;
    ov5640_clock_defaults(&clk, f->bit_mode, ov5640_lanes(ctx));

    st = OV5640_ClockCompute(ov5640_xvclk(ctx), &clk,
                             f->bits_per_pixel, ov5640_lanes(ctx));
    if (st != HAL_OK)
    {
        return st;      /* illegal PLL, or the lane budget cannot carry it */
    }

    return OV5640_ClockApply(ctx, &clk);
}

HAL_StatusTypeDef OV5640_SetFormat(OV5640_Ctx_t *ctx, OV5640_Format_t fmt)
{
    const OV5640_FormatCfg_t *cfg;
    OV5640_Format_t           previous;
    HAL_StatusTypeDef         st;

    if ((ctx == NULL) || (fmt >= OV5640_FORMAT_COUNT))
    {
        return HAL_ERROR;
    }

    cfg      = &ov5640_formats[fmt];
    previous = ctx->format;
    ctx->format = fmt;

    /* Do the arithmetic before touching the sensor, so a format that will not
       fit the lane budget leaves the current configuration alone. */
    st = ov5640_refresh_clocks(ctx);
    if (st != HAL_OK)
    {
        ctx->format = previous;
        return st;
    }

    st = OV5640_WriteReg(ctx, OV5640_FORMAT_CTRL00, cfg->format_ctrl00);
    if (st != HAL_OK) { return st; }

    /* 0x501F must agree with 0x4300 or you get well-formed nonsense: correct
       packet sizes, correct frame timing, wrong pixels. */
    st = OV5640_WriteReg(ctx, OV5640_ISP_FORMAT_MUX_CTRL, cfg->format_mux);
    if (st != HAL_OK) { return st; }

    /* RAW needs demosaic and RAW gamma off; everything else wants them on. */
    return OV5640_WriteReg(ctx, OV5640_ISP_CONTROL00, cfg->isp_control00);
}

HAL_StatusTypeDef OV5640_SetResolution(OV5640_Ctx_t *ctx, OV5640_Resolution_t res)
{
    const OV5640_Mode_t *m;
    OV5640_Resolution_t  previous;
    HAL_StatusTypeDef    st;

    if ((ctx == NULL) || (res >= OV5640_RES_COUNT))
    {
        return HAL_ERROR;
    }

    m        = &ov5640_modes[res];
    previous = ctx->resolution;
    ctx->resolution = res;

    st = ov5640_refresh_clocks(ctx);
    if (st != HAL_OK)
    {
        ctx->resolution = previous;
        return st;
    }

    /* Sensor window - the crop out of the physical array. Datasheet 4.2. */
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_HS_H, m->x_start);
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_VS_H, m->y_start);
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_HW_H, m->x_end);
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_VH_H, m->y_end);
    if (st != HAL_OK) { return st; }

    /* Output size, after the scaler. */
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_DVPHO_H, m->width);
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_DVPVO_H, m->height);
    if (st != HAL_OK) { return st; }

    /* Line and frame period, in pixel periods. */
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_HTS_H, m->hts);
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_VTS_H, m->vts);
    if (st != HAL_OK) { return st; }

    /* Offsets into the ISP input, which set the pre-scaling size. */
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_HOFFSET_H, m->x_offset);
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg16(ctx, OV5640_TIMING_VOFFSET_H, m->y_offset);
    if (st != HAL_OK) { return st; }

    /* Subsample increments, {odd[7:4], even[3:0]}. 0x11 full, 0x31 = 2x. */
    st = OV5640_WriteReg(ctx, OV5640_TIMING_X_INC, m->x_inc);
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg(ctx, OV5640_TIMING_Y_INC, m->y_inc);
    if (st != HAL_OK) { return st; }

    /* Horizontal binning, 0x3821[0], and the ISP binning enable, 0x5003[2]. */
    st = OV5640_ModifyReg(ctx, OV5640_TIMING_TC_REG21, 0x01U,
                          m->binning ? 0x01U : 0x00U);
    if (st != HAL_OK) { return st; }
    st = OV5640_ModifyReg(ctx, OV5640_ISP_CONTROL03, 0x04U,
                          m->binning ? 0x04U : 0x00U);
    if (st != HAL_OK) { return st; }

    /* ISP scaler, 0x5001[5]. */
    st = OV5640_ModifyReg(ctx, OV5640_ISP_CONTROL01, 0x20U,
                          m->scaler ? 0x20U : 0x00U);
    if (st != HAL_OK) { return st; }

    /* Refresh the cached timing from what the sensor actually holds, so the
       exposure and banding maths work off real values. */
    (void)OV5640_GetTiming(ctx, NULL);

    HAL_Delay(10U);

    return HAL_OK;
}

HAL_StatusTypeDef OV5640_SetMirrorFlip(OV5640_Ctx_t *ctx, bool mirror, bool flip)
{
    HAL_StatusTypeDef st;

    /* 0x3820[2] ISP vflip, [1] sensor vflip. Datasheet 7.7.
       Both must move together or the Bayer phase shifts and the colours come
       out wrong on alternate rows. */
    st = OV5640_ModifyReg(ctx, OV5640_TIMING_TC_REG20, 0x06U,
                          flip ? 0x06U : 0x00U);
    if (st != HAL_OK)
    {
        return st;
    }

    /* 0x3821[2] ISP mirror, [1] sensor mirror. */
    return OV5640_ModifyReg(ctx, OV5640_TIMING_TC_REG21, 0x06U,
                            mirror ? 0x06U : 0x00U);
}

void OV5640_GetResolutionSize(OV5640_Resolution_t res, uint16_t *w, uint16_t *h)
{
    if (res >= OV5640_RES_COUNT)
    {
        if (w != NULL) { *w = 0U; }
        if (h != NULL) { *h = 0U; }
        return;
    }

    if (w != NULL) { *w = ov5640_modes[res].width;  }
    if (h != NULL) { *h = ov5640_modes[res].height; }
}

uint8_t OV5640_GetBitsPerPixel(OV5640_Format_t fmt)
{
    return (fmt < OV5640_FORMAT_COUNT) ? ov5640_formats[fmt].bits_per_pixel : 0U;
}

uint32_t OV5640_GetFrameSize(OV5640_Resolution_t res, OV5640_Format_t fmt)
{
    uint16_t w;
    uint16_t h;
    uint8_t  bpp = OV5640_GetBitsPerPixel(fmt);

    if (bpp == 0U)
    {
        return 0U;
    }

    OV5640_GetResolutionSize(res, &w, &h);

    /* Packed: RAW10 is 10 bits per pixel on the wire, so round up to bytes. */
    return (((uint32_t)w * (uint32_t)h * (uint32_t)bpp) + 7U) / 8U;
}

/*============================================================================*/
/* Exposure, gain, white balance                                              */
/*============================================================================*/

HAL_StatusTypeDef OV5640_SetAutoExposure(OV5640_Ctx_t *ctx, bool enable)
{
    /* 0x3503[0]: 0 = auto, 1 = manual. Datasheet 7.5. */
    return OV5640_ModifyReg(ctx, OV5640_AEC_PK_MANUAL, 0x01U,
                            enable ? 0x00U : 0x01U);
}

HAL_StatusTypeDef OV5640_SetAutoGain(OV5640_Ctx_t *ctx, bool enable)
{
    /* 0x3503[1]: 0 = auto, 1 = manual. */
    return OV5640_ModifyReg(ctx, OV5640_AEC_PK_MANUAL, 0x02U,
                            enable ? 0x00U : 0x02U);
}

HAL_StatusTypeDef OV5640_SetAutoWhiteBalance(OV5640_Ctx_t *ctx, bool enable)
{
    HAL_StatusTypeDef st;

    /* 0x5001[0] is the AWB block; 0x3406[0] switches its gains to manual. */
    st = OV5640_ModifyReg(ctx, OV5640_ISP_CONTROL01, 0x01U,
                          enable ? 0x01U : 0x00U);
    if (st != HAL_OK)
    {
        return st;
    }

    return OV5640_ModifyReg(ctx, OV5640_AWB_MANUAL_CTRL, 0x01U,
                            enable ? 0x00U : 0x01U);
}

HAL_StatusTypeDef OV5640_SetExposureLines(OV5640_Ctx_t *ctx, uint32_t lines)
{
    HAL_StatusTypeDef st;
    OV5640_Timing_t   t;
    uint16_t          extra_vts = 0U;
    uint32_t          max_lines;
    uint32_t          reg;

    if (ctx == NULL)
    {
        return HAL_ERROR;
    }

    st = OV5640_GetTiming(ctx, &t);
    if (st != HAL_OK) { return st; }

    st = OV5640_ReadReg16(ctx, OV5640_AEC_PK_VTS_H, &extra_vts);
    if (st != HAL_OK) { return st; }

    /* Datasheet 4.6.2: exposure must stay under {0x380E,0x380F} +
       {0x350C,0x350D}, in lines. Four lines of margin. */
    max_lines = (uint32_t)t.vts + (uint32_t)extra_vts;
    max_lines = (max_lines > 4U) ? (max_lines - 4U) : 1U;

    if (lines == 0U)         { lines = 1U;         }
    if (lines > max_lines)   { lines = max_lines;  }

    st = OV5640_SetAutoExposure(ctx, false);
    if (st != HAL_OK) { return st; }

    /* Units are 1/16 line, and 0x3502[3:0] must be zero: the OV5640 does not
       do fractional-line exposure. Datasheet 7.5. */
    reg = lines << 4;
    if (reg > 0x000FFFFFU)
    {
        reg = 0x000FFFF0U;
    }

    st = OV5640_WriteReg(ctx, OV5640_AEC_EXPOSURE_H,
                         (uint8_t)((reg >> 16) & 0x0FU));
    if (st != HAL_OK) { return st; }

    st = OV5640_WriteReg(ctx, OV5640_AEC_EXPOSURE_M,
                         (uint8_t)((reg >> 8) & 0xFFU));
    if (st != HAL_OK) { return st; }

    return OV5640_WriteReg(ctx, OV5640_AEC_EXPOSURE_L,
                           (uint8_t)(reg & 0xF0U));
}

HAL_StatusTypeDef OV5640_SetExposureUs(OV5640_Ctx_t *ctx, uint32_t us)
{
    OV5640_Timing_t   t;
    HAL_StatusTypeDef st;
    uint64_t          lines;

    if ((ctx == NULL) || (ctx->clock.pclk_hz == 0U))
    {
        return HAL_ERROR;
    }

    st = OV5640_GetTiming(ctx, &t);
    if (st != HAL_OK) { return st; }
    if (t.hts == 0U)  { return HAL_ERROR; }

    /* t_row = HTS / PCLK, so lines = us * PCLK / (HTS * 1e6). */
    lines = ((uint64_t)us * ctx->clock.pclk_hz) / ((uint64_t)t.hts * 1000000U);

    return OV5640_SetExposureLines(ctx, (uint32_t)lines);
}

HAL_StatusTypeDef OV5640_GetExposureLines(OV5640_Ctx_t *ctx, uint32_t *lines)
{
    uint8_t           h;
    uint8_t           m;
    uint8_t           l;
    HAL_StatusTypeDef st;

    if (lines == NULL)
    {
        return HAL_ERROR;
    }

    st = OV5640_ReadReg(ctx, OV5640_AEC_EXPOSURE_H, &h);
    if (st != HAL_OK) { return st; }
    st = OV5640_ReadReg(ctx, OV5640_AEC_EXPOSURE_M, &m);
    if (st != HAL_OK) { return st; }
    st = OV5640_ReadReg(ctx, OV5640_AEC_EXPOSURE_L, &l);
    if (st != HAL_OK) { return st; }

    *lines = ((((uint32_t)(h & 0x0FU) << 16) |
               ((uint32_t)m << 8) |
                (uint32_t)l) >> 4);

    return HAL_OK;
}

HAL_StatusTypeDef OV5640_SetGain(OV5640_Ctx_t *ctx, uint16_t gain_x16)
{
    HAL_StatusTypeDef st;

    if (gain_x16 < 16U)     { gain_x16 = 16U;   }   /* 1x minimum  */
    if (gain_x16 > 1023U)   { gain_x16 = 1023U; }   /* 64x maximum */

    st = OV5640_SetAutoGain(ctx, false);
    if (st != HAL_OK) { return st; }

    st = OV5640_WriteReg(ctx, OV5640_AEC_PK_REAL_GAIN_H,
                         (uint8_t)((gain_x16 >> 8) & 0x03U));
    if (st != HAL_OK) { return st; }

    return OV5640_WriteReg(ctx, OV5640_AEC_PK_REAL_GAIN_L,
                           (uint8_t)(gain_x16 & 0xFFU));
}

HAL_StatusTypeDef OV5640_GetGain(OV5640_Ctx_t *ctx, uint16_t *gain_x16)
{
    HAL_StatusTypeDef st;
    uint16_t          raw;

    if (gain_x16 == NULL)
    {
        return HAL_ERROR;
    }

    st = OV5640_ReadReg16(ctx, OV5640_AEC_PK_REAL_GAIN_H, &raw);
    if (st != HAL_OK) { return st; }

    *gain_x16 = (uint16_t)(raw & 0x03FFU);

    return HAL_OK;
}

HAL_StatusTypeDef OV5640_SetGainCeiling(OV5640_Ctx_t *ctx, uint16_t gain_x16)
{
    HAL_StatusTypeDef st;

    if (gain_x16 < 16U)     { gain_x16 = 16U;   }
    if (gain_x16 > 1023U)   { gain_x16 = 1023U; }

    /* {0x3A18[1:0], 0x3A19}. Datasheet 4.6.3.4. */
    st = OV5640_WriteReg(ctx, OV5640_AEC_GAIN_CEILING_H,
                         (uint8_t)((gain_x16 >> 8) & 0x03U));
    if (st != HAL_OK) { return st; }

    return OV5640_WriteReg(ctx, OV5640_AEC_GAIN_CEILING_L,
                           (uint8_t)(gain_x16 & 0xFFU));
}

HAL_StatusTypeDef OV5640_SetBandingFilter(OV5640_Ctx_t *ctx, OV5640_Banding_t b)
{
    OV5640_Timing_t   t;
    HAL_StatusTypeDef st;
    uint32_t          step50;
    uint32_t          step60;
    uint32_t          usable;

    if ((ctx == NULL) || (ctx->clock.pclk_hz == 0U))
    {
        return HAL_ERROR;
    }

    if (b == OV5640_BANDING_OFF)
    {
        /* 0x3A00[5] band function enable. Datasheet 7.8. */
        return OV5640_ModifyReg(ctx, OV5640_AEC_CTRL00, 0x20U, 0x00U);
    }

    st = OV5640_GetTiming(ctx, &t);
    if (st != HAL_OK) { return st; }
    if (t.hts == 0U)  { return HAL_ERROR; }

    /* Datasheet 4.6.1.1: band step is the number of rows in one period of the
       light intensity - 1/100 s at 50 Hz mains, 1/120 s at 60 Hz, because the
       intensity peaks twice per mains cycle.

           band_step = (PCLK / freq) / HTS                                   */
    step50 = (ctx->clock.pclk_hz / 100U) / t.hts;
    step60 = (ctx->clock.pclk_hz / 120U) / t.hts;

    if (step50 == 0U)    { step50 = 1U;     }
    if (step60 == 0U)    { step60 = 1U;     }
    if (step50 > 0x3FFU) { step50 = 0x3FFU; }
    if (step60 > 0x3FFU) { step60 = 0x3FFU; }

    st = OV5640_WriteReg(ctx, OV5640_AEC_B50_STEP_H,
                         (uint8_t)((step50 >> 8) & 0x03U));
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg(ctx, OV5640_AEC_B50_STEP_L, (uint8_t)(step50 & 0xFFU));
    if (st != HAL_OK) { return st; }

    st = OV5640_WriteReg(ctx, OV5640_AEC_B60_STEP_H,
                         (uint8_t)((step60 >> 8) & 0x03U));
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg(ctx, OV5640_AEC_B60_STEP_L, (uint8_t)(step60 & 0xFFU));
    if (st != HAL_OK) { return st; }

    /* max_bands = (VTS - 4) / band_step */
    usable = (t.vts > 4U) ? ((uint32_t)t.vts - 4U) : 1U;

    st = OV5640_WriteReg(ctx, OV5640_AEC_MAX_BANDS_50,
                         (uint8_t)((usable / step50) & 0xFFU));
    if (st != HAL_OK) { return st; }

    st = OV5640_WriteReg(ctx, OV5640_AEC_MAX_BANDS_60,
                         (uint8_t)((usable / step60) & 0xFFU));
    if (st != HAL_OK) { return st; }

    /* Max exposure, in lines, for each mains frequency. */
    st = OV5640_WriteReg16(ctx, OV5640_AEC_MAX_EXPO_50_H, (uint16_t)usable);
    if (st != HAL_OK) { return st; }
    st = OV5640_WriteReg16(ctx, OV5640_AEC_MAX_EXPO_60_H, (uint16_t)usable);
    if (st != HAL_OK) { return st; }

    /* 0x3C00[2] picks the band when manual; 0x3C01[7] selects manual mode.
       Datasheet 7.10. AUTO leaves the on-chip detector in charge. */
    if (b == OV5640_BANDING_AUTO)
    {
        st = OV5640_ModifyReg(ctx, OV5640_LIGHT_FREQ_CTRL01, 0x80U, 0x00U);
    }
    else
    {
        st = OV5640_ModifyReg(ctx, OV5640_LIGHT_FREQ_CTRL01, 0x80U, 0x80U);
        if (st != HAL_OK) { return st; }

        st = OV5640_ModifyReg(ctx, OV5640_LIGHT_FREQ_CTRL00, 0x04U,
                              (b == OV5640_BANDING_50HZ) ? 0x04U : 0x00U);
    }
    if (st != HAL_OK) { return st; }

    /* Enable the band function. */
    return OV5640_ModifyReg(ctx, OV5640_AEC_CTRL00, 0x20U, 0x20U);
}

/*============================================================================*/
/* Image adjustment (SDE, datasheet 5.11 / 7.26)                              */
/*============================================================================*/

/** @brief Clamp a caller level to -4..+4. */
static int8_t ov5640_clamp_level(int8_t level)
{
    if (level >  4) { return  4; }
    if (level < -4) { return -4; }
    return level;
}

HAL_StatusTypeDef OV5640_SetBrightness(OV5640_Ctx_t *ctx, int8_t level)
{
    HAL_StatusTypeDef st;
    uint8_t           magnitude;
    bool              negative;

    level     = ov5640_clamp_level(level);
    negative  = (level < 0);
    magnitude = (uint8_t)((negative ? -level : level) * 0x10);

    /* 0x5587 is "Y bright for contrast" and 0x5588[3] its sign. The brightness
       path lives inside the contrast block, so 0x5580[2] has to be on. */
    st = OV5640_ModifyReg(ctx, OV5640_SDE_CTRL0, 0x04U, 0x04U);
    if (st != HAL_OK) { return st; }

    st = OV5640_WriteReg(ctx, OV5640_SDE_CTRL7, magnitude);
    if (st != HAL_OK) { return st; }

    return OV5640_ModifyReg(ctx, OV5640_SDE_CTRL8, 0x08U,
                            negative ? 0x08U : 0x00U);
}

HAL_StatusTypeDef OV5640_SetContrast(OV5640_Ctx_t *ctx, int8_t level)
{
    HAL_StatusTypeDef st;
    int32_t           gain;

    level = ov5640_clamp_level(level);

    /* 0x5586 is the Y gain for contrast, with 0x20 meaning 1.0. Each step is
       1/8 of unity, so the range runs 0x10 (0.5x) to 0x30 (1.5x). */
    gain = 0x20 + ((int32_t)level * 4);
    if (gain < 0x10) { gain = 0x10; }
    if (gain > 0x30) { gain = 0x30; }

    st = OV5640_ModifyReg(ctx, OV5640_SDE_CTRL0, 0x04U, 0x04U);
    if (st != HAL_OK) { return st; }

    return OV5640_WriteReg(ctx, OV5640_SDE_CTRL6, (uint8_t)gain);
}

HAL_StatusTypeDef OV5640_SetSaturation(OV5640_Ctx_t *ctx, int8_t level)
{
    HAL_StatusTypeDef st;
    int32_t           sat;

    level = ov5640_clamp_level(level);

    /* 0x5583 / 0x5584 are the U and V saturation multipliers, valid when
       0x5580[1] = 1 and 0x5588[6] = 1. 0x40 is neutral. */
    sat = 0x40 + ((int32_t)level * 0x10);
    if (sat < 0x00) { sat = 0x00; }
    if (sat > 0xFF) { sat = 0xFF; }

    st = OV5640_ModifyReg(ctx, OV5640_SDE_CTRL0, 0x02U, 0x02U);
    if (st != HAL_OK) { return st; }

    st = OV5640_ModifyReg(ctx, OV5640_SDE_CTRL8, 0x40U, 0x40U);
    if (st != HAL_OK) { return st; }

    st = OV5640_WriteReg(ctx, OV5640_SDE_CTRL3, (uint8_t)sat);
    if (st != HAL_OK) { return st; }

    return OV5640_WriteReg(ctx, OV5640_SDE_CTRL4, (uint8_t)sat);
}

/** @brief cos and sin scaled by 128, for 0, 15, ..., 345 degrees. */
static const int16_t ov5640_cos128[24] =
{
     128,  124,  111,   91,   64,   33,    0,  -33,
     -64,  -91, -111, -124, -128, -124, -111,  -91,
     -64,  -33,    0,   33,   64,   91,  111,  124,
};

static const int16_t ov5640_sin128[24] =
{
       0,   33,   64,   91,  111,  124,  128,  124,
     111,   91,   64,   33,    0,  -33,  -64,  -91,
    -111, -124, -128, -124, -111,  -91,  -64,  -33,
};

HAL_StatusTypeDef OV5640_SetHue(OV5640_Ctx_t *ctx, int16_t degrees)
{
    HAL_StatusTypeDef st;
    int16_t           c;
    int16_t           s;
    uint8_t           sign = 0U;
    uint32_t          idx;

    /* Snap to the 15-degree grid the tables above cover. */
    degrees %= 360;
    if (degrees < 0)
    {
        degrees = (int16_t)(degrees + 360);
    }
    idx = ((uint32_t)degrees + 7U) / 15U;
    if (idx > 23U)
    {
        idx = 0U;
    }

    c = ov5640_cos128[idx];
    s = ov5640_sin128[idx];

    /* Datasheet 7.26: 0x5581 is the cos coefficient, 0x5582 the sin, and
       0x5588 carries their signs -
         [4] hue U cos, [5] hue V cos, [0] hue U sin, [1] hue V sin.
       The rotation is  U' =  U cos + V sin
                        V' = -U sin + V cos
       so the two sin terms always carry opposite signs. Check the result on a
       colour chart: the sign convention is documented per-bit but not as a
       worked example. */
    if (c < 0)
    {
        sign |= 0x30U;      /* negate both cos terms */
        c = (int16_t)-c;
    }

    if (s < 0)
    {
        sign |= 0x01U;      /* sin negative: negate the U term */
        s = (int16_t)-s;
    }
    else
    {
        sign |= 0x02U;      /* sin positive: negate the V term */
    }

    st = OV5640_ModifyReg(ctx, OV5640_SDE_CTRL0, 0x01U, 0x01U);
    if (st != HAL_OK) { return st; }

    st = OV5640_WriteReg(ctx, OV5640_SDE_CTRL1, (uint8_t)c);
    if (st != HAL_OK) { return st; }

    st = OV5640_WriteReg(ctx, OV5640_SDE_CTRL2, (uint8_t)s);
    if (st != HAL_OK) { return st; }

    return OV5640_ModifyReg(ctx, OV5640_SDE_CTRL8, 0x33U, sign);
}

HAL_StatusTypeDef OV5640_SetEffect(OV5640_Ctx_t *ctx, OV5640_Effect_t effect)
{
    HAL_StatusTypeDef st;
    uint8_t           ctrl0;    /* 0x5580 */
    uint8_t           u = 0x40U;
    uint8_t           v = 0x40U;

    /* 0x5580: [7] fixed Y, [6] negative, [5] gray, [4] fixed V, [3] fixed U.
       Datasheet 7.26. Tints are "fixed U and V" with the chroma pinned. */
    switch (effect)
    {
        case OV5640_EFFECT_NEGATIVE:  ctrl0 = 0x40U;                        break;
        case OV5640_EFFECT_GRAYSCALE: ctrl0 = 0x20U;                        break;
        case OV5640_EFFECT_SEPIA:     ctrl0 = 0x18U; u = 0x40U; v = 0xA0U;  break;
        case OV5640_EFFECT_RED_TINT:  ctrl0 = 0x18U; u = 0x80U; v = 0xC0U;  break;
        case OV5640_EFFECT_GREEN_TINT:ctrl0 = 0x18U; u = 0x60U; v = 0x60U;  break;
        case OV5640_EFFECT_BLUE_TINT: ctrl0 = 0x18U; u = 0xA0U; v = 0x40U;  break;
        case OV5640_EFFECT_NONE:
        default:                      ctrl0 = 0x00U;                        break;
    }

    /* Clear the effect bits, keep contrast/saturation/hue enables. */
    st = OV5640_ModifyReg(ctx, OV5640_SDE_CTRL0, 0xF8U, ctrl0);
    if (st != HAL_OK) { return st; }

    if ((ctrl0 & 0x18U) != 0U)
    {
        st = OV5640_WriteReg(ctx, OV5640_SDE_CTRL3, u);
        if (st != HAL_OK) { return st; }

        st = OV5640_WriteReg(ctx, OV5640_SDE_CTRL4, v);
        if (st != HAL_OK) { return st; }
    }

    return HAL_OK;
}

HAL_StatusTypeDef OV5640_SetTestPattern(OV5640_Ctx_t *ctx, bool enable)
{
    /* 0x503D = 0x80 is the ISP colour bar. Generated inside the ISP, so a good
       bar proves ISP output -> D-PHY -> receiver -> DCMIPP -> memory. */
    return OV5640_WriteReg(ctx, OV5640_ISP_TEST_PATTERN, enable ? 0x80U : 0x00U);
}

/*============================================================================*/
/* Manual focus (VCM, datasheet 3.3)                                          */
/*============================================================================*/

HAL_StatusTypeDef OV5640_SetFocusTarget(OV5640_Ctx_t *ctx, uint16_t target)
{
    HAL_StatusTypeDef st;

    if (target > 1023U)
    {
        target = 1023U;
    }

    /* 0x3602[7:4] = target[3:0], with [3:0] left as the slew rate control.
       0x3603[5:0] = target[9:4], [7] is the VCM power-down bit. */
    st = OV5640_ModifyReg(ctx, OV5640_VCM_CONTROL0, 0xF0U,
                          (uint8_t)((target & 0x0FU) << 4));
    if (st != HAL_OK)
    {
        return st;
    }

    return OV5640_ModifyReg(ctx, OV5640_VCM_CONTROL1, 0x3FU,
                            (uint8_t)((target >> 4) & 0x3FU));
}

HAL_StatusTypeDef OV5640_FocusPowerDown(OV5640_Ctx_t *ctx, bool down)
{
    return OV5640_ModifyReg(ctx, OV5640_VCM_CONTROL1, 0x80U,
                            down ? 0x80U : 0x00U);
}

/*============================================================================*/
/* Group write (datasheet 2.6)                                                */
/*============================================================================*/

HAL_StatusTypeDef OV5640_GroupBegin(OV5640_Ctx_t *ctx, uint8_t group)
{
    if (group > 3U)
    {
        return HAL_ERROR;
    }

    /* 0x3212 = 0x0n starts buffering into group n. */
    return OV5640_WriteReg(ctx, OV5640_SRM_GROUP_ACCESS, group);
}

HAL_StatusTypeDef OV5640_GroupEnd(OV5640_Ctx_t *ctx, uint8_t group)
{
    if (group > 3U)
    {
        return HAL_ERROR;
    }

    /* bit[4] group hold end. */
    return OV5640_WriteReg(ctx, OV5640_SRM_GROUP_ACCESS, (uint8_t)(0x10U | group));
}

HAL_StatusTypeDef OV5640_GroupLaunch(OV5640_Ctx_t *ctx, uint8_t group)
{
    if (group > 3U)
    {
        return HAL_ERROR;
    }

    /* bit[7] launch enable | bit[5] launch. The buffered writes land together
       at the next frame boundary. */
    return OV5640_WriteReg(ctx, OV5640_SRM_GROUP_ACCESS, (uint8_t)(0xA0U | group));
}

/*============================================================================*/
/* Capture (DCMIPP wrappers)                                                  */
/*============================================================================*/

/*
 * PORTING LAYER - read the note in ov5640.h before relying on this.
 *
 * Everything above is derived from the OV5640 datasheet and is independent of
 * your STM32Cube version. The code below calls into the DCMIPP HAL, whose exact
 * symbol names were NOT verified against an installed CubeH7RS package. Check
 * them against your stm32h7rsxx_hal_dcmipp.h and RM0477.
 *
 * The pipe choice is deliberate: pipe 0 is the dump pipe, which writes the
 * received bytes straight to memory. It works with YUV422 and RGB565 as-is and
 * removes a layer from the first bring-up. Move to pipe 1 once frames are
 * arriving, if you want DCMIPP's ISP to debayer RAW for you - which is worth
 * doing, because it lets the sensor send RAW8 at half the lane rate.
 */
#ifdef OV5640_USE_DCMIPP

#ifndef OV5640_DCMIPP_PIPE
#define OV5640_DCMIPP_PIPE      DCMIPP_PIPE0
#endif

static HAL_StatusTypeDef ov5640_pipe_start(OV5640_Ctx_t *ctx, uint32_t mode,
                                           uint8_t *buffer, uint32_t size)
{
    if ((ctx == NULL) || (ctx->hdcmipp == NULL) || (buffer == NULL) || (size == 0U))
    {
        return HAL_ERROR;
    }

    /* No 65535-word ceiling here: DCMIPP writes through its own master port
       with a full byte count, so a 5 MP frame is one destination address. */
    (void)size;

    return HAL_DCMIPP_PIPE_Start((DCMIPP_HandleTypeDef *)ctx->hdcmipp,
                                 OV5640_DCMIPP_PIPE,
                                 (uint32_t)buffer, mode);
}

HAL_StatusTypeDef OV5640_StartCapture(OV5640_Ctx_t *ctx,
                                      uint8_t *buffer, uint32_t size)
{
    return ov5640_pipe_start(ctx, DCMIPP_MODE_CONTINUOUS, buffer, size);
}

HAL_StatusTypeDef OV5640_StartSnapshot(OV5640_Ctx_t *ctx,
                                       uint8_t *buffer, uint32_t size)
{
    return ov5640_pipe_start(ctx, DCMIPP_MODE_SNAPSHOT, buffer, size);
}

HAL_StatusTypeDef OV5640_StopCapture(OV5640_Ctx_t *ctx)
{
    if ((ctx == NULL) || (ctx->hdcmipp == NULL))
    {
        return HAL_ERROR;
    }

    return HAL_DCMIPP_PIPE_Stop((DCMIPP_HandleTypeDef *)ctx->hdcmipp,
                                OV5640_DCMIPP_PIPE);
}

#endif /* OV5640_USE_DCMIPP */
