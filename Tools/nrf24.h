/**
 * @author  Pablo Reyes Robles
 * @email   pablo.reyesr@alumnos.usm.cl
 * @version v1.0
@verbatim
   ----------------------------------------------------------------------
   Created by LonelyWolf. https://github.com/LonelyWolf/stm32
   Mod by Sysmic Robotics, 2019
   ----------------------------------------------------------------------
@endverbatim
 */

#ifndef __NRF24_H__
#define __NRF24_H__

/* Low level functions (hardware depended) */
//#include "nrf24_hal.h"
#include "stm32f7xx_hal.h"

/* nRF24L0 instruction definitions */
#define nRF24_CMD_R_REGISTER       (uint8_t)0x00 // Register read
#define nRF24_CMD_W_REGISTER       (uint8_t)0x20 // Register write
#define nRF24_CMD_R_RX_PAYLOAD     (uint8_t)0x61 // Read RX payload
#define nRF24_CMD_W_TX_PAYLOAD     (uint8_t)0xA0 // Write TX payload
#define nRF24_CMD_FLUSH_TX         (uint8_t)0xE1 // Flush TX FIFO
#define nRF24_CMD_FLUSH_RX         (uint8_t)0xE2 // Flush RX FIFO
#define nRF24_CMD_REUSE_TX_PL      (uint8_t)0xE3 // Reuse TX payload
#define nRF24_CMD_LOCK_UNLOCK      (uint8_t)0x50 // Lock/unlock exclusive features
#define nRF24_CMD_NOP              (uint8_t)0xFF // No operation (used for reading status register)

/* nRF24L0 register definitions */
#define nRF24_REG_CONFIG           (uint8_t)0x00 // Configuration register
#define nRF24_REG_EN_AA            (uint8_t)0x01 // Enable "Auto acknowledgment"
#define nRF24_REG_EN_RXADDR        (uint8_t)0x02 // Enable RX addresses
#define nRF24_REG_SETUP_AW         (uint8_t)0x03 // Setup of address widths
#define nRF24_REG_SETUP_RETR       (uint8_t)0x04 // Setup of automatic retransmit
#define nRF24_REG_RF_CH            (uint8_t)0x05 // RF channel
#define nRF24_REG_RF_SETUP         (uint8_t)0x06 // RF setup register
#define nRF24_REG_STATUS           (uint8_t)0x07 // Status register
#define nRF24_REG_OBSERVE_TX       (uint8_t)0x08 // Transmit observe register
#define nRF24_REG_RPD              (uint8_t)0x09 // Received power detector
#define nRF24_REG_RX_ADDR_P0       (uint8_t)0x0A // Receive address data pipe 0
#define nRF24_REG_RX_ADDR_P1       (uint8_t)0x0B // Receive address data pipe 1
#define nRF24_REG_RX_ADDR_P2       (uint8_t)0x0C // Receive address data pipe 2
#define nRF24_REG_RX_ADDR_P3       (uint8_t)0x0D // Receive address data pipe 3
#define nRF24_REG_RX_ADDR_P4       (uint8_t)0x0E // Receive address data pipe 4
#define nRF24_REG_RX_ADDR_P5       (uint8_t)0x0F // Receive address data pipe 5
#define nRF24_REG_TX_ADDR          (uint8_t)0x10 // Transmit address
#define nRF24_REG_RX_PW_P0         (uint8_t)0x11 // Number of bytes in RX payload in data pipe 0
#define nRF24_REG_RX_PW_P1         (uint8_t)0x12 // Number of bytes in RX payload in data pipe 1
#define nRF24_REG_RX_PW_P2         (uint8_t)0x13 // Number of bytes in RX payload in data pipe 2
#define nRF24_REG_RX_PW_P3         (uint8_t)0x14 // Number of bytes in RX payload in data pipe 3
#define nRF24_REG_RX_PW_P4         (uint8_t)0x15 // Number of bytes in RX payload in data pipe 4
#define nRF24_REG_RX_PW_P5         (uint8_t)0x16 // Number of bytes in RX payload in data pipe 5
#define nRF24_REG_FIFO_STATUS      (uint8_t)0x17 // FIFO status register
#define nRF24_REG_DYNPD            (uint8_t)0x1C // Enable dynamic payload length
#define nRF24_REG_FEATURE          (uint8_t)0x1D // Feature register

