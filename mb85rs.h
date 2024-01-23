#ifndef C1B73D4C_D362_4E42_9775_72E39BCE5722
#define C1B73D4C_D362_4E42_9775_72E39BCE5722

#include "stdint.h"

typedef struct MB85RS_Config {
    void (*WP_Enable)(void);
    void (*WP_Disable)(void);
    void (*HOLD_Enable)(void);
    void (*HOLD_Disable)(void);
    void (*CS_Enable)(void);
    void (*CS_Disable)(void);
    void (*SPI_TransmitBytes)(uint8_t *txBuffer, uint8_t bufSizeInBytes);
    void (*SPI_ReceiveBytes)(uint8_t *rxBuffer, uint8_t bufSizeInBytes);
} MB85RS_Config_t;
typedef enum MB85RS_BlockProtect {
    NONE = 0x00,
    UPPER_QUARTER = 0x01,
    UPPER_HALF = 0x02,
    ALL = 0x03
} MB85RS_BlockProtect_t;

void MB85RS_Init(MB85RS_Config_t config);
void HOLD_Enable(void);
void HOLD_Disable(void);
uint32_t MB85RS_GetRDID(void);
void MB85RS_Read(uint16_t address, uint8_t *rxBuffer, uint8_t bufSizeInBytes);
void MB85RS_Write(uint16_t address, uint8_t *txBuffer, uint8_t bufSizeInBytes);
void MB85RS_SetWPEN(void);
void MB85RS_ResetWPEN(void);
void MB85RS_SetBlockProtect(MB85RS_BlockProtect_t protectMode);
uint8_t MB85RS_ReadBlockProtectStatus(void);

#endif /* C1B73D4C_D362_4E42_9775_72E39BCE5722 */
