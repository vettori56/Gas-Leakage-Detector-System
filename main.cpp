#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int gasSensor = A0;
int led = 7;
int buzzer = 8;
int relay = 9;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {

  int gasValue = analogRead(gasSensor);

  String status;
  int fanState = 0;
  int buzzerState = 0;

  if (gasValue < 500) {
    status = "SAFE";
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);
  }

  else if (gasValue < 650) {
    status = "WARNING";
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);
  }

  else {
    status = "DANGER";
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
    fanState = 1;
    buzzerState = 1;
  }

  // LCD Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gasValue);

  lcd.setCursor(0, 1);
  lcd.print(status);

  // Send data to PC
  Serial.print(gasValue);
  Serial.print(",");
  Serial.print(status);
  Serial.print(",");
  Serial.print(fanState);
  Serial.print(",");
  Serial.println(buzzerState);

  delay(1000);
}