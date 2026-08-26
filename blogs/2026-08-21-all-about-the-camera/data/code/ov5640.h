/**
  ******************************************************************************
  * @file    ov5640.h
  * @brief   OmniVision OV5640 (1/4" 5 MP CMOS) driver for STM32H7R7,
  *          MIPI CSI-2 output.
  *
  * The STM32H7R7 has a CSI-2 host with a D-PHY receiver feeding DCMIPP, so the
  * sensor runs in MIPI mode: 1 clock lane + 2 data lanes. The parallel DVP
  * interface is not used and its pins are left unconnected.
  *
  * Control is over SCCB, which is I2C compatible: 16-bit register address,
  * 8-bit data, slave address 0x78.
  *
  * Register references in comments are to:
  *   OV5640 datasheet, product specification version 2.03, may 2011.
  *
  * See README.md for the bring-up procedure and NOTES.md for the pin tables
  * and the calculations these functions implement.
  ******************************************************************************
  */

#ifndef OV5640_H
#define OV5640_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7rsxx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/*============================================================================*/
/* Identity                                                                   */
/*============================================================================*/

#define OV5640_I2C_ADDR             0x78U   /*!< 8-bit form, as HAL wants it   */
#define OV5640_I2C_ADDR_7BIT        0x3CU   /*!< the same address, 7-bit       */
#define OV5640_CHIP_ID              0x5640U /*!< {0x300A, 0x300B}              */

#define OV5640_XVCLK_DEFAULT_HZ     24000000U  /*!< every reg table assumes it */
#define OV5640_XVCLK_MIN_HZ          6000000U  /*!< datasheet 8.4, table 8-5   */
#define OV5640_XVCLK_MAX_HZ         27000000U
#define OV5640_VCO_MAX_HZ          800000000U  /*!< datasheet 2.5              */

#define OV5640_MAX_WIDTH            2592U
#define OV5640_MAX_HEIGHT           1944U

/*============================================================================*/
/* Register map                                                               */
/*============================================================================*/

/* --- system and IO pad control, datasheet 7.1 ----------------------------- */
#define OV5640_SYSTEM_RESET00       0x3000U /*!< per-block reset               */
#define OV5640_SYSTEM_RESET01       0x3001U
#define OV5640_SYSTEM_RESET02       0x3002U
#define OV5640_SYSTEM_RESET03       0x3003U
#define OV5640_CLOCK_ENABLE00       0x3004U /*!< per-block clock gate          */
#define OV5640_CLOCK_ENABLE01       0x3005U
#define OV5640_CLOCK_ENABLE02       0x3006U
#define OV5640_CLOCK_ENABLE03       0x3007U
#define OV5640_SYSTEM_CTRL0         0x3008U /*!< [7] sw reset, [6] sw pwdn     */
#define OV5640_CHIP_ID_HIGH         0x300AU /*!< 0x56                          */
#define OV5640_CHIP_ID_LOW          0x300BU /*!< 0x40                          */
#define OV5640_IO_MIPI_CTRL00       0x300EU /*!< lane mode, PHY pwdn, mipi_en  */
#define OV5640_PAD_OUTPUT_ENABLE00  0x3016U
#define OV5640_PAD_OUTPUT_ENABLE01  0x3017U
#define OV5640_PAD_OUTPUT_ENABLE02  0x3018U
#define OV5640_PAD_OUTPUT_VALUE00   0x301AU
#define OV5640_PAD_SELECT00         0x301DU
#define OV5640_PAD_CONTROL00        0x302CU
#define OV5640_SC_PLL_CTRL0         0x3034U /*!< [3:0] MIPI bit mode           */
#define OV5640_SC_PLL_CTRL1         0x3035U /*!< [7:4] sys div, [3:0] mipi div */
#define OV5640_SC_PLL_CTRL2         0x3036U /*!< [7:0] PLL multiplier          */
#define OV5640_SC_PLL_CTRL3         0x3037U /*!< [4] root div, [3:0] pre-div   */
#define OV5640_SC_PLL_CTRL5         0x3039U /*!< [7] PLL bypass                */

/* --- SCCB control, datasheet 7.2 ------------------------------------------ */
#define OV5640_SCCB_ID              0x3100U /*!< slave ID, default 0x78        */
#define OV5640_SCCB_SYSTEM_CTRL0    0x3102U
#define OV5640_SCCB_SYSTEM_CTRL1    0x3103U /*!< [1] 0=pad clock 1=PLL         */
#define OV5640_SYSTEM_ROOT_DIVIDER  0x3108U /*!< [1:0] SCLK root divider       */

/* --- group write, datasheet 7.3 ------------------------------------------- */
#define OV5640_SRM_GROUP_ACCESS     0x3212U
#define OV5640_SRM_GROUP_STATUS     0x3213U

