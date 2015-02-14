#include <SoftwareSerial.h>

#define TRACK1 9 // Mapped to pin 1 of the L293D
#define TRACK1_DIRB 4 // Mapped to pin 2 of the L293D (IN1)
#define TRACK1_DIRA 5 // Mapped ti pin 7 of the L293D (IN2)

#define TRACK2 10 // Mapped to pin 9 of the L293D
#define TRACK2_DIRB 2 // Mapped to pin 10 of the L293D (IN3)
#define TRACK2_DIRA 3 // Mapped ti pin 15 of the L293D (IN4)

#define MIN_PWM 80 // Minimun power
#define NORMAL_DELAY 100 // The default delay

// Rx/Tx for the first Bluetooth module
#define TRACK1_RxD A0
#define TRACK1_TxD A1

// Rx/Tx for the second Bluetooth module
#define TRACK2_RxD A2
#define TRACK2_TxD A3

#define LEDPIN 13

int data1 = 0;
int count1 = 0;

int data2 = 0;
int count2 = 0;

SoftwareSerial TRACK1_BTserial(TRACK1_RxD, TRACK1_TxD);
//SoftwareSerial TRACK2_BTserial(TRACK2_RxD, TRACK2_TxD);

int p1 = 128; // start at 80 otherwise the motor does start without help
int p2 = 128;

int sens = 1; // accelerate

void setup() {

  // Debugging
  Serial.begin(9600);

  pinMode(TRACK1_RxD, INPUT);
  pinMode(TRACK1_TxD, OUTPUT);
  
//  pinMode(TRACK2_RxD, INPUT);
//  pinMode(TRACK2_TxD, OUTPUT);

  // Start the software serials
  TRACK1_BTserial.begin(9600);
//  TRACK2_BTserial.begin(9600);

//  Set the motor to turn anticlockwise
/*
    digitalWrite(TRACK1_DIRA,HIGH);
    digitalWrite(TRACK1_DIRB,LOW);

    digitalWrite(TRACK2_DIRA,HIGH);
    digitalWrite(TRACK2_DIRB,LOW);

*/
  
  // Set the motor to turn clockwise
  digitalWrite(TRACK1_DIRA,LOW);
  digitalWrite(TRACK1_DIRB,HIGH);

  digitalWrite(TRACK2_DIRA,LOW);
  digitalWrite(TRACK2_DIRB,HIGH);

  // Make sure the motors dont rotate
  analogWrite(TRACK1,0);
  analogWrite(TRACK2,0);
  
  Serial.println("Ready to receive data...");
}

// Main loop
void loop() {
  
      if (TRACK1_BTserial.available() > 0){     
      data1 = TRACK1_BTserial.read(); 

      Serial.println(data1);

      if (data1 >= 49 && data1 <=149) {
         p1 = ceil(((data1 - 48) * 255) /100);

        analogWrite(TRACK1, p1);
        count1 = 0;
      } else {
        analogWrite(TRACK1,0);
        p1 = MIN_PWM;
      }

    }

     /*if (TRACK2_BTserial.available() > 0){     
      data2 = TRACK2_BTserial.read(); 

      if (data2 >= 49 && data2 <=149) {
         p2 = ceil(((data2 - 48) * 255) /100);

        analogWrite(TRACK2, p2);
        count2 = 0;
      } else {
        analogWrite(TRACK2,0);
        p2 = MIN_PWM;
      }

    }*/

    
   delay(10);
   count1++;
   count2++;
   
   if (count1 > 200) {
     count1 = 0;
//     analogWrite(ENABLE,0);
//     digitalWrite(LEDPIN,LOW);
   }
   
 
}
