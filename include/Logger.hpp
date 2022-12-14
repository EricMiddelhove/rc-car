#ifndef Logger_hpp
#define Logger_hpp

#include "Arduino.h"
#include "SD.h"

class Logger {
 public:
  bool errorFlag = false;
  Logger();
  ~Logger();
  void log(char* message, int length);

  File logFile;
};

#endif