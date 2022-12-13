#include "Logger.hpp"

#define HEADLESS 1
#define DEBUG_MODE 0

#define DEBUG_MODE DEBUG_MODE

Logger::Logger() {
#if DEBUG_MODE != HEADLESS
  Serial.begin(1200);
  Serial.println("Initializing SD card...");
#endif

  bool successful = SD.begin(53);

#if DEBUG_MODE != HEADLESS
  if (!successful) {
    Serial.println("Card Mount Failed");
    return;
  } else {
    Serial.println("Card Mount Successful");
  }
#endif

  int logcount = 0;

  bool fileExists = true;
  String filename = "";

  while (fileExists) {
    filename = "log";
    filename.concat(logcount);
    filename.concat(".txt");

#if DEBUG_MODE != HEADLESS
    Serial.print("Checking file: ");
    Serial.print(filename);
    Serial.print("\n");
    delay(100);
#endif

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

#if DEBUG_MODE != HEADLESS
  Serial.println("Logger closed");
#endif
}

void Logger::log(String message) {
  if (Logger::logFile) {
    Logger::logFile.println(message);
    Logger::logFile.flush();

#if DEBUG_MODE != HEADLESS
    Serial.println(message);
#endif
  } else {
#if DEBUG_MODE != HEADLESS
    Serial.print("NO SD CARD: ");
    Serial.print(message);
    Serial.print("\n");
#else
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    errorFlag = true;
#endif
  }
  delay(10);
  return;
}