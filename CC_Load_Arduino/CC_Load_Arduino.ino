// include the libraries
#include <LiquidCrystal.h>
#include <RotaryEncoder.h>
#include <PCF8591.h>
#include "defines.h"
#include "helper_functions.h"

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// A pointer to the dynamic created rotary encoder instance
RotaryEncoder *encoder = nullptr;

// ADC/DAC converter
PCF8591 pcf8591(PCF8591_I2C_ADDRESS);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // setup the rotary encoder functionality
  encoder = new RotaryEncoder(ENCOD_PIN_IN1, ENCOD_PIN_IN2, RotaryEncoder::LatchMode::TWO03);

  // register interrupt routine
  attachInterrupt(digitalPinToInterrupt(ENCOD_PIN_IN1), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCOD_PIN_IN2), checkPosition, CHANGE);
  
	pcf8591.begin();

  pinMode(FAN_PIN, OUTPUT);

  // Print a message to the LCD.
  lcdPrintWelcomeMessage();
  delay(1500);
}

void loop() {
  static int pos = 0;
  static int posPrev = 0;
  static float Iset = 0;
  static int outputCurr = 0;

  /* Read input */
  int currAnaIn = analogRead(CURR_READ_PIN);
  int voltAnaIn = analogRead(VOLT_READ_PIN);
  int tempAnaIn = analogRead(TEMP_READ_PIN);

  if(currAnaIn >= 1) { currAnaIn -= 1;}

  /* Calculate physical values */
  float current = currAnaIn * 0.04795383256f;
  float voltage = voltAnaIn * 0.028330424f;
  float power = voltage * current;
  float temperature = tempAnaIn;

  /* Handle encoder */
  encoder->tick(); // just call tick() to check the state.
  pos = encoder->getPosition();

  if(pos > posPrev){
    Iset -= 0.1;
  }
  else if(pos < posPrev){
    Iset += 0.1;
  }
  posPrev = pos;

  if(Iset < 0){
    Iset = 0;
  }
  if(Iset > 3){
    Iset = 3;
  }

  /* Print frist line */
  lcd.setCursor(0, 0);
  lcd.print("SET=");
  lcd.print(Iset);
  lcd.print(" ");
  lcd.print("C=");
  lcd.print(current);
  lcd.print("     ");


  /* Print second line */
  lcd.setCursor(0, 1);
  lcd.print("  V=");
  lcd.print(voltage);
  //lcd.print(" P=");
  //lcd.print(power);
  lcd.print(" P=");
  lcd.print(power);
  lcd.print("        ");
  
  outputCurr = Iset * 67;
  if(current > Iset){
    outputCurr -= 2;
  }
  else if(current < Iset){
    outputCurr += 2;
  }
  
  if(Iset <= 0.05){
    outputCurr = 0;
  }

  /* Set the current with DAC output */
  pcf8591.analogWrite(outputCurr);

  // Turn on the fan if needed 
  // 515 is room temperature, 22°, 580 is around 30°
  if(temperature > 650){
    analogWrite(FAN_PIN, 255);
  }
  else if(temperature > 580){
    analogWrite(FAN_PIN, 127);
  }
  else{
    analogWrite(FAN_PIN, 0);
  }
}
