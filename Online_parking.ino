#include <ArduinoJson.h>

#include <Servo.h> //includes the servo library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>



LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial nodemcu(2, 3);

Servo myservo1;
Servo myservo2;

int sensor1;
int sensor2;
int sensor3;
int sensor4;



#define ir_enter 34
#define ir_back  35

#define ir_car1 33
#define ir_car2 32
#define ir_car3 31
#define ir_car4 30


int S1 = 0, S2 = 0, S3 = 0, S4 = 0;
int flag1 = 0, flag2 = 0;
int slot;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  nodemcu.begin(9600);
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
  lcd.setCursor (0, 0);
  lcd.print("    Smart Car   ");
  lcd.setCursor (1, 1);
  lcd.print(" Parking System ");
  delay(5000);
  lcd.clear();

  lcd.setCursor (0, 0);
  lcd.print("  Parking Slot   ");
  lcd.setCursor (1, 1);
  lcd.print("     1-4     ");
  delay(3000);
  lcd.clear();

  int total = S1 + S2 + S3 + S4;
  slot = slot - total;
}

void loop() {
  StaticJsonBuffer<1000>jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  // put your main code here, to run repeatedly:
  readEntranceSensor();
  readExitSensor();
  Read_Sensor();
  digitalWrite(ir_car1, HIGH);
  digitalWrite(ir_car2, HIGH);
  digitalWrite(ir_car3, HIGH);
  digitalWrite(ir_car4, HIGH);

  data["sensor1"] = sensor1;
  data["sensor2"] = sensor2;
  data["sensor3"] = sensor3;
  data["sensor4"] = sensor4;

  data.printTo(nodemcu);
//  jsonBuffer.clear();
  delay(100);

  lcd.setCursor (0, 0);
  lcd.print("E.S=");
  lcd.print(slot);
  lcd.print(" ");

  lcd.setCursor (0, 1);
  lcd.print("T.S=4");
}
void readEntranceSensor() {
  bool value_enter = digitalRead(ir_enter);

  if (value_enter == 0) {
    myservo1.write(0);
    delay(3000);

    lcd.setCursor (0, 0);
    lcd.print("    Gate Open   ");
    lcd.setCursor (0, 1);
    lcd.print("    Welcome!!   ");
    delay(2000);
    lcd.clear();
  } else if (value_enter == 1) {
    myservo1.write(90);
    delay(500);
  }
}

void readExitSensor() {
  bool value_exit = digitalRead(ir_back);

  if (value_exit == 0) {
    myservo2.write(0);
    delay(3000);
  } else if (value_exit == 1) {
    myservo2.write(90);
    delay(500);
  }
}

