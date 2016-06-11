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

#ifndef I2C_4DI4RO_H
#define I2C_4DI4RO_H

// Retro-compatibility with arduino 0023 and previous version
#if ARDUINO >= 100
#include "Arduino.h"
#define I2CWRITE(x) Wire.write(x)
#define I2CREAD() Wire.read()
#else
#include "WProgram.h"
#define I2CWRITE(x) Wire.send(x)
#define I2CREAD() Wire.receive()
#define INPUT_PULLUP 2
#endif

class I2C_4DI4RO {
public:
	I2C_4DI4RO();
	void begin(uint8_t address = 0x00);
	void relayWrite(uint8_t pin, uint8_t value);
	uint8_t dinRead(uint8_t pin);
	boolean lastCommandOK;
	
protected:
	volatile uint8_t _PORT;
	volatile uint8_t _PIN;
	volatile uint8_t _DDR;
	uint8_t _address;
	void readGPIO();
	void updateGPIO();
};

#endif
