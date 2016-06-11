// Raimundo Alfonso Sanchez
// Ray Ingeniería Electrónica, S.L. - 2016
// Test módulo de expansión I2C-4DI4RO

#include "I2C_4DI4RO.h" 

// Instancia...
I2C_4DI4RO expander;

void menu_inicio(void){
  Serial.println(F("---    Test MODULO I2C-4DI4RO    ---"));
  Serial.println(F("   Ray Ingenieria Electronica,S.L."));  
  Serial.println();
  Serial.println(F("Pulse '?' para menu de ayuda"));    
}

void menu(void){
  Serial.println(F("                MENU PRINCIPAL"));
  Serial.println(F("-----------------------------------------------"));
  Serial.println(F("Rn       Activa rele n (n de 1 a 6)"));
  Serial.println(F("Fn       Desactiva rele n (n de 1 a 6)"));
  Serial.println(F("E        Lee entradas digitales"));            
}

String inString;

void setup(){ 
    
  // Configura puertos serie...
  Serial.begin(9600); 
 
  // Inicializa y configura módulo expansión con el número de expansión de 0 a 7
  expander.begin(0);  

  // Mensaje inicial...
  menu_inicio();

  // Menu de opciones...
  menu();
} 

void loop(){ 
  int c;
 
  // Comprueba lo que recibes por puerto USB....
  if (Serial.available() > 0) {
    int c = Serial.read();
    inString += (char)c; 
    if (c == 0x0D) {
      // Quita el retorno de carro...
      //inString = inString.substring(0, inString.length() - 1);
      inString.trim();
      // comprueba el comando...
   
      // Menu...
      if(inString == "?"){
        menu();
      }
      
      // Rele ON...
      if(inString.startsWith("R")){
        releOn(inString.charAt(1));
        if(expander.lastCommandOK)     
          Serial.println("OK");      
        else
          Serial.println("FALLO DE ESCRITURA!");      
      }
      
      // Rele OFF...
      if(inString.startsWith("F")){
        releOff(inString.charAt(1));
        if(expander.lastCommandOK)     
          Serial.println("OK");      
        else
          Serial.println("FALLO DE ESCRITURA!");             
      }   
   
      if(inString.startsWith("E")){
        Serial.println(expander.dinRead(1),DEC);      
        Serial.println(expander.dinRead(2),DEC);  
        Serial.println(expander.dinRead(3),DEC);  
        Serial.println(expander.dinRead(4),DEC);   
        if(expander.lastCommandOK)     
          Serial.println("OK");      
        else
          Serial.println("FALLO DE LECTURA!");      
     }       
    
      inString = ""; 
      Serial.flush();
    }    
  }

} 


void releOn(char rele){
  byte r;
  r = byte(rele) - 0x30;
  if(r == 1) expander.relayWrite(1, HIGH);
  if(r == 2) expander.relayWrite(2, HIGH);
  if(r == 3) expander.relayWrite(3, HIGH);  
  if(r == 4) expander.relayWrite(4, HIGH);    
}

void releOff(char rele){
  byte r;
  r = byte(rele) - 0x30;
  if(r == 1) expander.relayWrite(1, LOW);
  if(r == 2) expander.relayWrite(2, LOW);
  if(r == 3) expander.relayWrite(3, LOW);  
  if(r == 4) expander.relayWrite(4, LOW);  
}