/* --- AWB gain, datasheet 7.4 ---------------------------------------------- */
#define OV5640_AWB_R_GAIN_H         0x3400U
#define OV5640_AWB_G_GAIN_H         0x3402U
#define OV5640_AWB_B_GAIN_H         0x3404U
#define OV5640_AWB_MANUAL_CTRL      0x3406U /*!< [0] 1 = manual AWB gain       */

/* --- AEC/AGC, datasheet 7.5 ----------------------------------------------- */
#define OV5640_AEC_EXPOSURE_H       0x3500U /*!< [3:0] exposure[19:16]         */
#define OV5640_AEC_EXPOSURE_M       0x3501U /*!< exposure[15:8]                */
#define OV5640_AEC_EXPOSURE_L       0x3502U /*!< exposure[7:0], [3:0] must = 0 */
#define OV5640_AEC_PK_MANUAL        0x3503U /*!< [1] AGC manual, [0] AEC man.  */
#define OV5640_AEC_PK_REAL_GAIN_H   0x350AU /*!< [1:0] gain[9:8], unit 1/16    */
#define OV5640_AEC_PK_REAL_GAIN_L   0x350BU /*!< gain[7:0]                     */
#define OV5640_AEC_PK_VTS_H         0x350CU /*!< extra VTS[15:8]               */
#define OV5640_AEC_PK_VTS_L         0x350DU

/* --- VCM (autofocus actuator), datasheet 7.6 ------------------------------ */
#define OV5640_VCM_CONTROL0         0x3602U /*!< [7:4] target[3:0], [3:0] slew */
#define OV5640_VCM_CONTROL1         0x3603U /*!< [7] pwdn, [5:0] target[9:4]   */

/* --- timing, datasheet 7.7 ------------------------------------------------ */
#define OV5640_TIMING_HS_H          0x3800U /*!< X_ADDR_ST[11:8]               */
#define OV5640_TIMING_VS_H          0x3802U /*!< Y_ADDR_ST[10:8]               */
#define OV5640_TIMING_HW_H          0x3804U /*!< X_ADDR_END[11:8]              */
#define OV5640_TIMING_VH_H          0x3806U /*!< Y_ADDR_END[10:8]              */
#define OV5640_TIMING_DVPHO_H       0x3808U /*!< X_OUTPUT_SIZE[11:8]           */
#define OV5640_TIMING_DVPVO_H       0x380AU /*!< Y_OUTPUT_SIZE[10:8]           */
#define OV5640_TIMING_HTS_H         0x380CU /*!< HTS[12:8], in PIXEL periods   */
#define OV5640_TIMING_VTS_H         0x380EU /*!< VTS[15:8], in lines           */
#define OV5640_TIMING_HOFFSET_H     0x3810U
#define OV5640_TIMING_VOFFSET_H     0x3812U
#define OV5640_TIMING_X_INC         0x3814U /*!< {odd_inc[7:4], even_inc[3:0]} */
#define OV5640_TIMING_Y_INC         0x3815U
#define OV5640_TIMING_TC_REG20      0x3820U /*!< [2] ISP vflip, [1] sensor     */
#define OV5640_TIMING_TC_REG21      0x3821U /*!< [2] ISP mirror, [0] h-binning */

/* --- AEC/AGC power-down domain (banding, night mode), datasheet 7.8 ------- */
#define OV5640_AEC_CTRL00           0x3A00U /*!< [5] band enable, [2] night    */
#define OV5640_AEC_MAX_EXPO_60_H    0x3A02U
#define OV5640_AEC_B50_STEP_H       0x3A08U /*!< 50 Hz band step[9:8]          */
#define OV5640_AEC_B50_STEP_L       0x3A09U
#define OV5640_AEC_B60_STEP_H       0x3A0AU /*!< 60 Hz band step[9:8]          */
#define OV5640_AEC_B60_STEP_L       0x3A0BU
#define OV5640_AEC_MAX_BANDS_60     0x3A0DU
#define OV5640_AEC_MAX_BANDS_50     0x3A0EU
#define OV5640_AEC_MAX_EXPO_50_H    0x3A14U
#define OV5640_AEC_GAIN_CEILING_H   0x3A18U /*!< [1:0] ceiling[9:8]            */
#define OV5640_AEC_GAIN_CEILING_L   0x3A19U

/* --- 50/60 Hz detector, datasheet 7.10 ------------------------------------ */
#define OV5640_LIGHT_FREQ_CTRL00    0x3C00U /*!< [2] 50 Hz select when manual  */
#define OV5640_LIGHT_FREQ_CTRL01    0x3C01U /*!< [7] band detect manual        */

