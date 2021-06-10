#include<SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 7
#define DHTTYPE DHT11
LiquidCrystal_I2C lcd(0x27,20,4);

//define the pin where different devices attached
int redLed = 12;
int greenLed = 11;
int buzzer = 13;
int smokeD = 9;
int fireD = 8;
DHT dht(DHTPIN, DHTTYPE);

//define the mode of the device attached
//it can be input or output
//initiate the devices
void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeD, INPUT);
  pinMode(fireD,INPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  delay(5000); //delay 5 seconds for smoke sensor to warm up, else may get wrong reading
}

void loop() {
//read temperature and humidity at all time
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
  }

//If smoke is detected, turn red led and buzzer on
//Display warning messages on LCD screen
//Print serial output to RasPi
  int smokeSensor = digitalRead(smokeD);
  int fireSensor = digitalRead(fireD);
  if (smokeSensor < 1) //By default, the smoke sensor digital output will be 1, and will become <1 when smoke is present
  {
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print(F("\"Zone\"\:\"1\"\,")); //Serial print information such as Zone, Humidity, Temperature, Heat Index, Fire and smoke presence
    Serial.print(F("\"Humidity\":\""));
    Serial.print(h);
    Serial.print(F("\",\"Temperature\":\""));
    Serial.print(t);
    Serial.print(F("\",\"HeatIndex\":\""));
    Serial.print(hic);
    Serial.print(F("\"\,"));
    Serial.print("\"Smoke\":\"TRUE\"\,");
    Serial.println("\"Fire\":\"SAFE\"");
    lcd.setCursor(1,0); //LCD print warning message
    lcd.print("Evacuate!");
    lcd.setCursor(1,1);
    lcd.println("   Smoke/Gas!  ");
    digitalWrite(redLed, HIGH); //Turn red LED on
    digitalWrite(greenLed, LOW); //Turn green LED off
    digitalWrite(buzzer, HIGH); //Turn buzzer on
    delay(30000); //The warning lasts for 30 seconds and will proceed to the next section
    lcd.clear();
  }
  else
//Default mode when there is no detection
//Print serial output to Raspi  
  {
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print(F("\"Zone\"\:\"1\"\,"));
    Serial.print(F("\"Humidity\":\""));
    Serial.print(h);
    Serial.print(F("\",\"Temperature\":\""));
    Serial.print(t);
    Serial.print(F("\",\"HeatIndex\":\""));
    Serial.print(hic);
    Serial.print(F("\"\,"));
    Serial.print("\"Smoke\":\"SAFE\"\,");
    Serial.println("\"Fire\":\"SAFE\"");
    lcd.setCursor(1,0);
    lcd.print("All Good");
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(10);
  }
  delay(1000);

//If fire is detected, turn red led and buzzer on
//Display warning messages on LCD screen
//Print serial output to RasPi
    if (fireSensor > 0) //Fire sensor will output 0 by default, when fire is present, value changes to >0
{
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print(F("\"Zone\"\:\"1\"\,"));
    Serial.print(F("\"Humidity\":\""));
    Serial.print(h);
    Serial.print(F("\",\"Temperature\":\""));
    Serial.print(t);
    Serial.print(F("\",\"HeatIndex\":\""));
    Serial.print(hic);
    Serial.print(F("\"\,"));
    Serial.print("\"Smoke\":\"SAFE\"\,");
    Serial.println("\"Fire\":\"TRUE\"");
    lcd.setCursor(1,0);
    lcd.print("Evacuate!");
    lcd.setCursor(1,1);
    lcd.println("     Fire!     ");
    digitalWrite(redLed,HIGH);
    digitalWrite(greenLed,LOW);
    digitalWrite(buzzer, HIGH);
    delay(30000);
    lcd.clear();
}
else
//Default mode when there is no detection
//Print serial output to Raspi  
{
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print(F("\"Zone\"\:\"1\"\,"));
    Serial.print(F("\"Humidity\":\""));
    Serial.print(h);
    Serial.print(F("\",\"Temperature\":\""));
    Serial.print(t);
    Serial.print(F("\",\"HeatIndex\":\""));
    Serial.print(hic);
    Serial.print(F("\"\,"));
    Serial.print("\"Smoke\":\"SAFE\"\,");
    Serial.println("\"Fire\":\"SAFE\"");
    lcd.setCursor(1,0);
    lcd.print("All Good");
    digitalWrite(redLed,LOW);
    digitalWrite(greenLed,HIGH);
    noTone(buzzer);
}
    delay(1000);
}
