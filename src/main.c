#include "AD5693.h"
#include "I2C_wrapper.h"
#include <stdint.h>
#include <stdio.h>

/* demo I2C1 configuration */
struct i2c_config i2c1_config = {
    .frequency = 100000,
    .own_address = 0x10,
    .ack_enable = true,
    .dma_enable = false,
    .interrupt_enable = false,
};
/* demo AD5693 configuration
 *  Vdac = Vref * gain * (D/65536)
 */
struct AD5693_config_def dac_config = {
    .operating_mode = NORMAL_MODE,
    .gain = AD5693_GAIN_1,
    .address = AD5693_ADDRESS_A0_LOW,
};

void main(void)
{
    /*  initialize I2C before communication with AD5693 */
    i2c_init(&i2c1_config);
    /* initialize AD5693 */
    if (ad5693_init(&dac_config) != 0)
        printf("AD5693 initialization failed!");
    else
        printf("AD5693 initialization completed successfully\n");
    /* set dac value to 40000 */
    uint8_t ret = ad5693_dac_write(40000);
    uint32_t a = 5 * ((40000 * 1000) / 65536);
    if (ret == 0)
        printf("DAC set to %uv as Vref = 5v \n", a / 1000);

    ad5693_set_gain(AD5693_GAIN_2);
    ad5693_set_operating_mode(POWER_DOWN_THREE_STATE_IMPEDANCE);
}
