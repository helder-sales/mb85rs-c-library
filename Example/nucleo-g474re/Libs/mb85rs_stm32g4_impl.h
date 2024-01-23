#include "main.h"
#include "spi.h"

void WP_Enable(void);
void WP_Disable(void);
void HOLD_Enable(void);
void HOLD_Disable(void);
void CS_Enable(void);
void CS_Disable(void);
void SPI_TransmitBytes(uint8_t *txBuffer, uint8_t bufSizeInBytes);
void SPI_ReceiveBytes(uint8_t *rxBuffer, uint8_t bufSizeInBytes);
