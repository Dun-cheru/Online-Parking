#include <Servo.h> //includes the servo library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo1;
Servo myservo2;

#define ir_enter 34
#define ir_back  35

#define ir_car1 33
#define ir_car2 32
#define ir_car3 31
#define ir_car4 30

int S1=0, S2=0, S3=0, S4=0;
int flag1=0, flag2=0; 
int slot;  

void setup() {
 Serial.begin(9600);
 pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);
pinMode(ir_car3, INPUT);
pinMode(ir_car4, INPUT);

pinMode(ir_enter, INPUT);
pinMode(ir_back, INPUT);
  
myservo1.attach(36);

myservo2.attach(37);

lcd.init(); 
lcd.backlight();
lcd.setCursor (0,0);
lcd.print("    Smart Car   ");
lcd.setCursor (1, 1);
lcd.print(" Parking System ");
delay(5000);   
lcd.clear();

lcd.setCursor (0,0);
lcd.print("  Parking Slot   ");
lcd.setCursor (1, 1);
lcd.print("     1-4     ");
delay(3000);
lcd.clear();

int total = S1+S2+S3+S4;
slot = slot-total; 
}

void loop() {
 readEntranceSensor();
 readExitSensor();
 Read_Sensor();

  lcd.setCursor (0,0);
  lcd.print("E.S="); 
  lcd.print(slot);
  lcd.print(" ");  

  lcd.setCursor (0,1);
  lcd.print("T.S=4"); 

}


void readEntranceSensor(){
  bool value_enter = digitalRead(ir_enter);

  if(value_enter == 1){
    myservo1.write(0);
    delay(2000);
  }else if(value_enter == 0){
    myservo1.write(90);
    delay(500);
  }
}

void readExitSensor(){
  bool value_exit = digitalRead(ir_back);

  if(value_exit == 1){
    myservo2.write(0);
    delay(2000);
  }else if(value_exit == 0){
    myservo2.write(90);
    delay(500);
  }
}

