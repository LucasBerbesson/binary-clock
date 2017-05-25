/*
An open-source binary clock for Arduino. 
Based on the code from by Rob Faludi (http://www.faludi.com)
Code under (cc) by Daniel Spillere Andrade, www.danielandrade.net
http://creativecommons.org/license/cc-gpl
*/
#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

// Init a Time-data structure
Time  t;


int second=0, minute=0, hour=0; //start the time on 00:00:00
int munit,hunit,valm=0,valh=0,ledstats,i;
int leds[4][4] = { 
 {17,1,17,0},
 {17,13,2,3},
 {10,9,7,4},
 {11,12,8,5}
};
void setup() { 
  //set outputs 
  for(int k=0;k<=13;k++) {
    pinMode(k, OUTPUT);
    digitalWrite(k, LOW);
    
  }
  Serial.begin(9600);
  Serial.println("setup...");
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  rtc.begin();
}

void loop() {
  t = rtc.getTime();
  second = t.sec;
  minute = t.min;
  hour = t.hour;
  Serial.println(second);


  munit = minute%10; //sets the variable munit and hunit for the unit digits
  hunit = hour%10;

  //minutes units
  if(munit == 1 || munit == 3 || munit == 5 || munit == 7 || munit == 9) {  digitalWrite(leds[3][3], HIGH);} else {  digitalWrite(leds[3][3],LOW);}
  if(munit == 2 || munit == 3 || munit == 6 || munit == 7) {digitalWrite(leds[2][3], HIGH);} else {digitalWrite(leds[2][3],LOW);}
  if(munit == 4 || munit == 5 || munit == 6 || munit == 7) {digitalWrite(leds[1][3], HIGH);} else {digitalWrite(leds[1][3],LOW);}
  if(munit == 8 || munit == 9) {digitalWrite(leds[0][3], HIGH);} else {digitalWrite(leds[0][3],LOW);}

  //minutes 
  if((minute >= 10 && minute < 20) || (minute >= 30 && minute < 40) || (minute >= 50 && minute < 60))  {digitalWrite(leds[3][2], HIGH);} else {digitalWrite(leds[3][2],LOW);}
  if(minute >= 20 && minute < 40)  {digitalWrite(leds[2][2], HIGH);} else {digitalWrite(leds[2][2],LOW);}
  if(minute >= 40 && minute < 60) {digitalWrite(leds[1][2], HIGH);} else {digitalWrite(leds[1][2],LOW);}

  //hour units
  if(hunit == 1 || hunit == 3 || hunit == 5 || hunit == 7 || hunit == 9) {digitalWrite(leds[3][1], HIGH);} else {digitalWrite(leds[3][1],LOW);}
  if(hunit == 2 || hunit == 3 || hunit == 6 || hunit == 7) {digitalWrite(leds[2][1], HIGH);} else {digitalWrite(leds[2][1],LOW);}
  if(hunit == 4 || hunit == 5 || hunit == 6 || hunit == 7) {digitalWrite(leds[1][1], HIGH);} else {digitalWrite(leds[1][1],LOW);}
  if(hunit == 8 || hunit == 9) {digitalWrite(leds[0][1], HIGH);} else {digitalWrite(leds[0][1],LOW);}


  //hour
  if(hour >= 10 && hour < 20)  {digitalWrite(leds[3][0], HIGH);} else {digitalWrite(leds[3][0],LOW);}
  if(hour >= 20 && hour < 24)  {digitalWrite(leds[2][0], HIGH);} else {digitalWrite(leds[2][0],LOW);}

   valm = digitalRead(A1);    // add one minute when pressed
   if(valm== HIGH) {
   minute++;
   second=0;
   rtc.setTime(hour, minute, second);
   delay(250);
  }

  valh = digitalRead(A2);    // add one hour when pressed
   if(valh==HIGH) {
   hour++;
   second=0;
   rtc.setTime(hour, minute, second);
   delay(250);
  }
  delay(50);
}
