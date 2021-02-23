/*
 *	AUTOR: Alexandre Gonçalves
 *	EMAIL:g.aleprojetos@gmail.com
 *	ARQUIVO:Entrada Digital Botão Pulsar
 *	DATA:05/08/2020
 *	
 */

// *** Mapeamento de Hardware ***//
#define bt1 (1<<4)           // configurando d12 como bt1
#define led (1<<5)           // configurando d13 como led

// *** Variaveis Globais ***//
boolean bt1_f = 0x00;

// *** Programa Principal ***//
void setup() {

  DDRB    &=   ~bt1;           // configura bt1 como entrada do botão
  PORTB   |=    bt1;           // habilita o pull-up interno

  DDRB    |=    led;           // configurado led como saida 
  PORTB   &=   ~led;           // inicializo o led em lOW
 
  while(1){

    if(!(PINB&bt1)) bt1_f = 0x01;

    if((PINB&bt1) && bt1_f){

      PORTB ^= led;
      bt1_f = 0x00;
      
    }//end if bt1
  }//end while
}//end setup
