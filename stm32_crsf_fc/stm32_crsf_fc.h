#ifndef STM32_CRSF_FC_H
#define STM32_CRSF_FC_H


#include "usart.h"

#ifndef STM32_CRSF_RH_H
// DEST
// #define CRSF_ADDRESS_CRSF_TRANSMITTER            0xEE
// #define CRSF_ADDRESS_RADIO_TRANSMITTER           0xEA
#define CRSF_ADDRESS_FLIGHT_CONTROLLER          0xC8
#define CRSF_ADDRESS_CRSF_RECEIVER              0xEC

// LEN
#define CRSF_LEN_MAX                            62

// TYPE
// TODO: Comment #define that cannot be used in the flight controller
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

typedef struct {
    UART_HandleTypeDef *p_prt;
    crsf_default_t rx;
    volatile uint8_t itr_flag; 
} crsf_fc_t;


/* 
 * @brief Start fucntoin for filling the basic CRSF FC struct 
 * !! WARNING !! This realization uses interrupts for receiving tha ALL CRSF data
 *
 * @param p_uart Pointer to the UART instance
 * 
 * return None 
 */
void begin(UART_HandleTypeDef *p_uart);

/* 
 * @brief UART receive interrupt handler
 * !! WARNING !! It should be used for receiving with interrupts
 *
 * @param p_crsf Pointer to the basic CRSF FC struct
 * 
 * return None 
 */
void uart_rx_interrupt_handler(crsf_fc_t *p_crsf);

/*
 * @brief Checking the buffer for actual data
 *
 * @return Checking status: 1 if data is available, 0 otherwise
 */
uint8_t available_pkt(crsf_fc_t *p_crsf);

/*
 * @brief Getting the RC values from remote input data
 *
 * @param p_crsf Pointer to the basic CRSF FC struct
 * @param p_channels Pointer to the channels struct
 * @param to_fc_range Flag to FC range converting
 */
uint8_t get_rc_channels(crsf_fc_t *p_crsf, crsf_rc_channels_t *p_channels, uint8_t to_fc_range);

#endif
