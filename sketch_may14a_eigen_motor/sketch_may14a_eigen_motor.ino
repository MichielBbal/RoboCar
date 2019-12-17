
//Include the required libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <SoftwareSerial.h>
//SoftwareSerial library is voor bluetooth. The SoftwareSerial library allows you to use two digital I/O pins to act as a serial port that is controlled via the library files.
int bluetoothTx = 2;
int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
//Create the Adafruit_MotorShield object
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
//Create the DC motor object
// OUD = rechtsachter=M1 rechtsvoor=M2 linksvoor=M3 linksachter=M4
//NIEUW = la = M1 ra = M2 rv= M3 lv = M4
Adafruit_DCMotor *laMotor = AFMS.getMotor(1);
Adafruit_DCMotor *raMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rvMotor = AFMS.getMotor(3);
Adafruit_DCMotor *lvMotor = AFMS.getMotor(4);

//Setup/Connect to the Controller
void setup()
{
//Setup usb serial connection to computer
Serial.begin(9600);

//Setup Bluetooth serial connection to android
bluetooth.begin(115200);
bluetooth.print("$$$");
delay(100);
bluetooth.println("U,9600,N");
bluetooth.begin(9600);

//Setup the AFMS
AFMS.begin(); // create with the default frequency 1.6KHz
//AFMS.begin(1000); // OR with a different frequency, say 1KHz

// Set the speed to start, from 0 (off) to 255 (max speed)
raMotor->setSpeed(200);
raMotor->run(FORWARD);
raMotor->run(RELEASE);
//
rvMotor->setSpeed(200);
rvMotor->run(FORWARD);
rvMotor->run(RELEASE);
//
lvMotor->setSpeed(200);
lvMotor->run(FORWARD);
lvMotor->run(RELEASE);
//
laMotor->setSpeed(200);
laMotor->run(FORWARD);
laMotor->run(RELEASE);
}
//Now we're a step closer to being able to receive messages from our android device. Firstly to start reading the message send via bluetooth and writing to usb serial and it looks a something like this

void loop()
{
//Read from bluetooth and write to usb serial
if(bluetooth.available())
{
char toSend = (char)bluetooth.read();
Serial.print(toSend);
//}

// Only really used to test to see if the Arduino is receiving the correct message
//Read from usb serial to bluetooth
if(Serial.available())
{
char toSend = (char)Serial.read();
bluetooth.print(toSend);
}
//}
//A summary for what our code does so far is: Receives a message from an android device that is running the correct app via Bluetooth and then prints it to the serial monitor. we'll touch on getting the motors to work in part Two of the Arduino code
//DEEL 2
//to get motors working for you need to add code to the if(Bluetooth.available) code so it will look like this:
// After the android device sends the data the arduino takes the information and reads it as a char,
// This code is here to read that data and turn it into actions for the motors.
if(toSend == 'F')
{
raMotor->run(FORWARD);
rvMotor->run(FORWARD);
lvMotor->run(FORWARD);
laMotor->run(FORWARD);
}
if(toSend == 'B')
{
raMotor->run(BACKWARD);
rvMotor->run(BACKWARD);
lvMotor->run(BACKWARD);
laMotor->run(BACKWARD);
}

if(toSend == 'S')
{
raMotor->run(RELEASE);
rvMotor->run(RELEASE);
lvMotor->run(RELEASE);
laMotor->run(RELEASE);
}

if(toSend == 'R')
{
raMotor->run(RELEASE);
rvMotor->run(RELEASE);
lvMotor->run(FORWARD);
laMotor->run(FORWARD);
}

if(toSend == 'L')
{
raMotor->run(FORWARD);
rvMotor->run(FORWARD);
lvMotor->run(RELEASE);
laMotor->run(RELEASE);
}
}
}
//in the if statements that turn the motors there are letters such as "f" for this first if statement, this is the message that is received from pressing the forward button on the Android App! Now that we can read a message sent from an Android device we can run an app to send these messages!
