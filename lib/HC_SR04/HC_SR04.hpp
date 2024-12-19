#ifndef HC_SR04_H
#define HC_SR04_H

class HC_SR04 {
public:
  enum Unit { CM, INCH }; // Enum to represent units

  HC_SR04(int iTriggerPin, int iEchoPin, Unit unit = CM); // Constructor with unit parameter
  double getDistance() const; // Method to get the distance in the specified unit
  double getRawDistance() const;
private:
  int _iTriggerPin;  // Trigger pin
  int _iEchoPin;     // Echo pin
  Unit _unit;        // Unit for distance measurement
};

#endif