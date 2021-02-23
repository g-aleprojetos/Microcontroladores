
/*
 *  AUTOR: Alexandre Gonçalves
 *  EMAIL:g.aleprojetos@gmail.com
 *  SKETCH: Configurado a saida digital
 *  ARQUIVO:blink.ino
 *  DATA:08/03/2020 
 */

 // *** Mapeamento de Hardware ***//
void setup() {

  DDRB |= (1<<5);              //configurado d13 como saida 
  PORTB &= ~(1<<5);            //inicializo o d13 em lOW

  while(1){

    PORTB |= (1<<5);             //coloca a saida d13 em HIGH
    delay(100);                  //temporizador de 100 mS
    PORTB &= ~(1<<5);            //coloca a saida d13 em LOW
    delay(100);                  //temporizador de 100 mS
    
  }//end while


}//end setup
