#include "device_drivers/i2c.h"

void i2c_init(void)
{
    /* Disable I2C */
    I2C1->CR1 &= ~I2C_CR1_PE;

    /* 100kHz timing for 4MHz I2C clock */
    I2C1->TIMINGR = 0x0010061A;

    /* Enable I2C */
    I2C1->CR1 |= I2C_CR1_PE;
}

uint8_t i2c_check_addr(uint8_t addr)
{
    /* Clear STOP and NACK flags */
    I2C1->ICR |= I2C_ICR_STOPCF | I2C_ICR_NACKCF;

    /* Clear CR2 transfer settings */
    I2C1->CR2 = 0;

    /* Set 7-bit slave address */
    I2C1->CR2 |= (addr << 1);

    /* Generate STOP automatically */
    I2C1->CR2 |= I2C_CR2_AUTOEND;

    /* Generate START condition */
    I2C1->CR2 |= I2C_CR2_START;

    /* Wait for STOP or NACK */
    while (!(I2C1->ISR & (I2C_ISR_STOPF | I2C_ISR_NACKF)));

    /* Return ACK status */
    return !(I2C1->ISR & I2C_ISR_NACKF);
}


