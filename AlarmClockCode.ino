#include <LiquidCrystal.h>
#include <DS3231.h>
#include <Wire.h>
#include <Arduino.h>
#define buzzer 3
#define  C     2100
#define  D     1870 
#define  E     1670
#define  f     1580
#define  G     1400 
#define  R     0
int melody[] = {E, E, E,R,
 E, E, E,R,
 E, G, C, D, E, R,
 f, f, f,f, f, E, E,E, E, D ,D,E, D, R, G ,R,
 E, E, E,R,
 E, E, E,R,
 E, G, C, D, E, R,
 f, f, f,f, f, E, E, E,  G,G, f, D, C,R };
 int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
 // Set overall tempo
 long tempo = 10000;
 // Set length of pause between notes
 int pause = 1000;
 // Loop variable to increase Rest length
 int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES
 // Initialize core variables
 int tone_ = 0;
 int beat = 0;
 long duration  = 0;

//     for (int i=0; i<MAX_COUNT; i++) {
//    tone_ = melody[i];
//    beat = 50;
//
//    duration = beat * tempo; // Set up timing
//
//    jinglebell();
//    // A pause between notes...
//    delayMicroseconds(pause);
//  }
DS3231 rtc(Wire);

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal mylcd(rs, en, d4, d5, d6, d7);
int menu = 0;
bool h12;
bool pm;
int currenthour = 1;
int currentminute = 0;
int currentmonth = 1;
int currentday = 1;
int currentyear = 1;
int alarmhour = 1;
int alarmminute = 0;
int alarmmonth = 0;
int alarmday = 1;
int alarmyear = 1;
const int currentsecond = 0;
const int debounce = 500;
void DisplayTimeAndDate() {
  bool h12 = true;
  bool pm = true;
  bool Century;
  byte hour = rtc.getHour(h12, pm);
  byte minute = rtc.getMinute();
  byte second = rtc.getSecond();
  byte month = rtc.getMonth(Century);
  byte day = rtc.getDate();
  byte year = rtc.getYear();
  mylcd.clear();
  mylcd.setCursor(0,0);
  mylcd.print("Time:");
  if (hour < 10){
    mylcd.print("0");
  }
  mylcd.print(hour);
  mylcd.print(":");
  if (minute < 10){
    mylcd.print("0");
  }
  mylcd.print(minute);
  mylcd.print(":");
  if (second < 10){
    mylcd.print("0");
  }
  mylcd.print(second);
  mylcd.print(" ");
  if (pm == true){
    mylcd.print("PM");
  }
  else {
    mylcd.print("AM");
  }
  mylcd.setCursor(0,1);
  mylcd.print("Date: ");
  if (month < 10){
    mylcd.print("0");
  }
  mylcd.print(month);
  mylcd.print("/");
  if (day < 10){
    mylcd.print("0");
  }
  mylcd.print(day);
  mylcd.print("/");
  if (year < 10){
    mylcd.print("0");
  }
  mylcd.print(year);
    if (currentyear == alarmyear && 
        currentmonth == alarmmonth && 
        currentday == alarmday && 
        currenthour == alarmhour && 
        currentminute == alarmminute) {
        
        // Trigger the alarm
        digitalWrite(buzzer, HIGH); // Turn on the buzzer
        delay(10000); // Sound the buzzer for 1 second
        digitalWrite(buzzer, LOW); // Turn off the buzzer
    }

  if (digitalRead(4) == HIGH){
    menu = 1;
    delay(debounce);
  }
}

void DisplaySetHours () {
  mylcd.clear();
  mylcd.setCursor(0,0);
  mylcd.print("Setting Hour: ");
  mylcd.setCursor(0,1);
  if (digitalRead(6) == HIGH) {
    currenthour = currenthour + 1;
    if (currenthour > 12){
      currenthour = 0;
    }
    delay(debounce);
  }
  else if (digitalRead(5) == HIGH){
    currenthour = currenthour - 1;
    if (currenthour < 0){
      currenthour = 0;
    }
    delay(debounce);
  }
  mylcd.setCursor(0,1);
  if (currenthour < 10) {
    mylcd.print("  ");
  } else {
    mylcd.print(" ");
  }
  mylcd.print(currenthour, DEC);

  if (digitalRead(4) == HIGH) {
    menu = 3;
    delay(debounce);
  }
}

