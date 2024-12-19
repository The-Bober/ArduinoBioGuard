#ifndef HC_SR04_H
#define HC_SR04_H

class HC_SR04 {
  public:
    HC_SR04(int iTriggerPin, int iEchoPin); // Constructor to initialize the pins
    double getDistance() const; // Method to get the distance in cm
    double getRawDistance() const;
  private:
    int _iTriggerPin;  // Trigger pin
    int _iEchoPin;     // Echo pin
};

#endif
