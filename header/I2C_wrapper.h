
#ifndef I2C_WRAPPER_H
#define I2C_WRAPPER_H
#include <stdint.h>

/*
 * One I2C Message.
 * This defines one I2C message to transact on the I2C bus.
 */
typedef enum
{
    I2C_MSG_WRITE,
    I2C_MSG_READ,
    I2C_MSG_STOP,
    I2C_MSG_RESTART,

} I2C_FLAGS;

struct i2c_msg
{
    uint8_t* buf;  // Data buffer in bytes
    uint32_t len;  // Length of buffer in bytes
    uint8_t flags; // Flags for this message
};

struct i2c_config
{
    /*  just sample of a possible implementation    */
    uint8_t instance;         // index of I2C instance
    uint32_t frequency;       // I2C bus frequency (in Hz)
    uint8_t own_address;      // Own address of the I2C device
    uint8_t ack_enable;       // Enable/disable acknowledge bit
    uint8_t ack_addr;         // Acknowledge address in 7-bit or 10-bit mode
    uint8_t ack_data;         // Acknowledge data in 7-bit or 10-bit mode
    uint8_t dma_enable;       // Enable/disable DMA for I2C transfer
    uint8_t interrupt_enable; // Enable/disable interrupts for I2C transfer
};

void i2c_init(struct i2c_config* config);

int i2c_transfer(struct i2c_msg* msgs, uint8_t num_msgs, uint16_t addr);

#endif