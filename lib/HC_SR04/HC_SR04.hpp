#ifndef HC_SR04_H
#define HC_SR04_H

class HC_SR04 {
  public:
    HC_SR04(int triggerPin, int echoPin); // Constructor to initialize the pins
    double getDistance(); // Method to get the distance in cm
    double getRawDistance();
  private:
    int _triggerPin;  // Trigger pin
    int _echoPin;     // Echo pin
};

#endif
