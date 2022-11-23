#include "Logger.hpp"

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

Logger::Logger() {
#if (DEBUG_MODE > 1)

  Serial.begin(9600);
  Serial.print("Initializing SD card...");
#endif

#if (DEBUG_MODE > 1)
  bool successful = SD.begin(53);
  if (!successful) {
    Serial.println("Card Mount Failed");
    return;
  }
#else
  SD.begin(53);
#endif

  Logger::logFile = SD.open("log.txt", FILE_WRITE);

#if (DEBUG_MODE > 1)
  Serial.println("Logger Initialized");
#endif
}

Logger::~Logger() {
  Logger::logFile.close();
#if (DEBUG_MODE > 1)
  Serial.println("Logger closed");
#endif
}

void Logger::log(String message) {
  if (Logger::logFile) {
    Logger::logFile.println(message);
    Logger::logFile.flush();
#if (DEBUG_MODE > 1)
    Serial.println(message);
#endif

  } else {
#if (DEBUG_MODE > 1)
    Serial.println("Error opening log file");
#endif
  }
  return;
}