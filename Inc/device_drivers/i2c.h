#ifndef DEVICE_DRIVERS_I2C_H_
#define DEVICE_DRIVERS_I2C_H_


#include <stdint.h>
#include "device_headers/stm32l432xx.h"

#define EHS160_ADDR 0x53
#define AHT21_ADDR	0x38

void i2c_init();

uint8_t i2c_check_addr(uint8_t addr);


#endif /* DEVICE_DRIVERS_I2C_H_ */