void Read_Sensor() {
  boolean ir_car1_value = digitalRead(ir_car1);
  boolean ir_car2_value = digitalRead(ir_car2);
  boolean ir_car3_value = digitalRead(ir_car3);
  boolean ir_car4_value = digitalRead(ir_car4);

  if (ir_car1_value == 0 && ir_car2_value == 0 && ir_car3_value == 0 && ir_car4_value == 0 ) {
    slot = 0;
    sensor1 = 0;
    sensor2 = 0;
    sensor3 = 0;
    sensor4 = 0;
    delay(1000);
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (0, 0);
    lcd.print("  Sorry Parking  ");
    lcd.setCursor (0, 1);
    lcd.print("      Full      ");
    delay(3000);
    lcd.clear();
  } else if (ir_car1_value == 0 && ir_car2_value == 0 && ir_car3_value == 0 && ir_car4_value == 1) {
    slot = 1;
    sensor1 = 0;
    sensor2 = 0;
    sensor3 = 0;
    sensor4 = 1;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=E ");
    lcd.setCursor (7, 1);
    lcd.print("S3=F ");
    lcd.setCursor (12, 0);
    lcd.print("S2=F ");
    lcd.setCursor (7, 0);
    lcd.print("S1=F ");
  }
  else if (ir_car1_value == 0 && ir_car2_value == 0 && ir_car3_value == 1 && ir_car4_value == 1) {
    slot = 2;
    sensor1 = 0;
    sensor2 = 0;
    sensor3 = 1;
    sensor4 = 1;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=E ");
    lcd.setCursor (7, 1);
    lcd.print("S3=E ");
    lcd.setCursor (12, 0);
    lcd.print("S2=F ");
    lcd.setCursor (7, 0);
    lcd.print("S1=F ");
  }
  else if (ir_car1_value == 0 && ir_car2_value == 1 && ir_car3_value == 1 && ir_car4_value == 1) {
    slot = 3;
    sensor1 = 0;
    sensor2 = 1;
    sensor3 = 1;
    sensor4 = 1;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=E ");
    lcd.setCursor (7, 1);
    lcd.print("S3=E ");
    lcd.setCursor (12, 0);
    lcd.print("S2=E ");
    lcd.setCursor (7, 0);
    lcd.print("S1=F ");
  }
  else if (ir_car1_value == 1 && ir_car2_value == 1 && ir_car3_value == 1 && ir_car4_value == 1) {
    slot = 4;
    sensor1 = 1;
    sensor2 = 1;
    sensor3 = 1;
    sensor4 = 1;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=E ");
    lcd.setCursor (7, 1);
    lcd.print("S3=E ");
    lcd.setCursor (12, 0);
    lcd.print("S2=E ");
    lcd.setCursor (7, 0);
    lcd.print("S1=E ");
  }
  else if (ir_car1_value == 1 && ir_car2_value == 1 && ir_car3_value == 1 && ir_car4_value == 0) {
    slot = 3;
    sensor1 = 1;
    sensor2 = 1;
    sensor3 = 1;
    sensor4 = 0;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=F ");
    lcd.setCursor (7, 1);
    lcd.print("S3=E ");
    lcd.setCursor (12, 0);
    lcd.print("S2=E ");
    lcd.setCursor (7, 0);
    lcd.print("S1=E ");
  }
  else if (ir_car1_value == 1 && ir_car2_value == 1 && ir_car3_value == 0 && ir_car4_value == 0) {
    slot = 2;
    sensor1 = 1;
    sensor2 = 1;
    sensor3 = 0;
    sensor4 = 0;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=F ");
    lcd.setCursor (7, 1);
    lcd.print("S3=F ");
    lcd.setCursor (12, 0);
    lcd.print("S2=E ");
    lcd.setCursor (7, 0);
    lcd.print("S1=E ");
  }
  else if (ir_car1_value == 1 && ir_car2_value == 0 && ir_car3_value == 0 && ir_car4_value == 0) {
    slot = 1;

    sensor1 = 1;
    sensor2 = 0;
    sensor3 = 0;
    sensor4 = 0;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=F ");
    lcd.setCursor (7, 1);
    lcd.print("S3=F ");
    lcd.setCursor (12, 0);
    lcd.print("S2=F ");
    lcd.setCursor (7, 0);
    lcd.print("S1=E ");
  }

  else if (ir_car1_value == 0 && ir_car2_value == 1 && ir_car3_value == 0 && ir_car4_value == 1) {
    slot = 2;
    sensor1 = 0;
    sensor2 = 1;
    sensor3 = 0;
    sensor4 = 1;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=E ");
    lcd.setCursor (7, 1);
    lcd.print("S3=F ");
    lcd.setCursor (12, 0);
    lcd.print("S2=E ");
    lcd.setCursor (7, 0);
    lcd.print("S1=F ");
  } else if (ir_car1_value == 1 && ir_car2_value == 0 && ir_car3_value == 1 && ir_car4_value == 0) {
    slot = 2;
    sensor1 = 1;
    sensor2 = 0;
    sensor3 = 1;
    sensor4 = 0;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=F ");
    lcd.setCursor (7, 1);
    lcd.print("S3=E ");
    lcd.setCursor (12, 0);
    lcd.print("S2=F ");
    lcd.setCursor (7, 0);
    lcd.print("S1=E ");
  }
  else if (ir_car1_value == 1 && ir_car2_value == 1 && ir_car3_value == 0 && ir_car4_value == 1) {
    slot = 3;
    sensor1 = 1;
    sensor2 = 1;
    sensor3 = 0;
    sensor4 = 1;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=E ");
    lcd.setCursor (7, 1);
    lcd.print("S3=F ");
    lcd.setCursor (12, 0);
    lcd.print("S2=E ");
    lcd.setCursor (7, 0);
    lcd.print("S1=E ");
  }
  else if (ir_car1_value == 1 && ir_car2_value == 0 && ir_car3_value == 1 && ir_car4_value == 1) {
    slot = 3;
    sensor1 = 1;
    sensor2 = 0;
    sensor3 = 1;
    sensor4 = 1;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=E ");
    lcd.setCursor (7, 1);
    lcd.print("S3=E ");
    lcd.setCursor (12, 0);
    lcd.print("S2=F ");
    lcd.setCursor (7, 0);
    lcd.print("S1=E ");
  } else if (ir_car1_value == 1 && ir_car2_value == 0 && ir_car3_value == 0 && ir_car4_value == 1) {
    slot = 2;
    sensor1 = 1;
    sensor2 = 0;
    sensor3 = 0;
    sensor4 = 1;
    Serial.println(sensor1); Serial.println(sensor2); Serial.println(sensor3); Serial.println(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=E ");
    lcd.setCursor (7, 1);
    lcd.print("S3=F ");
    lcd.setCursor (12, 0);
    lcd.print("S2=F ");
    lcd.setCursor (7, 0);
    lcd.print("S1=E ");
  }
  else if (ir_car1_value == 0 && ir_car2_value == 1 && ir_car3_value == 1 && ir_car4_value == 0) {
    slot = 2;
    sensor1 = 0;
    sensor2 = 1;
    sensor3 = 1;
    sensor4 = 0;
    Serial.print(sensor1); Serial.print(sensor2); Serial.print(sensor3); Serial.print(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=F ");
    lcd.setCursor (7, 1);
    lcd.print("S3=E ");
    lcd.setCursor (12, 0);
    lcd.print("S2=E ");
    lcd.setCursor (7, 0);
    lcd.print("S1=F ");
  } else if (ir_car1_value == 0 && ir_car2_value == 1 && ir_car3_value == 0 && ir_car4_value == 0) {
    slot = 1;
    sensor1 = 0;
    sensor2 = 1;
    sensor3 = 0;
    sensor4 = 0;
    Serial.print(sensor1); Serial.print(sensor2); Serial.print(sensor3); Serial.print(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=F ");
    lcd.setCursor (7, 1);
    lcd.print("S3=F ");
    lcd.setCursor (12, 0);
    lcd.print("S2=E ");
    lcd.setCursor (7, 0);
    lcd.print("S1=F ");
  } else if (ir_car1_value == 0 && ir_car2_value == 0 && ir_car3_value == 1 && ir_car4_value == 0) {
    slot = 1;
    sensor1 = 0;
    sensor2 = 0;
    sensor3 = 1;
    sensor4 = 0;
    Serial.print(sensor1); Serial.print(sensor2); Serial.print(sensor3); Serial.print(sensor4);
    lcd.setCursor (12, 1);
    lcd.print("S4=F ");
    lcd.setCursor (7, 1);
    lcd.print("S3=E ");
    lcd.setCursor (12, 0);
    lcd.print("S2=F ");
    lcd.setCursor (7, 0);
    lcd.print("S1=F ");
  }

}
