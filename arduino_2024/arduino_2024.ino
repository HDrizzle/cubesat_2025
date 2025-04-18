#include <SD.h>
#include <SPI.h>
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
    Serial.println("Removing csv.txt");
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