/* --- black level calibration, datasheet 7.13 ------------------------------ */
#define OV5640_BLC_CTRL00           0x4000U /*!< [0] BLC enable                */

/* --- format control, datasheet 7.15 --------------------------------------- */
#define OV5640_FORMAT_CTRL00        0x4300U /*!< {format[7:4], sequence[3:0]}  */

/* --- MIPI transmitter and D-PHY timing, datasheet 7.19 -------------------- */
#define OV5640_MIPI_CTRL00          0x4800U /*!< clock gate, line sync, idle   */
#define OV5640_MIPI_CTRL01          0x4801U /*!< packet header order for ECC   */
#define OV5640_MIPI_CTRL05          0x4805U /*!< lane disable, LPX timing sel  */
#define OV5640_MIPI_DATA_ORDER      0x480AU
#define OV5640_MIPI_MIN_HS_ZERO_H   0x4818U /*!< ns floor, pairs with 0x482A   */
#define OV5640_MIPI_MIN_HS_TRAIL_H  0x481AU /*!< ns floor, pairs with 0x482B   */
#define OV5640_MIPI_MIN_CLK_ZERO_H  0x481CU /*!< ns floor, pairs with 0x482C   */
#define OV5640_MIPI_MIN_CLK_PREP_H  0x481EU /*!< ns floor, pairs with 0x482D   */
#define OV5640_MIPI_MIN_CLK_POST_H  0x4820U /*!< ns floor, pairs with 0x482E   */
#define OV5640_MIPI_MIN_CLK_TRAIL_H 0x4822U /*!< ns floor, pairs with 0x482F   */
#define OV5640_MIPI_MIN_LPX_PCLK_H  0x4824U /*!< ns floor, pairs with 0x4830   */
#define OV5640_MIPI_MIN_HS_PREP_H   0x4826U /*!< ns floor, pairs with 0x4831   */
#define OV5640_MIPI_MIN_HS_EXIT_H   0x4828U /*!< ns floor, pairs with 0x4832   */
#define OV5640_MIPI_UI_HS_ZERO      0x482AU /*!< UI floor                      */
#define OV5640_MIPI_UI_HS_TRAIL     0x482BU
#define OV5640_MIPI_UI_CLK_ZERO     0x482CU
#define OV5640_MIPI_UI_CLK_PREPARE  0x482DU
#define OV5640_MIPI_UI_CLK_POST     0x482EU
#define OV5640_MIPI_UI_CLK_TRAIL    0x482FU
#define OV5640_MIPI_UI_LPX_PCLK     0x4830U
#define OV5640_MIPI_UI_HS_PREPARE   0x4831U
#define OV5640_MIPI_UI_HS_EXIT      0x4832U
#define OV5640_MIPI_PCLK_PERIOD     0x4837U /*!< period in HALF-nanoseconds    */

/* --- ISP top, datasheet 7.21 ---------------------------------------------- */
#define OV5640_ISP_CONTROL00        0x5000U /*!< LENC/GMA/DPC/CIP enables      */
#define OV5640_ISP_CONTROL01        0x5001U /*!< SDE/scale/UV/CMX/AWB enables  */
#define OV5640_ISP_CONTROL03        0x5003U /*!< [2] binning enable            */
#define OV5640_ISP_FORMAT_MUX_CTRL  0x501FU /*!< must agree with 0x4300        */
#define OV5640_ISP_TEST_PATTERN     0x503DU /*!< 0x80 = colour bar             */

/* --- SDE, datasheet 7.26 -------------------------------------------------- */
#define OV5640_SDE_CTRL0            0x5580U /*!< effect enable bits            */
#define OV5640_SDE_CTRL1            0x5581U /*!< hue cos coefficient           */
#define OV5640_SDE_CTRL2            0x5582U /*!< hue sin coefficient           */
#define OV5640_SDE_CTRL3            0x5583U /*!< U / saturation                */
#define OV5640_SDE_CTRL4            0x5584U /*!< V / saturation                */
#define OV5640_SDE_CTRL5            0x5585U /*!< Y offset for contrast         */
#define OV5640_SDE_CTRL6            0x5586U /*!< Y gain for contrast, 0x20 = 1 */
#define OV5640_SDE_CTRL7            0x5587U /*!< brightness magnitude          */
#define OV5640_SDE_CTRL8            0x5588U /*!< sign bits                     */

/* --- autofocus firmware handshake, datasheet 7.30 ------------------------- */
#define OV5640_AF_CMD_MAIN          0x3022U
#define OV5640_AF_FW_STATUS         0x3029U /*!< 0x70 = firmware ready         */

/*============================================================================*/
/* MIPI control values                                                        */
/*============================================================================*/