void DisplaySetMinutes(){
  mylcd.clear();
  mylcd.setCursor(0,0);
  mylcd.print("Setting Minutes:");
  mylcd.setCursor(0,1);
  if (digitalRead(6) == HIGH){
    currentminute = currentminute + 1;
    if (currentminute > 60){
      currentminute = 0;
    }
    delay(debounce);
  }
  else if (digitalRead(5) == HIGH){
    currentminute = currentminute - 1;
    if (currentminute < 0){
      currentminute = 0;
    }
    delay(debounce);
  }
  if (currentminute < 10) {
    mylcd.print("  ");
  } else {
    mylcd.print(" ");
  }
  mylcd.print(currentminute, DEC);

  if (digitalRead(4) == HIGH){
    menu = 4;
    delay(debounce);
}
}

void jinglebell (){
  mylcd.clear();
long elapsed_time = 0;
 if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
   //  played less long than 'duration', pulse speaker HIGH and LOW
      while (elapsed_time < duration) {
       digitalWrite(buzzer,HIGH);
       delayMicroseconds(tone_ / 2);
       // DOWN
       digitalWrite(buzzer, LOW);
       delayMicroseconds(tone_ / 2);
       // Keep track of how long we pulsed
       elapsed_time += (tone_);
    }
  }
   else { // Rest beat; loop times delay
     for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
       delayMicroseconds(duration); 
    } 
  }                                
}

void DisplayAMorPM(){
  mylcd.clear();
  mylcd.setCursor(0,0);
  mylcd.print("AM or PM?");
  if (digitalRead(6) == HIGH){
    pm = false;
    delay(debounce);
  }
  if (digitalRead(5) == HIGH){
    pm = true;
    delay(debounce);
  }
if (pm == false){
      mylcd.clear();
      mylcd.setCursor(0,0);
      mylcd.print("AM or PM?");
      mylcd.setCursor(0,1);
      mylcd.print("AM");
}
else{
      mylcd.clear();
      mylcd.setCursor(0,0);
      mylcd.print("AM or PM?");
      mylcd.setCursor(0,1);
      mylcd.print("PM");
}
if (digitalRead(4) == HIGH){
  menu = 5;
  delay(debounce);
}
}
void DisplaySetMonth(){
  mylcd.clear();
  mylcd.setCursor(0,0);
  mylcd.print("Setting Month:");
  mylcd.setCursor(0,1);
  if (digitalRead(6) == HIGH){
    currentmonth = currentmonth + 1;
    if (currentmonth > 12){
      currentmonth = 0;
    }
    delay(debounce);
  }
  else if (digitalRead(5) == HIGH){
    currentmonth = currentmonth - 1;
    if (currentmonth < 0){
      currentmonth = 0;
    }
    delay(debounce);
  }
if (currentmonth < 10) {
    mylcd.print("  ");
  } else {
    mylcd.print(" ");
  }
  mylcd.print(currentmonth, DEC);
if (digitalRead(4) == HIGH){
  menu = 7;
  delay(debounce);
}
}

void DisplaySetDay(){
  mylcd.clear();
  mylcd.setCursor(0,0);
  mylcd.print("Setting Day:");
  mylcd.setCursor(0,1);
  if (digitalRead(6) == HIGH){
    currentday = currentday + 1;
    if (currentday > 31){
      currentday = 1;
    }
    delay(debounce);
  }
  else if (digitalRead(5) == HIGH){
    currentday = currentday - 1;
    if (currentday < 1){
      currentday = 1;
    }
    delay(debounce);
  }
  if (currentday < 10) {
    mylcd.print("  ");
  } else {
    mylcd.print(" ");
  }
  mylcd.print(currentday, DEC);
  if (digitalRead(4) == HIGH){
    menu = 8;
    delay(debounce);
  }
}

