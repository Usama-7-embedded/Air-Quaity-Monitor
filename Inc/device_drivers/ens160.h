#ifndef DEVICE_DRIVERS_ENS160_H_
#define DEVICE_DRIVERS_ENS160_H_

#include <stdint.h>
#include "device_headers/stm32l432xx.h"

#define ENS160_ADDR            0x53U
#define ENS160_STANDARD_MODE   0x02U
#define ENS160_PART_ID_REG     0x00U

uint16_t ens160_read_part_id(void);
void ens160_write(uint8_t reg, uint8_t data);
uint8_t ens160_read(uint8_t reg);

#endif /* DEVICE_DRIVERS_ENS160_H_ */
