/*
An open-source binary clock for Arduino.
Based on the code from by Rob Faludi (http://www.faludi.com)
Code under (cc) by Lucas Berbesson
http://creativecommons.org/license/cc-gpl
*/
#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

// Init a Time-data structure
Time  t;

int second=0, minute=57, hour=21; //start the time on 00:00:00
int munit,hunit,minuteTens,hourTens,valm=0,valh=0,ledstats,i;
// LEDS positions matrix
int leds[4][4] = {
 {17,1,17,0},
 {17,13,2,3},
 {10,9,7,4},
 {11,12,8,5}
};


void turnoff() {
  for(int k=0;k<=13;k++) {
    pinMode(k, OUTPUT);
    digitalWrite(k, LOW);
  }
}

void setup() {
  //set outputs
  for(int k=0;k<=13;k++) {
    pinMode(k, OUTPUT);
    digitalWrite(k, HIGH);
  }
  delay(500);
  turnoff();

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  rtc.begin();
}

void loop() {


  t = rtc.getTime();
  second = t.sec;
  minute = t.min;
  hour = t.hour;


  if ( 0 < hour && hour < 8) {
    turnoff();
  } else {
    munit = minute%10; //sets the variable munit and hunit for the unit digits
    hunit = hour%10;
    minuteTens = (int)(minute/10);
    hourTens = (int)(hour/10);
    //minutes units
    if(munit & 1) {  digitalWrite(leds[3][3], HIGH);} else {  digitalWrite(leds[3][3],LOW);}
    if(munit & 2) {digitalWrite(leds[2][3], HIGH);} else {digitalWrite(leds[2][3],LOW);}
    if(munit & 4) {digitalWrite(leds[1][3], HIGH);} else {digitalWrite(leds[1][3],LOW);}
    if(munit & 8) {digitalWrite(leds[0][3], HIGH);} else {digitalWrite(leds[0][3],LOW);}

    //minutes
    if(minuteTens & 1)  {digitalWrite(leds[3][2], HIGH);} else {digitalWrite(leds[3][2],LOW);}
    if(minuteTens & 2)  {digitalWrite(leds[2][2], HIGH);} else {digitalWrite(leds[2][2],LOW);}
    if(minuteTens & 4) {digitalWrite(leds[1][2], HIGH);} else {digitalWrite(leds[1][2],LOW);}

    //hour units
    if(hunit & 1) {digitalWrite(leds[3][1], HIGH);} else {digitalWrite(leds[3][1],LOW);}
    if(hunit & 2) {digitalWrite(leds[2][1], HIGH);} else {digitalWrite(leds[2][1],LOW);}
    if(hunit & 4) {digitalWrite(leds[1][1], HIGH);} else {digitalWrite(leds[1][1],LOW);}
    if(hunit & 8) {digitalWrite(leds[0][1], HIGH);} else {digitalWrite(leds[0][1],LOW);}

    //hour
    if(hourTens & 1)  {digitalWrite(leds[3][0], HIGH);} else {digitalWrite(leds[3][0],LOW);}
    if(hourTens & 2)  {digitalWrite(leds[2][0], HIGH);} else {digitalWrite(leds[2][0],LOW);}

  }

   valm = digitalRead(A1);    // add one minute when pressed
   if(valm== HIGH) {
   minute++;
   if (minute>=60) {
    minute = 0;
   }
   second=0;
   rtc.setTime(hour, minute, second);
   delay(200);
  }

  valh = digitalRead(A2);    // add one hour when pressed
   if(valh==HIGH) {
   hour++;
   if (hour>=24) {
    hour = 0;
   }
   second=0;
   rtc.setTime(hour, minute, second);
   delay(200);
  }
  delay(50);
}

