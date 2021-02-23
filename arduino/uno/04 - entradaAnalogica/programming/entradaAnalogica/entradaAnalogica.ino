/*
 *	AUTOR: Alexandre Gonçalves
 *	EMAIL:g.aleprojetos@gmail.com
 *  SKETCH:leitura da entrada analogica e enviaso pela comunicação serial
 *	ARQUIVO:conversão digital
 *	DATA:04/08/2020
 *	
 */

// *** Protótipo das Funções ***//
int ad_conv();                    //função para conversão AD

// *** Programa Principal ***//
void setup() {

   Serial.begin(9600);            //inicializa comunicação serial em 9600 baud rate

   ADCSRA  = 0x93;                //liga conversão AD, fator de divisão de 8     
   ADMUX   = 0x42;                //tensão de ref. de 5V, canal A2  

 
    while(1){

   Serial.println(ad_conv());
 
   delay(250);

  }//end while
}//end setup

// *** Configurações Iniciais ***//
int ad_conv()
{
   static int analogH, analogL, analog;    //variáveis locais para valores ADC
 
   ADCSRA |= (1<<ADSC);                    //inicia conversão ad
 
   while(!(ADCSRA&=~(1<<ADIF)));           //aguarda conversão ad completar
   
   ADCSRA |= (1<<ADIF);                    //limpa ADIF com transição LOW para HIGH
 
   analogL = ADCL;                         //armazena o byte menos significativo
   analogH = ADCH;                         //armazena o byte mais  significativo
 
   analog  = (analogH<<8) | analogL;       //calcula para valor de 10 bits

   return analog;                          //retorna resultado da conversão
    
} //end ad_conv
