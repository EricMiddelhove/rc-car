#include "Logger.hpp"

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

Logger::Logger() {
  Serial.begin(1200);
  Serial.println("Initializing SD card...");

  bool successful = SD.begin(53);
  if (!successful) {
    Serial.println("Card Mount Failed");
    return;
  } else {
    Serial.println("Card Mount Successful");
  }

  int logcount = 0;

  bool fileExists = true;
  String filename = "";

  while (fileExists) {
    filename = "log";
    filename.concat(logcount);
    filename.concat(".txt");

    Serial.print("Checking file: ");
    Serial.print(filename);
    Serial.print("\n");
    delay(100);
    fileExists = SD.exists(filename);

    logcount++;
  }
  delay(500);
  Logger::logFile = SD.open(filename, FILE_WRITE);
  this->log("Logger Initialized");
}

Logger::~Logger() {
  this->log("Log Ending");
  Logger::logFile.close();

  Serial.println("Logger closed");
}

void Logger::log(String message) {
  if (Logger::logFile) {
    Logger::logFile.println(message);
    Logger::logFile.flush();

    Serial.println(message);
  } else {
    Serial.print("NO SD CARD: ");
    Serial.print(message);
    Serial.print("\n");
  }
  delay(10);
  return;
}