#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//-----------------------------------------------------------------------------------------------------------------
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd_2(0x3F, 16, 2); //Kleines Display
LiquidCrystal_I2C lcd_4(0x27, 20, 4); //Grosses Display
//-----------------------------------------------------------------------------------------------------------------
int tempMin = 22;
int tempMax = 32;
int tempOFF = 36;

int sensorDurchfluss = 3;
int fanRelais = 6;
int pumpeRelais = 8;
int rotLed = 9;
int gruenLed = 12;
float tempCTank = 0;
float tempCLuft = 0;

byte degree[8]       = { B00010, B00101, B00010, B00000, B00000, B00000, B00000, B00000 };// Symbol für Grad
byte percentage_1[8] = { B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000 };// Lauflicht--------
byte percentage_2[8] = { B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000 };//------------------
byte percentage_3[8] = { B11100, B11100, B11100, B11100, B11100, B11100, B11100, B11100 };//------------------
byte percentage_4[8] = { B11110, B11110, B11110, B11110, B11110, B11110, B11110, B11110 };//------------------
byte percentage_5[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 };//------------------ 
//-----------------------------------------------------------------------------------------------------------------
void setup()
            {
             sensors.begin();
             pinMode(3, INPUT);
             pinMode(6, OUTPUT);
             pinMode(8, OUTPUT);
             pinMode(9, OUTPUT);
             pinMode(12, OUTPUT);
             Serial.begin(9600);
            lcd_2.begin();                                         //starte LCD Display
            lcd_4.begin();  
             lcd_2.backlight();                                    // LCD Hintergrundbeleuchtung einschalten
             lcd_4.backlight();
              lcd_4.createChar(6, degree);
              lcd_4.createChar(1, percentage_1);
              lcd_4.createChar(2, percentage_2);
              lcd_4.createChar(3, percentage_3);
              lcd_4.createChar(4, percentage_4);
              lcd_4.createChar(5, percentage_5);
              lcd_4.setBacklight(HIGH);
              lcd_4.setCursor(0,0);
              lcd_4.print ("       SYSTEM       ");
              lcd_4.setCursor(0,1);
              lcd_4.print ("        WIRD        ");
              lcd_4.setCursor(0,2);
              lcd_4.print ("    INITIALISIERT   ");
              lcd_4.setCursor(0,3);
              for (int i=0; i<20; ++i ){for(int j=0; j<5;j++)
                                      {lcd_4.setCursor(i,3);
                                       lcd_4.write(j);
                                       delay(20);}} 
                                        
              lcd_4.clear();
              lcd_2.clear();
              digitalWrite(pumpeRelais,LOW); // LOW = Relais ist geschalten ---- HIGGH = Relais ist nicht geschalten
              digitalWrite(fanRelais,LOW);
}

void loop()
{
  digitalWrite(pumpeRelais,HIGH);
 // Send the command to get temperatures
  sensors.requestTemperatures();
  tempCTank = (sensors.getTempCByIndex(0));
  tempCLuft = (sensors.getTempCByIndex(1));
  Serial.println(tempCTank,0);
  Serial.println(tempCLuft,2);
   lcd_2.setCursor(0, 0);
    lcd_2.print("Durchflussmenge");
     lcd_2.setCursor(10, 1);
      lcd_2.print("l/min");
  lcd_4.setCursor(0, 0);
   lcd_4.print("Spindelueberwachung");
    lcd_4.setCursor(3, 1);
     lcd_4.print("--------------");
  lcd_4.setCursor(0, 2);
   lcd_4.print("Tank-->Temp:");
    lcd_4.println(tempCTank);
     lcd_4.setCursor(17, 2);
      lcd_4.write(6);
         lcd_4.print("C");
     lcd_4.setCursor(0, 3);
      lcd_4.print("Luft-->Temp:");
       lcd_4.println(tempCLuft); 
        lcd_4.setCursor(17, 3); 
        lcd_4.write(6);
         lcd_4.print("C");
  delay(1000);
}

