
#define PCF8591_I2C_ADDRESS 0x48

#define TEMP_BASE_CALIB 130 // 130 ADC value is general room temperature
#define TEMP_BASE_FACT 1 // For every ADC count, how many degrees celsius to go up

#define ENCOD_PIN_IN1 9
#define ENCOD_PIN_IN2 10

#define CURR_READ_PIN A0
#define VOLT_READ_PIN A1
#define TEMP_READ_PIN A2

#define FAN_PIN 13

// initialize the LCD by associating any needed interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;