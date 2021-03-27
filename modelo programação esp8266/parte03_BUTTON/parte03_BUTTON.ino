#define  led1       D0                    // gpio16 led onbord vermelho
#define  led2       D4                    // gpio02 led onbord azul
#define  button     D2                    // gpio00 button

// --- Variáveis Globais ---
boolean auxButton = 0;                    // auxiliar para o button

void setup() 
{
  Serial.begin(9600);                      // Inicia a serial
  pinMode(led1, OUTPUT);                   // Configura porta como saida
  pinMode(led2, OUTPUT);                   // Configura porta como saida
  pinMode(button, INPUT);                  // Configura porta como entrada
  
}

void loop() 
{
   auxButton = digitalRead(button);       // Faz a leitura na porta e adiciona na variavel

   if(auxButton == HIGH){
    digitalWrite(led1, HIGH);            // coloca a porta led1 em nivel alto
    digitalWrite(led2, LOW);             // coloca a porta led2 em nivel baixo
   
   } else{
    digitalWrite(led1, LOW);             // coloca a porta led1 em nivel baixo
    digitalWrite(led2, HIGH);            // coloca a porta led2 em nivel alto
     
   }
 
}
