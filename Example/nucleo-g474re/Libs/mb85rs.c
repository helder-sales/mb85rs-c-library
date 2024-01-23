#include "mb85rs.h"

typedef enum MB85RS_OpCode {
    WREN = 0x06,
    WRDI = 0x04,
    RDSR = 0x05,
    WRSR = 0x01,
    READ = 0x03,
    WRITE = 0x02,
    RDID = 0x9F
} MB85RS_OpCode_t;

MB85RS_Config_t mb85rs;

void MB85RS_Init(const MB85RS_Config_t config) {
    mb85rs = config;
    mb85rs.WP_Enable();
    mb85rs.HOLD_Disable();
    mb85rs.CS_Disable();
}

static void MB85RS_WriteOpCode(MB85RS_OpCode_t opCode) {
    mb85rs.SPI_TransmitBytes(&opCode, 1);
}

static void MB85RS_SetWEL(void) {
    MB85RS_OpCode_t opCode = WREN;

    mb85rs.CS_Enable();
    MB85RS_WriteOpCode(opCode);
    mb85rs.CS_Disable();
}

static void MB85RS_ResetWEL(void) {
    MB85RS_OpCode_t opCode = WRDI;

    mb85rs.CS_Enable();
    MB85RS_WriteOpCode(opCode);
    mb85rs.CS_Disable();
}

uint32_t MB85RS_GetRDID(void) {
    uint8_t rdidArray[4] = {0};
    MB85RS_OpCode_t opCode = RDID;

    mb85rs.CS_Enable();
    MB85RS_WriteOpCode(opCode);
    mb85rs.SPI_ReceiveBytes(rdidArray, 4);
    mb85rs.CS_Disable();

    uint32_t rdid = 0;

    for (uint8_t i = 0; i < 4; i++) {
        rdid = (rdid << 8) | rdidArray[i];
    }

    return rdid;
}

void MB85RS_Read(uint16_t address, uint8_t *rxBuffer, uint8_t bufSizeInBytes) {
    MB85RS_OpCode_t opCode = READ;
    uint8_t addressArray[2] = {address >> 8, address & 0xFF};

    mb85rs.CS_Enable();
    MB85RS_WriteOpCode(opCode);
    mb85rs.SPI_TransmitBytes(addressArray, 2);
    mb85rs.SPI_ReceiveBytes(rxBuffer, bufSizeInBytes);
    mb85rs.CS_Disable();
}

void MB85RS_Write(uint16_t address, uint8_t *txBuffer, uint8_t bufSizeInBytes) {
    MB85RS_OpCode_t opCode = WRITE;
    uint8_t addressArray[2] = {address >> 8, address & 0xFF};

    MB85RS_SetWEL();
    mb85rs.CS_Enable();
    MB85RS_WriteOpCode(opCode);
    mb85rs.SPI_TransmitBytes(addressArray, 2);
    mb85rs.SPI_TransmitBytes(txBuffer, bufSizeInBytes);
    mb85rs.CS_Disable();
    MB85RS_ResetWEL();
}

static uint8_t MB85RS_ReadStatusRegister(void) {
    uint8_t statusRegister = 0;
    MB85RS_OpCode_t opCode = RDSR;

    mb85rs.CS_Enable();
    MB85RS_WriteOpCode(opCode);
    mb85rs.SPI_ReceiveBytes(&statusRegister, 1);
    mb85rs.CS_Disable();

    return statusRegister;
}

static void MB85RS_WriteStatusRegister(uint8_t data) {
    MB85RS_OpCode_t opCode = WRSR;

    mb85rs.WP_Disable();
    MB85RS_SetWEL();
    mb85rs.CS_Enable();
    MB85RS_WriteOpCode(opCode);
    mb85rs.SPI_TransmitBytes(&data, 1);
    mb85rs.CS_Disable();
    MB85RS_ResetWEL();
    mb85rs.WP_Enable();
}

void MB85RS_SetWPEN(void) {
    uint8_t wpenBit = 0x80;
    uint8_t statusRegister = MB85RS_ReadStatusRegister();

    statusRegister |= wpenBit;
    MB85RS_WriteStatusRegister(statusRegister);
}

void MB85RS_ResetWPEN(void) {
    uint8_t wpenBit = 0x7E;
    uint8_t statusRegister = MB85RS_ReadStatusRegister();

    statusRegister &= wpenBit;
    MB85RS_WriteStatusRegister(statusRegister);
}

void MB85RS_SetBlockProtect(MB85RS_BlockProtect_t protectMode) {
    uint8_t protectBits = protectMode << 2;
    uint8_t statusRegister = MB85RS_ReadStatusRegister();

    statusRegister &= 0xF2;
    statusRegister |= protectBits;
    MB85RS_WriteStatusRegister(statusRegister);
}

uint8_t MB85RS_ReadBlockProtectStatus(void) {
    uint8_t statusRegister = MB85RS_ReadStatusRegister();
    uint8_t blockProtectBits = (statusRegister >> 2) & 0x03;

    return blockProtectBits;
}
