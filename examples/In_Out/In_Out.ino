// Raimundo Alfonso Sanchez
// Ray Ingeniería Electrónica, S.L. - 2016
// Asigna cada entrada digital a una salida de relé

#include "I2C_4DI4RO.h" 

// Instancia...
I2C_4DI4RO expander;

void setup(){ 
  // Inicializa y configura módulo en la dirección 0
  expander.begin(0);  
} 

void loop(){ 
  expander.relayWrite(1, expander.dinRead(1));
  expander.relayWrite(2, expander.dinRead(2));
  expander.relayWrite(3, expander.dinRead(3));
  expander.relayWrite(4, expander.dinRead(4));
} 

