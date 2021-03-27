#define  led1       D0                    // gpio16 led onbord vermelho
#define  led2       D4                    // gpio02 led onbord azul
#define  button     D3                    // gpio00 button

// --- Protótipo das Funções Auxiliares ---
void changeButt();                                      //Função para modificar o estado do led

// --- Variáveis Globais ---
boolean auxButton, t_butt;                    // auxiliar para o button

void setup() 
{
  Serial.begin(9600);                      // Inicia a serial
  pinMode(led1, OUTPUT);                   // Configura porta como saida
  pinMode(led2, OUTPUT);                   // Configura porta como saida
  pinMode(button, INPUT);                  // Configura porta como entrada

  auxButton  = 0x00;                       //limpa flag do auxButton
  t_butt     = 0x00;                       //limpa flag do t_butt

  digitalWrite(led1, HIGH);                              //Lâmpada 1 inicia apagada
  digitalWrite(led2, HIGH);                              //Lâmpada 2 inicia apagada
}

void loop() 
{
  
   auxButton = digitalRead(button);       // Faz a leitura na porta e adiciona na variavel
  
   if(auxButton == HIGH){
    digitalWrite(led1, HIGH);            // coloca a porta led1 em nivel alto
    
   } else{
    digitalWrite(led1, LOW);             // coloca a porta led1 em nivel baixo
  }

  changeButt();
  delay(80);
   
 }// end loop

 void changeButt(){

      if(!digitalRead(button))   t_butt   = 0x01;         //Botão pressionado? Seta flag

      if(digitalRead(button) && t_butt)                   //Botão Up solto e flag setada?
      {                                                   //Sim...
        digitalWrite(led2, !digitalRead(led2));           //Inverte o estado da saída do led
        t_butt = 0x00;                                    //Limpa flag
     
      } //end setbutton
 }//end chargeButt
