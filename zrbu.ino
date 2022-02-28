/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialEvent
*/
#include <SoftwareSerial.h>

#define SOF     0xFE
const byte rxPin = 2;
const byte txPin = 3;

// set up a new serial object
SoftwareSerial mySerial (rxPin, txPin);
char incomingByte[50];
int i = 0;
//int DataValue = 0;
void setup() {
  // initialize serial:
  Serial.begin(115200);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200); 
  zigbee_init();
}

void loop() 
{
  zigwait();
}

void zigwait (void)
{
  while(mySerial.available()>0)
  {
    char c = mySerial.read();
    Serial.print(c);
  } 
}

void zigbee_init()
{
  SYS_OSAL_NV_WRITE(1);
  delay(1000);
  //loop();
  HwReset();
  delay(1000);
  //loop();
  SYS_OSAL_NV_WRITE(2);
  delay(1000);
  //loop();
  APP_CNF_BDB_SET_CHANNEL(1);
  delay(1000);
  //loop();
  APP_CNF_BDB_SET_CHANNEL(2);
  delay(1000);
  //loop();
  APP_CNF_BDB_START_COMMISSIONING();
  delay(1000);
  //loop();
  UTIL_GET_DEVICE_INFO();
  delay(1000);
  //loop();
  SYS_OSAL_NV_WRITE(3);
  delay(1000);
  //loop();
  APP_CNF_BDB_START_COMMISSIONING();
  delay(1000);
  //loop();
  UTIL_GET_DEVICE_INFO();
  delay(1000);
  //loop();
  SYS_OSAL_NV_WRITE(3);
  delay(1000);
  //loop();
  APP_CNF_BDB_START_COMMISSIONING();
  delay(1000);
  //loop();
  SYS_OSAL_NV_WRITE(2);
  delay(1000);
  //loop();
  APP_CNF_BDB_SET_CHANNEL(1);
  delay(1000);
  //loop();
  APP_CNF_BDB_SET_CHANNEL(2);
  delay(1000);
 // loop();
  APP_CNF_BDB_START_COMMISSIONING();
  delay(1000);
  //loop();
  UTIL_GET_DEVICE_INFO();
  delay(1000);
  //loop();
}
void HwReset(void)
{
  unsigned char buf[6];
  buf[0]=0xFE; 
  buf[1]=0x01;
  buf[2]=0x41; 
  buf[3]=0x00;
  buf[4]=0x00;
  buf[5]=buf[1]^buf[2]^buf[3]^buf[4];
 // Serial.write(buf,6);
 mySerial.write(buf,sizeof(buf));
}

void SYS_OSAL_NV_WRITE(int Datavalue)
{
  unsigned char buf[10];
  ////////////////////////  SYS_OSAL_NV_WRITE ////////////////////////
  buf[0]=0xFE; 
  buf[1]=0x05; 
  buf[2]=0x21; 
  buf[3]=0x09; 
  buf[4]=0x00; 
  if(Datavalue == 1)
  {
    buf[5]=0x03;
  }
  else if(Datavalue == 2)
  {
    buf[5]=0x87;
  } 
  else if( Datavalue == 3)
  {
    buf[5] = 0x8F; 
  }
  buf[6]=0x00;
  buf[7]=0x01;
  buf[8]=0x03;    
  buf[9]=buf[1]^buf[2]^buf[3]^buf[4]^buf[5]^buf[6]^buf[7]^buf[8];
  //Serial.write(buf,sizeof(buf));
  mySerial.write(buf,sizeof(buf));
}

void APP_CNF_BDB_SET_CHANNEL(int channel)
{
  unsigned char buf[10];

  buf[0]=0xFE; 
  buf[1]=0x05;
  buf[2]=0x2F; 
  buf[3]=0x08;
  if(channel == 1 )
  {
    buf[4]=0x01;
  }
  else
  if( channel == 2 )
  {
    buf[4] = 0x00;
  }
  buf[5]=0x00; 
  buf[6]=0x00;
  if(channel == 1 )
  {
    buf[7]=0x20;
  }
  else
  if( channel == 2 )
  {
    buf[7]=0x00;
  }
  buf[8]=0x00;    
  buf[9]=buf[1]^buf[2]^buf[3]^buf[4]^buf[5]^buf[6]^buf[7]^buf[8];
  //Serial.write(buf,sizeof(buf));
    mySerial.write(buf,sizeof(buf));  
}

void APP_CNF_BDB_START_COMMISSIONING(void)
{
  unsigned char buf[6];
  
  buf[0]=0xFE; 
  buf[1]=0x01;
  buf[2]=0x2F; 
  buf[3]=0x05;
  buf[4]=0x04;    
  buf[5]=buf[1]^buf[2]^buf[3]^buf[4];
  //Serial.write(buf,sizeof(buf));
  mySerial.write(buf,sizeof(buf));
}

void UTIL_GET_DEVICE_INFO(void)
{
  unsigned char buf[5];

  buf[0]=0xFE; 
  buf[1]=0x00;
  buf[2]=0x27; 
  buf[3]=0x00;    
  buf[4]=buf[1]^buf[2]^buf[3];
  //Serial.write(buf,sizeof(buf));
  mySerial.write(buf,sizeof(buf));
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
/*void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
  
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}*/
