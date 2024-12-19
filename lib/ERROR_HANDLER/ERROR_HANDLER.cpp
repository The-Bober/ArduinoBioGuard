#include "ERROR_HANDLER.hpp"
#include <Arduino.h>
void errorHandler(char* cErr)
{
  Serial.println(cErr);
  for(;;)
  {}  
}