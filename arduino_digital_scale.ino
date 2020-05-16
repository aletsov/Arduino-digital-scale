#include "HX711.h"
#include <LiquidCrystal.h>
HX711 scale;
float elements = 2.5;
LiquidCrystal lcd(7,6,5,4,A0,A5);
const int BackLight = 8;
String LCDLine1,LCDLine2;
int n;
float rounded;
void updateLCD () {
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(LCDLine1);


 lcd.setCursor(0,1);
lcd.print(LCDLine2);

 }

 void setup() {
 Serial.begin(9600);
 Serial.println("HX711 Demo");
 lcd.begin(16,2);
 pinMode(BackLight, OUTPUT);
 digitalWrite(BackLight, HIGH);
 LCDLine1="Initializing ...";
 LCDLine2="";
 updateLCD();
69
 // parameter "gain" is ommited; the default value 128 is used by the library
 // HX711.DOUT - pin #A1
 // HX711.PD_SCK - pin #A0
 scale.begin(A4, A3);



 scale.set_scale(1900.f); // this value is obtained by calibrating the scale with known weights; see the README for details
 scale.tare(); // reset the scale to 0

 Serial.println("After setting up the scale:");

 Serial.print("read: \t\t");
 Serial.println(scale.read()); // print a raw reading from the ADC

 Serial.print("read average: \t\t");
 Serial.println(scale.read_average(20)); // print the average of 20 readings from the ADC

 Serial.print("get value: \t\t");
 Serial.println(scale.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight, set with tare()

 Serial.print("get units: \t\t");
 Serial.println(scale.get_units(10), 1); // print the average of 5 readings from the ADC minus tare weight, divided
 // by the SCALE parameter set with set_scale

 Serial.println("Readings:");
 }

 void loop() {
 float average = scale.get_units(10);
 if (average < 0.3)
 {
 average = 0;
 }


 float number = scale.get_units()/elements;//divide the average of 20 readings with the elements value to get the number of elements
 n = round(number);
 //n = (int)number; // convert float into int

 Serial.print("\t| elements:\t");
 Serial.print(n); //serial monitor

 // lcd.clear();
 //set cursor first row
 LCDLine1=String(average,1)+" g"; //print on lcd average value from 10 raw readings 1 time
 LCDLine2=String(n)+" pcs";

 Serial.print("\t| average:\t");
 Serial.println(average); // serial monitor -||-


 //print PCS

 scale.power_down(); // put the ADC in sleep mode
 delay(1000);
 scale.power_up();
 updateLCD();
 }
