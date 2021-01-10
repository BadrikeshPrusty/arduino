/*
 * Author Name  : Badrikesh Prusty
 * Date         : 12/02/2018
 * Description  : To implement an arduino project called Human Tracking Fan and Light system.
 * 
 */


#include<Servo.h>
Servo servo;                  //inclusion of servo library and declaring servo object

int pir1 = 2;
int pir2 = 3;                 //Signal wire of PIR sensors attached to these pins of the arduino
int pir3 = 4;
int pir4 = 5;
int pir5 = 6;

int run_fan = 8;              //fan and light attachment pin
int light   = 13;
 
void setup() {                //code within setup function run only once
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);       //PIRs pinmode as input
  pinMode(pir4, INPUT);
  pinMode(pir5, INPUT);
  
  servo.attach(9, 500, 2400);   //connected pin is 9, min pulse width(ms) 500, max 2400

  pinMode(run_fan, OUTPUT);     //set the pins output for light and fan
  pinMode(light,   OUTPUT);
}

void loop() {
  int chk_pir1 = digitalRead(pir1);
  int chk_pir2 = digitalRead(pir2);
  int chk_pir3 = digitalRead(pir3);       //read PIR pins
  int chk_pir4 = digitalRead(pir4);
  int chk_pir5 = digitalRead(pir5);

  int n;

  if(chk_pir1 == 1 && chk_pir2 == 0 && chk_pir3 == 0 && chk_pir4 == 0 && chk_pir5 == 0){
    digitalWrite(light, HIGH);
    servo.write(0);                   //If PIR 1 detects move the servo to 0 degree and run the fan
    delay(500);
    digitalWrite(run_fan, HIGH);
  }
  
  else if(chk_pir1 == 1 && chk_pir2 == 1 && chk_pir3 == 0 && chk_pir4 == 0 && chk_pir5 == 0){
    digitalWrite(light, HIGH);        //If both sensors detect blow air in between 2 PIR sensors
    servo.write(22);
    delay(500);
    digitalWrite(run_fan, HIGH);
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 1 && chk_pir3 == 0 && chk_pir4 == 0 && chk_pir5 == 0){
    digitalWrite(light, HIGH);
    servo.write(45);
    delay(500);
    digitalWrite(run_fan, HIGH);
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 1 && chk_pir3 == 1 && chk_pir4 == 0 && chk_pir5 == 0){
    digitalWrite(light, HIGH);
    servo.write(67);
    delay(500);
    digitalWrite(run_fan, HIGH);
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 0 && chk_pir3 == 1 && chk_pir4 == 0 && chk_pir5 == 0){
    digitalWrite(light, HIGH);
    servo.write(90);
    delay(500);
    digitalWrite(run_fan, HIGH);
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 0 && chk_pir3 == 1 && chk_pir4 == 1 && chk_pir5 == 0){
    digitalWrite(light, HIGH);
    servo.write(112);
    delay(500);
    digitalWrite(run_fan, HIGH);
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 0 && chk_pir3 == 0 && chk_pir4 == 1 && chk_pir5 == 0){
    digitalWrite(light, HIGH);
    servo.write(135);
    delay(500);
    digitalWrite(run_fan, OUTPUT);
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 0 && chk_pir3 == 0 && chk_pir4 == 1 && chk_pir5 == 1){
    digitalWrite(light, HIGH);
    servo.write(157);
    delay(500);
    digitalWrite(run_fan, HIGH);
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 0 && chk_pir3 == 0 && chk_pir4 == 0 && chk_pir5 == 1){
    digitalWrite(light, HIGH);
    servo.write(180);
    delay(500);
    digitalWrite(run_fan, HIGH);
  }
  
  else if(chk_pir1 == 1 && chk_pir3 == 1 && chk_pir4 == 0 && chk_pir5 == 0){
    digitalWrite(light, HIGH);
    digitalWrite(run_fan, HIGH);
    for(int n = 0; n<=90; n++){
      servo.write(n);
      delay(25);
    }
    
    for(int n = 90; n>=0; n--){           //Servo in swing mode
      servo.write(n);
      delay(25);
    }
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 1 && chk_pir4 == 1 && chk_pir5 == 0){
    digitalWrite(light, HIGH);
    digitalWrite(run_fan, HIGH);
    for(int n = 45; n<=135; n++){
      servo.write(n);
      delay(25);
    }
    
    for(int n = 135; n>=45; n--){
      servo.write(n);
      delay(25);
    }   
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 0 && chk_pir3 == 1 && chk_pir5 == 1){
    digitalWrite(light, HIGH);
    digitalWrite(run_fan, HIGH);
    for(int n = 90; n<=180; n++){
      servo.write(n);
      delay(25);
    }
    
    for(int n = 180; n>=90; n--){
      servo.write(n);
      delay(25);
    }      
  }
  
  else if(chk_pir1 == 1 && chk_pir4 == 1 && chk_pir5 == 0){
    digitalWrite(light, HIGH);
    digitalWrite(run_fan, HIGH);
    for(int n = 0; n<=135; n++){
      servo.write(n);
      delay(25);
    }
    
    for(int n = 135; n>=0; n--){
      servo.write(n);
      delay(25);
    }   
  }
  
  else if(chk_pir1 == 0 && chk_pir2 == 1 && chk_pir5 == 1){
    digitalWrite(light, HIGH);
    digitalWrite(run_fan, HIGH);
    for(int n = 45; n<=180; n++){
      servo.write(n);
      delay(25);
    }
    
    for(int n = 180; n>=45; n--){
      servo.write(n);
      delay(25);
    }   
  }
  
  else if(chk_pir1 == 1 && chk_pir5 == 1){
    digitalWrite(light, HIGH);
    digitalWrite(run_fan, HIGH);
    for(n=0; n<=180; n++){
      servo.write(n);
      delay(25);
    }
    
    for(n=180; n>=0; n--){
      servo.write(n);
      delay(25);
    }
  }
  
  else{
    digitalWrite(run_fan, LOW);
    servo.write(90);
    delay(1000);
    digitalWrite(light, LOW);
    
  }
}