/*
 * 0x300E field definitions per datasheet 7.1:
 *   [7:5] lane mode  000 = one lane, 001 = two lane, others "debug mode"
 *   [4]   MIPI TX PHY power down  (1 = powered down; must be 0 to transmit)
 *   [3]   MIPI RX PHY power down
 *   [2]   mipi_en     0 = DVP, 1 = MIPI
 *
 * The catch: the register's own reset default is 0x58, whose [7:5] field is
 * 010 - one of the supposedly-invalid values - and the mainline Linux driver
 * streams with 0x45 (also 010) and stops with 0x40. Either the encoding table
 * is incomplete or [7:5] is not really a lane selector.
 *
 * OV5640_SetLanes() builds the value from the documented fields. If your
 * receiver never sees the lanes leave LP-11, write the field-proven pair below
 * instead before debugging anything else. See README section 0.
 */
#define OV5640_MIPI_CTRL00_STREAM_ON    0x45U  /*!< field-proven fallback      */
#define OV5640_MIPI_CTRL00_STREAM_OFF   0x40U

/*============================================================================*/
/* Types                                                                      */
/*============================================================================*/

/**
  * @brief Output pixel format.
  *
  * Three things must agree for a format to work, and the driver sets all three:
  *   1. 0x4300 / 0x501F - what the sensor formats
  *   2. 0x3034[3:0]     - 8-bit vs 10-bit serialisation (also sets bit_div)
  *   3. the CSI-2 data type the receiver is told to accept
  *
  * Number 3 is on you: pass OV5640_GetCsiDataType() to your DCMIPP virtual
  * channel configuration. A mismatch there produces no frames and no errors.
  */
typedef enum
{
    OV5640_FORMAT_RGB565_BGR = 0, /*!< {b,g}{g,r} - usual choice for STM32     */
    OV5640_FORMAT_RGB565_RGB,     /*!< {r,g}{g,b} - try this if colours swap   */
    OV5640_FORMAT_YUV422_YUYV,
    OV5640_FORMAT_YUV422_UYVY,
    OV5640_FORMAT_RAW8_BGGR,      /*!< demosaic and gamma bypassed, 8 bpp      */
    OV5640_FORMAT_RAW10_BGGR,     /*!< 10 bpp; moves bit_div from 2 to 2.5     */
    OV5640_FORMAT_COUNT
} OV5640_Format_t;

/** @brief CSI-2 data type codes, MIPI CSI-2 specification. */
#define OV5640_CSI_DT_YUV422_8B     0x1EU
#define OV5640_CSI_DT_RGB565        0x22U
#define OV5640_CSI_DT_RAW8          0x2AU
#define OV5640_CSI_DT_RAW10         0x2BU

/**
  * @brief Output resolution. Everything up to SXGA is the ISP scaler working on
  *        the same 1280x960 pre-scaled frame, so the field of view is constant.
  */
typedef enum
{
    OV5640_RES_QQVGA = 0,   /*!< 160 x 120,   scaled                           */
    OV5640_RES_QVGA,        /*!< 320 x 240,   scaled                           */
    OV5640_RES_VGA,         /*!< 640 x 480,   scaled                           */
    OV5640_RES_SVGA,        /*!< 800 x 600,   scaled                           */
    OV5640_RES_XGA,         /*!< 1024 x 768,  scaled                           */
    OV5640_RES_SXGA,        /*!< 1280 x 960,  2x subsampled, scaler 1:1        */
    OV5640_RES_720P,        /*!< 1280 x 720,  cropped then 2x subsampled       */
    OV5640_RES_1080P,       /*!< 1920 x 1080, cropped from full resolution     */
    OV5640_RES_5MP,         /*!< 2592 x 1944, full resolution                  */
    OV5640_RES_COUNT
} OV5640_Resolution_t;

/** @brief Number of CSI-2 data lanes in use. */
typedef enum
{
    OV5640_LANES_1 = 1,     /*!< half the bandwidth, half the frame rate       */
    OV5640_LANES_2 = 2      /*!< use this unless the board cannot route it     */
} OV5640_Lanes_t;

/** @brief Mains frequency for the flicker banding filter. Datasheet 4.6.1.1. */
typedef enum
{
    OV5640_BANDING_AUTO = 0, /*!< let the 0x3C00 detector decide               */
    OV5640_BANDING_50HZ,
    OV5640_BANDING_60HZ,
    OV5640_BANDING_OFF
} OV5640_Banding_t;

/** @brief Canned SDE effects. Datasheet 5.11. */
typedef enum
{
    OV5640_EFFECT_NONE = 0,
    OV5640_EFFECT_NEGATIVE,
    OV5640_EFFECT_GRAYSCALE,
    OV5640_EFFECT_SEPIA,
    OV5640_EFFECT_RED_TINT,
    OV5640_EFFECT_GREEN_TINT,
    OV5640_EFFECT_BLUE_TINT
} OV5640_Effect_t;

