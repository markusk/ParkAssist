 // Source https://wiki.dfrobot.com/_A02YYUW_Waterproof_Ultrasonic_Sensor_SKU_SEN0311

/*
  *@File  : DFRobot_Distance_A02.ino 
  *@Brief : This example use A02YYUW ultrasonic sensor to measure distance
  *         With initialization completed, We can get distance value 
  *@Copyright [DFRobot](https://www.dfrobot.com),2016         
  *           GUN Lesser General Pulic License
  *@version V1.0           
  *@data  2019-8-28
*/

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
    do{
     for(int i=0;i<4;i++)
     {
       data[i]=mySerial.read();
     }
  }while(mySerial.read()==0xff);

  mySerial.flush();

  // read header
  if (data[0] == 0xff)
  {
      int sum;
      // data[0] = Header (1 Byte, 0xFF)
      // data[1] = Distance Data High 8-bits
      // data[2] = Distance Data Low  8-bits
      sum = (data[0]+data[1]+data[2])&0x00FF;

      // data[3] = checksum (but only the low 8-bits of the accumulated value)
      if (sum == data[3])
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
      }else Serial.println("ERROR");
   }

     // delay between each measurement
     delay(100);
}
