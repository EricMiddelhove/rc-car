#include "Logger.hpp"

#define HEADLESS 1
#define DEBUG_MODE 0

Logger::Logger() {
  Serial.begin(9600);
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
    filename.concat(".bin");

    Serial.print("Checking file: ");
    Serial.print(filename);
    Serial.print("\n");
    delay(100);

    fileExists = SD.exists(filename);

    logcount++;
  }
  delay(500);
  Logger::logFile = SD.open(filename, FILE_WRITE);
  Serial.println("Logger Initialized");
}

Logger::~Logger() {
  Serial.println("Log Ending");
  Logger::logFile.close();

  Serial.println("Logger closed");
}

void Logger::log(char* message, int length) {
  if (Logger::logFile) {
    Logger::logFile.write(message, length);
    Logger::logFile.flush();

  } else {
    Serial.println("Error writing to file");
    this->errorFlag = true;
  }
  return;
}