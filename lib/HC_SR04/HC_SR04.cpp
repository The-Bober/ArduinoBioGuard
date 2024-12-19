#include <HC_SR04.hpp>
#include <Arduino.h>


double findMedian(double arr[], int n) {
  for (int i = 1; i < n; i++) {
    double key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
  return arr[n / 2];
}



HC_SR04::HC_SR04(int triggerPin, int echoPin) {
  _triggerPin = triggerPin;
  _echoPin = echoPin;

  pinMode(_triggerPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}



double HC_SR04::getDistance() {
  const int NUM_READINGS = 10;
  double readings[NUM_READINGS];

  for (int i = 0; i < NUM_READINGS; i++) {
    readings[i] = getRawDistance();
    delay(50);  // Delay between readings
  }

  double medianDistance = findMedian(readings, NUM_READINGS);

  return medianDistance;
}



double HC_SR04::getRawDistance() {
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_triggerPin, LOW);

  double duration = pulseIn(_echoPin, HIGH);

  double distance = duration / 58;  // Convert the pulse duration to distance (in cm)

  return distance;
}