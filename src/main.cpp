#include <Adafruit_BusIO_Register.h>
#include <RTClib.h>
#include <Wire.h>
#include <SD.h>
#include <Arduino.h>

#include <ERROR_HANDLER.hpp>
#include <HC_SR04.hpp>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define PH_INPUT_PIN A0 // Analog input for pH sensor (adjust as needed)
#define PIN_CS 10

RTC_DS3231 rtc;
HC_SR04 sensor(TRIG_PIN, ECHO_PIN); // Ultrasonic sensor object

File file; // File object for SD card

char szNumeFisier[] = "data.csv";

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  while (!Serial)
    ;
  // Initialize SD card
  if (!SD.begin(PIN_CS))
  {
    errorHandler("SD NOT INITIALISED");
  }

  // Open file for appending data
  file = SD.open(szNumeFisier, FILE_WRITE);
  if (!file)
  {
    errorHandler("FAILED TO OPEN FILE");
  }

  // Initialize RTC
  if (!rtc.begin())
  {
    errorHandler("RTC NOT INITIALISED");
  }

  if (rtc.lostPower())
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set the RTC to the date & time this sketch was compiled
  // Write headers to the file if it's empty
  if (file.size() == 0)
  {
    file.println("Data,Ora,Nivelul Apei, Nivel PH"); //date,hour, water level, ph level
    file.flush();
  }
  delay(200);
}
void loop()
{
    // Get current date and time
    DateTime now = rtc.now();
    // Format date and time
    char dateBuffer[11]; // Format: YYYY-MM-DD
    char timeBuffer[9];  // Format: HH:MM:SS
    sprintf(dateBuffer, "%04d-%02d-%02d", now.year(), now.month(), now.day());
    sprintf(timeBuffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

    float distance = sensor.getDistance();
    int phValue = analogRead(PH_INPUT_PIN); // Raw pH sensor data

    // Write data to the file
    if (file)
    {
      file.print(dateBuffer);
      file.print(",");
      file.print(timeBuffer);
      file.print(",");
      file.print(distance, 2); // Ultrasonic data with 2 decimal points
      file.print(",");
      file.println(phValue); // pH sensor data
      file.flush();          // Ensure data is written to SD card
    }
    else
    {
      Serial.println("Failed to write to file!");
    }

    // Add a delay to control logging frequency
    delay(500); // Adjust delay as needed
}