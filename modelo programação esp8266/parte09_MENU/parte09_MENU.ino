
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// --- Mapeamento de Hardware ---
#define button    D3                                     //Botão para selecionar tela acima no digital 12


// --- Protótipo das Funções Auxiliares ---
void changeMenu();                                      //Função para modificar o menu atual
void dispMenu();                                        //Função para mostrar o menu atual
void temperatura();                                     //Função do menu1, temperatura 
void offset();                                          //Função do menu2, offset
void modoffset();

// --- Variáveis Globais ---
char menu = 0x01;                                       //Variável para selecionar o menu
boolean t_button;                                        //Flags para armazenar o estado dos botões


// --- Configurações Iniciais ---
void setup()
{
   Serial.begin(9600);                                  // Inicia a serial
   lcd.begin();
   lcd.backlight();
   lcd.setCursor(0, 0);
   lcd.print("INICIALIZANDO...");
  
   pinMode(button, INPUT);                             // Configura porta como entrada
   
   t_button   = 0x00;                                    //limpa flag do botão Up
 
   delay(2000);
   lcd.clear();                                         //Limpa display

} //end setup


// --- Loop Infinito ---
void loop()
{
      
     changeMenu();                              //Chama a carregar menu
     dispMenu();                                //Chama a função display



} //end loop

// --- Desenvolvimento das Funções Auxiliares ---
void changeMenu()                                       //Modifica o menu atual
{
   if(!digitalRead(button))   t_button   = 0x01;          //Botão Up pressionado? Seta flag
       
   if(digitalRead(button) && t_button)                    //Botão Up solto e flag setada?
   {                                                    //Sim...
      t_button = 0x00;                                   //Limpa flag
      
      lcd.clear();                                     //Limpa display
      menu++;                                           //Incrementa menu
      
      if(menu > 0x02) menu = 0x01;                      //Se menu maior que 4, volta a ser 1
   
   } //end button

} //end changeMenu

void dispMenu()                                         //Mostra o menu atual
{
    switch(menu)                                        //Controle da variável menu
    {
       case 0x01:                                       //Caso 1
             temperatura();                               //Chama a função de termômetro
             
             break;                                     //break
       case 0x02:                                       //Caso 2
             offset();                                  //Chama a função do offset
             
             break;                                     //break

    
    } //end switch submenu1

} //end dispMenu


void temperatura()                                      //Temperatura (menu2)
{
   lcd.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   lcd.print("Temperatura");                           //Imprime mensagem
   lcd.setCursor(1,1);                                 //Posiciona cursor na coluna 2, linha 2
   
   // Desenvolver uma função de data e hora...
   
   lcd.print("25 Celsius");                            //Mostrador (apenas ilustrativo......)   

} //end temperatura()

 void offset()                                        //Data e Hora (menu1)
{
    
   lcd.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   lcd.print("OFFSET");                                //Imprime mensagem
   lcd.setCursor(1,1);                                 //Posiciona cursor na coluna 1, linha 2
   
   // Desenvolver uma função de data e hora...
   
   lcd.print(" -01");                                  //Mostrador (apenas ilustrativo......)

} //end data_hora
