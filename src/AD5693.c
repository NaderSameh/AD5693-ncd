#include "AD5693.h"
#include "I2C_wrapper.h"

struct AD5693_config_def internal_config;

static int write_bytes(uint8_t addr, uint8_t* data, uint32_t num_bytes,
                       uint8_t slaveAddr)
{
    uint8_t wr_addr[1];
    struct i2c_msg msgs[2];
    /* FRAM cmd address */
    wr_addr[0] = addr & 0xFF;
    /* Setup I2C messages */
    /* Send cmd code */
    msgs[0].buf = wr_addr;
    msgs[0].len = 1U;
    msgs[0].flags = I2C_MSG_WRITE;
    /* Data to be written, and STOP after this. */
    msgs[1].buf = data;
    msgs[1].len = num_bytes;
    msgs[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;
    return i2c_transfer(&msgs[0], 2, slaveAddr);
}

// Implementation of the AD5693 HAL functions

int ad5693_init(struct AD5693_config_def* config)
{
    uint8_t data[2];
    uint8_t err;
    uint8_t value = 0x00;

    internal_config = *config;
    // force a reset upon initialization
    config->reset = 1;
    value |= (config->gain << 4);
    value |= (config->operating_mode << 5);
    value |= (config->reset << 7);
    data[0] = value & 0xFF;
    data[1] = 0x00;
    err = write_bytes(0x40, data, 2, internal_config.address);
    return err;
}

int ad5693_set_operating_mode(AD5693_operating_mode mode)
{
    internal_config.operating_mode = mode;
    uint8_t data[2];
    uint8_t err;
    uint8_t value = 0x00;
    value |= (internal_config.gain << 4);
    value |= (internal_config.operating_mode << 5);
    value |= (internal_config.reset << 7);
    data[0] = value & 0xFF;
    data[1] = 0x00;
    err = write_bytes(0x40, data, 2, internal_config.address);
    return err;
}

int ad5693_set_gain(AD5693_GAIN gain)
{
    internal_config.gain = gain;
    uint8_t data[2];
    uint8_t err;
    uint8_t value = 0x00;
    value |= (internal_config.gain << 4);
    value |= (internal_config.operating_mode << 5);
    value |= (internal_config.reset << 7);
    data[0] = value & 0xFF;
    data[1] = 0x00;
    err = write_bytes(0x40, data, 2, internal_config.address);
    return err;
}
int ad5693_reset()
{
    struct AD5693_config_def config;
    config = internal_config;
    config.reset = 1;
    uint8_t data[2];
    uint8_t err;
    uint8_t value = 0x00;
    value |= (config.gain << 4);
    value |= (config.operating_mode << 5);
    value |= (config.reset << 7);
    data[0] = value & 0xFF;
    data[1] = 0x00;
    err = write_bytes(0x40, data, 2, internal_config.address);
    return err;
}

int ad5693_dac_write(uint16_t value)
{
    uint8_t data[2];
    uint8_t err;
    data[0] = (value >> 8) & 0xFF;
    data[1] = (value & 0xFF);
    err = write_bytes(0x30, data, 2, internal_config.address);
    return err;
}

int ad5693_write_input_register(uint16_t value)
{
    uint8_t data[2];
    uint8_t err;
    data[0] = (value >> 8) & 0xFF;
    data[1] = (value & 0xFF);
    err = write_bytes(0x10, data, 2, internal_config.address);
    return err;
}

int ad5693_update_dac_reg()
{
    uint8_t data[2];
    uint8_t err;
    data[0] = 0x00;
    data[1] = 0x00;
    err = write_bytes(0x20, data, 2, internal_config.address);
    return err;
}