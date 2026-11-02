#include<LiquidCrystal.h>
#include<EEPROM.h>

LiquidCrystal lcd(12,11,10,9,8,7);

const int incrementbutton=6;
const int resetbutton=7;
#define led 13

int count=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(incrementbutton,INPUT_PULLUP);
  pinMode(resetbutton,INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16,2);

  EEPROM.get(0,count);
  if(count<0 || count>999999){
    count=0;
    EEPROM.put(0,count);
  }
  displaycount();

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led,HIGH);
  if(digitalRead(incrementbutton)== LOW){
    delay(50);
    if(digitalRead(incrementbutton) == LOW){
      count++;
      EEPROM.put(0,count);
      displaycount();
      while(digitalRead(incrementbutton)== LOW);
      delay(50);
    }
  }
  if(digitalRead(resetbutton)==LOW){
   delay(50);
   if(digitalRead(resetbutton) == LOW){
    count=0;
    EEPROM.put(0,count);
    displaycount();
    while(digitalRead(resetbutton)==LOW);
    delay(50);
   }
  }
 
}
void displaycount(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("count is ");
  lcd.print(count);
  Serial.print("count is");
  Serial.println(count);
}
