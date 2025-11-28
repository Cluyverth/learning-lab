//== INCLUDES
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

//== CONSTANTS
const int pinLDR = A0;
const int pot1 = A1;
const int pot2 = A2;
const int pot3 = A3;
const int pot4 = A4;
const int lightLevel = 200;
const int pinServ1 = 7;
const int pinServ2 = 6;
const int pinServ3 = 5;
const int pinServ4 = 4;
const int pinLED = 3;
const int pinLED2 = 2;
const int butt = 8;
const int butt2 = 9;

//== OBJECTS
Servo serv1, serv2, serv3, serv4;
SoftwareSerial bluetoothSerial(10, 11);

//== FUNCTION DECLARATIONS
void setupPins();
void setupServos();
void setupSerial();
int readLDR();
bool checkLightLevel(int ldrValue);
void handleLED(int ldrValue);
void handleButtons();
void handleBluetooth();
void moveServos(int angle1, int angle2, int angle3, int angle4);
void movementOfButt1();
void movementOfButt2();
void movementOfBluetoothButt1();
void movementOfBluetoothButt2();

//== SETUP
void setup() {
    setupPins();
    setupServos();
    setupSerial();
}

//== LOOP
void loop() {
    int ldrValue = readLDR();
    handleLED(ldrValue);
    handleButtons();
    handleBluetooth();
}

//== FUNCTION DEFINITIONS
void setupPins() {
    pinMode(pinLED, OUTPUT);
    pinMode(pinLED2, OUTPUT);
    pinMode(butt, INPUT_PULLUP);
    pinMode(butt2, INPUT_PULLUP);
}

void setupServos() {
    serv1.attach(pinServ1);
    serv2.attach(pinServ2);
    serv3.attach(pinServ3);
    serv4.attach(pinServ4);
}

void setupSerial() {
    Serial.begin(9600);
    bluetoothSerial.begin(9600);
}

int readLDR() {
    return analogRead(pinLDR);
}

bool checkLightLevel(int ldrValue) {
    return ldrValue > lightLevel;
}

void handleLED(int ldrValue) {
    if (checkLightLevel(ldrValue)) {
        digitalWrite(pinLED, HIGH);
    } else {
        digitalWrite(pinLED, LOW);
    }
}

void handleButtons() {
    int Butt = digitalRead(butt);
    int Butt2 = digitalRead(butt2);
    if (Butt == LOW) {
        movementOfButt1();
        digitalWrite(pinLED2, HIGH);
    } else {
        moveServos(90, 90, 90, 90);
        digitalWrite(pinLED2, LOW);
    }

    if (Butt2 == LOW) {
        movementOfButt2();
    }
}

void handleBluetooth() {
    if (bluetoothSerial.available() > 0) {
        char data = (char)bluetoothSerial.read();
        if (data == '1') {
            movementOfBluetoothButt1();
        } else if (data == '2') {
            movementOfBluetoothButt2();
        }
    }
}

void moveServos(int angle1, int angle2, int angle3, int angle4) {
    serv1.write(angle1);
    serv2.write(angle2);
    serv3.write(angle3);
    serv4.write(angle4);
}

void movementOfButt1() {
    moveServos(90, 90, 90, 90);
    // other code here
}

void movementOfButt2() {
    moveServos(135, 45, 0, 180);
    // other code here
}

void movementOfBluetoothButt1() {
    moveServos(0,0,0,0);
    // other code here
}

void movementOfBluetoothButt2() {
    moveServos(180,180,180,180);
    // other code here
}