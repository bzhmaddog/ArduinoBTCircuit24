#include <SoftwareSerial.h>

#define TRACK1 9 // Mapped to pin 1 of the L293D
#define TRACK1_DIRB 4 // Mapped to pin 2 of the L293D (IN1)
#define TRACK1_DIRA 5 // Mapped ti pin 7 of the L293D (IN2)

#define TRACK2 10 // Mapped to pin 9 of the L293D
#define TRACK2_DIRB 2 // Mapped to pin 10 of the L293D (IN3)
#define TRACK2_DIRA 3 // Mapped ti pin 15 of the L293D (IN4)

#define DIR_FORWARD true
#define DIR_REVERSE false


#define MIN_PWM 80 // Minimun power
#define NORMAL_DELAY 100 // The default delay

// Rx/Tx for the first Bluetooth module
#define TRACK1_RxD A0
#define TRACK1_TxD A1

int data1 = 0;
int count1 = 0;

int data2 = 0;
int count2 = 0;

SoftwareSerial TRACK1_BTserial(TRACK1_RxD, TRACK1_TxD);

int p1 = 128; // start at 80 otherwise the motor does start without help
int p2 = 128;

void setup() {

  // Debugging
  Serial.begin(9600);

  pinMode(TRACK1_RxD, INPUT);
  pinMode(TRACK1_TxD, OUTPUT);
  

  // Start the software serials
  TRACK1_BTserial.begin(9600);

//  Set the motor to turn anticlockwise
/*
    digitalWrite(TRACK1_DIRA,HIGH);
    digitalWrite(TRACK1_DIRB,LOW);

    digitalWrite(TRACK2_DIRA,HIGH);
    digitalWrite(TRACK2_DIRB,LOW);

*/
  
  // Set the motor to turn clockwise
  setMotorDir(1,DIR_FORWARD);
  setMotorDir(2,DIR_FORWARD);
  
  
  // Make sure the motors dont rotate
  analogWrite(TRACK1,0);
  analogWrite(TRACK2,0);
  
//  Serial.println("Ready to receive data...");
}

void setMotorDir(int track, boolean fwd) {
  int ta,tb;
  
  if (track == 1){
    ta = TRACK1_DIRA;
    tb = TRACK1_DIRB;
  } else {
    ta = TRACK2_DIRA;
    tb = TRACK2_DIRB;
  }

  if (fwd) {
    digitalWrite(ta, LOW);
    digitalWrite(tb, HIGH);
  } else {
    digitalWrite(ta, HIGH);
    digitalWrite(tb, LOW);
  }
}

// Main loop
void loop() {


  if (TRACK1_BTserial.available() > 0){     
    data1 = TRACK1_BTserial.read(); 

      if (data1 >= 49 && data1 <=150) {
        p1 = ceil(((data1 - 48) * 255) /100);
        analogWrite(TRACK1, p1);
        count1 = 0;
      } else if (data1 == 151) {
        analogWrite(TRACK1, 0);
        setMotorDir(1, DIR_REVERSE);
        count1 = 0;        
      } else if (data1 == 152) {
        analogWrite(TRACK1, 0);
        setMotorDir(1, DIR_FORWARD);
        count1 = 0;
      } else {
        analogWrite(TRACK1,0);
      }

  }
    
  if (Serial.available() > 0){     
      data2 = Serial.read(); 
      
       if (data2 >= 49 && data2 <=150) {
         p2 = ceil(((data2 - 48) * 255) /100);

        analogWrite(TRACK2, p2);
        count2 = 0;
      } else if (data2 == 151) {

        analogWrite(TRACK2, 0);
        setMotorDir(2, DIR_REVERSE);
 
      } else if (data2 == 152) {

        analogWrite(TRACK2, 0);
        setMotorDir(2, DIR_FORWARD);

      } else {
        analogWrite(TRACK2,0);
      }

  }

    
   delay(10);
   count1++;
   count2++;
   
   /*if (count1 > 100) {
      count1 = 0;
      analogWrite(TRACK1,0);
   }

   if (count2 > 100) {
      count2 = 0;
      analogWrite(TRACK2,0);
   }*/
   
 
}
