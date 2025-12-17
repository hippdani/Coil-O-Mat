#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "buttons.h"

#define TICKS_PER_REV 2
#define BTN_RES 4
#define BTN_PM 3
#define J1 14
#define J2 15
#define LONGPRESS 900 //ms

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Button btn_res(BTN_RES);
Button btn_pm(BTN_PM);
Encoder enc(J1,J2, 2); //last argument is debounce time in ms

bool lcdNew = 1; //lcd refresh flag
long w_num = 0; //winding number
long man_p = 0; //number of manual additions
long man_m = 0; //number of manual substractions
long enc_ref = 0; //storage for last checked encoder position

void saveValues(long w, long p, long m)
{
  EEPROM.put(0,w);
  EEPROM.put(8,p);
  EEPROM.put(16,m);
  EEPROM.commit();
}
void loadValues(long &w, long &p, long &m)
{
  EEPROM.get(0,w_num);
  man_p = EEPROM.get(8,p);
  EEPROM.get(16,m);
}

void setup() 
{
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH); //put SMPS in LOW Noise PWM-mode
  EEPROM.begin(32);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Spulenwickel-");
  lcd.setCursor(0,1);
  lcd.print("Mitzaehlautomat");
  delay(2000);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Hallo");
  lcd.setCursor(5,1);
  lcd.print("Mario");
  delay(1500);
  loadValues(w_num, man_p, man_m);
  //--------clear powerup button events--------
  btn_res.refresh();
  btn_pm.refresh();
  enc.refresh();
  delay(2*DEBOUNCE_TIME);
  btn_res.refresh();
  btn_pm.refresh();
  enc.refresh();
  btn_pm.getRisingEvent();
  btn_res.getRisingEvent();
  enc.reset();
}

void loop() 
{
  //btn_falling(BTN_RES, btn_res_state, btn_res_event);
  btn_res.refresh();
  btn_pm.refresh();
  enc.refresh();
  
  if(btn_pm.getRisingEvent())
  {
    if(btn_pm.downFor() > LONGPRESS) 
    {
      w_num = w_num-TICKS_PER_REV;
      man_m ++;
    }
    else 
    {
      w_num += TICKS_PER_REV;
      man_p ++;
    }
    lcdNew = 1;
  }
  if(btn_res.getRisingEvent())
  {
    w_num = 0;
    man_m = 0;
    man_p = 0;
    enc_ref = enc.getNum();
    lcdNew = 1;
  }
  if(enc.getEvent())
  { //Add ticks since last encoder check
    unsigned long enc_now = enc.getNum();
    w_num += enc_now - enc_ref;
    enc_ref = enc_now;
    lcdNew = 1;
  }
  
  if(lcdNew)
  {
    lcdNew = 0;
    saveValues(w_num, man_p, man_m); //Every lcdNew event will be saved to EEPROM
    lcd.clear();
    lcd.setCursor(2,0);
    long w_disp;
    if(w_num < 0)
    {
      lcd.print("-");
      w_disp = -w_num;
    }
    else{w_disp = w_num;}
    lcd.print(w_disp/TICKS_PER_REV); //print rounded down integer of coil windings
    lcd.print(".");
    lcd.print((w_disp % TICKS_PER_REV)*10/TICKS_PER_REV); //print first digit after decimal point 
    lcd.setCursor(0,1);
    lcd.print("MAN+:");
    lcd.print(man_p);
    lcd.setCursor(8,1);
    lcd.print("MAN-:");
    lcd.print(man_m);
  }

}
