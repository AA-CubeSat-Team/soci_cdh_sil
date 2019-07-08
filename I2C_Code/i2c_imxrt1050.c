

// p. 2584
// The transmit FIFO stores command data to initiate the various I2C operations. The
// following operations can be initiated through commands in the transmit FIFO:
// • START or Repeated START condition with address byte and expecting ACK or NACK.
// • Transmit data (this is the default for zero extended byte writes to the transmit FIFO).
// • Receive 1-256 bytes of data (can also be configured to discard receive data and not
// store in receive FIFO).
// • STOP condition (can also be configured to send STOP condition when transmit FIFO
// is empty).

// incomplete
// very poor attempt to fill out what could be useful but very unsure...
void I2C1_Init() {
  MIER_LPI2C1_R = (1<<1);  // Transmit data interrupt enabled
  MDER_LPI2C1_R = (1<<0);  // Transmit data DMA request enabled
  MCFGR0_LPI2C1_R = (1<<2) +
                    (1<<1) +
                    (1<<0)  // p. 2603 (not sure how to use this register)

  MCR_LPI2C1_R = (1<<0);  // Master logic enabled
}

// TODO: find the register that sets the slave address
// should be used as internal function in TX and RX functions
void set_slave_addr(uint8_t slav_addr) {

}

// TODO: find the register that sets send or receive mode
// should be used as internal function in TX and RX functions
void set_TX_RX(int mode) {

}

// incomplete
void I2C1_Transmit_Data(uint8_t data) {
  MTDR_LPI2C1_R = (0x0<<8);  // transmit data (p. 2616)
}

// incomplete
uint8_t I2C1_Receive_Data(uint8_t reg_2_b_read) {
  uint8_t data_received;
  while (!(MRDR_LPI2C1_R & 0x4000)) {}  // check if bit 14 == 0 
  data_received = MRDR_LPI2C1_R & 0xFF;  // data stored in bits[7:0]
  return data_received;
} 
