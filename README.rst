

AD5693 HAL Driver
#################

Overview
********

AD5693 HAL driver provide interface for the chip through I2C to
control its functionality. mainly the DAC functionality

The APIs are built on x86 architecture but it is written in portabal C 
to fit different architecture

Requirements
************

- provide the target I2C instance implementation in the I2C_wrapper.c
- connect the AD5693 chip I2C lines to the target I2C bus

Build and Running output
************************

AD5693 initialization completed successfully
DAC set to 3v as Vref = 5v