/* Register bits definitions */
#define nRF24_CONFIG_PRIM_RX       (uint8_t)0x01 // PRIM_RX bit in CONFIG register
#define nRF24_CONFIG_PWR_UP        (uint8_t)0x02 // PWR_UP bit in CONFIG register
#define nRF24_FLAG_RX_DR           (uint8_t)0x40 // RX_DR bit (data ready RX FIFO interrupt)
#define nRF24_FLAG_TX_DS           (uint8_t)0x20 // TX_DS bit (data sent TX FIFO interrupt)
#define nRF24_FLAG_MAX_RT          (uint8_t)0x10 // MAX_RT bit (maximum number of TX retransmits interrupt)

/* Register masks definitions */
#define nRF24_MASK_REG_MAP         (uint8_t)0x1F // Mask bits[4:0] for CMD_RREG and CMD_WREG commands
#define nRF24_MASK_CRC             (uint8_t)0x0C // Mask for CRC bits [3:2] in CONFIG register
#define nRF24_MASK_STATUS_IRQ      (uint8_t)0x70 // Mask for all IRQ bits in STATUS register
#define nRF24_MASK_RF_PWR          (uint8_t)0x06 // Mask RF_PWR[2:1] bits in RF_SETUP register
#define nRF24_MASK_RX_P_NO         (uint8_t)0x0E // Mask RX_P_NO[3:1] bits in STATUS register
#define nRF24_MASK_DATARATE        (uint8_t)0x28 // Mask RD_DR_[5,3] bits in RF_SETUP register
#define nRF24_MASK_EN_RX           (uint8_t)0x3F // Mask ERX_P[5:0] bits in EN_RXADDR register
#define nRF24_MASK_RX_PW           (uint8_t)0x3F // Mask [5:0] bits in RX_PW_Px register
#define nRF24_MASK_RETR_ARD        (uint8_t)0xF0 // Mask for ARD[7:4] bits in SETUP_RETR register
#define nRF24_MASK_RETR_ARC        (uint8_t)0x0F // Mask for ARC[3:0] bits in SETUP_RETR register
#define nRF24_MASK_RXFIFO          (uint8_t)0x03 // Mask for RX FIFO status bits [1:0] in FIFO_STATUS register
#define nRF24_MASK_TXFIFO          (uint8_t)0x30 // Mask for TX FIFO status bits [5:4] in FIFO_STATUS register
#define nRF24_MASK_PLOS_CNT        (uint8_t)0xF0 // Mask for PLOS_CNT[7:4] bits in OBSERVE_TX register
#define nRF24_MASK_ARC_CNT         (uint8_t)0x0F // Mask for ARC_CNT[3:0] bits in OBSERVE_TX register

#define nRF24_TEST_ADDR            "nRF24"

#define nRF24_RX_ON(dev)    nRF24_CE_State(dev, GPIO_PIN_SET);
#define nRF24_RX_OFF(dev)   nRF24_CE_State(dev, GPIO_PIN_RESET);

/* Macros of ARD config in ascent order */
enum {
  nRF24_ARD_NONE   = (uint8_t)0x00, // Dummy value for case when retransmission is not used
  nRF24_ARD_250us  = (uint8_t)0x00,
  nRF24_ARD_500us  = (uint8_t)0x01,
  nRF24_ARD_750us  = (uint8_t)0x02,
  nRF24_ARD_1000us = (uint8_t)0x03,
  nRF24_ARD_1250us = (uint8_t)0x04,
  nRF24_ARD_1500us = (uint8_t)0x05,
  nRF24_ARD_1750us = (uint8_t)0x06,
  nRF24_ARD_2000us = (uint8_t)0x07,
  nRF24_ARD_2250us = (uint8_t)0x08,
  nRF24_ARD_2500us = (uint8_t)0x09,
  nRF24_ARD_2750us = (uint8_t)0x0A,
  nRF24_ARD_3000us = (uint8_t)0x0B,
  nRF24_ARD_3250us = (uint8_t)0x0C,
  nRF24_ARD_3500us = (uint8_t)0x0D,
  nRF24_ARD_3750us = (uint8_t)0x0E,
  nRF24_ARD_4000us = (uint8_t)0x0F
};

/* Data rate */
enum {
  nRF24_DR_250kbps = (uint8_t)0x20, // 250kbps data rate
  nRF24_DR_1Mbps   = (uint8_t)0x00, // 1Mbps data rate
  nRF24_DR_2Mbps   = (uint8_t)0x08  // 2Mbps data rate
};

