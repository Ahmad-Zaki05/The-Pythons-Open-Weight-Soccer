#include <SoftwareSerial.h>

// Slave address: 0023:09:01423E


/*
 Slave:

Command | Response | Description

AT | OK | Check if the HC-05 is in AT Command mode

AT+ROLE=0 | OK | This makes the HC=05 a Slave

AT+ADDR? | <addr>, OK | Displays the HC-05's address

Make sure to copy the address because we will be using it later on. We are done setting up this HC-05 module, so take it off the breadboard and plug in a new one. 
We will set that HC-05 as a master.
 */

/*
 Master:
Command | Response | Description

AT | OK | Check if the HC-05 is in AT Command mode

AT+ROLE=1 | OK | This makes the HC-05 a Master

AT+CMODE=0 | OK | This allows the HC-05 connect to a specified address

AT+BIND=00<addr> | OK | When the HC-05 turns on, it will look for this address

Make sure to replace the colins with commas when pasting the address of the slave HC-05 copied earlier.
 */

SoftwareSerial bt (3, 2); // TX || RX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Code has started");
  bt.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bt.available()) {
//    int c = bt.read();
    Serial.println(bt.read());
  }
  if (Serial.available()) {
    bt.println(Serial.read());
  }
}
