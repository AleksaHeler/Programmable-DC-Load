
extern RotaryEncoder *encoder;
extern LiquidCrystal lcd;

// This interrupt routine will be called on any change of one of the input signals
void checkPosition()
{
  encoder->tick(); // just call tick() to check the state.
}

void lcdPrintWelcomeMessage()
{
  lcd.setCursor(0, 0);
  lcd.print("CC/CP LOAD");
  lcd.setCursor(0, 1);
  lcd.print("-Aleksa Heler-");
}