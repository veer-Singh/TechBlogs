/**
  ******************************************************************************
  * @file    mt25tl01g.h
  * @brief   Component driver for the Micron MT25TL01G 1-Gbit "Twin-Quad"
  *          serial NOR flash (2 x 512-Mbit dies in one package, shared CLK and
  *          CS#, independent 4-bit data buses).
  *
  *          Datasheet : Drivers/Bsp_driver/MT25TL01GBBB8ESF-0AAT.pdf  (Rev. F)
  *
  *          This layer only knows the flash: it issues command / address /
  *          data phases through a HAL QSPI handle.  All geometry constants
  *          below are given for the STM32 QUADSPI *dual-flash mode* (DFM), i.e.
  *          the two dies seen as a single memory:
  *
  *              page          = 2 x 256 B   = 512 B
  *              4KB subsector = 2 x 4  KB   = 8   KB
  *              32KB subsector= 2 x 32 KB   = 64  KB
  *              64KB sector   = 2 x 64 KB   = 128 KB
  *              total         = 2 x 64 MB   = 128 MB   (0x0800_0000)
  *
  *          In DFM the QUADSPI hardware halves every address and interleaves
  *          the data bytes (even -> flash 1, odd -> flash 2) automatically, so
  *          the caller always works with the combined address space.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MT25TL01G_H
#define MT25TL01G_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "stm32h7xx_hal.h"

/* Return codes ----------------------------------------------------------------*/
#define MT25TL01G_OK                        (0)
#define MT25TL01G_ERROR                     (-1)

/* Device geometry (dual-flash / combined view) ------------------------------ */
#define MT25TL01G_FLASH_SIZE               0x8000000U   /* 1 Gbit  => 128 MByte  */
#define MT25TL01G_DIE_SIZE                 0x4000000U   /* one 512-Mbit die (64 MB) */

#define MT25TL01G_SECTOR_SIZE             0x20000U      /* 2 x 64 KB              */
#define MT25TL01G_SECTOR_NUMBER           1024U

#define MT25TL01G_SUBSECTOR_32K_SIZE     0x10000U       /* 2 x 32 KB             */
#define MT25TL01G_SUBSECTOR_32K_NUMBER   2048U

#define MT25TL01G_SUBSECTOR_4K_SIZE      0x2000U        /* 2 x 4 KB              */
#define MT25TL01G_SUBSECTOR_4K_NUMBER    16384U

#define MT25TL01G_PAGE_SIZE              0x200U         /* 2 x 256 B             */
#define MT25TL01G_PAGE_NUMBER           262144U

/* Timings (worst case, both dies, from datasheet AC characteristics) -------- */
#define MT25TL01G_BULK_ERASE_MAX_TIME       460000U     /* ms                   */
#define MT25TL01G_SECTOR_ERASE_MAX_TIME     1000U       /* ms  (64 KB)          */
#define MT25TL01G_SUBSECTOR_32K_ERASE_MAX_TIME 1000U    /* ms                   */
#define MT25TL01G_SUBSECTOR_4K_ERASE_MAX_TIME  400U     /* ms                   */
#define MT25TL01G_PAGE_PROG_MAX_TIME        2U          /* ms                   */

/* Memory-mapped base address (STM32H7 QUADSPI) ---------------------------- */
#define MT25TL01G_MMP_BASE_ADDRESS         0x90000000U

/* JEDEC / device identification (per die) --------------------------------- */
#define MT25TL01G_MANUFACTURER_ID           0x20U       /* Micron               */
#define MT25TL01G_DEVICE_TYPE_3V            0xBAU
#define MT25TL01G_DEVICE_CAPACITY_512M      0x20U

/* READ ID returns these six bytes in dual-flash mode (die1 | die2 pattern). */
#define MT25TL01G_ID_LENGTH                 6U

/* ===========================================================================
 *  Command set  (Datasheet Table 20)
 * ===========================================================================*/
/* Software reset */
#define MT25TL01G_RESET_ENABLE_CMD                       0x66U
#define MT25TL01G_RESET_MEMORY_CMD                       0x99U

/* Identification */
#define MT25TL01G_READ_ID_CMD                            0x9EU
#define MT25TL01G_READ_ID_CMD2                           0x9FU
#define MT25TL01G_MULTIPLE_IO_READ_ID_CMD                0xAFU
#define MT25TL01G_READ_SERIAL_FLASH_DISCO_PARAM_CMD      0x5AU