/**
  * @brief  Clock configuration, computed rather than tabulated.
  *
  *   VCO       = XVCLK * mult / pre_div                        (<= 800 MHz)
  *   PCLK      = VCO / sys_div / root_div / bit_div / sclk_root_div
  *   SERCLK    = VCO / sys_div / root_div / mipi_div
  *   lane_rate = 2 * SERCLK                       (DDR: 2 bits per clock)
  *
  * The bandwidth constraint the driver enforces:
  *
  *   required_lane_rate = PCLK * bits_per_pixel / num_lanes
  *
  * Note VTS and frame rate are absent from that: blanking lines do not slow
  * the pixels inside an active line, so lowering the frame rate does NOT
  * lower the peak lane rate. Only lowering PCLK does.
  */
typedef struct
{
    /* Inputs. */
    uint8_t  pre_div;        /*!< 0x3037[3:0]: 1, 2, 3, 4, 6 or 8             */
    uint8_t  mult;           /*!< 0x3036[7:0]: 4..127, or even 128..252       */
    uint8_t  root_div;       /*!< 0x3037[4]:   1 or 2                         */
    uint8_t  sys_div;        /*!< 0x3035[7:4]: 1..16                          */
    uint8_t  bit_mode;       /*!< 0x3034[3:0]: 0x8 (/2) or 0xA (/2.5)         */
    uint8_t  sclk_root_div;  /*!< 0x3108[1:0]: 1, 2, 4 or 8                   */

    /* Computed by OV5640_ClockCompute(). */
    uint8_t  mipi_div;       /*!< 0x3035[3:0]                                 */
    uint32_t vco_hz;
    uint32_t pclk_hz;        /*!< pixel clock; HTS/VTS live in this domain    */
    uint32_t lane_rate_bps;  /*!< per lane, bits per second                   */
    uint32_t required_bps;   /*!< per lane, what the mode and format need     */
} OV5640_Clock_t;

/** @brief Timing registers read back from the sensor. */
typedef struct
{
    uint16_t hts;           /*!< {0x380C, 0x380D}, pixel periods per line     */
    uint16_t vts;           /*!< {0x380E, 0x380F}, lines per frame            */
    uint16_t width;         /*!< {0x3808, 0x3809}                             */
    uint16_t height;        /*!< {0x380A, 0x380B}                             */
} OV5640_Timing_t;

/**
  * @brief Driver context. Fill in the inputs before calling OV5640_Init().
  *
  * @note  @p hdcmipp may be NULL if you drive DCMIPP yourself; only the capture
  *        helpers at the bottom of ov5640.c need it.
  */
typedef struct
{
    I2C_HandleTypeDef    *hi2c;        /*!< SCCB bus                          */
    void                 *hdcmipp;     /*!< DCMIPP_HandleTypeDef*, may be NULL*/

    GPIO_TypeDef         *reset_port;  /*!< RESETB, active low. May be NULL.  */
    uint16_t              reset_pin;
    GPIO_TypeDef         *pwdn_port;   /*!< PWDN, active high. May be NULL.   */
    uint16_t              pwdn_pin;

    uint32_t              xvclk_hz;    /*!< 0 defaults to 24 MHz              */
    uint8_t               i2c_addr;    /*!< 0 defaults to OV5640_I2C_ADDR     */
    OV5640_Lanes_t        lanes;       /*!< 0 defaults to 2                   */

    /* Filled in by the driver. */
    OV5640_Clock_t        clock;
    OV5640_Timing_t       timing;
    OV5640_Resolution_t   resolution;
    OV5640_Format_t       format;
    bool                  streaming;
} OV5640_Ctx_t;

/*============================================================================*/
/* Low level: SCCB register access                                            */
/*============================================================================*/

HAL_StatusTypeDef OV5640_WriteReg  (OV5640_Ctx_t *ctx, uint16_t reg, uint8_t val);
HAL_StatusTypeDef OV5640_ReadReg   (OV5640_Ctx_t *ctx, uint16_t reg, uint8_t *val);
HAL_StatusTypeDef OV5640_ModifyReg (OV5640_Ctx_t *ctx, uint16_t reg,
                                    uint8_t mask, uint8_t val);
HAL_StatusTypeDef OV5640_WriteReg16(OV5640_Ctx_t *ctx, uint16_t reg_h, uint16_t val);
HAL_StatusTypeDef OV5640_ReadReg16 (OV5640_Ctx_t *ctx, uint16_t reg_h, uint16_t *val);

/*============================================================================*/
/* Lifecycle                                                                  */
/*============================================================================*/

