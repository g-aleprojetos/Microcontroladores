/*
 *	AUTOR: Alexandre Gonçalves
 *	EMAIL:g.aleprojetos@gmail.com
 *  SKETCH: configurado uma entrada e saida digital
 *	ARQUIVO:Entrada Digital
 *	DATA:04/08/2020
 *	
 */

// *** Programa Principal ***//
void setup() {

  DDRB &= ~(1<<4);             // configuro d12 como entrada


  DDRB |= (1<<5);              //configurado d13 como saida 
  PORTB &= ~(1<<5);            //inicializo o d13 em lOW
 
    while(1){

  /*** primeiro método ***/
      //  if(PINB & (1<<4)) PORTB &= ~(1<<5);                           // se o d12 estiver em HIGH o d13 estará em LOW
      //  else PORTB |= (1<<5);                                         // se o d12 estiver em LOW o d13 estará em HIGH

  /*** segundo método ***/
      PORTB = (PINB & (1<<4)) ? (PORTB &= ~(1<<5)) : (PORTB |= (1<<5)); // se o d12 estiver em HIGH o d13 estará em LOW
                                                                        // se o d12 estiver em LOW o d13 estará em HIGH
  }//end while
}//end setup
