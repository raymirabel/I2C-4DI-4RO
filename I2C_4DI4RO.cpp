/*
  I2C_4DI4RO.cpp - Libreria para la placa módulo de expansión I2C_4DI4RO
  Copyright (c) 2016 Raimundo Alfonso
  Ray Ingeniería Electrónica, S.L.
  
  Esta librería está basada en software libre. Tu puedes redistribuir
  y/o modificar esta librería bajo los terminos de licencia GNU.

  Esta biblioteca se distribuye con la esperanza de que sea útil,
  pero SIN NINGUNA GARANTÍA, incluso sin la garantía implícita de
  COMERCIALIZACIÓN O PARA UN PROPÓSITO PARTICULAR.
  Consulte los terminos de licencia GNU para más detalles.
*/

/* Dependencies */
#include <Wire.h>
#include "I2C_4DI4RO.h"

I2C_4DI4RO::I2C_4DI4RO() :
		_PORT(0), _PIN(0), _DDR(0), _address(0)
{
}

void I2C_4DI4RO::begin(uint8_t address) {
	_address = address + 0x20;
	Wire.begin();
	readGPIO();
	_DDR  = 0b11110000;
	_PORT = 0b11111111;
	updateGPIO();
	lastCommandOK = false;
}

void I2C_4DI4RO::relayWrite(uint8_t pin, uint8_t value) {
	pin += 3;

	/* Set PORT bit value */
	if (value)
		_PORT &= ~(1 << pin);

	else
		_PORT |= (1 << pin);

	/* Update GPIO values */
	lastCommandOK = false;
	updateGPIO();
	if(dinRead(pin+3) == value) lastCommandOK = true;
	
}

uint8_t I2C_4DI4RO::dinRead(uint8_t pin) {
	pin -= 1;
	
	/* Read GPIO */
	readGPIO();

	/* Read and return the pin state */
	return (_PIN & (1 << pin)) ? LOW : HIGH;
}

void I2C_4DI4RO::readGPIO() {
	unsigned long t;

	/* Start request, wait for data and receive GPIO values as byte */
	Wire.requestFrom(_address, (uint8_t) 0x01);
	t = micros();
	// Time-out = 100uS
	lastCommandOK = false;
	while (Wire.available() < 1 && (micros() - t) < 100);
	if(Wire.available() > 0) lastCommandOK = true;
	_PIN = I2CREAD();
}

void I2C_4DI4RO::updateGPIO() {
	/* Compute new GPIO states */
	uint8_t value = (_PIN & ~_DDR) | _PORT;

	/* Start communication and send GPIO values as byte */
	Wire.beginTransmission(_address);
	I2CWRITE(value);
	Wire.endTransmission();
}
