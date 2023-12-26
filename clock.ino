#include <LiquidCrystal.h>

// Pins for the LCD screen
LiquidCrystal lcd(12,11,5,4,3,2);

int h=23;
int m=25;
int s=00;
uint32_t current_time = 0; 
uint32_t timer = 0;

void setup() {
  lcd.begin(16,2);
  current_time=millis();

  char time[16];
  sprintf(time, "%02i:%02i:%02i", h, m, s);
  lcd.clear();
  lcd.print(time);
}

void loop() {
  uint32_t new_time = millis(); 
  uint32_t frame_milliseconds = new_time - current_time;
  current_time = new_time;

  timer += frame_milliseconds;
  if(timer >= 1000)
  {
    timer -= 1000; // 1 second passed
    s += 1;
  }

  //
  // time overflow
  //
  if(s >= 60){
    s = 0;
    m += 1;
  }
  if(m >= 60)
  {
    m -= 60;
    h += 1;
  }
  if(h >= 24)
  {
    h -= 24;
    // its a new dawn, a new day!
  }

  // update seconds
  char seconds_label[2];
  sprintf(seconds_label, "%02i", s);
  lcd.setCursor(6, 0);
  lcd.print(seconds_label);

  // update minutes
  char minutes_label[2];
  sprintf(minutes_label, "%02i", m);
  lcd.setCursor(3, 0);
  lcd.print(minutes_label);
  
  // update hours
  char hours_label[2];
  sprintf(hours_label, "%02i", h);
  lcd.setCursor(0, 0);
  lcd.print(hours_label);

  // might as well
  delay(250);
}