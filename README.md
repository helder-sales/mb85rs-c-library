# mb85rs-c-library

A C library to control an MB85RS FRAM with SPI communication

## Features

- Platform agnostic: create your own implementation of SPI and GPIOs
- Write operation
- Read operation
- Set protection bits
- Read the device ID
- Control over the ~WP and ~HOLD lines

## How to use

An example for the `NUCLEO-G474RE` board from STMicroelectronics is available in the `Examples` folder (tested with `MB85RS16`)

## Initializing the library

```c
const MB85RS_Config_t config = {
    .WP_Enable = WP_Enable, // Your custom implementation of WP_Enable
    .WP_Disable = WP_Disable, // Your custom implementation of WP_Disable
    .HOLD_Enable = HOLD_Enable, // Your custom implementation of HOLD_Enable
    .HOLD_Disable = HOLD_Disable, // Your custom implementation of HOLD_Disable
    .CS_Enable = CS_Enable, // Your custom implementation of CS_Enable
    .CS_Disable = CS_Disable, // Your custom implementation of CS_Disable
    .SPI_TransmitBytes = SPI_TransmitBytes, // Your custom implementation of SPI_TransmitBytes
    .SPI_ReceiveBytes = SPI_ReceiveBytes, // Your custom implementation of SPI_ReceiveBytes
};

MB85RS_Init(config); // Initialize the library with your device-specific implementations

```

### Reading the device ID

```c
uint32_t rdid = MB85RS_GetRDID(); // Get the device ID
```

### Setting the block protection

```c
MB85RS_SetBlockProtect(NONE); // Disable the protection for all blocks
uint32_t sr = MB85RS_ReadBlockProtectStatus(); // Read the current protection status
```

### Writing to a memory address

```c
uint8_t txData[4] = {0xAB, 0xCD, 0xEF, 0x12}; // Buffer to send data
uint16_t address = 0x03F2; // Address for writing the data

MB85RS_Write(address, txData, 4); // Write to a memory address
```

### Reading from a memory address

```c
uint8_t rxData[4] = {0}; // Buffer to receive data
uint16_t address = 0x03F2; // Address for reading the data

MB85RS_Read(address, rxData, 4); // Read from a memory address
```
