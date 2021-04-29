#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



const int potentiometer = A0; //From the main potentiometer
const int PWM = 3;

int voltage = 0;
int VALUE = 0;
int dutycycle = 0;

void setup() {
  pinMode(potentiometer, INPUT);
  pinMode(PWM, OUTPUT);
  //TCCR2B = TCCR2B & B11111000 | B00000001;    // pin 3 and 11 PWM frequency of 31372.55 Hz
  Serial.begin(9600);
  //set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {

  voltage = analogRead(potentiometer);
  VALUE = map(voltage, 0, 1023, 0, 255);
  analogWrite(PWM, VALUE);
  dutycycle = (VALUE * 100) / 255;

  Serial.print("Pot = ");
  Serial.print(voltage);

  Serial.print("  PWM = ");
  Serial.print(VALUE);

  Serial.print("  Volatge = ");
  Serial.print(map(VALUE, 0, 255, 0, 24));

  Serial.print("  DC = ");
  Serial.println(dutycycle);
  LCD();
  delay(10);

}

void LCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("POT= ");
  lcd.setCursor(4, 0);
  lcd.print(voltage);

  lcd.setCursor(8, 0);
  lcd.print(";DC=");
  lcd.setCursor(12, 0);
  lcd.print(dutycycle);
  lcd.setCursor(15, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("PWM=");
  lcd.setCursor(5, 1);
  lcd.print(VALUE);

  lcd.setCursor(8, 1);
  lcd.print(";V =");
  lcd.setCursor(12, 1);
  lcd.print(map(VALUE, 0, 255, 0, 24));

}
