#include <SD.h>
#include<SPI.h>
#include <Arduino.h>
#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 baro;
unsigned char buffer[64];// buffer array for data receive over serial port
int count=0; //something for the GPS sensor
File myFile; //data being stored to SD card
const int chipSelect = 53; //SD card port
const int gasPin = A0; //
const int uvPin = A1;
//millis
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("SD Card Demo");
  if (!baro.begin()) {
   Serial.println("Could not find sensor. Check wiring.");
   while(1);
 }
 baro.setSeaPressure(1013.26);








if (SD.begin(chipSelect))
{
  Serial.println("SD card is present & ready");
}
else
{
  Serial.println("SD card missing or failure");
  while(1); //halt program
}
//clear out old data file
if (SD.exists("csv.txt"))
{
  Serial.println("Removing simple.txt");
  SD.remove("csv.txt");
  Serial.println("Done");
}
//write csv headers to file:
 myFile = SD.open("csv.txt", FILE_WRITE);
 if (myFile){
   Serial.println("File opened");
 }
}
void loop() {
float pressure = baro.getPressure();
float altitude = baro.getAltitude();
float temperature = baro.getTemperature();
int gasDen = analogRead(gasPin);
int uvRad = analogRead(uvPin);








if (Serial1.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
  {
      while(Serial1.available())               // reading data into char array
      {
          buffer[count++]=Serial1.read();      // writing data into array
          if(count == 64)break;
      }
      Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
      clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
      count = 0;                                  // set counter of while loop to zero
  }
  if (Serial.available())                 // if data is available on hardware serial port ==> data is coming from PC or notebook
  Serial1.write(Serial.read());
  if (myFile) // it opened OK
  {
   if (millis() > 12600000){ // will collect data for 3.5 hours
        myFile.close();
        Serial.println("Closed");
   }
   else if (millis() > 900000) { //15 minute start delay until data collection
      Serial.println("Writing test to csv.txt");
      gasDen = analogRead(gasPin);
      uvRad = analogRead(uvPin);
      Serial.println("yay");
      myFile.println(gasDen);
      myFile.println(uvRad);
      myFile.println(pressure);
      myFile.println(altitude);
      myFile.println(temperature);
    }




  }
}
void clearBufferArray()
{
  for (int i=0; i<count;i++)
  {
      buffer[i]=NULL;
  }               
}
















































#include <SD.h>
#include<SPI.h>
#include <Arduino.h>
#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 baro;
unsigned char buffer[64];// buffer array for data receive over serial port
int count=0; //something for the GPS sensor
File myFile; //data being stored to SD card
const int chipSelect = 53; //SD card port
const int gasPin = A0; //
const int uvPin = A1;
//millis
void setup() {
   Serial1.begin(9600);
   Serial.begin(9600);
   Serial.println("SD Card Demo");
   if (!baro.begin()) {
    Serial.println("Could not find sensor. Check wiring.");
    while(1);
  }
  baro.setSeaPressure(1013.26);




 if (SD.begin(chipSelect))
 {
   Serial.println("SD card is present & ready");
 }
 else
 {
   Serial.println("SD card missing or failure");
   while(1); //halt program
 }
 //clear out old data file
 if (SD.exists("csv.txt"))
 {
   Serial.println("Removing simple.txt");
   SD.remove("csv.txt");
   Serial.println("Done");
 }
















 //write csv headers to file:
  myFile = SD.open("csv.txt", FILE_WRITE);
}
void loop() {
 float pressure = baro.getPressure();
 float altitude = baro.getAltitude();
 float temperature = baro.getTemperature();
 int gasDen = analogRead(gasPin);
 int uvRad = analogRead(uvPin);
 




 if (Serial1.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
   {
       while(Serial1.available())               // reading data into char array
       {
           buffer[count++]=Serial1.read();      // writing data into array
           if(count == 64)break;
       }
       Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
       clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
       count = 0;                                  // set counter of while loop to zero
   }
   if (Serial.available())                 // if data is available on hardware serial port ==> data is coming from PC or notebook
   Serial1.write(Serial.read());
   if (myFile) // it opened OK
   
   Serial.println("Writing test to csv.txt");
     if (millis() > 12000) {
       gasDen = analogRead(gasPin);
       uvRad = analogRead(uvPin);
       myFile.println(gasDen);
       myFile.println(uvRad);
       myFile.println(pressure);
       myFile.println(altitude);
       myFile.println(temperature);
     }
   myFile.close();
   }
}
void clearBufferArray()
{
   for (int i=0; i<count;i++)
   {
       buffer[i]=NULL;
   }                
}










































//set the ports
const int(?) gas D4;
const int 
/*
 * Grove - Gas Sensor Demo v1.0
 *
 * The Gas Sensor detect the related Gas density, 
 * Arduino get the result by anologread. the gas Density is 
 * 0~1, larger the output is, the denser the gas.
 * Connect the Sensor to A0 in this demo;
 * 
 *  By: http://www.seeedstudio.com
*/
void setup() 
{
    Serial.begin(9600);
}
 
void loop() 
{
    float vol;
    int sensorValue = analogRead(A0);
    vol=(float)sensorValue/1024;
    Serial.print("The gas density is ");
    Serial.println(vol);
    delay(100);
}



const int gasPin = A4; //GAS sensor output pin to Arduino analog A0 pin




void setup()
{
 Serial.begin(9600); //Initialize serial port - 9600 bps
}


void loop()
{
 Serial.println(analogRead(gasPin));
 delay(1000); // Print value every 1 sec.
}


Working gas code:
//set ports
const int gasPin = A0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("gas density:");
  Serial.println(analogRead(gasPin));
  delay(1000);
}

