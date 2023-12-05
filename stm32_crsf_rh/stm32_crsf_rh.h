#ifndef STM32_CRSF_RH_H
#define STM32_CRSF_RH_H

#include "usart.h"

#ifndef STM32_CRSF_FC_H
// DEST
#define CRSF_ADDRESS_CRSF_TRANSMITTER           0xEE
#define CRSF_ADDRESS_RADIO_TRANSMITTER          0xEA
#define CRSF_ADDRESS_FLIGHT_CONTROLLER          0xC8
#define CRSF_ADDRESS_CRSF_RECEIVER              0xEC

// LEN
#define CRSF_LEN_MAX                            62

// TYPE
#define CRSF_FRAMETYPE_RC_CHANNELS              0x16
#define CRSF_FRAMETYPE_DEVICE_PING              0x28
#define CRSF_FRAMETYPE_DEVICE_INFO              0x29
#define CRSF_FRAMETYPE_PARAMETER_SETTINGS_ENTRY 0x2B
#define CRSF_FRAMETYPE_PARAMETER_READ           0x2C
#define CRSF_FRAMETYPE_PARAMETER_WRITE          0x2D
#define CRSF_FRAMETYPE_COMMAND                  0x32


typedef struct {
    uint8_t dest;
    uint8_t len;
    uint8_t type;
    uint8_t payload[CRSF_LEN_MAX - 3]; // including crc8 byte
} crsf_default_t;

typedef struct {
    uint16_t ch[16];
} crsf_rc_channels_t;

#endif

/*
 * @brief Sending channels to the flight controller
 *
 * Function process the input channels and transmit data via UART to the external radio-module.
 * !! WARNING!! Function uses interrupt on UART sending (Tx).
 *
 * @param channels Channels values for sending to the flight controller
 *
 * @return Data sending status
 */
HAL_StatusTypeDef send_rc_channels(UART_HandleTypeDef *p_uart, crsf_rc_channels_t *p_channels);
#endif
