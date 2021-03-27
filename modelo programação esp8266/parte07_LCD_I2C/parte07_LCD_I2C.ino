#include <LiquidCrystal_I2C.h>

// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(0x27, 20, 4);
// --------Protótipo das funções----------//
void clear_LCD();


signed short minutes, secondes;
char timeline[16];
boolean lcd_clr = 0;

void setup() {

  lcd.begin();
  
  // Turn on the backlight.
  lcd.backlight();

  // Move the cursor characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(5, 0);

  // Print HELLO to the screen, starting at 5,0.
  lcd.print("HELLO WORLD");


}

void loop() {

  lcd.setCursor(3, 1);
  sprintf(timeline,"%0.2d mins %0.2d secs", minutes, secondes);
  lcd.print(timeline);
  
  delay(1000);
  secondes++;
  
  if (secondes == 60)
  {
    secondes = 0;
    minutes ++;
    lcd_clr = 1;
    clear_LCD();
  }
  

}
void clear_LCD(){

if(lcd_clr){                                       // lcd_clr setada?
                                                   // sim
  lcd.setCursor(0, 0);                             // posiciona o cursor na primeira linha e na primero coluna
  lcd.print("                ");                   // apaga a linha toda
  lcd_clr = 0;                                     // invalida o laço
  }
 }
