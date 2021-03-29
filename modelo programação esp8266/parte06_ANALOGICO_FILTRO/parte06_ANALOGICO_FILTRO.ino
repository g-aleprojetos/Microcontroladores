

// ======================================================================================================== //
// --- Constantes Auxiliares ---
#define     num    100         //número de iterações da média móvel

// ======================================================================================================== //
// --- Protótipo das Funções ---
long moving_average(int sig);
void temp();


// ======================================================================================================== //
// --- Variáveis Globais ---
int sensorAnalogico = A0;
int values[num];             //vetor com num posições, armazena os valores para cálculo da média móvel
int adc_noise1;              //armazena a leitura sem filtro da entrada analógica
int adc_noise2;              //armazena a leitura filtrada da entrada analógica
int offset = 40;
int valorTemp = 0;

float temperature = 0.0,       //Armazena a temperatura em graus Celsius
     current_temp = 0.0;      //Armazena a temperatura atual

void setup() {
Serial.begin(115200); 
Serial.println("inicializando");

}

void loop()       //main loop

{

 temp();

}

// ======================================================================================================== //
// --- Desenvolvimento das Funções ---
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

// ************************************************************************************************************ //

void temp()
{
adc_noise1 = analogRead(sensorAnalogico);
adc_noise2 = moving_average(adc_noise1);
temperature = ((adc_noise2 * 3.3)/1024.0);
temperature = temperature * 100;
temperature = temperature - offset;

  if(temperature < (current_temp - 1.0) || temperature > (current_temp + 1.0))
  {
      current_temp = temperature;              //atualiza temperatura atual

       valorTemp = (int) temperature; 
     
      Serial.println(valorTemp);

   } //end if

  delay(80);
  
}//fim void temp
