#include <Wire.h>
#include "SparkFunISL29125.h"
#include <DHT.h>
#include <SPI.h>
#include <SD.h>

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

/*
 {
    "id": 123,
    "hum": 0.1,
    "temp": 10,
    "light": {
       "r": 10,
       "g": 20,
       "b": 30
    }
 }
*/

void saveMeasurementToFile(int m_id, float hum, float temp, int r, int g, int b) {
    File myFile = SD.open("measurement" + m_id + ".json", FILE_WRITE); // measurement_1.json => measurement_2020-04-22-17-28-01.11.json
    char buffer[100];
    sprintf(buffer, "{\"id\": %d, \"hum\": %f, \"temp\": %d, \"light\": { \"r\": %d, \"g\": %d, \b\": %d } }", m_id, hum, temp, r, g, b)
    myFile.print(buffer)
    myFile.close();
}


// Read sensor values for each color and print them to serial monitor
void loop()
{
  m_id++;

  hum = dht.readHumidity();
  temp = dht.readTemperature();
  // Read sensor values (16 bit integers)
  unsigned int red = RGB_sensor.readRed();
  unsigned int green = RGB_sensor.readGreen();
  unsigned int blue = RGB_sensor.readBlue();

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
