#ifndef Logger_hpp
#define Logger_hpp

#include "Arduino.h"
#include "SD.h"

#define LOG_BUFFER_SIZE 400

class Logger {
 private:
  byte buffer[LOG_BUFFER_SIZE];

  int bufferIndex = 0;
  uint16_t bufferUsed = 0;

  void flushBuffer();

 public:
  bool errorFlag = false;
  Logger();
  ~Logger();
  void log(byte* message, int length);

  void bufLog(byte* message, int length);

  File logFile;
};

#endif