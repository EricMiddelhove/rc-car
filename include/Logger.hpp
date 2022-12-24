#ifndef Logger_hpp
#define Logger_hpp

#include "Arduino.h"
#include "SD.h"

class Logger {
 public:
  bool errorFlag = false;
  Logger();
  ~Logger();
  void log(byte* message, int length);

  File logFile;
};

#endif