void Read_Sensor(){
  boolean ir_car1_value = digitalRead(ir_car1);
  boolean ir_car2_value = digitalRead(ir_car2);
  boolean ir_car3_value = digitalRead(ir_car3);
  boolean ir_car4_value = digitalRead(ir_car4);

if(ir_car1_value == 0 && ir_car2_value == 0 && ir_car3_value == 0 && ir_car4_value == 0 ){
  slot = 0;
  lcd.setCursor (0,0);
  lcd.print("  Sorry Parking  ");
  lcd.setCursor (0, 1);
  lcd.print("      Full      "); 
  delay(3000);
  lcd.clear();
}else if(ir_car1_value == 0 && ir_car2_value == 0 && ir_car3_value == 0 && ir_car4_value == 1){
  slot = 1;
  lcd.setCursor (12, 1);
  lcd.print("S4=E ");
  lcd.setCursor (7, 1);
  lcd.print("S3=F ");
  lcd.setCursor (12,0);
  lcd.print("S2=F ");
  lcd.setCursor (7,0);
  lcd.print("S1=F ");
}
else if(ir_car1_value == 0 && ir_car2_value == 0 && ir_car3_value == 1 && ir_car4_value == 1){
  slot = 2;
  lcd.setCursor (12, 1);
  lcd.print("S4=E ");
  
  lcd.setCursor (7, 1);
  lcd.print("S3=E ");
  lcd.setCursor (12,0);
  lcd.print("S2=F ");
  lcd.setCursor (7,0);
  lcd.print("S1=F ");
}
else if(ir_car1_value == 0 && ir_car2_value == 1 && ir_car3_value == 1 && ir_car4_value == 1){
  slot = 3;
  lcd.setCursor (12, 1);
  lcd.print("S4=E ");
  lcd.setCursor (7, 1);
  lcd.print("S3=E ");
  lcd.setCursor (12,0);
  lcd.print("S2=E ");
  lcd.setCursor (7,0);
  lcd.print("S1=F ");
}
else if(ir_car1_value == 1 && ir_car2_value == 1 && ir_car3_value == 1 && ir_car4_value == 1){
  slot = 4;
  lcd.setCursor (12, 1);
  lcd.print("S4=E ");
  lcd.setCursor (7, 1);
  lcd.print("S3=E ");
  lcd.setCursor (12,0);
  lcd.print("S2=E ");
  lcd.setCursor (7,0);
  lcd.print("S1=E ");
}
else if(ir_car1_value == 1 && ir_car2_value == 1 && ir_car3_value == 1 && ir_car4_value == 0){
  slot = 3;
    lcd.setCursor (12, 1);
  lcd.print("S4=F ");
  lcd.setCursor (7, 1);
  lcd.print("S3=E ");
  lcd.setCursor (12,0);
  lcd.print("S2=E ");
  lcd.setCursor (7,0);
  lcd.print("S1=E ");
}
else if(ir_car1_value == 1 && ir_car2_value == 1 && ir_car3_value == 0 && ir_car4_value == 0){
  slot = 2;
    lcd.setCursor (12, 1);
  lcd.print("S4=F ");
  lcd.setCursor (7, 1);
  lcd.print("S3=F ");
  lcd.setCursor (12,0);
  lcd.print("S2=E ");
  lcd.setCursor (7,0);
  lcd.print("S1=E ");
}
else if(ir_car1_value == 1 && ir_car2_value == 0 && ir_car3_value == 0 && ir_car4_value == 0){
  slot = 1;
  lcd.setCursor (12, 1);
  lcd.print("S4=F ");
  lcd.setCursor (7, 1);
  lcd.print("S3=F ");
  lcd.setCursor (12,0);
  lcd.print("S2=F ");
  lcd.setCursor (7,0);
  lcd.print("S1=E ");
}

else if(ir_car1_value == 0 && ir_car2_value == 1 && ir_car3_value == 0 && ir_car4_value == 1){
  slot = 2;
    lcd.setCursor (12, 1);
  lcd.print("S4=E ");
  lcd.setCursor (7, 1);
  lcd.print("S3=F ");
  lcd.setCursor (12,0);
  lcd.print("S2=E ");
  lcd.setCursor (7,0);
  lcd.print("S1=F ");
}else if(ir_car1_value == 1 && ir_car2_value == 0 && ir_car3_value == 1 && ir_car4_value == 0){
  slot = 2;
    lcd.setCursor (12, 1);
  lcd.print("S4=F ");
  lcd.setCursor (7, 1);
  lcd.print("S3=E ");
  lcd.setCursor (12,0);
  lcd.print("S2=F ");
  lcd.setCursor (7,0);
  lcd.print("S1=E ");
}
else if(ir_car1_value == 1 && ir_car2_value == 1 && ir_car3_value == 0 && ir_car4_value == 1){
  slot = 3;
    lcd.setCursor (12, 1);
  lcd.print("S4=E ");
  lcd.setCursor (7, 1);
  lcd.print("S3=F ");
  lcd.setCursor (12,0);
  lcd.print("S2=E ");
  lcd.setCursor (7,0);
  lcd.print("S1=E ");
}
else if(ir_car1_value == 1 && ir_car2_value == 0 && ir_car3_value == 1 && ir_car4_value == 1){
  slot = 3;
    lcd.setCursor (12, 1);
  lcd.print("S4=E ");
  lcd.setCursor (7, 1);
  lcd.print("S3=E ");
  lcd.setCursor (12,0);
  lcd.print("S2=F ");
  lcd.setCursor (7,0);
  lcd.print("S1=E ");
}else if(ir_car1_value == 1 && ir_car2_value == 0 && ir_car3_value == 0 && ir_car4_value == 1){
  slot = 2;
    lcd.setCursor (12, 1);
  lcd.print("S4=E ");
  lcd.setCursor (7, 1);
  lcd.print("S3=F ");
  lcd.setCursor (12,0);
  lcd.print("S2=F ");
  lcd.setCursor (7,0);
  lcd.print("S1=E ");
}
else if(ir_car1_value == 0 && ir_car2_value == 1 && ir_car3_value == 1 && ir_car4_value == 0){
  slot = 2;
    lcd.setCursor (12, 1);
  lcd.print("S4=F ");
  lcd.setCursor (7, 1);
  lcd.print("S3=E ");
  lcd.setCursor (12,0);
  lcd.print("S2=E ");
  lcd.setCursor (7,0);
  lcd.print("S1=F ");
}else if(ir_car1_value == 0 && ir_car2_value == 1 && ir_car3_value == 0 && ir_car4_value == 0){
  slot = 1;
    lcd.setCursor (12, 1);
  lcd.print("S4=F ");
  lcd.setCursor (7, 1);
  lcd.print("S3=F ");
  lcd.setCursor (12,0);
  lcd.print("S2=E ");
  lcd.setCursor (7,0);
  lcd.print("S1=F ");
}else if(ir_car1_value == 0 && ir_car2_value == 0 && ir_car3_value == 1 && ir_car4_value == 0){
  slot = 1;
    lcd.setCursor (12, 1);
  lcd.print("S4=F ");
  lcd.setCursor (7, 1);
  lcd.print("S3=E ");
  lcd.setCursor (12,0);
  lcd.print("S2=F ");
  lcd.setCursor (7,0);
  lcd.print("S1=F ");
}

}
