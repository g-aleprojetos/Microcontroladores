
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// --- Mapeamento de Hardware ---
#define out            D0                               // GPIO02 led onbord vermelho
#define button         D5                               //Botão para selecionar no digital GPIO14
#define buttonEnter    D6                               //Botão para selecionar enter no digital GPIO12

// --- Constantes Auxiliares ---
#define     num    100         //número de iterações da média 

// --- Protótipo das Funções Auxiliares ---
long moving_average(int sig);
void changeMenu();                                      //Função para modificar o menu atual
void dispMenu();                                        //Função para mostrar o menu atual
void temperatura();                                     //Função do menu1, temperatura 
void offset();                                          //Função do menu2, offset
void modoffset();

// --- Variáveis Globais ---
char menu = 0x01;                                       //Variável para selecionar o menu
char submenu1 = 0x01;                                   //Variável para selecionar o submenu1
char selet = 0x01;
boolean t_button;                                       //Flags para armazenar o estado dos botões
boolean t_enter;
int sensorAnalogico = A0;
int values[num];                                       //vetor com num posições, armazena os valores para cálculo da média móvel
int adc_noise1;                                        //armazena a leitura sem filtro da entrada analógica
int adc_noise2;                                        //armazena a leitura filtrada da entrada analógica
int Offset = 0;
int valorTemp = 0;

float temperature = 0.0,                               //Armazena a temperatura em graus Celsius
     current_temp = 0.0;                               //Armazena a temperatura atual

char counter1  = 0x00;                                  //variável auxiliar de contagem
char counter2  = 0x00;                                  //variável auxiliar de contagem

// --- Rotina de Interrupção ---
void ICACHE_RAM_ATTR onTimerISR(){
  
      timer1_write(100000);
      counter1++;                                      // incrementa counter
      counter2++;                                      // incrementa counter
    
 
    if(counter1 == 0x05) // counter 
      {                 // sim...
       digitalWrite(out, !digitalRead(out)); //Inverte o estado da saída de teste
        counter1 = 0x00; 
       
       } //end if counter 
    
    if(counter2 == 0x02) // counter 
      {                 // sim...
             
        adc_noise1 = analogRead(sensorAnalogico);
        adc_noise2 = moving_average(adc_noise1);
        temperature = ((adc_noise2 * 3.3)/1024.0);
        temperature = temperature * 100;
        temperature = temperature - Offset;

       if(temperature < (current_temp - 1.0) || temperature > (current_temp + 1.0))
        {
         current_temp = temperature;              //atualiza temperatura atual

         valorTemp = (int) temperature; 

        } //end if
       
       counter2 = 0x00;
       
       } //end if counter 

 }//end interrupt
 
// --- Configurações Iniciais ---
void setup()
{
   Serial.begin(9600);                                  // Inicia a serial
   lcd.begin();
   lcd.backlight();
   lcd.setCursor(0, 0);
   lcd.print("INICIALIZANDO...");
  
   pinMode(button, INPUT);                             // Configura porta como entrada
   pinMode(buttonEnter, INPUT);                        // Configura porta como entrada
   pinMode(out, OUTPUT);                               // Configura porta como saida
  
   t_button   = 0x00;                                  //limpa flag do botão Up

   //Initialize Ticker every 
  timer1_attachInterrupt(onTimerISR);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  timer1_write(100000); 
 
   delay(2000);
   lcd.clear();                                         //Limpa display

} //end setup


// --- Loop Infinito ---
void loop()
{
         switch(menu)                                        //Controle da variável menu
    {
       case 0x01:                                       //Caso 1
             changeMenu();                              //Chama a carregar menu
             dispMenu();                                //Chama a função display                         
             
             break;                                     //break
       case 0x02:                                       //Caso 2
             modoffset();
             
             break;                                     //break

    
    } //end switch menu 
 
} //end loop

// --- Desenvolvimento das Funções Auxiliares ---
void changeMenu()                                         //Modifica o menu atual
{
   if(!digitalRead(button))   t_button   = 0x01;          //Botão Up pressionado? Seta flag
       
   if(digitalRead(button) && t_button)                    //Botão Up solto e flag setada?
   {                                                      //Sim...
      t_button = 0x00;                                    //Limpa flag
      
      lcd.clear();                                        //Limpa display
      submenu1++;                                         //Incrementa menu
      
      if(submenu1 > 0x02) submenu1 = 0x01;                //Se menu maior que 2, volta a ser 1
   
   } //end button

} //end changeMenu

void dispMenu()                                         //Mostra o menu atual
{
    switch(submenu1)                                    //Controle da variável menu
    {
       case 0x01:                                       //Caso 1
             temperatura();                             //Chama a função de termômetro
             
             break;                                     //break
       case 0x02:                                       //Caso 2
             offset();                                  //Chama a função do offset
             
             break;                                     //break

    
    } //end switch submenu1

} //end dispMenu

long moving_average(int sig)
{
  int i;               //variável auxiliar para iterações
  long acc = 0;        //acumulador
  
  //Desloca o vetor completamente eliminando o valor mais antigo
  for(i = num; i > 0; i--) values[i] = values[i-1];    
  
  values[0] = sig;           //carrega o sinal no primeiro elemento do vetor
  
   
  for(i = 0; i < num; i++) acc += values[i];
   
  
  return acc / num;         //Retorna a média móvel

} //end moving_average

void temperatura()                                      //Temperatura (menu1)
{
   lcd.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   lcd.print("Temperatura");                           //Imprime mensagem
   lcd.setCursor(1,1);                                 //Posiciona cursor na coluna 2, linha 2
   lcd.print(valorTemp);
   lcd.print(" Celsius");                              //Mostrador (apenas ilustrativo......)   
   
   selet = 0x01;
   
} //end temperatura()

 void offset()                                         //offset (menu2)
{
    
   lcd.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   lcd.print("OFFSET");                                //Imprime mensagem
   lcd.setCursor(1,1);                                 //Posiciona cursor na coluna 1, linha 2
   lcd.print(" -01");                                  //Mostrador (apenas ilustrativo......)
   selet = 0x02;

   if(!digitalRead(buttonEnter))   t_enter = 0x01;
  
   if(digitalRead(buttonEnter) && t_enter && selet == 0x02)
   {
      t_enter = 0x00;
      menu = 0x02;
      lcd.clear();                                        //Limpa display
   }
} //end offset

void modoffset(){

   lcd.setCursor(0,0);                                   //Posiciona cursor na coluna 1, linha 1
   lcd.print("MODO OFFSET");                             //Imprime mensagem
   lcd.setCursor(1,1);                                   //Posiciona cursor na coluna 1, linha 2
   lcd.print("            ");                            //Mostrador (apenas ilustrativo......)
 
   if(!digitalRead(buttonEnter))   t_enter = 0x01;
  
   if(digitalRead(buttonEnter) && t_enter)
   {
      t_enter = 0x00;
      menu = 0x01;
      lcd.clear();                                        //Limpa display
   }

}
