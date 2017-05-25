/***********************************************************
Description: Horloge binaire
***********************************************************/

// definir l'heure a l'allumage ici
int second=0, minute=0, hour=0;


int munit,hunit,valm=0,valh=0,ledstats,i;
// Matrice de description des positions des LEDS
int leds[4][4] = {
 {17,2,17,1},
 {17,5,4,3},
 {9,8,7,6},
 {13,12,11,10}
};
void setup() {
//set outputs
for(int k=0;k<=13;k++) {
  pinMode(k, OUTPUT);
  digitalWrite(k, LOW);

}
hour = 16;
minute = 54;
second=0;
}

void loop() {

static unsigned long lastTick = 0;
// Cette variable va nous permettre de compter les secondes qui passent
// dans la boucle qui suit
if (millis() - lastTick >= 1000) {
  lastTick = millis();
  second++;
}

// On avance d'une minute toutes les 60 secondes
  if (second >= 60) {
  minute++;
  second = 0; // et les secondes repartent a 0
}

// On avance d'une heure toutes les 60 minutes
if (minute >=60) {
  hour++;
  minute = 0; // et les minutes repartent a 0
}

// On avance d'une journee toutes les 24 heures
if (hour >=24) {
  hour  = 0;
  minute  = 0; // et les heures repartent a 0
}

  // Le calcul qui suit permet de convertir l'heure en systeme binaire
  munit = minute%10; // reste de la division des minutes par 10
  hunit = hour%10; // reste de la division des heures par 10

  //conversion des minutes. Chaque ligne gere une ligne de la quatrieme colonne.
  if(munit == 1 || munit == 3 || munit == 5 || munit == 7 || munit == 9) {  digitalWrite(leds[3][3], HIGH);} else {  digitalWrite(leds[3][3],LOW);}
  if(munit == 2 || munit == 3 || munit == 6 || munit == 7) {digitalWrite(leds[2][3], HIGH);} else {digitalWrite(leds[2][3],LOW);}
  if(munit == 4 || munit == 5 || munit == 6 || munit == 7) {digitalWrite(leds[1][3], HIGH);} else {digitalWrite(leds[1][3],LOW);}
  if(munit == 8 || munit == 9) {digitalWrite(leds[0][3], HIGH);} else {digitalWrite(leds[0][3],LOW);}

  //conversion des dizaines de minutes. Chaque ligne gere une ligne de la troisieme colonne.
  if((minute >= 10 && minute < 20) || (minute >= 30 && minute < 40) || (minute >= 50 && minute < 60))  {digitalWrite(leds[3][2], HIGH);} else {digitalWrite(leds[3][2],LOW);}
  if(minute >= 20 && minute < 40)  {digitalWrite(leds[2][2], HIGH);} else {digitalWrite(leds[2][2],LOW);}
  if(minute >= 40 && minute < 60) {digitalWrite(leds[1][2], HIGH);} else {digitalWrite(leds[1][2],LOW);}

  //conversion des heures. Chaque ligne gere une ligne de la deuxieme colonne.
  if(hunit == 1 || hunit == 3 || hunit == 5 || hunit == 7 || hunit == 9) {digitalWrite(leds[3][1], HIGH);} else {digitalWrite(leds[3][1],LOW);}
  if(hunit == 2 || hunit == 3 || hunit == 6 || hunit == 7) {digitalWrite(leds[2][1], HIGH);} else {digitalWrite(leds[2][1],LOW);}
  if(hunit == 4 || hunit == 5 || hunit == 6 || hunit == 7) {digitalWrite(leds[1][1], HIGH);} else {digitalWrite(leds[1][1],LOW);}
  if(hunit == 8 || hunit == 9) {digitalWrite(leds[0][1], HIGH);} else {digitalWrite(leds[0][1],LOW);}


  //conversion des dizaines d'heures. Chaque ligne gere une ligne de la premiere colonne.
  if(hour >= 10 && hour < 20)  {digitalWrite(leds[3][0], HIGH);} else {digitalWrite(leds[3][0],LOW);}
  if(hour >= 20 && hour < 24)  {digitalWrite(leds[2][0], HIGH);} else {digitalWrite(leds[2][0],LOW);}
}