/**
  * @brief  Drive RESETB and PWDN through the sequence in datasheet 2.7/2.8.
  * @note   Assumes the supplies and XVCLK are already up and stable. Blocks for
  *         roughly 35 ms.
  */
void OV5640_HwReset(OV5640_Ctx_t *ctx);

/** @brief Assert or release hardware standby via PWDN. Datasheet 2.9. */
void OV5640_HwPowerDown(OV5640_Ctx_t *ctx, bool down);

/** @brief Software power down, 0x3008[6]. Register content is preserved. */
HAL_StatusTypeDef OV5640_SwPowerDown(OV5640_Ctx_t *ctx, bool down);

/** @brief Software reset, 0x3008[7], then 5 ms settle. */
HAL_StatusTypeDef OV5640_SwReset(OV5640_Ctx_t *ctx);

/** @brief Read {0x300A, 0x300B}. Expect OV5640_CHIP_ID. */
HAL_StatusTypeDef OV5640_ReadID(OV5640_Ctx_t *ctx, uint16_t *id);

/**
  * @brief  Full bring-up: hardware reset, ID check, software reset, common
  *         register table, MIPI configuration, clocks, D-PHY timing, format and
  *         resolution. Leaves the sensor configured but NOT streaming.
  *
  * @note   Does not configure DCMIPP, the CSI-2 host, GPIO, I2C or the MCO.
  *         Do those first, and configure the D-PHY receiver for the lane rate
  *         this call works out - read it back with OV5640_GetLaneRate().
  *
  * @return HAL_ERROR if the chip ID is wrong, or if the requested mode and
  *         format need more lane bandwidth than the configuration can carry.
  */
HAL_StatusTypeDef OV5640_Init(OV5640_Ctx_t *ctx,
                              OV5640_Resolution_t res,
                              OV5640_Format_t fmt);

/**
  * @brief  Start or stop transmitting on the CSI-2 link.
  * @note   Init leaves the sensor idle so you can bring the receiver up first.
  *         With the sensor configured and not streaming, the data lanes should
  *         sit in LP-11 - scope them, it is the cheapest check that the PHY is
  *         alive. See README section 10.
  */
HAL_StatusTypeDef OV5640_SetStreaming(OV5640_Ctx_t *ctx, bool on);

/*============================================================================*/
/* MIPI CSI-2 configuration                                                   */
/*============================================================================*/

/** @brief Set the lane count. Called by OV5640_Init() from ctx->lanes. */
HAL_StatusTypeDef OV5640_SetLanes(OV5640_Ctx_t *ctx, OV5640_Lanes_t lanes);

/**
  * @brief  Configure the clock lane mode.
  * @param  continuous  true: clock lane free-runs (simpler for the receiver to
  *                     lock to, and the safer default for bring-up).
  *                     false: gated, drops to LP between packets. Lower power,
  *                     needs receiver support for non-continuous clock.
  * @note   0x4800[5]. If you see intermittent SoT errors with gating on, clear
  *         it before chasing anything else.
  */
HAL_StatusTypeDef OV5640_SetClockLaneMode(OV5640_Ctx_t *ctx, bool continuous);

/**
  * @brief  Write the D-PHY global timing register 0x4837 from the configured
  *         lane rate: period of SERCLK in half-nanosecond units.
  *
  *             0x4837 = round(2000 / SERCLK_MHz)
  *
  *         This is how the sensor converts the nanosecond floors in
  *         0x4818..0x4832 into internal cycles. It is the single most commonly
  *         missed register in an OV5640 CSI-2 bring-up: get it wrong and the
  *         link runs but the receiver logs SoT or ECC errors.
  *
  * @note   Called automatically by OV5640_Init() and whenever the clocks
  *         change, so it cannot drift out of sync with the PLL.
  */
HAL_StatusTypeDef OV5640_ApplyDphyTiming(OV5640_Ctx_t *ctx);

/** @brief Configured per-lane rate in bits/s. Feed this to your D-PHY setup. */
uint32_t OV5640_GetLaneRate(const OV5640_Ctx_t *ctx);

/** @brief CSI-2 data type for a format. Feed this to your VC configuration. */
uint8_t OV5640_GetCsiDataType(OV5640_Format_t fmt);

/*============================================================================*/
/* Clocking                                                                   */
/*============================================================================*/

/**
  * @brief  Work out every derived clock for a configuration, without touching
  *         hardware. Fills the computed fields of @p clk.
  *
  * @param  bpp    bits per pixel of the intended output format
  * @param  lanes  number of CSI-2 data lanes
  *
  * @return HAL_ERROR if the settings are illegal (VCO over 800 MHz, a divider
  *         of zero, an unsupported pre-divider) or if the resulting lane rate
  *         cannot carry @p bpp at the resulting pixel clock.
  */
