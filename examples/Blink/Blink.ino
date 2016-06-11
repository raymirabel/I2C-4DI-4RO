// Raimundo Alfonso Sanchez
// Ray Ingeniería Electrónica, S.L. - 2016
// Test módulo de expansión I2C-4DI4RO

#include "I2C_4DI4RO.h" 

// Instancia...
I2C_4DI4RO expander;

void setup(){ 
  // Inicializa y configura módulo en la dirección 0
  expander.begin(0);  
} 

void loop(){ 
  // Activa salida 1
  expander.relayWrite(1, HIGH);
  delay(500);
  // Desactiva salida 1
  expander.relayWrite(1, LOW);
  delay(500);
} 