/* RF output power in TX mode */
enum {
  nRF24_TXPWR_18dBm = (uint8_t)0x00, // -18dBm
  nRF24_TXPWR_12dBm = (uint8_t)0x02, // -12dBm
  nRF24_TXPWR_6dBm  = (uint8_t)0x04, //  -6dBm
  nRF24_TXPWR_0dBm  = (uint8_t)0x06  //   0dBm
};

/* CRC encoding scheme */
enum {
  nRF24_CRC_off   = (uint8_t)0x00, // CRC disabled
  nRF24_CRC_1byte = (uint8_t)0x08, // 1-byte CRC
  nRF24_CRC_2byte = (uint8_t)0x0c  // 2-byte CRC
};

/* nRF24L01 power control */
enum {
  nRF24_PWR_UP   = (uint8_t)0x02, // Power up
  nRF24_PWR_DOWN = (uint8_t)0x00  // Power down
};

/* Transceiver mode */
enum {
  nRF24_MODE_RX = (uint8_t)0x01, // PRX
  nRF24_MODE_TX = (uint8_t)0x00  // PTX
};

/* Enumeration of RX pipe addresses and TX address */
enum {
  nRF24_PIPE0  = (uint8_t)0x00, // pipe0
  nRF24_PIPE1  = (uint8_t)0x01, // pipe1
  nRF24_PIPE2  = (uint8_t)0x02, // pipe2
  nRF24_PIPE3  = (uint8_t)0x03, // pipe3
  nRF24_PIPE4  = (uint8_t)0x04, // pipe4
  nRF24_PIPE5  = (uint8_t)0x05, // pipe5
  nRF24_PIPETX = (uint8_t)0x06  // TX address (not a pipe in fact)
};

/* State of auto acknowledgment for specified pipe */
enum {
  nRF24_AA_OFF = (uint8_t)0x00,
  nRF24_AA_ON  = (uint8_t)0x01
};

/* Status of the RX FIFO */
enum {
  nRF24_STATUS_RXFIFO_DATA  = (uint8_t)0x00, // The RX FIFO contains data and available locations
  nRF24_STATUS_RXFIFO_EMPTY = (uint8_t)0x01, // The RX FIFO is empty
  nRF24_STATUS_RXFIFO_FULL  = (uint8_t)0x02, // The RX FIFO is full
  nRF24_STATUS_RXFIFO_ERROR = (uint8_t)0x03  // Impossible state: RX FIFO cannot be empty and full at the same time
};

/* Status of the TX FIFO */
enum {
  nRF24_STATUS_TXFIFO_DATA  = (uint8_t)0x00, // The TX FIFO contains data and available locations
  nRF24_STATUS_TXFIFO_EMPTY = (uint8_t)0x01, // The TX FIFO is empty
  nRF24_STATUS_TXFIFO_FULL  = (uint8_t)0x02, // The TX FIFO is full
  nRF24_STATUS_TXFIFO_ERROR = (uint8_t)0x03  // Impossible state: TX FIFO cannot be empty and full at the same time
};

/* Result of RX FIFO reading */
typedef enum {
  nRF24_RX_PIPE0  = (uint8_t)0x00, // Packet received from the PIPE#0
  nRF24_RX_PIPE1  = (uint8_t)0x01, // Packet received from the PIPE#1
  nRF24_RX_PIPE2  = (uint8_t)0x02, // Packet received from the PIPE#2
  nRF24_RX_PIPE3  = (uint8_t)0x03, // Packet received from the PIPE#3
  nRF24_RX_PIPE4  = (uint8_t)0x04, // Packet received from the PIPE#4
  nRF24_RX_PIPE5  = (uint8_t)0x05, // Packet received from the PIPE#5
  nRF24_RX_EMPTY  = (uint8_t)0xff  // The RX FIFO is empty
} nRF24_RXResult;


/* Addresses of the RX_PW_P# registers */
static const uint8_t nRF24_RX_PW_PIPE[6] = {
  nRF24_REG_RX_PW_P0,
  nRF24_REG_RX_PW_P1,
  nRF24_REG_RX_PW_P2,
  nRF24_REG_RX_PW_P3,
  nRF24_REG_RX_PW_P4,
  nRF24_REG_RX_PW_P5
};

/* Addresses of the address registers */
static const uint8_t nRF24_ADDR_REGS[7] = {
  nRF24_REG_RX_ADDR_P0,
  nRF24_REG_RX_ADDR_P1,
  nRF24_REG_RX_ADDR_P2,
  nRF24_REG_RX_ADDR_P3,
  nRF24_REG_RX_ADDR_P4,
  nRF24_REG_RX_ADDR_P5,
  nRF24_REG_TX_ADDR
};