void DisplaySetYear(){
  mylcd.clear();
  mylcd.setCursor(0,0);
  mylcd.print("Setting Year:");
  mylcd.setCursor(0,1);
  if (digitalRead(6) == HIGH){
    currentyear = currentyear + 1;
    if (currentyear > 99){
      currentyear = 1;
    }
  }
  else if (digitalRead(5) == HIGH){
    currentyear = currentyear - 1;
    if (currentyear < 1){
      currentyear = 1;
    }
  }
    if (currentyear < 10) {
    mylcd.print("  ");
  } else {
    mylcd.print(" ");
  }
  mylcd.print(currentyear);
  if (digitalRead(4) == HIGH){
    menu = 9;
    delay(debounce);
  }
}
void DisplaySetAlarmHours() {
  mylcd.clear();
  mylcd.setCursor(0, 0);
  mylcd.print("Setting Alarm Hour:");
  mylcd.setCursor(0, 1);

  if (digitalRead(6) == HIGH) {
    alarmhour = alarmhour + 1;
    if (alarmhour > 12) {
      alarmhour = 1;
    }
    delay(debounce);
  }
  else if (digitalRead(5) == HIGH) {
    alarmhour = alarmhour - 1;
    if (alarmhour < 1) {
      alarmhour = 12;
    }
    delay(debounce);
  }

  if (alarmhour < 10) {
    mylcd.print("  ");
  } else {
    mylcd.print(" ");
  }
  mylcd.print(alarmhour, DEC);

  if (digitalRead(4) == HIGH) {
    menu = 13;
    delay(debounce);
  }
}
void DisplaySetAlarmMinutes() {
  mylcd.clear();
  mylcd.setCursor(0, 0);
  mylcd.print("Setting Alarm Min:");
  mylcd.setCursor(0, 1);

  if (digitalRead(6) == HIGH) {
    alarmminute = alarmminute + 1;
    if (alarmminute >= 60) { 
      alarmminute = 0; 
    }
    delay(debounce);
  }

  else if (digitalRead(5) == HIGH) {
    alarmminute = alarmminute - 1;
    if (alarmminute < 0) {
      alarmminute = 59;
    }
    delay(debounce);
  }

  if (alarmminute < 10) {
    mylcd.print("  ");
  } else {
    mylcd.print(" ");
  }
  mylcd.print(alarmminute, DEC);

  if (digitalRead(4) == HIGH) {
    menu = 14;
    delay(debounce);
  }
}

void DisplaySetAlarmMonth() {
  mylcd.clear();
  mylcd.setCursor(0, 0);
  mylcd.print("Setting Alarm Month:");
  mylcd.setCursor(0, 1);

  if (digitalRead(6) == HIGH) {
    alarmmonth = alarmmonth + 1;
    if (alarmmonth > 12) {
      alarmmonth = 1;
    }
    delay(debounce);
  }
  else if (digitalRead(5) == HIGH) {
    alarmmonth = alarmmonth - 1;
    if (alarmmonth < 1) {
      alarmmonth = 12;
    }
    delay(debounce);
  }

  if (alarmmonth < 10) {
    mylcd.print("  ");
  } else {
    mylcd.print(" ");
  }
  mylcd.print(alarmmonth, DEC);

  if (digitalRead(4) == HIGH) {
    menu = 16;
    delay(debounce);
  }
}

