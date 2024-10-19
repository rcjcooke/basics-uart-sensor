#include <Arduino.h>
// #include <SoftwareSerial.h>

#include "A02YYUWviaUARTStream.hpp"
#include "SerialDebugger.hpp"

/* The sensor control pin that determines whether hardware low-pass filtering
 * happens on the sensor output data or not */
static const uint8_t MODE_SELECT_PIN = 8;

/*
 * WARNING: Not all pins on the Mega and Mega 2560 boards support change
 * interrupts, so only the following can be used for RX: 10, 11, 12, 13, 14, 15,
 * 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14
 * (68), A15 (69)
 */
// SoftwareSerial mySerial(11,10); // RX, TX

/* NOTE: On an Arduino Mega 2560, the Serial1 UART interface physical pins are
 19 (RX) and 18 (TX)*/

A02YYUWviaUARTStream* sensor;
SerialDebugger* serialDebugger;

void setup() {

  // Set up user serial interface
  serialDebugger = new SerialDebugger(115200);
  
  // Set up sensor serial interface
  Serial1.begin(9600);
  // mySerial.begin(9600);

  // Set up the sensor
  sensor = new A02YYUWviaUARTStream(&Serial1, MODE_SELECT_PIN, true);
  // sensor = new A02YYUWviaUARTStream(&mySerial, MODE_SELECT_PIN, true);
}

void loop() {

  // Update the latest distance reading on the sensor (self-throttling)
  sensor->readDistance();

  // Lets see what we've got
  serialDebugger->updateValue("distance / mm", sensor->getDistance());
  serialDebugger->updateValue("last read time / ms since reset", sensor->getLastReadTime());
  serialDebugger->updateValue("last successful read time / ms since reset", sensor->getLastReadSuccess());
  serialDebugger->updateValue("last read status", sensor->getLastReadStatus());
  serialDebugger->updateValue("last read result", sensor->getLastReadResult());
  serialDebugger->updateValue("is pre-processed", sensor->isProcessed());
  serialDebugger->throttledPrintUpdate();

}
