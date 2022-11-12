#ifndef Logger_hpp
#define Logger_hpp

#include "Arduino.h"
#include "SD.h"

class Logger {
 public:
  Logger();
  void log(String message);

  File logFile;
};

void deleteLogger(Logger* logger);

#endif