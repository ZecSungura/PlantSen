#include <Wire.h>
#include "SparkFunISL29125.h"
#include <DHT.h>
#include <SPI.h>
#include <SD.h>



File myFile;
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht (DHTPIN,DHTTYPE);

// Declare sensor object
SFE_ISL29125 RGB_sensor;

int chk;
float hum;
float temp;
int m_id=0;

void setup()
{
  // Initialize serial communication
  Serial.begin(115200);
  dht.begin();
  // Initialize the ISL29125 with simple configuration so it starts sampling
  if (RGB_sensor.init())
  {
    Serial.println("Sensor Initialization Successful\n\r");
  }
   Serial.print("Initializing SD card...");

  if (!SD.begin(0)) {
    Serial.println("initialization failed!");
  }
  else {
    Serial.println("initialization done.");
  }
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("hola como estas?");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

// Read sensor values for each color and print them to serial monitor
void loop()
{ 
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  // Read sensor values (16 bit integers)
  unsigned int red = RGB_sensor.readRed();
  unsigned int green = RGB_sensor.readGreen();
  unsigned int blue = RGB_sensor.readBlue();

    myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.print("Measurement ID: ");
    myFile.println(m_id);
    myFile.print("Humidity: ");
    myFile.print(hum);
    myFile.print(" %, Temp: ");
    myFile.print(temp);
    myFile.println(" Celsius");
    myFile.print("Red: "); 
    myFile.println(red,DEC);
    myFile.print("Green: "); 
    myFile.println(green,DEC);
    myFile.print("Blue: "); 
    myFile.println(blue,DEC);
    myFile.println();
    delay(2000);
    m_id++;
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
   // Serial.println("error opening test.txt1");
  }
    myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
    Serial.println("finished");
  } else {
    // if the file didn't open, print an error:
   // Serial.println("error opening test.txt2");
  }
  delay (3000);// Print out readings, change HEX to DEC if you prefer decimal output

}
