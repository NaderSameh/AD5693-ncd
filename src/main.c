#include "AD5693.h"
#include "I2C_wrapper.h"
#include <stdint.h>
#include <stdio.h>

struct i2c_config i2c1_config = {
    .frequency = 100000,
    .own_address = 0x10,
    .ack_enable = 0x01,
    .dma_enable = 0x00,
    .interrupt_enable = 0x00,
};

struct AD5693_config_def dac_config = {
    .operating_mode = NORMAL_MODE,
    .gain = AD5693_GAIN_1,
    .address = AD5693_ADDRESS_A0_LOW,
};

void main(void)
{
    i2c_init(&i2c1_config);
    ad5693_init(&dac_config);
    printf("Intialization completed successfully\n");
    uint8_t ret = ad5693_dac_write(40000);
    uint32_t a = 5 * ((40000 * 1000) / 65536);
    if (ret == 0)
        printf("DAC set to %uv as Vref = 5v \n", a / 1000);
}
