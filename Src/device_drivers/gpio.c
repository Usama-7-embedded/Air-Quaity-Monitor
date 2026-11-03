#include "device_drivers/gpio.h"

void GPIO_Init(GPIO_TypeDef * port,
		uint8_t pin,
		GPIO_Mode_t mode,
		GPIO_OutputType_t outputType,
		GPIO_OutputSpeed_t outputSpeed,
		GPIO_Pull_t pullUpDown){

	// -------- GPIO MODE CONFIGURATION --------
	// Each pin uses 2 bits in MODER
	// Clear the 2 bits for the selected pin
	port->MODER &= ~(0x3UL << (pin * 2U));

	// Set the mode for the selected pin (e.g., input, output, alternate)
	port->MODER |= ((uint32_t)(mode << (pin * 2U)));

	// -------- OUTPUT TYPE CONFIGURATION --------
	// Each pin uses 1 bit in OTYPER
	// Clear the bit for the selected pin
	port->OTYPER &= ~(0x1UL << pin);

	// Set output type (push-pull or open-drain)
	port->OTYPER |= ((uint32_t)(outputType << pin));

	// -------- OUTPUT SPEED CONFIGURATION --------
	// Each pin uses 2 bits in OSPEEDR
	// Clear the 2 bits for the selected pin
	port->OSPEEDR &= ~(0x3UL << (pin * 2));

	// Set output speed (low, medium, high, very high)
	port->OSPEEDR |= ((uint32_t)(outputSpeed << (pin * 2U)));

	// -------- PULL-UP / PULL-DOWN CONFIGURATION --------
	// Each pin uses 2 bits in PUPDR
	// Clear the 2 bits for the selected pin
	port->PUPDR &= ~(0x3UL << (pin * 2));

	// Set pull-up, pull-down, or no pull resistor
	port->PUPDR |= ((uint32_t)(pullUpDown << (pin * 2U)));
}

void GPIO_WritePin(GPIO_TypeDef * port,
				uint8_t pin,
				GPIO_Level_t value) {

	// Check whether we want to set the pin HIGH or LOW
	if (value == 1U) {
		// Write to the lower 16 bits of BSRR to set the pin HIGH
		// This operation is atomic (no read-modify-write)
		port->BSRR |= (1UL << pin);
	} else {
		// Write to the upper 16 bits of BSRR to reset the pin LOW
		// (pin number + 16 targets the reset bits)
		port->BSRR |= (1UL << (pin + 16));
	}
}


GPIO_Level_t GPIO_ReadPin(GPIO_TypeDef * port, uint8_t pin){
	uint32_t value = 0U;

	// Read the pin's current state from IDR register
	// Mask isolates just the bit for our pin
	value = port->IDR & (1UL << pin);

	// Return HIGH if the pin's bit is set, otherwise LOW
	if (value != 0U) {
		return GPIO_HIGH;
	} else {
		return GPIO_LOW;
	}
}

void SelectAltFunction(GPIO_TypeDef * port, uint8_t pin, uint8_t alt_func) {
	// Mask to ensure only the lower 4 bits are used (AF0–AF15)
	alt_func &= 0xFU;

	if (pin <= 7) {
		// Pins 0–7 use AFR[0] (low alternate function register)
		// Clear existing AF bits for this pin
		port->AFR[0] &= ~(0xFUL << (pin * 4U));
		// Set the new alternate function for this pin
		port->AFR[0] |= ((uint32_t)(alt_func << (pin * 4U)));
	} else {
		// Pins 8–15 use AFR[1] (high alternate function register)
		// Clear existing AF bits for this pin
		port->AFR[1] &= ~(0xFUL << ((pin - 8U) * 4U));
		// Set the new alternate function for this pin
		port->AFR[1] |= ((uint32_t)(alt_func << ((pin - 8U) * 4U)));
	}
}

