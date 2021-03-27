
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// --- Mapeamento de Hardware ---
#define out            D0                               // GPIO02 led onbord vermelho
#define button         D5                               //Botão para selecionar no digital GPIO14
#define buttonEnter    D6                               //Botão para selecionar enter no digital GPIO12

// --- Protótipo das Funções Auxiliares ---
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
char counter  = 0x00;                                   //variável auxiliar de contagem

// --- Rotina de Interrupção ---
void ICACHE_RAM_ATTR onTimerISR(){
  
      timer1_write(100000);
      counter++;               // incrementa counter
    
 
    if(counter == 0x05) // counter 
      {                 // sim...
       digitalWrite(out, !digitalRead(out)); //Inverte o estado da saída de teste
        counter = 0x00; 
       
       } //end if counter 
 }
 
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
void changeMenu()                                       //Modifica o menu atual
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


void temperatura()                                      //Temperatura (menu1)
{
   lcd.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   lcd.print("Temperatura");                           //Imprime mensagem
   lcd.setCursor(1,1);                                 //Posiciona cursor na coluna 2, linha 2
   lcd.print("25 Celsius");                            //Mostrador (apenas ilustrativo......)   
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
  
   if(digitalRead(buttonEnter) && t_enter)
   {
      t_enter = 0x00;
      menu = 0x02;
      lcd.clear();                                        //Limpa display
   }
} //end offset

void modoffset(){

   lcd.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   lcd.print("MODO OFFSET");                           //Imprime mensagem
   lcd.setCursor(1,1);                                 //Posiciona cursor na coluna 1, linha 2
   lcd.print("            ");                          //Mostrador (apenas ilustrativo......)
 
   if(!digitalRead(buttonEnter))   t_enter = 0x01;
  
   if(digitalRead(buttonEnter) && t_enter)
   {
      t_enter = 0x00;
      menu = 0x01;
      lcd.clear();                                        //Limpa display
   }

}
