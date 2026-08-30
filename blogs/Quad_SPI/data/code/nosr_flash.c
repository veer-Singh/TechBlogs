/**
  ******************************************************************************
  * @file    mt25tl01g.c
  * @brief   Component driver for the Micron MT25TL01G 1-Gbit twin-quad NOR
  *          flash, used through the STM32 QUADSPI peripheral in *dual-flash
  *          mode* (two 512-Mbit dies accessed in parallel: 8 data lines).
  *
  *          All addresses / sizes handled here are in the combined address
  *          space (0 .. 0x07FF_FFFF).  The QUADSPI hardware transparently
  *          splits address and data between the two dies, therefore:
  *              - the flash is always driven in 4-byte address mode
  *              - every transfer length passed to HAL is even
  *              - the status / flag bytes come back duplicated (one per die)
  ******************************************************************************
  */

#include "mt25tl01g.h"

/* Single command time-out (ms). */
#define MT25TL01G_CMD_TIMEOUT              (HAL_QSPI_TIMEOUT_DEFAULT_VALUE)

/* Auto-polling match interval (QSPI clock cycles). */
#define MT25TL01G_AUTOPOLLING_INTERVAL    0x10U

/* -------------------------------------------------------------------------- */
/*  Local helpers                                                            */
/* -------------------------------------------------------------------------- */

/* Instructizon line mode for the requested transfer type. */
static uint32_t MT25TL01G_LineMode(MT25TL01G_Transfer_t Mode, uint32_t Phase)
{
  /* Phase: 0 = instruction, 1 = address, 2 = data */
  if (Mode == MT25TL01G_QPI_MODE)
  {
    switch (Phase)
    {
      case 0:  return QSPI_INSTRUCTION_4_LINES;
      case 1:  return QSPI_ADDRESS_4_LINES;
      default: return QSPI_DATA_4_LINES;
    }
  }

  switch (Phase)
  {
    case 0:  return QSPI_INSTRUCTION_1_LINE;
    case 1:  return QSPI_ADDRESS_1_LINE;
    default: return QSPI_DATA_1_LINE;
  }
}