/* Register access */
#define MT25TL01G_READ_STATUS_REG_CMD                    0x05U
#define MT25TL01G_WRITE_STATUS_REG_CMD                   0x01U
#define MT25TL01G_READ_FLAG_STATUS_REG_CMD               0x70U
#define MT25TL01G_CLEAR_FLAG_STATUS_REG_CMD              0x50U
#define MT25TL01G_READ_NONVOL_CFG_REG_CMD                0xB5U
#define MT25TL01G_WRITE_NONVOL_CFG_REG_CMD               0xB1U
#define MT25TL01G_READ_VOL_CFG_REG_CMD                   0x85U
#define MT25TL01G_WRITE_VOL_CFG_REG_CMD                  0x81U
#define MT25TL01G_READ_ENH_VOL_CFG_REG_CMD               0x65U
#define MT25TL01G_WRITE_ENH_VOL_CFG_REG_CMD              0x61U
#define MT25TL01G_READ_EXT_ADDR_REG_CMD                  0xC8U
#define MT25TL01G_WRITE_EXT_ADDR_REG_CMD                 0xC5U

/* Write enable / disable */
#define MT25TL01G_WRITE_ENABLE_CMD                       0x06U
#define MT25TL01G_WRITE_DISABLE_CMD                      0x04U

/* Read (3-byte address) */
#define MT25TL01G_READ_CMD                               0x03U
#define MT25TL01G_FAST_READ_CMD                          0x0BU
#define MT25TL01G_QUAD_OUT_FAST_READ_CMD                 0x6BU
#define MT25TL01G_QUAD_INOUT_FAST_READ_CMD               0xEBU
#define MT25TL01G_DTR_QUAD_INOUT_FAST_READ_CMD           0xEDU

/* Read (4-byte address) */
#define MT25TL01G_4_BYTE_READ_CMD                        0x13U
#define MT25TL01G_4_BYTE_FAST_READ_CMD                   0x0CU
#define MT25TL01G_4_BYTE_QUAD_OUT_FAST_READ_CMD          0x6CU
#define MT25TL01G_4_BYTE_QUAD_INOUT_FAST_READ_CMD        0xECU
#define MT25TL01G_4_BYTE_DTR_QUAD_INOUT_FAST_READ_CMD    0xEEU

/* Program (3-byte address) */
#define MT25TL01G_PAGE_PROG_CMD                          0x02U
#define MT25TL01G_QUAD_IN_FAST_PROG_CMD                  0x32U
#define MT25TL01G_EXT_QUAD_IN_FAST_PROG_CMD              0x38U

/* Program (4-byte address) */
#define MT25TL01G_4_BYTE_PAGE_PROG_CMD                   0x12U
#define MT25TL01G_4_BYTE_QUAD_IN_FAST_PROG_CMD           0x34U
#define MT25TL01G_4_BYTE_QUAD_IN_EXT_FAST_PROG_CMD       0x3EU

/* Erase (3-byte address) */
#define MT25TL01G_SUBSECTOR_ERASE_4K_CMD                 0x20U
#define MT25TL01G_SUBSECTOR_ERASE_32K_CMD               0x52U
#define MT25TL01G_SECTOR_ERASE_64K_CMD                  0xD8U
#define MT25TL01G_DIE_ERASE_CMD                         0xC7U   /* 60h alias    */
#define MT25TL01G_DIE_ERASE_CMD2                        0x60U

/* Erase (4-byte address) */
#define MT25TL01G_4_BYTE_SUBSECTOR_ERASE_4K_CMD          0x21U
#define MT25TL01G_4_BYTE_SUBSECTOR_ERASE_32K_CMD         0x5CU
#define MT25TL01G_4_BYTE_SECTOR_ERASE_64K_CMD            0xDCU

/* Suspend / resume */
#define MT25TL01G_PROG_ERASE_SUSPEND_CMD                 0x75U
#define MT25TL01G_PROG_ERASE_RESUME_CMD                  0x7AU

/* 4-byte address mode */
#define MT25TL01G_ENTER_4_BYTE_ADDR_MODE_CMD             0xB7U
#define MT25TL01G_EXIT_4_BYTE_ADDR_MODE_CMD              0xE9U

/* Quad protocol (QPI) */
#define MT25TL01G_ENTER_QUAD_CMD                         0x35U
#define MT25TL01G_EXIT_QUAD_CMD                          0xF5U

/* Deep power down */
#define MT25TL01G_ENTER_DEEP_POWER_DOWN_CMD              0xB9U
#define MT25TL01G_RELEASE_FROM_DEEP_POWER_DOWN_CMD       0xABU

/* ===========================================================================
 *  Status register (Datasheet Table 3)
 * ===========================================================================*/
#define MT25TL01G_SR_WIP                    0x01U   /* write in progress          */
#define MT25TL01G_SR_WEL                    0x02U   /* write enable latch         */
#define MT25TL01G_SR_BP0                    0x04U   /* block protect              */
#define MT25TL01G_SR_BP1                    0x08U
#define MT25TL01G_SR_BP2                    0x10U
#define MT25TL01G_SR_TB                     0x20U   /* top / bottom               */
#define MT25TL01G_SR_BP3                    0x40U
#define MT25TL01G_SR_SRWD                   0x80U   /* status reg write disable   */

