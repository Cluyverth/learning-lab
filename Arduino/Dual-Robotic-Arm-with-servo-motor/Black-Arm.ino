//== INCLUDES
#include <Servo.h>          //* include the library Servo
#include <SoftwareSerial.h> //* include the library SoftwareSerial
#include <Arduino.h>        //* include the library Arduino

//== END INCLUDES

//== DEFINES
#define pinLDR A0       //* set analog pin 0 as the LDR pin
#define pot1 A1         //* potentiometer 1
#define pot2 A2         //* potentiometer 2
#define pot3 A3         //* potentiometer 3
#define pot4 A4         //* potentiometer 4
#define lightLevel 200  //* light level to be calibrated
#define pinServ1 7      //* set digital pin 7 as servomotor 1 pin
#define pinServ2 6      //* set digital pin 6 as servomotor 2 pin
#define pinServ3 5      //* set digital pin 5 as servomotor 3 pin
#define pinServ4 4      //* set digital pin 4 as servomotor 4 pin
#define pinLED 3        //* set digital pin 3 as LED 1 pin
#define pinLED2 2       //* set digital pin 2 as LED 2 pin
#define butt 8          //* set digital pin 8 as Button 1 pin
#define butt2 9          //* set digital pin 9 as Button 2 pin
//== END DEFINES

//== OBJECTS AND FUNCTIONS DECLARATIONS
Servo serv1, serv2, serv3, serv4;        //* create the object serv1, serv2, serv3, and serv4
int motor1,motor2,motor3,motor4;         //* create motor1, motor1, motor3, and motor4 variable
SoftwareSerial bluetoothSerial (10, 11); //* create a bluetooth serial (RX: 10, TX: 11)
void printMonitor();
void movementOfButt1();
void movementOfButt2();
void movementOfBluetoothButt1();
void movementOfBluetoothButt2();
//== END OBJECTS AND FUNCTIONS DECLARATIONS

//== SETUP
void setup() {
    Serial.begin(9600);             //* start the serial
    bluetoothSerial.begin(9600);    //* start bluetooth serial
    pinMode(pinLED, OUTPUT);        //* set pinLED as digital output
    pinMode(pinLED2, OUTPUT);       //* set pinLED2 as digital output
    pinMode(butt,INPUT_PULLUP);     //* sets button 1 pin as input with pullup resistor
    pinMode(butt2,INPUT_PULLUP);     //* sets button 2 pin as input with pullup resistor
    serv1.attach(pinServ1);         //* assign object serv1 to pinserv1
    serv2.attach(pinServ2);         //* assign object serv2 to pinserv2
    serv3.attach(pinServ3);         //* assign object serv3 to pinserv3
    serv4.attach(pinServ4);         //* assign object serv4 to pinserv4
}
//== END SETUP

//== LOOP BEGINNING
void loop() { 
//== LOOP VARIABLES
    int ldrValue = analogRead(pinLDR);        //* read value from sensor
    Serial.println(analogRead(pinLDR));       //* print value from sensor
    // ldrValue = map(ldrValue,0,1023,0,255); //! if you want convert from analog to digital
    int Butt = digitalRead(butt);             //* read the button value
    int Butt2 = digitalRead(butt2);           //* read the button value
//== END LOOP VARIABLES

//== POTENTIOMETER CONTROLS                     //! use to see the limits of the arm setup you created before configuring the arm
//motor1 = map(analogRead(pot1),0,1023,0,180);  //* convert the analog potentiometer to angles
//motor2 = map(analogRead(pot2),0,1023,0,180);  //* convert the analog potentiometer to angles
//motor3 = map(analogRead(pot3),0,1023,0,180);  //* convert the analog potentiometer to angles
// motor4 = map(analogRead(pot4),0,1023,0,180); //* convert the analog potentiometer to angles
// serv1.write(motor1);                         //* do the serv move
//serv2.write(motor2);                          //* do the serv move
//serv3.write(motor3);                          //* do the serv move
//serv4.write(motor4);                          //* do the serv move
//== END OF POTENTIOMETER CONTROLS

//== LIGHT SENSOR LOGIC
    if(ldrValue > lightLevel){
        digitalWrite(pinLED, HIGH); //? turns on the LED to indicate that the sensor has seen the new cargo truck
        delay(1000);
        digitalWrite(pinLED, LOW);
//== END OF LIGHT SENSOR LOGIC

        //== BUTTONS LOGIC
        if(Butt == LOW){                    //* See if the button is pressed
            digitalWrite(pinLED2, HIGH);    //* turn on the LED light to indicate the beginning of the movement of the arm
            movementOfButt1();
            delay(1000);
            digitalWrite(pinLED2, LOW);     //* turn off the LED light to indicate the end of the movement of the arm
            delay(100);   
        }
        if(Butt2 == LOW){                   //* See if the button is pressed
            digitalWrite(pinLED2, HIGH);    //* turn on the LED light to indicate the beginning of the movement of the arm
            movementOfButt2();
            delay(1000);
            digitalWrite(pinLED2, LOW);     //* turn off the LED light to indicate the end of the movement of the arm
            delay(100);   
        }
        //== END OF BUTTONS LOGIC

        //== BEGINNING OF BLUETOOTH LOGIC
        if(bluetoothSerial.available()){
            int byteReceived = bluetoothSerial.read(); //* bluetooth read from serial
                if(byteReceived = 1){    
                    digitalWrite(pinLED2, HIGH);       //* turn on the LED light to indicate the beginning of the movement of the arm
                    movementOfBluetoothButt1();
                    delay(1000);
                    digitalWrite(pinLED2, LOW);        //* turn off the LED light to indicate the end of the movement of the arm
                    delay(100); 
                }
                if(byteReceived = 2){    
                    digitalWrite(pinLED2, HIGH);       //* turn on the LED light to indicate the beginning of the movement of the arm
                    movementOfBluetoothButt2();
                    delay(1000);
                    digitalWrite(pinLED2, LOW);        //* turn off the LED light to indicate the end of the movement of the arm
                    delay(100); 
                }
        }
        //== END OF BLUETOOTH LOGIC
    }

}
//== END LOOP

//== AUXILIARIES FUNCTIONS
void printMonitor(){             //* Print monitor function
    Serial.println("===================");
    Serial.println(analogRead(pinLDR));
  }

void movementOfButt1(){          //! Configure the movement of the Button 1

  for(int angleServo = 0; angleServo < 180; angleServo++){ //! configure the moviment
    serv1.write(angleServo);
    serv2.write(angleServo);
    serv3.write(angleServo);
    serv4.write(angleServo);
    delay(20);
  }
}

void movementOfButt2(){          //! Configure the movement of the Button 2
  for(int angleServo = 0; angleServo < 180; angleServo++){ //! configure the moviment
    serv1.write(angleServo);
    serv2.write(angleServo);
    serv3.write(angleServo);
    serv4.write(angleServo);
    delay(20);
  }
}

void movementOfBluetoothButt1(){ //! Configure the movement of the Bluetooh Button 1
  for(int angleServo = 0; angleServo < 180; angleServo++){ //! configure the moviment
    serv1.write(angleServo);
    serv2.write(angleServo);
    serv3.write(angleServo);
    serv4.write(angleServo);
    delay(20);
  }
}

void movementOfBluetoothButt2(){ //! Configure the movement of the Bluetooh Button 2
  for(int angleServo = 0; angleServo < 180; angleServo++){ //! configure the moviment
    serv1.write(angleServo);
    serv2.write(angleServo);
    serv3.write(angleServo);
    serv4.write(angleServo);
    delay(20);
  }
}
//== END AUXILIARIES FUNCTIONS
