#include "Logger.hpp"

#include "SPI.h"

Logger::Logger() {
  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  bool successful = SD.begin(53);

  if (!successful) {
    Serial.println("Card Mount Failed");
    return;
  }

  Logger::logFile = SD.open("log.txt", FILE_WRITE);

  Serial.println("Logger Initialized");
}

void Logger::log(String message) {
  if (Logger::logFile) {
    Logger::logFile.println(message);
    Logger::logFile.flush();
    Serial.println(message);
  } else {
    Serial.println("Error opening log file");
  }
  return;
}

void deleteLogger(Logger* logger) {
  logger->logFile.close();
  Serial.println("Logger closed");
  delete logger;
}