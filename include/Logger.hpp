#ifndef Logger_hpp
#define Logger_hpp

#include "Arduino.h"
#include "SD.h"

class Logger {
 public:
  Logger();
  ~Logger();
  void log(String message);

  File logFile;
};

#endif