/* ===========================================================================
 *  Flag status register (Datasheet Table 5)
 * ===========================================================================*/
#define MT25TL01G_FSR_4BYTE                 0x01U   /* 1 = 4-byte addressing      */
#define MT25TL01G_FSR_PROTECTION            0x02U   /* prot. error                */
#define MT25TL01G_FSR_PROGRAM_SUSPEND       0x04U
#define MT25TL01G_FSR_PROGRAM_ERROR         0x10U
#define MT25TL01G_FSR_ERASE_ERROR          0x20U
#define MT25TL01G_FSR_ERASE_SUSPEND        0x40U
#define MT25TL01G_FSR_READY                0x80U   /* 1 = P/E controller ready   */

/* ===========================================================================
 *  Volatile configuration register (Datasheet Table 8)
 *  bits [7:4] = number of dummy clock cycles for FAST READ commands
 * ===========================================================================*/
#define MT25TL01G_DUMMY_CYCLES_READ_QUAD    8U
/* VCR: 8 dummy cycles, XIP disabled, continuous wrap */
#define MT25TL01G_VCR_VALUE                 0x8BU

/* Types ------------------------------------------------------------------- */
typedef enum
{
  MT25TL01G_SPI_MODE = 0,   /* 1-line command / address / data (extended SPI) */
  MT25TL01G_QPI_MODE        /* 4-line command / address / data (QPI)          */
} MT25TL01G_Transfer_t;

typedef enum
{
  MT25TL01G_ERASE_4K = 0,
  MT25TL01G_ERASE_32K,
  MT25TL01G_ERASE_64K,
  MT25TL01G_ERASE_CHIP
} MT25TL01G_Erase_t;

typedef struct
{
  uint32_t FlashSize;
  uint32_t EraseSectorSize;       /* 64 KB sector (x2) */
  uint32_t EraseSectorsNumber;
  uint32_t EraseSubSectorSize;    /* 32 KB subsector (x2) */
  uint32_t EraseSubSectorNumber;
  uint32_t EraseSubSector1Size;   /* 4 KB subsector (x2) */
  uint32_t EraseSubSector1Number;
  uint32_t ProgPageSize;
  uint32_t ProgPagesNumber;
} MT25TL01G_Info_t;

/* Exported functions ----------------------------------------------------- */
int32_t MT25TL01G_GetFlashInfo(MT25TL01G_Info_t *pInfo);

int32_t MT25TL01G_ResetEnable(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);
int32_t MT25TL01G_ResetMemory(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);

int32_t MT25TL01G_WriteEnable(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);
int32_t MT25TL01G_WriteDisable(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);

int32_t MT25TL01G_ReadStatusRegister(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode, uint8_t *Value);
int32_t MT25TL01G_WriteStatusRegister(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode, uint8_t Value);
int32_t MT25TL01G_ReadFlagStatusRegister(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode, uint8_t *Value);
int32_t MT25TL01G_ClearFlagStatusRegister(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);

int32_t MT25TL01G_AutoPollingMemReady(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);

int32_t MT25TL01G_ConfigureDummyCycles(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);

int32_t MT25TL01G_Enter4BytesAddressMode(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);
int32_t MT25TL01G_Exit4BytesAddressMode(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);

int32_t MT25TL01G_EnterQPIMode(QSPI_HandleTypeDef *Ctx);
int32_t MT25TL01G_ExitQPIMode(QSPI_HandleTypeDef *Ctx);

int32_t MT25TL01G_ReadID(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode, uint8_t *ID);

int32_t MT25TL01G_Read(QSPI_HandleTypeDef *Ctx, uint8_t *pData, uint32_t ReadAddr, uint32_t Size);
int32_t MT25TL01G_PageProgram(QSPI_HandleTypeDef *Ctx, const uint8_t *pData, uint32_t WriteAddr, uint32_t Size);

int32_t MT25TL01G_BlockErase(QSPI_HandleTypeDef *Ctx, uint32_t Address, MT25TL01G_Erase_t Size);
int32_t MT25TL01G_ChipErase(QSPI_HandleTypeDef *Ctx);

int32_t MT25TL01G_EnableMemoryMappedModeSTR(QSPI_HandleTypeDef *Ctx);

int32_t MT25TL01G_EnterDeepPowerDown(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);
int32_t MT25TL01G_LeaveDeepPowerDown(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode);

#ifdef __cplusplus
}
#endif

#endif /* MT25TL01G_H */
