/*
project automatic retractable landing gear  
by: tinnakon kheowree  
tinnakon_za@hotmail.com
tinnakonza@gmail.com
https://sites.google.com/site/tinnakonkheowree/
http://quad3d-tin.lnwshop.com/
https://www.facebook.com/tinnakonza

2/04/2558  ,auto_landing_gear_328p_V1.ino  ,,Read Ultrasonic Module HC-SR04
3/04/2558  ,Auto_landing_gear_328p_V2.ino  ,,Write Retractable Landing Gear ,, Algorithm tin

support: 
-arduino 328p
-Ultrasonic Module HC-SR04 วัดระยะทาง
-DJI Phantom 1 & 2 Retractable Landing Gear
*/
#include <Arduino.h>
#include "Ultrasonic_gear.h"

int servoPos;
int servoPin = 9;
#define LEDPin 13

// Main loop variables
unsigned long previousTime = 0;
long Dt_roop = 20000;
float G_Dt = 0.01; 
int frameCounter =0;
int Status_LED = LOW;

void setup() {
 Serial.begin (9600);
 Serial.print("TK_automatic retractable landing gear");Serial.println("\t");
 pinMode(LEDPin, OUTPUT);
 UltrasonicInt();
 previousTime = micros();
}
void loop() {
   Dt_roop = micros() - previousTime;// 50 Hz task loop (10 ms) 
   if(Dt_roop <= 0)
   {
    Dt_roop = 20001; 
   }   
    if (Dt_roop >= 20000) //// 50 Hz task loop
    {
      previousTime = micros();
      G_Dt = Dt_roop*0.000001;
      frameCounter++;
      UltrasonicRead();
      //////Algorithm tin///////////////////////////////////////////////////////////////
      if(Altitude_sonaf > 1.1){
        servoPos = 1000;
      }
      if(Altitude_sonaf < 0.8){
        servoPos = 1900;
      }
      /////Write Retractable Landing Gear///////////////////////////////////////////////
       OCR1A = servoPos * 2 ;//PB1  set PWM data (1000 - 2000)*2 to (2000 - 4000)
       OCR1B = 10 * 2 ;//PB2 PIN = 10;//PB2 set PWM data create a trigger pulse for 10 us
      
       if (frameCounter % 10 == 0)//roop print  ,TASK_noHZ TASK_5HZ  TASK_10HZ
      {
      Serial.print(Altitude_sonaf);Serial.print("\t");
      //Serial.print(servoPos);Serial.print("\t");
      Serial.print("\n"); 
      }
       if (frameCounter >= 50) { // Reset frameCounter back to 0 after reaching 50 (1s)
             frameCounter = 0;
              if(Status_LED == LOW)
            {
            Status_LED = HIGH;
            }
            else
            {
            Status_LED = LOW;
            }
            digitalWrite(13, Status_LED);//A
     }//end roop 1 Hz
    }// 50 Hz task loop
}