/* Send a command that has no address and no data (RESET, WREN, ...). */
static int32_t MT25TL01G_SendCommand(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode, uint8_t Instruction)
{
  QSPI_CommandTypeDef s_command = {0};

  s_command.InstructionMode       = MT25TL01G_LineMode(Mode, 0);
  s_command.Instruction           = Instruction;
  s_command.AddressMode           = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode     = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles           = 0;
  s_command.DataMode              = QSPI_DATA_NONE;
  s_command.DdrMode               = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle      = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode              = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(Ctx, &s_command, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_OK;
}

/* -------------------------------------------------------------------------- */
/*  Info                                                                     */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_GetFlashInfo(MT25TL01G_Info_t *pInfo)
{
  if (pInfo == NULL)
  {
    return MT25TL01G_ERROR;
  }

  pInfo->FlashSize             = MT25TL01G_FLASH_SIZE;
  pInfo->EraseSectorSize       = MT25TL01G_SECTOR_SIZE;
  pInfo->EraseSectorsNumber    = MT25TL01G_SECTOR_NUMBER;
  pInfo->EraseSubSectorSize    = MT25TL01G_SUBSECTOR_32K_SIZE;
  pInfo->EraseSubSectorNumber  = MT25TL01G_SUBSECTOR_32K_NUMBER;
  pInfo->EraseSubSector1Size   = MT25TL01G_SUBSECTOR_4K_SIZE;
  pInfo->EraseSubSector1Number = MT25TL01G_SUBSECTOR_4K_NUMBER;
  pInfo->ProgPageSize          = MT25TL01G_PAGE_SIZE;
  pInfo->ProgPagesNumber       = MT25TL01G_PAGE_NUMBER;

  return MT25TL01G_OK;
}

/* -------------------------------------------------------------------------- */
/*  Reset                                                                    */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_ResetEnable(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  return MT25TL01G_SendCommand(Ctx, Mode, MT25TL01G_RESET_ENABLE_CMD);
}

int32_t MT25TL01G_ResetMemory(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  return MT25TL01G_SendCommand(Ctx, Mode, MT25TL01G_RESET_MEMORY_CMD);
}

/* -------------------------------------------------------------------------- */
/*  Write enable / disable                                                   */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_WriteEnable(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  QSPI_AutoPollingTypeDef s_config = {0};
  QSPI_CommandTypeDef     s_command = {0};

  if (MT25TL01G_SendCommand(Ctx, Mode, MT25TL01G_WRITE_ENABLE_CMD) != MT25TL01G_OK)
  {
    return MT25TL01G_ERROR;
  }

  /* Poll the status register until WEL is set in *both* dies. */
  s_command.InstructionMode   = MT25TL01G_LineMode(Mode, 0);
  s_command.Instruction       = MT25TL01G_READ_STATUS_REG_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DataMode          = MT25TL01G_LineMode(Mode, 2);
  s_command.NbData            = 2;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  s_config.Match           = (MT25TL01G_SR_WEL << 8) | MT25TL01G_SR_WEL;
  s_config.Mask            = (MT25TL01G_SR_WEL << 8) | MT25TL01G_SR_WEL;
  s_config.MatchMode       = QSPI_MATCH_MODE_AND;
  s_config.StatusBytesSize = 2;
  s_config.Interval        = MT25TL01G_AUTOPOLLING_INTERVAL;
  s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling(Ctx, &s_command, &s_config, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_OK;
}

int32_t MT25TL01G_WriteDisable(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  return MT25TL01G_SendCommand(Ctx, Mode, MT25TL01G_WRITE_DISABLE_CMD);
}

/* -------------------------------------------------------------------------- */
/*  Register access                                                          */
/* -------------------------------------------------------------------------- */
static int32_t MT25TL01G_ReadReg(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode,
                                 uint8_t Instruction, uint8_t *Value)
{
  QSPI_CommandTypeDef s_command = {0};
  uint8_t reg[2] = {0};

  s_command.InstructionMode   = MT25TL01G_LineMode(Mode, 0);
  s_command.Instruction       = Instruction;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DataMode          = MT25TL01G_LineMode(Mode, 2);
  s_command.NbData            = 2;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(Ctx, &s_command, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  if (HAL_QSPI_Receive(Ctx, reg, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }

  /* reg[0] = die 1, reg[1] = die 2 - report their bitwise OR. */
  *Value = (uint8_t)(reg[0] | reg[1]);
  return MT25TL01G_OK;
}

int32_t MT25TL01G_ReadStatusRegister(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode, uint8_t *Value)
{
  return MT25TL01G_ReadReg(Ctx, Mode, MT25TL01G_READ_STATUS_REG_CMD, Value);
}

int32_t MT25TL01G_ReadFlagStatusRegister(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode, uint8_t *Value)
{
  return MT25TL01G_ReadReg(Ctx, Mode, MT25TL01G_READ_FLAG_STATUS_REG_CMD, Value);
}

int32_t MT25TL01G_WriteStatusRegister(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode, uint8_t Value)
{
  QSPI_CommandTypeDef s_command = {0};
  uint8_t reg[2] = { Value, Value };

  s_command.InstructionMode   = MT25TL01G_LineMode(Mode, 0);
  s_command.Instruction       = MT25TL01G_WRITE_STATUS_REG_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DataMode          = MT25TL01G_LineMode(Mode, 2);
  s_command.NbData            = 2;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(Ctx, &s_command, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  if (HAL_QSPI_Transmit(Ctx, reg, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_OK;
}

int32_t MT25TL01G_ClearFlagStatusRegister(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  return MT25TL01G_SendCommand(Ctx, Mode, MT25TL01G_CLEAR_FLAG_STATUS_REG_CMD);
}

/* -------------------------------------------------------------------------- */
/*  Auto-polling: wait until neither die is busy                             */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_AutoPollingMemReady(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  QSPI_CommandTypeDef     s_command = {0};
  QSPI_AutoPollingTypeDef s_config  = {0};

  s_command.InstructionMode   = MT25TL01G_LineMode(Mode, 0);
  s_command.Instruction       = MT25TL01G_READ_STATUS_REG_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DataMode          = MT25TL01G_LineMode(Mode, 2);
  s_command.NbData            = 2;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  /* WIP == 0 on both dies. */
  s_config.Match           = 0x0000;
  s_config.Mask            = (MT25TL01G_SR_WIP << 8) | MT25TL01G_SR_WIP;
  s_config.MatchMode       = QSPI_MATCH_MODE_AND;
  s_config.StatusBytesSize = 2;
  s_config.Interval        = MT25TL01G_AUTOPOLLING_INTERVAL;
  s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling(Ctx, &s_command, &s_config, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_OK;
}

/* -------------------------------------------------------------------------- */
/*  Volatile configuration register: set the FAST-READ dummy-cycle count     */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_ConfigureDummyCycles(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  QSPI_CommandTypeDef s_command = {0};
  uint8_t reg[2] = { MT25TL01G_VCR_VALUE, MT25TL01G_VCR_VALUE };

  if (MT25TL01G_WriteEnable(Ctx, Mode) != MT25TL01G_OK)
  {
    return MT25TL01G_ERROR;
  }

  s_command.InstructionMode   = MT25TL01G_LineMode(Mode, 0);
  s_command.Instruction       = MT25TL01G_WRITE_VOL_CFG_REG_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DataMode          = MT25TL01G_LineMode(Mode, 2);
  s_command.NbData            = 2;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(Ctx, &s_command, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  if (HAL_QSPI_Transmit(Ctx, reg, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_AutoPollingMemReady(Ctx, Mode);
}

/* -------------------------------------------------------------------------- */
/*  4-byte address mode                                                      */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_Enter4BytesAddressMode(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  if (MT25TL01G_WriteEnable(Ctx, Mode) != MT25TL01G_OK)
  {
    return MT25TL01G_ERROR;
  }
  if (MT25TL01G_SendCommand(Ctx, Mode, MT25TL01G_ENTER_4_BYTE_ADDR_MODE_CMD) != MT25TL01G_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_AutoPollingMemReady(Ctx, Mode);
}

int32_t MT25TL01G_Exit4BytesAddressMode(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  if (MT25TL01G_WriteEnable(Ctx, Mode) != MT25TL01G_OK)
  {
    return MT25TL01G_ERROR;
  }
  if (MT25TL01G_SendCommand(Ctx, Mode, MT25TL01G_EXIT_4_BYTE_ADDR_MODE_CMD) != MT25TL01G_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_AutoPollingMemReady(Ctx, Mode);
}

/* -------------------------------------------------------------------------- */
/*  QPI (4-4-4) protocol                                                     */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_EnterQPIMode(QSPI_HandleTypeDef *Ctx)
{
  return MT25TL01G_SendCommand(Ctx, MT25TL01G_SPI_MODE, MT25TL01G_ENTER_QUAD_CMD);
}

int32_t MT25TL01G_ExitQPIMode(QSPI_HandleTypeDef *Ctx)
{
  return MT25TL01G_SendCommand(Ctx, MT25TL01G_QPI_MODE, MT25TL01G_EXIT_QUAD_CMD);
}

/* -------------------------------------------------------------------------- */
/*  Read ID                                                                  */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_ReadID(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode, uint8_t *ID)
{
  QSPI_CommandTypeDef s_command = {0};

  s_command.InstructionMode   = MT25TL01G_LineMode(Mode, 0);
  s_command.Instruction       = MT25TL01G_MULTIPLE_IO_READ_ID_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DataMode          = MT25TL01G_LineMode(Mode, 2);
  s_command.NbData            = MT25TL01G_ID_LENGTH; /* 3 bytes x 2 dies */
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(Ctx, &s_command, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  if (HAL_QSPI_Receive(Ctx, ID, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_OK;
}

/* -------------------------------------------------------------------------- */
/*  Read (4-byte quad I/O fast read, STR)                                    */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_Read(QSPI_HandleTypeDef *Ctx, uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
  QSPI_CommandTypeDef s_command = {0};

  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = MT25TL01G_4_BYTE_QUAD_INOUT_FAST_READ_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.Address           = ReadAddr;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = MT25TL01G_DUMMY_CYCLES_READ_QUAD;
  s_command.DataMode          = QSPI_DATA_4_LINES;
  s_command.NbData            = Size;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(Ctx, &s_command, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  if (HAL_QSPI_Receive(Ctx, pData, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_OK;
}

/* -------------------------------------------------------------------------- */
/*  Page program (4-byte quad input fast program) - Size <= MT25TL01G_PAGE_SIZE
 *  and must not cross a combined-page (512 B) boundary.                      */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_PageProgram(QSPI_HandleTypeDef *Ctx, const uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
  QSPI_CommandTypeDef s_command = {0};

  if (MT25TL01G_WriteEnable(Ctx, MT25TL01G_SPI_MODE) != MT25TL01G_OK)
  {
    return MT25TL01G_ERROR;
  }

  /* 0x34 = 4-BYTE QUAD INPUT FAST PROGRAM: 1-1-4 in extended SPI
   * (instruction 1 line, ADDRESS 1 line, data 4 lines).  The 1-4-4 variant
   * is a different opcode (0x3E). */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = MT25TL01G_4_BYTE_QUAD_IN_FAST_PROG_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.Address           = WriteAddr;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DataMode          = QSPI_DATA_4_LINES;
  s_command.NbData            = Size;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(Ctx, &s_command, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  if (HAL_QSPI_Transmit(Ctx, (uint8_t *)pData, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_AutoPollingMemReady(Ctx, MT25TL01G_SPI_MODE);
}

/* -------------------------------------------------------------------------- */
/*  Erase                                                                    */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_BlockErase(QSPI_HandleTypeDef *Ctx, uint32_t Address, MT25TL01G_Erase_t Size)
{
  QSPI_CommandTypeDef s_command = {0};

  if (Size == MT25TL01G_ERASE_CHIP)
  {
    return MT25TL01G_ChipErase(Ctx);
  }

  if (MT25TL01G_WriteEnable(Ctx, MT25TL01G_SPI_MODE) != MT25TL01G_OK)
  {
    return MT25TL01G_ERROR;
  }

  switch (Size)
  {
    case MT25TL01G_ERASE_4K:
      s_command.Instruction = MT25TL01G_4_BYTE_SUBSECTOR_ERASE_4K_CMD;
      break;
    case MT25TL01G_ERASE_32K:
      s_command.Instruction = MT25TL01G_4_BYTE_SUBSECTOR_ERASE_32K_CMD;
      break;
    case MT25TL01G_ERASE_64K:
    default:
      s_command.Instruction = MT25TL01G_4_BYTE_SECTOR_ERASE_64K_CMD;
      break;
  }

  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.Address           = Address;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(Ctx, &s_command, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_OK; /* caller polls with MT25TL01G_AutoPollingMemReady */
}

int32_t MT25TL01G_ChipErase(QSPI_HandleTypeDef *Ctx)
{
  QSPI_CommandTypeDef s_command = {0};

  if (MT25TL01G_WriteEnable(Ctx, MT25TL01G_SPI_MODE) != MT25TL01G_OK)
  {
    return MT25TL01G_ERROR;
  }

  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = MT25TL01G_DIE_ERASE_CMD;       /* C7h: whole device */
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(Ctx, &s_command, MT25TL01G_CMD_TIMEOUT) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_OK; /* caller polls with MT25TL01G_AutoPollingMemReady */
}

/* -------------------------------------------------------------------------- */
/*  Memory-mapped mode (STR, 4-byte quad I/O read)                           */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_EnableMemoryMappedModeSTR(QSPI_HandleTypeDef *Ctx)
{
  QSPI_CommandTypeDef      s_command = {0};
  QSPI_MemoryMappedTypeDef s_mem_mapped_cfg = {0};

  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = MT25TL01G_4_BYTE_QUAD_INOUT_FAST_READ_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = MT25TL01G_DUMMY_CYCLES_READ_QUAD;
  s_command.DataMode          = QSPI_DATA_4_LINES;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
  s_mem_mapped_cfg.TimeOutPeriod     = 0;

  if (HAL_QSPI_MemoryMapped(Ctx, &s_command, &s_mem_mapped_cfg) != HAL_OK)
  {
    return MT25TL01G_ERROR;
  }
  return MT25TL01G_OK;
}

/* -------------------------------------------------------------------------- */
/*  Deep power down                                                          */
/* -------------------------------------------------------------------------- */
int32_t MT25TL01G_EnterDeepPowerDown(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  return MT25TL01G_SendCommand(Ctx, Mode, MT25TL01G_ENTER_DEEP_POWER_DOWN_CMD);
}

int32_t MT25TL01G_LeaveDeepPowerDown(QSPI_HandleTypeDef *Ctx, MT25TL01G_Transfer_t Mode)
{
  return MT25TL01G_SendCommand(Ctx, Mode, MT25TL01G_RELEASE_FROM_DEEP_POWER_DOWN_CMD);
}