typedef struct nrf24 {
  SPI_HandleTypeDef *hspi;
  GPIO_TypeDef *csn_port;
  GPIO_TypeDef *ce_port;
  GPIO_TypeDef *irq_port;
  uint16_t csn_pin;
  uint16_t ce_pin;
  uint16_t irq_pin;

  uint8_t tx_data[32];
  uint8_t rx_data[32];
} nRF24_Handler_t;

/**
 * \brief Set and reset the Chip Enable pin of the nRF24L01+ transceiver
 */
void nRF24_CE_State(nRF24_Handler_t *device, GPIO_PinState state);

/**
 * \brief Set and reset the SPI Chip Select of the nRF24L01+ transceiver
 */
void nRF24_CSN_State(nRF24_Handler_t *device, GPIO_PinState state);

/* Hardware abstraction layer for nRF24L01+ transceiver */
/**
 * \brief Set and reset the GPIO lines of the nRF24L01+ transceiver
 */
void nRF24_HW_Init(nRF24_Handler_t *device, SPI_HandleTypeDef *hspi, GPIO_TypeDef *csn_port, uint16_t csn_pin, GPIO_TypeDef *ce_port, uint16_t ce_pin);

/**
 * \brief Low level SPI transmit/receive function (hardware depended)
 * \param data: Value to transmit via SPI
 * \return Value received from SPI
 */
uint8_t nRF24_LL_RW(nRF24_Handler_t *device, uint8_t data);

/**
 * \brief Set transceiver to default state
 */
void nRF24_Init(nRF24_Handler_t *device);

/**
 * \brief Check if nRF24L01+ is connected to SPI
 * \return Return `1` if the device response is correct, `0` otherwise
 */
uint8_t nRF24_Check(nRF24_Handler_t *device);

/**
 * \brief Read a register
 * \param reg: Address of register to read
 * \return Value of register
 */
uint8_t nRF24_ReadReg(nRF24_Handler_t *device, uint8_t reg);

/**
 * \brief Write a new value to register
 * \param reg: Address of register to write
 * \param value: Value to write
 */
void nRF24_WriteReg(nRF24_Handler_t *device, uint8_t reg, uint8_t value);

/**
 * \brief Read a multi-byte register
 * \param reg: Address of register to read
 * \param pBuf: Pointer where store data read
 * \param count: number of bytes to read
 */
void nRF24_ReadMBReg(nRF24_Handler_t *device, uint8_t reg, uint8_t *pBuf, uint8_t count);

/**
 * \brief Write a multi-byte register
 * \param reg: Address of register to write
 * \param pBuf: Pointer of data to be written
 * \param count: number of bytes to write
 */
void nRF24_WriteMBReg(nRF24_Handler_t *device, uint8_t reg, uint8_t *pBuf, uint8_t count);

/**
 * \brief Control transceiver power mode
 * \param mode: New state of power mode, one of nRF24_PWR_xx values
 */
void nRF24_SetPowerMode(nRF24_Handler_t *device, uint8_t mode);

/**
 * \brief Set transceiver operational mode
 * \param mode: Operational mode, one of nRF24_MODE_xx values
 */
void nRF24_SetOperationalMode(nRF24_Handler_t *device, uint8_t mode);

/**
 * \brief Set frequency channel
 * \param channel: Radio frequency channel, value from 0 to 127
 * \note Frequency will be 2400 + channel MHz
 */
void nRF24_SetRFChannel(nRF24_Handler_t *device, uint8_t channel);

/**
 * \brief Set automatic retransmission parameters
 * \param ard: Auto retransmit delay, one of nRF24_ARD_xx values
 * \param arc: Count of auto retransmits, value form 0 to 15
 * \note Zero arc value means that the automatic retransmission disabled
 */
void nRF24_SetAutoRetr(nRF24_Handler_t *device, uint8_t ard, uint8_t arc);

/**
 * \brief Set of address widths
 * \param addrWidth: RX/TX address field width, value from 3 to 5
 */
void nRF24_SetAddrWidth(nRF24_Handler_t *device, uint8_t addrWidth);

/**
 * \brief Set static RX address for a specified pipe
 * \param pipe: Configuration address, one of nRF24_PIPEx values
 * \param addr: Pointer to the buffer with address
 * \note Pipe can be a number from 0 to 5 (RX pipes) and 6 (TX pipe)
      Check the macros in nRF24.h
 */
