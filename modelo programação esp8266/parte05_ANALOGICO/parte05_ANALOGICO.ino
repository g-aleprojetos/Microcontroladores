
// --- Variáveis Globais ---
int sensorAnalogico = A0;
int analogico;

void setup() {
Serial.begin(9600); 
analogico = 0;

}

void loop()       //main loop

{
analogico = analogRead(sensorAnalogico);

  Serial.println(analogico);

  delay(1000);
}
