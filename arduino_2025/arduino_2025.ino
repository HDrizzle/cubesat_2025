/* MSSM Cubesat team 2025, adapted from 2024 version
Each of the 5 geiger counters will be attached to an interrupt pin to trigger a count in a corresponding number in `geiger_counts`
Arduino Mega interrupts:
  2, 3, 18, 19, 20, 21
  https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/
*/
#include <SD.h>
#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_MPL3115A2.h>

#define DATA_FILENAME "data.csv"

// Global variables
Adafruit_MPL3115A2 baro;
unsigned char buffer[64];// buffer array for data receive over serial port
int count=0; //something for the GPS sensor
File myFile; //data being stored to SD card
const int chipSelect = 53; //SD card port
volatile uint32_t geiger_counts[5] = {0, 0, 0, 0, 0};// Declared as volatile because it will be modified by ISRs
// Timing
unsigned long data_collect_period_ms = 15000;// 15,000 millisecs, 15 secs
unsigned long t_last_data_collect_ms = millis();

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
  // clear out old data file
  if (SD.exists(DATA_FILENAME))
  {
    Serial.println("Removing file");
    SD.remove(DATA_FILENAME);
    Serial.println("Done");
  }
  // write csv headers to file:
  myFile = SD.open(DATA_FILENAME, FILE_WRITE);
  if (myFile){
    Serial.println("File opened");
  }
  // Setup geiger counter interrupts
  attachInterrupt(digitalPinToInterrupt(3), counter_ISR_0, RISING);// Either rising or falling, doesn't matter
  attachInterrupt(digitalPinToInterrupt(18), counter_ISR_1, RISING);// Either rising or falling, doesn't matter
  attachInterrupt(digitalPinToInterrupt(19), counter_ISR_2, RISING);// Either rising or falling, doesn't matter
  attachInterrupt(digitalPinToInterrupt(20), counter_ISR_3, RISING);// Either rising or falling, doesn't matter
  attachInterrupt(digitalPinToInterrupt(21), counter_ISR_4, RISING);// Either rising or falling, doesn't matter
}

void loop() {
  float pressure = baro.getPressure();
  float altitude = baro.getAltitude();
  float temperature = baro.getTemperature();
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
      Serial.println("yay");
      myFile.println(pressure);
      myFile.println(altitude);
      myFile.println(temperature);
    }
  }
  // Delay
  delay(min(data_collect_period_ms - (millis() - t_last_data_collect_ms), data_collect_period_ms));// Take minimum of calculated delay and default delay. In case the loop for some reason takes too long, this won't be hung up by an unsigned integer undeflow
  t_last_data_collect_ms = millis();
}

void clearBufferArray()
{
  for (int i=0; i<count;i++)
  {
    buffer[i]=NULL;
  }               
}

// Geiger counter ISRs
void counter_ISR_0() {
  geiger_counts[0] += 1;
}
void counter_ISR_1() {
  geiger_counts[1] += 1;
}
void counter_ISR_2() {
  geiger_counts[2] += 1;
}
void counter_ISR_3() {
  geiger_counts[3] += 1;
}
void counter_ISR_4() {
  geiger_counts[4] += 1;
}