void nRF24_SetAddr(nRF24_Handler_t *device, uint8_t pipe, uint8_t *addr);

/**
 * \brief Configure RF output power in TX mode
 * \param tx_pwr: RF output power, one of nRF24_TXPWR_xx values
 */
void nRF24_SetTXPower(nRF24_Handler_t *device, uint8_t txPwr);

/**
 * \brief Configure transceiver data rate
 * \param data_rate: Data rate, one of nRF24_DR_xx values
 */
void nRF24_SetDataRate(nRF24_Handler_t *device, uint8_t dataRate);

/**
 * \brief Configure transceiver CRC scheme
 * \param scheme: CRC scheme, one of nRF24_CRC_xx values
 * \note CRC required activation if one RX pipe has AA activated
 */
void nRF24_SetCRCScheme(nRF24_Handler_t *device, uint8_t scheme);

/**
 * \brief Configure a specified RX pipe
 * \param pipe - number of the RX pipe, value from 0 to 5
 * \param aa_state: State of auto acknowledgment, one of nRF24_AA_xx values
 * \param payloadLen - payload length in bytes
 */
void nRF24_SetRXPipe(nRF24_Handler_t *device, uint8_t pipe, uint8_t aaState, uint8_t payloadLen);

/**
 * \brief Disable specified RX pipe
 * \param pipe: Number of RX pipe, value from 0 to 5
 */
void nRF24_ClosePipe(nRF24_Handler_t *device, uint8_t pipe);

/**
 * \brief Enable the auto retransmit for the specified RX pipe
 * \param pipe: number of the RX pipe, value from 0 to 5
 */
void nRF24_EnableAA(nRF24_Handler_t *device, uint8_t pipe);

/**
 * \brief Disable the auto retransmit for one or all RX pipes
 * \param pipe: number of the RX pipe, value from 0 to 5, any other value will disable AA for all RX pipes
 */
void nRF24_DisableAA(nRF24_Handler_t *device, uint8_t pipe);

/**
 * \brief Get value of the STATUS register
 * \return Value of STATUS register
 */
uint8_t nRF24_GetStatus(nRF24_Handler_t *device);

/**
 * \brief Get pending IRQ flags
 * \return Current status of RX_DR, TX_DS and MAX_RT bits of the STATUS register
 */
uint8_t nRF24_GetIRQFlags(nRF24_Handler_t *device);

/**
 * \brief Get status of the RX FIFO
 * \return One of the nRF24_STATUS_RXFIFO_xx values
 */
uint8_t nRF24_GetStatus_RXFIFO(nRF24_Handler_t *device);

/**
 * \brief Get status of the TX FIFO
 * \return One of the nRF24_STATUS_TXFIFO_xx values
 */
uint8_t nRF24_GetStatus_TXFIFO(nRF24_Handler_t *device);

/**
 * \brief Get pipe number for the payload available for reading from RX FIFO
 * \return Pipe number or �0x07� if the RX FIFO is empty
 */
uint8_t nRF24_GetRXSource(nRF24_Handler_t *device);

/**
 * \brief Get auto retransmit statistic
 * \return Value of OBSERVE_TX register
 */
uint8_t nRF24_GetRetransmitCounters(nRF24_Handler_t *device);

/**
 * \brief Reset packet lost counter (PLOS_CNT bits in OBSERVER_TX register)
 */
void nRF24_ResetPLOS(nRF24_Handler_t *device);

/**
 * \brief Flush TX FIFO
 */
void nRF24_FlushTX(nRF24_Handler_t *device);

/**
 * \brief Flush RX FIFO
 */
void nRF24_FlushRX(nRF24_Handler_t *device);

/**
 * \brief Clear any pending IRQ flags
 */
void nRF24_ClearIRQFlags(nRF24_Handler_t *device);

/**
 * \brief Write TX payload
 * \param pBuf: Pointer to the buffer with payload data
 * \param length: Payload length in bytes
 */
void nRF24_WritePayload(nRF24_Handler_t *device, uint8_t *pBuf, uint8_t length);

/**
 * \brief Read top level payload available in the RX FIFO
 * \param pBuf: Pointer to the buffer to store a payload data
 * \param length: Payload length in bytes
 * \return Return one of \ref nRF24_RXResult values
 */
nRF24_RXResult nRF24_ReadPayload(nRF24_Handler_t *device, uint8_t *pBuf, uint8_t *length);

#endif
