#include "Logger.hpp"

#define HEADLESS 1
#define DEBUG_MODE 0

Logger::Logger() {
  Serial.begin(115200);
  Serial.println(F("Initializing SD card..."));

  bool successful = SD.begin(53);

  if (!successful) {
    Serial.println(F("Card Mount Failed"));
    return;
  } else {
    Serial.println(F("Card Mount Successful"));
  }

  int logcount = 0;

  bool fileExists = true;
  String filename = "";

  while (fileExists) {
    filename = F("log");
    filename.concat(logcount);
    filename.concat(F(".bin"));

    Serial.print(F("Checking file: "));
    Serial.print(filename);
    Serial.print(F("\n"));
    delay(100);

    fileExists = SD.exists(filename);

    logcount++;
  }
  delay(500);
  Logger::logFile = SD.open(filename, FILE_WRITE);
  Serial.println(F("Logger Initialized"));
}

void Logger::flushBuffer() {
  if (bufferUsed > 0) {
    Logger::logFile.write((char*)buffer, bufferUsed);
    Logger::logFile.flush();

    Serial.print(F("\tBuffer forcefully flushed"));

    bufferIndex = 0;
    bufferUsed = 0;
  }
}
Logger::~Logger() {
  Serial.print(F("Log Ending"));

  // logFile.close();

  flushBuffer();
  Serial.println(F("\tLogger closed"));
}

void Logger::close() {
  logFile.close();
}

void Logger::log(byte* message, int length) {
  if (Logger::logFile) {
    // TODO: Convert bytes array to char array (fast)
    Logger::logFile.write((char*)message, length);
    Logger::logFile.flush();

  } else {
    Serial.print(F("\tError writing to file"));
    this->errorFlag = true;
  }
  return;
}

void Logger::bufLog(byte* message, int length) {
  if (bufferUsed + length > LOG_BUFFER_SIZE) {
    Logger::logFile.write((char*)buffer, LOG_BUFFER_SIZE);
    Logger::logFile.flush();

    Serial.print(F("\tBuffer flushed"));

    bufferIndex = 0;
    bufferUsed = 0;
  }

  for (int i = 0; i < length; i++) {
    buffer[bufferIndex] = message[i];
    bufferIndex++;
  }
  bufferUsed += length;
}
