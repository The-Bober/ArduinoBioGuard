#include "ERROR_HANDLER.hpp"
#include <Arduino.h>
void errorHandler(const char* cErr)
{
  Serial.println(cErr);
    while (true)
    {}
}