HAL_StatusTypeDef OV5640_ClockCompute(uint32_t xvclk_hz, OV5640_Clock_t *clk,
                                      uint8_t bpp, OV5640_Lanes_t lanes);

/** @brief Write a computed clock configuration and cache it in @p ctx. */
HAL_StatusTypeDef OV5640_ClockApply(OV5640_Ctx_t *ctx, const OV5640_Clock_t *clk);

/** @brief Last applied pixel clock in Hz, or 0 if not yet configured. */
uint32_t OV5640_GetPclk(const OV5640_Ctx_t *ctx);

/** @brief Read HTS, VTS and the output size back from the sensor. */
HAL_StatusTypeDef OV5640_GetTiming(OV5640_Ctx_t *ctx, OV5640_Timing_t *t);

/** @brief Frame rate in milli-fps, from the cached PCLK and live HTS/VTS. */
uint32_t OV5640_GetFrameRate_mfps(OV5640_Ctx_t *ctx);

/**
  * @brief  Set the frame rate by stretching VTS, leaving the PLL alone.
  * @note   Only lowers the rate below the mode's native maximum. This does not
  *         change the lane rate requirement - see OV5640_Clock_t.
  */
HAL_StatusTypeDef OV5640_SetFrameRate(OV5640_Ctx_t *ctx, uint32_t fps);

/*============================================================================*/
/* Format, resolution, orientation                                            */
/*============================================================================*/

/**
  * @brief  Set the output format.
  * @note   Changes bits per pixel, so it re-runs the clock computation and can
  *         fail if the new format does not fit the lane budget. If it succeeds,
  *         re-read OV5640_GetLaneRate() and OV5640_GetCsiDataType() and update
  *         the receiver to match.
  */
HAL_StatusTypeDef OV5640_SetFormat(OV5640_Ctx_t *ctx, OV5640_Format_t fmt);

/** @brief Set the output resolution, applying that mode's window and clocks. */
HAL_StatusTypeDef OV5640_SetResolution(OV5640_Ctx_t *ctx, OV5640_Resolution_t res);

HAL_StatusTypeDef OV5640_SetMirrorFlip(OV5640_Ctx_t *ctx, bool mirror, bool flip);

/** @brief Pixel dimensions of a resolution, for sizing frame buffers. */
void OV5640_GetResolutionSize(OV5640_Resolution_t res, uint16_t *w, uint16_t *h);

/** @brief Bits per pixel on the wire: 16 for RGB565/YUV422, 8 or 10 for RAW. */
uint8_t OV5640_GetBitsPerPixel(OV5640_Format_t fmt);

/** @brief Frame size in bytes, for a fully packed frame. */
uint32_t OV5640_GetFrameSize(OV5640_Resolution_t res, OV5640_Format_t fmt);

/*============================================================================*/
/* Exposure, gain, white balance                                              */
/*============================================================================*/

HAL_StatusTypeDef OV5640_SetAutoExposure(OV5640_Ctx_t *ctx, bool enable);
HAL_StatusTypeDef OV5640_SetAutoGain    (OV5640_Ctx_t *ctx, bool enable);
HAL_StatusTypeDef OV5640_SetAutoWhiteBalance(OV5640_Ctx_t *ctx, bool enable);

/**
  * @brief  Set exposure in lines. Enables manual AEC.
  * @note   Clamped to VTS + extra_VTS - 4. To go beyond one frame period, raise
  *         VTS first with OV5640_SetFrameRate() - datasheet 4.6.2.
  */
HAL_StatusTypeDef OV5640_SetExposureLines(OV5640_Ctx_t *ctx, uint32_t lines);

/** @brief Set exposure in microseconds. Converts using the live HTS and PCLK. */
HAL_StatusTypeDef OV5640_SetExposureUs(OV5640_Ctx_t *ctx, uint32_t us);

/** @brief Read back the current exposure, in lines. */
HAL_StatusTypeDef OV5640_GetExposureLines(OV5640_Ctx_t *ctx, uint32_t *lines);

/**
  * @brief  Set analog gain in 1/16 steps. Enables manual AGC.
  * @param  gain_x16  16 = 1x, 1024 = 64x (the maximum).
  */
HAL_StatusTypeDef OV5640_SetGain(OV5640_Ctx_t *ctx, uint16_t gain_x16);

/** @brief Read back the current gain, in 1/16 steps. */
HAL_StatusTypeDef OV5640_GetGain(OV5640_Ctx_t *ctx, uint16_t *gain_x16);

