#include <SoftwareSerial.h>

// Define the pins for the RGB LED module
#define RED_PIN 6
#define GREEN_PIN 7
#define BLUE_PIN 8

// Define the pins for the HC-05 Bluetooth module
#define BT_RX 10
#define BT_TX 11

// Create a SoftwareSerial object for Bluetooth communication
SoftwareSerial bluetooth(BT_RX, BT_TX);

void setup() {
  // Initialize the RGB LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Initialize serial communication for debugging purposes
  Serial.begin(9600);

  // Set up Bluetooth communication
  bluetooth.begin(9600);
}

void loop() {
  // Check if data is available to be read from the Bluetooth module
  if (bluetooth.available() > 0) {
    // Read the incoming byte from the Bluetooth module
    char receivedChar = bluetooth.read();

    // Print the received character for debugging
    Serial.println(receivedChar);

    // Check the received command
    if (receivedChar == 'r') { // If the received command is 'r' (red)
      setColor(255, 0, 0); // Set RGB values to turn the LED red
    } else if (receivedChar == 'g') { // If the received command is 'g' (green)
      setColor(0, 255, 0); // Set RGB values to turn the LED green
    } else if (receivedChar == 'b') { // If the received command is 'b' (blue)
      setColor(0, 0, 255); // Set RGB values to turn the LED blue
    }
  }
}

// Function to set the RGB values of the LED
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_PIN, redValue); // Set the intensity of the red LED
  analogWrite(GREEN_PIN, greenValue); // Set the intensity of the green LED
  analogWrite(BLUE_PIN, blueValue); // Set the intensity of the blue LED
}   