r structures are saved to file or transmitted over a link. It is also format-compatible with MS Excel so that when you open the file or drag into Excel, it will automatically set itself up in rows and columns with the first row of 
the file creating headings for the columns. Once in Excel, you can easily display the data as graphs of many types.
#include <SD.h>
#include <SPI.h>
File myFile;

const int chipSelect = 10;




void setup()
{
  Serial.begin(9600);
  Serial.println("SD Card Demo");
  if (SD.begin(chipSelect))
  {
    Serial.println("SD card is present & ready");
  } 
  else
  {
    Serial.println("SD card missing or failure");
    while(1); //halt program
  }
  //clear out old data file
  if (SD.exists("csv.txt")) 
  {
    Serial.println("Removing simple.txt");
    SD.remove("csv.txt");
    Serial.println("Done");
  } 

  //write csv headers to file:
   myFile = SD.open("csv.txt", FILE_WRITE);  
   if (myFile) // it opened OK
    {
    Serial.println("Writing test to csv.txt");
    myFile.println("test");
    myFile.close(); 
    Serial.println("test written");
    }
  else 
    Serial.println("Error opening csv.txt");  
}

void loop(void) 
{

   // open the file. note that only one file can be open at a time,
    myFile = SD.open("csv.txt", FILE_WRITE);     
    // if the file opened okay, write to it:
    if (myFile) 
    {
      Serial.println("Writing to csv.txt");
      myFile.println(“test”); 
      myFile.close();
    } 
    else 
    {
      Serial.println("error opening csv.txt");
    }
    delay(1000);  
  }

}

CURRENT CODE:
#include <SD.h>
#include<SPI.h>


File myFile;
const int chipSelect = 53;
const int gasPin = A0;
const int uvPin = A1;
void setup() {
    Serial.begin(9600);
  Serial.println("SD Card Demo");
  if (SD.begin(chipSelect))
  {
    Serial.println("SD card is present & ready");
  }
  else
  {
    Serial.println("SD card missing or failure");
    while(1); //halt program
  }
  //clear out old data file
  if (SD.exists("csv.txt"))
  {
    Serial.println("Removing simple.txt");
    SD.remove("csv.txt");
    Serial.println("Done");
  }


  //write csv headers to file:
   myFile = SD.open("csv.txt", FILE_WRITE);  
 
}
void loop() {
  int gasDen = analogRead(gasPin); //gas sensor data (I feel like it will be easier to keep track with variables)
  int uvRad = analogRead(uvPin); //uv sensor data
   if (myFile) // it opened OK
    {
    Serial.println("Writing test to csv.txt");
      for (int i = 0; i < 10; i++); { //this loop isn't working, it's only printing it once and then glitching the
      //serial thing so yay :P
        gasDen = analogRead(gasPin);
        uvRad = analogRead(uvPin);
        Serial.println("Gas Density:");
        myFile.println(gasDen);
        Serial.println(gasDen);
        Serial.println("UV");
        myFile.println(uvRad);
        Serial.println(uvRad);
      }
    myFile.close(); //I think this line is the issue, we don't want to close the file I don't think but idk
    Serial.println("test written");
    }
  // else
  //   Serial.println("Error opening csv.txt");  


}




Latest Code(5/3/24):
#include <SD.h>
#include<SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial SoftSerial(2, 3);
unsigned char buffer[64];                   // buffer array for data receive over serial port
int count=0; 


File myFile;
const int chipSelect = 53;
const int gasPin = A0;
const int uvPin = A1;
void setup() {
   SoftSerial.begin(9600);
   Serial.begin(9600);
 Serial.println("SD Card Demo");
 if (SD.begin(chipSelect))
 {
   Serial.println("SD card is present & ready");
 }
 else
 {
   Serial.println("SD card missing or failure");
   while(1); //halt program
 }
 //clear out old data file
 if (SD.exists("csv.txt"))
 {
   Serial.println("Removing simple.txt");
   SD.remove("csv.txt");
   Serial.println("Done");
 }




 //write csv headers to file:
  myFile = SD.open("csv.txt", FILE_WRITE); 
}
void loop() {
 int gasDen = analogRead(gasPin); //gas sensor data (I feel like it will be easier to keep track with variables)
 int uvRad = analogRead(uvPin); //uv sensor data
 if (SoftSerial.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
   {
       while(SoftSerial.available())               // reading data into char array
       {
           buffer[count++]=SoftSerial.read();      // writing data into array
           if(count == 64)break;
       }
       Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
       clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
       count = 0;                                  // set counter of while loop to zero
   }
   if (Serial.available())                 // if data is available on hardware serial port ==> data is coming from PC or notebook
   SoftSerial.write(Serial.read()); 
   if (myFile) // it opened OK
   {
   Serial.println("Writing test to csv.txt");
     for (int i = 0; i < 10; i++) {
       gasDen = analogRead(gasPin);
       uvRad = analogRead(uvPin);
       Serial.println("Gas Density:");
       myFile.println(gasDen);
       Serial.println(gasDen);
       Serial.println("UV");
       myFile.println(uvRad);
       Serial.println(uvRad);
     }
   myFile.close(); //I think this line is the issue, we don't want to close the file I don't think but idk
   Serial.println("test written");
   }
 // else
 //   Serial.println("Error opening csv.txt"); 
}
void clearBufferArray()                     // function to clear buffer array
{
   for (int i=0; i<count;i++)
   {
       buffer[i]=NULL;
   }                      // clear all index of array with command NULL
}
