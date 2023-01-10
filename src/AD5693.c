#include "AD5693.h"
#include "I2C_wrapper.h"

/*  internal stored copy of the latest configuration for the AD5693
 *   it is used to ensure that only the change required is written
 */
struct AD5693_config_def internal_config;

/*
 *   I2C function based on the i2c_transfer function that should be implemented
 * in the I2C_wrapper.c
 */
static int write_bytes(uint8_t cmd, uint8_t* data, uint32_t num_bytes,
                       uint8_t slaveAddr)
{
    uint8_t wr_cmd[1];
    struct i2c_msg msgs[2];
    /* cmd code */
    wr_cmd[0] = cmd & 0xFF;
    /* Setup I2C messages */
    /* Send cmd code */
    msgs[0].buf = wr_cmd;
    msgs[0].len = 1U;
    msgs[0].flags = I2C_MSG_WRITE;
    /* Data to be written, and STOP after this. */
    msgs[1].buf = data;
    msgs[1].len = num_bytes;
    msgs[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;
    return i2c_transfer(&msgs[0], 2, slaveAddr);
}

// Implementation of the AD5693 HAL functions

/*
 *   initialize the AD5693 with the required configuration
 *   force a chip restart to ensure its initialization state
 *   return 0 upon success
 */
int ad5693_init(struct AD5693_config_def* config)
{
    uint8_t data[2];
    uint8_t err;
    uint8_t value = 0x00;

    internal_config = *config;
    // force a reset upon initialization
    config->reset = 1;
    value |= (config->gain << 3);
    value |= (config->operating_mode << 5);
    value |= (config->reset << 7);
    data[0] = value & 0xFF;
    data[1] = 0x00;
    err = write_bytes(0x40, data, 2, internal_config.address);
    return err;
}

/*
 * set the AD5693 in different operating modes, normal mode or 3 different sleep
 * modes return 0 upon success
 */
int ad5693_set_operating_mode(AD5693_operating_mode mode)
{
    internal_config.operating_mode = mode;
    uint8_t data[2];
    uint8_t err;
    uint8_t value = 0x00;
    value |= (internal_config.gain << 3);
    value |= (internal_config.operating_mode << 5);
    value |= (internal_config.reset << 7);
    data[0] = value & 0xFF;
    data[1] = 0x00;
    err = write_bytes(0x40, data, 2, internal_config.address);
    return err;
}
/*
 *   Set gain for the AD5693
 *   params: AD5693_GAIN_1 or AD5693_GAIN_2
 *   note: Vdac = Vref * gain * (D/65536)
 *   return 0 upon success
 */
int ad5693_set_gain(AD5693_GAIN gain)
{
    internal_config.gain = gain;
    uint8_t data[2];
    uint8_t err;
    uint8_t value = 0x00;
    value |= (internal_config.gain << 3);
    value |= (internal_config.operating_mode << 5);
    value |= (internal_config.reset << 7);
    data[0] = value & 0xFF;
    data[1] = 0x00;
    err = write_bytes(0x40, data, 2, internal_config.address);
    return err;
}
/*
 * resets the AD5693
 * return 0 upon success
 */
int ad5693_reset()
{
    struct AD5693_config_def config;
    config = internal_config;
    config.reset = 1;
    uint8_t data[2];
    uint8_t err;
    uint8_t value = 0x00;
    value |= (config.gain << 3);
    value |= (config.operating_mode << 5);
    value |= (config.reset << 7);
    data[0] = value & 0xFF;
    data[1] = 0x00;
    err = write_bytes(0x40, data, 2, internal_config.address);
    return err;
}
/*
 * set the DAC voltage based on the below equation
 * note: Vdac = Vref * gain * (D/65536)
 * return 0 upon success
 */
int ad5693_dac_write(uint16_t value)
{
    uint8_t data[2];
    uint8_t err;
    data[0] = (value >> 8) & 0xFF;
    data[1] = (value & 0xFF);
    err = write_bytes(0x30, data, 2, internal_config.address);
    return err;
}
/*
 *  Update the DAC voltage in async mode, load the input register then
 *  call ad5693_update_dac_reg for update
 *  return 0 upon success
 */
int ad5693_write_input_register(uint16_t value)
{
    uint8_t data[2];
    uint8_t err;
    data[0] = (value >> 8) & 0xFF;
    data[1] = (value & 0xFF);
    err = write_bytes(0x10, data, 2, internal_config.address);
    return err;
}
/*
 *  transfer the input register to the DAC value register
 *  return 0 upon success
 */
int ad5693_update_dac_reg()
{
    uint8_t data[2];
    uint8_t err;
    data[0] = 0x00;
    data[1] = 0x00;
    err = write_bytes(0x20, data, 2, internal_config.address);
    return err;
}

/*
 *   reads the loaded value in the input register
 *   return the read value
 */
uint16_t ad5693_read_input_register()
{
    // to be implement if needed
    // i2c_read need to be included in the I2C_wrapper
}