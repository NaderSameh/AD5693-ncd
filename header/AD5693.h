// AD5693 Hardware Abstraction Layer

#ifndef AD5693_HAL_H
#define AD5693_HAL_H

#include <stdint.h>

typedef enum
{
    NORMAL_MODE,
    POWER_DOWN_ONE_K_IMPEDANCE,
    POWER_DOWN_HUNDRED_K_IMPEDANCE,
    POWER_DOWN_THREE_STATE_IMPEDANCE
} AD5693_operating_mode;

typedef enum
{
    AD5693_GAIN_1,
    AD5693_GAIN_2
} AD5693_GAIN;

typedef enum
{
    AD5693_RESET_OFF,
    AD5693_RESET_ON
} AD5693_RESET;

typedef enum
{
    AD5693_ADDRESS_A0_LOW = 0x4C,
    AD5693_ADDRESS_A0_HIGH = 0x4E
} AD5693_ADDRESS;

struct AD5693_config_def
{
    AD5693_operating_mode operating_mode;
    AD5693_GAIN gain;
    AD5693_RESET reset;
    AD5693_ADDRESS address;
};

// Function prototypes for the AD5693 HAL

// Initialize the AD5693
int ad5693_init(struct AD5693_config_def* config);
// set the AD5693 operating mode
int ad5693_set_operating_mode(AD5693_operating_mode mode);
// set gain, note: Vdac = Vref * gain * (D/65536)
int ad5693_set_gain(AD5693_GAIN gain);
// reset the AD5693 chip
int ad5693_reset();
// load the input register with desired DAC value, will only update after
// calling ad5693_update_dac_reg function
int ad5693_write_input_register(uint16_t value);
// transfer input register value to DAC value
int ad5693_update_dac_reg();
// Write a value to the DAC
int ad5693_dac_write(uint16_t value);

#endif // AD5693_HAL_H