
#include <Wire.h>  
#include <LiquidCrystal.h>

// 16 is A2
#define BUZZER_PIN 16

#define beep() tone(BUZZER_PIN, 2093, 50);

volatile int pedalDelay = 0;
volatile int oldPedal = 0;
volatile int newPedal = 0;
volatile long totalTime = 0;
volatile int pedalCount = 0;

// 810ish keeps my heart rate above 135
volatile int pedalThreshold = 810;

#define RIGHT  0
#define UP     1
#define DOWN   2
#define LEFT   3
#define SELECT 4
#define NONE   5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() 
{
  Serial.begin(9600);

  lcd.begin(16,2); 

  oldPedal = millis();
  pedalDelay = pedalThreshold;
  
  attachInterrupt(0, pedal, RISING);
}

void pedal()
{
  newPedal = millis();
  
  if (newPedal - oldPedal < 100)
    return;
  
  pedalCount++;
  
  pedalDelay = newPedal - oldPedal;
  oldPedal = newPedal; 
  
   totalTime += pedalDelay;

  if (pedalDelay > pedalThreshold)
    beep()
    
  Serial.println(pedalDelay);
}

void loop()
{
  int minutes, seconds, button;
  
  button = get_button();
  if (button == UP)
    pedalThreshold += 10;
  if (button == DOWN)
    pedalThreshold -= 10;
  
  seconds = totalTime / 1000;
  minutes = seconds / 60;
  seconds = seconds % 60;
  
  lcd.setCursor(0,0);
  if (minutes < 10)
    lcd.print(" ");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10)
    lcd.print("0");
  lcd.print(seconds);

  lcd.setCursor(10,0);
  lcd.print(pedalCount);
    
  lcd.setCursor(0,1);
  if (pedalDelay > 999)
    pedalDelay = 999;
  lcd.print(pedalDelay);
  lcd.setCursor(10,1);
  lcd.print(pedalThreshold);
  
  delay(200);
}

int get_button()
{ 
  int adc_key_in = analogRead(0);  

  if (adc_key_in > 1000) return NONE; 
  if (adc_key_in < 50)   return RIGHT;  
  if (adc_key_in < 195)  return UP; 
  if (adc_key_in < 380)  return DOWN; 
  if (adc_key_in < 555)  return LEFT; 
  if (adc_key_in < 790)  return SELECT;   
  
  return NONE;
}

