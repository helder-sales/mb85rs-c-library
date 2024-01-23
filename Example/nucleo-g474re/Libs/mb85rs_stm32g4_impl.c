#include "mb85rs_stm32g4_impl.h"

void WP_Enable(void) {
    HAL_GPIO_WritePin(WP_GPIO_Port, WP_Pin, GPIO_PIN_RESET);
}

void WP_Disable(void) {
    HAL_GPIO_WritePin(WP_GPIO_Port, WP_Pin, GPIO_PIN_SET);
}

void HOLD_Enable(void) {
    HAL_GPIO_WritePin(HOLD_GPIO_Port, HOLD_Pin, GPIO_PIN_RESET);
}

void HOLD_Disable(void) {
    HAL_GPIO_WritePin(HOLD_GPIO_Port, HOLD_Pin, GPIO_PIN_SET);
}

void CS_Enable(void) {
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
}

void CS_Disable(void) {
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

void SPI_TransmitBytes(uint8_t *txBuffer, uint8_t bufSizeInBytes) {
    HAL_SPI_Transmit(&hspi2, txBuffer, bufSizeInBytes, HAL_MAX_DELAY);
}

void SPI_ReceiveBytes(uint8_t *rxBuffer, uint8_t bufSizeInBytes) {
    HAL_SPI_Receive(&hspi2, rxBuffer, bufSizeInBytes, HAL_MAX_DELAY);
}