void DisplaySetAlarmYear() {
  mylcd.clear();
  mylcd.setCursor(0, 0);
  mylcd.print("Setting Alarm Year:");
  mylcd.setCursor(0, 1);

  if (digitalRead(6) == HIGH) {
    alarmyear = alarmyear + 1;
    if (alarmyear > 99) {
      alarmyear = 1;
    }
    delay(debounce);
  }
  else if (digitalRead(5) == HIGH) {
    alarmyear = alarmyear - 1;
    if (alarmyear < 1) {
      alarmyear = 99;
    }
    delay(debounce);
  }

  if (alarmyear < 10) {
    mylcd.print("  ");
  } else {
    mylcd.print(" ");
  }
  mylcd.print(alarmyear, DEC);

  if (digitalRead(4) == HIGH) {
    menu = 17;
    delay(debounce);
  }
}
void SaveData(){
  rtc.setHour(currenthour);
  rtc.setMinute(currentminute);
  rtc.setSecond(currentsecond);
  rtc.setMonth(currentmonth);
  rtc.setYear(currentyear);
  rtc.setDate(currentday);
}
void setup () {
  mylcd.begin(16,2);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop () {
  if (menu == 0){
    DisplayTimeAndDate();
  }
  else if (menu == 1){
    mylcd.clear();
    mylcd.setCursor(0,0);
    mylcd.print("Would you like");
    mylcd.setCursor(0,1);
    mylcd.print("to set the time?");
    if (digitalRead(6) == HIGH){
      menu = 2;
      delay(debounce);
    }
    else if (digitalRead(5) == HIGH){
      menu = 5;
      delay(debounce);
    }
  }
  else if (menu == 2){
    DisplaySetHours();
  }
  else if (menu == 3){
    DisplaySetMinutes();
  }
  else if (menu == 4){
    DisplayAMorPM();
  }
  else if (menu == 5){
    mylcd.clear();
    mylcd.setCursor(0,0);
    mylcd.print("Would you like");
    mylcd.setCursor(0,1);
    mylcd.print("to set the date?");
    if (digitalRead(6) == HIGH){
      menu = 6;
      delay(debounce);
    }
    else if (digitalRead(5) == HIGH){
      menu = 9;
      delay(debounce);
    }
  }
  else if (menu == 6){
    DisplaySetMonth();
  }
  else if (menu == 7){
    DisplaySetDay();
  }
  else if (menu == 8){
    DisplaySetYear();
  }
  else if (menu == 9){
    mylcd.clear();
    mylcd.setCursor(0,0);
    mylcd.print("Do you want to");
    mylcd.setCursor(0,1);
    mylcd.print("set an alarm?");
    if (digitalRead(6) == HIGH){
      menu = 11;
      delay(debounce);
    }
    if (digitalRead(5) == HIGH){
      menu = 10;
      delay(debounce);
    }

  }
  else if (menu == 10){
    if (currenthour == 1 && currentminute == 0 && currentmonth == 1 && currentday == 1 && currentyear == 1){
    mylcd.clear();
    mylcd.print("Saving...");
    delay(1000);
    menu = 0;
    }
    else {
      SaveData();
      delay(1000);
      mylcd.print("Saving...");
      delay(1000);
      menu = 0;
    }
  }
  else if (menu == 11){
    mylcd.clear();
    mylcd.setCursor(0,0);
    mylcd.print("Would you like");
    mylcd.setCursor(0,1);
    mylcd.print("to set the time?");
    if (digitalRead(6) == HIGH){
      menu = 12;
      delay(debounce);
    }
    else if (digitalRead(14) == HIGH){
      menu = 5;
      delay(debounce);
    }
  }
  else if (menu == 12){
    DisplaySetAlarmHours();
  }
  else if (menu == 13){
    DisplaySetAlarmMinutes();
  }
  else if (menu == 14){
    mylcd.clear();
    mylcd.setCursor(0,0);
    mylcd.print("Would you like");
    mylcd.setCursor(0,1);
    mylcd.print("to set the date?");
    if (digitalRead(6) == HIGH){
      menu = 15;
      delay(debounce);
    }
    else if (digitalRead(14) == HIGH){
      menu = 17;
      delay(debounce);
    }
  }
  else if (menu == 15){
    DisplaySetAlarmMonth();
  }
  else if (menu == 16){
    DisplaySetAlarmYear();
  }
  else if (menu == 17){
    SaveData();
    menu = 0;
  }
  delay(50);
  }