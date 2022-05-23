 // Source https://wiki.dfrobot.com/_A02YYUW_Waterproof_Ultrasonic_Sensor_SKU_SEN0311


#include <SoftwareSerial.h>


SoftwareSerial mySerial(10,11); // RX, TX   (module: rx=blue=11  tx=green=10)
unsigned char data[4]={};
float distance;


void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600); 
}


void loop()
{
  do
  {
    for(int i=0;i<4;i++)
    {
      data[i]=mySerial.read();
    }
  } while(mySerial.read()==0xff);

  mySerial.flush();

  // read header
  if (data[0] == 0xff)
  {
    // data[0] = Header (1 Byte, 0xFF)
    // data[1] = Distance Data High 8-bits
    // data[2] = Distance Data Low  8-bits
    int checksum;
    checksum = (data[0]+data[1]+data[2])&0x00FF;

    // data[3] = checkchecksum (but only the low 8-bits of the accumulated value)
    if (checksum == data[3])
    {
      distance = (data[1]<<8)+data[2];
        
      if (distance > 30)
      {
        Serial.print("distance=");
        Serial.print(distance/10);
        Serial.println("cm");
      }
      else 
      {
        Serial.println("Below the lower limit");
      }
    }
    else
    {
      Serial.println("ERROR");
    }
  }

  // delay between each measurement
  delay(100);
}
