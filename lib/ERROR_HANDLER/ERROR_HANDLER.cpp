#include "ERROR_HANDLER.hpp"
#include <Arduino.h>
void errorHandler(char* err)
{
  Serial.println(err);
  for(;;)
  {}  
}