/** @brief AGC ceiling in 1/16 steps, {0x3A18[1:0], 0x3A19}. */
HAL_StatusTypeDef OV5640_SetGainCeiling(OV5640_Ctx_t *ctx, uint16_t gain_x16);

/**
  * @brief  Configure the flicker banding filter from the live HTS/VTS and PCLK.
  *         Implements the band-step arithmetic in datasheet 4.6.1.1.
  */
HAL_StatusTypeDef OV5640_SetBandingFilter(OV5640_Ctx_t *ctx, OV5640_Banding_t b);

/*============================================================================*/
/* Image adjustment                                                           */
/*============================================================================*/

HAL_StatusTypeDef OV5640_SetBrightness(OV5640_Ctx_t *ctx, int8_t level); /* -4..+4 */
HAL_StatusTypeDef OV5640_SetContrast  (OV5640_Ctx_t *ctx, int8_t level); /* -4..+4 */
HAL_StatusTypeDef OV5640_SetSaturation(OV5640_Ctx_t *ctx, int8_t level); /* -4..+4 */
HAL_StatusTypeDef OV5640_SetHue       (OV5640_Ctx_t *ctx, int16_t degrees);
HAL_StatusTypeDef OV5640_SetEffect    (OV5640_Ctx_t *ctx, OV5640_Effect_t effect);

/**
  * @brief  Colour bar test pattern, 0x503D. Generated inside the ISP, so a good
  *         bar proves ISP output -> D-PHY -> receiver -> DCMIPP -> memory with
  *         the pixel array and the optics out of the picture.
  */
HAL_StatusTypeDef OV5640_SetTestPattern(OV5640_Ctx_t *ctx, bool enable);

/*============================================================================*/
/* Manual focus (VCM)                                                         */
/*============================================================================*/

/**
  * @brief  Drive the voice coil motor directly. Datasheet 3.3.
  * @param  target  0..1023. Higher sinks more current and moves the lens
  *                 further from its rest position.
  * @note   Open loop. Closed-loop autofocus needs the OmniVision firmware blob,
  *         which is out of scope - see README section 11.
  */
HAL_StatusTypeDef OV5640_SetFocusTarget(OV5640_Ctx_t *ctx, uint16_t target);

/** @brief Power the VCM driver down, 0x3603[7]. */
HAL_StatusTypeDef OV5640_FocusPowerDown(OV5640_Ctx_t *ctx, bool down);

/*============================================================================*/
/* Atomic multi-register updates (group write, datasheet 2.6)                  */
/*============================================================================*/

/**
  * @brief  Begin buffering writes into a group, to be latched together at the
  *         next frame boundary. Use for exposure + gain pairs.
  * @param  group  0..3
  */
HAL_StatusTypeDef OV5640_GroupBegin (OV5640_Ctx_t *ctx, uint8_t group);
HAL_StatusTypeDef OV5640_GroupEnd   (OV5640_Ctx_t *ctx, uint8_t group);
HAL_StatusTypeDef OV5640_GroupLaunch(OV5640_Ctx_t *ctx, uint8_t group);

/*============================================================================*/
/* Capture (DCMIPP wrappers)                                                  */
/*============================================================================*/

/*
 * PORTING LAYER. Everything above this point is derived from the OV5640
 * datasheet and is independent of your STM32Cube version. The three functions
 * below call into the DCMIPP HAL, whose exact symbol names were NOT verified
 * against an installed CubeH7RS package while this was written. Check them
 * against your stm32h7rsxx_hal_dcmipp.h and RM0477 before relying on them.
 *
 * They are compiled only when OV5640_USE_DCMIPP is defined, so the sensor
 * driver builds cleanly without them.
 */
#ifdef OV5640_USE_DCMIPP

/**
  * @brief  Start a continuous capture into @p buffer on DCMIPP pipe 0.
  * @param  buffer  32-byte aligned if the M7 D-cache is enabled.
  * @param  size    frame size in bytes.
  * @note   Unlike DCMI + DMA there is no 65535-word transfer ceiling: a 5 MP
  *         frame is one destination address. You still have to invalidate the
  *         D-cache before reading, or map the buffer non-cacheable.
  */
HAL_StatusTypeDef OV5640_StartCapture(OV5640_Ctx_t *ctx,
                                      uint8_t *buffer, uint32_t size);

/** @brief Start a single-frame (snapshot) capture. */
HAL_StatusTypeDef OV5640_StartSnapshot(OV5640_Ctx_t *ctx,
                                       uint8_t *buffer, uint32_t size);

/** @brief Stop the DCMIPP pipe. */
HAL_StatusTypeDef OV5640_StopCapture(OV5640_Ctx_t *ctx);

#endif /* OV5640_USE_DCMIPP */

#ifdef __cplusplus
}
#endif

#endif /* OV5640_H */
