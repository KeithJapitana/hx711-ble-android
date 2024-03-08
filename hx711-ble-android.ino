#include <SoftwareSerial.h>
#include <HX711.h>

#define calibration_factor -11000.0 // This value is obtained using the SparkFun_HX711_Calibration sketch
#define LOADCELL_DOUT_PIN  2
#define LOADCELL_SCK_PIN   3
#define RED_PIN 6
#define GREEN_PIN 7
#define BLUE_PIN 8
#define HC05_RX 10
#define HC05_TX 11

HX711 scale;
SoftwareSerial HC05(HC05_RX, HC05_TX);

void setup() {
  Serial.begin(9600);
  HC05.begin(9600); // Initialize HC-05 serial communication
  delay(1000); // Short delay after initializing HC-05



  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  float calibration_factor_grams = calibration_factor / 453.59237; // Conversion factor from lbs to grams
  scale.set_scale(calibration_factor_grams);
  scale.tare();

//   // Prompt the user to enter the desired weight
//   HC05.println("Please enter the desired weight in grams:");
//   delay(100); // Short delay after prompting
//   while (!HC05.available()); // Wait for user input
//   float desired_weight = HC05.parseFloat(); // Read desired weight from HC-05 input

// Prompt the user to enter the weight percentage restriction
//   HC05.println("Please enter the weight percentage restriction in percentage (0-100):");
//   delay(100); // Short delay after prompting
//   float weight_percentage = -1;
//   while (weight_percentage < 0 || weight_percentage > 100) {
//     while (!HC05.available()); // Wait for user input
//     weight_percentage = HC05.parseFloat(); // Read weight percentage restriction from HC-05 input
//     if (weight_percentage < 0 || weight_percentage > 100) {
//       HC05.println("Invalid input. Please enter a percentage between 0 and 100:");
//       delay(100); // Short delay after error message
//     }
//   }

  // Calculate the weight limit based on the desired weight and weight percentage restriction
  
}

void loop() {
    // float weight_limit = desired_weight * weight_percentage / 100.0;
    float weight_limit = HC05.parseFloat() 
     float current_weight = scale.get_units(10); // Get the current weight readings
     HC05.print(current_weight, 1);

     if (HC05.available() > 0) {
    // Read the incoming byte from the Bluetooth module
    char receivedChar = HC05.read();

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

  while (true) {
   

    // Display the current weight and weight restriction
    // HC05.print("Current weight: ");
    // Display weight with one decimal place
    // HC05.print(" grams, Weight restriction: ");
    // HC05.print(weight_percentage);
    // HC05.println("%");

    // Compare the current weight with the weight limit
    // if (current_weight < weight_limit) {
    //   // Blue LED if lacking
    //   digitalWrite(LED_R_PIN, LOW);
    //   digitalWrite(LED_G_PIN, LOW);
    //   digitalWrite(LED_B_PIN, HIGH);
    //   HC05.println("Warning: Weight is below the restriction!");
    // } else if (current_weight > desired_weight) {
    //   // Red LED if exceeds
    //   digitalWrite(LED_R_PIN, HIGH);
    //   digitalWrite(LED_G_PIN, LOW);
    //   digitalWrite(LED_B_PIN, LOW);
    //   HC05.println("Warning: Weight exceeds the desired weight!");
    // } else {
    //   // Green LED if safe
    //   digitalWrite(LED_R_PIN, LOW);
    //   digitalWrite(LED_G_PIN, HIGH);
    //   digitalWrite(LED_B_PIN, LOW);
    //   HC05.println("Weight within acceptable range.");
    // }

    // // Delay to stabilize readings
    // delay(0);
  }
  // The main logic is handled in the setup() function, so the loop() function remains empty
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_PIN, redValue); // Set the intensity of the red LED
  analogWrite(GREEN_PIN, greenValue); // Set the intensity of the green LED
  analogWrite(BLUE_PIN, blueValue); // Set the intensity of the blue LED
}