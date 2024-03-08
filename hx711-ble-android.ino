#include <SoftwareSerial.h>
#include <HX711.h>

#define calibration_factor -11000.0 // This value is obtained using the SparkFun_HX711_Calibration sketch
#define LOADCELL_DOUT_PIN  2
#define LOADCELL_SCK_PIN   3
#define LED_R_PIN 6
#define LED_G_PIN 7
#define LED_B_PIN 8
#define HC05_RX 10
#define HC05_TX 11

HX711 scale;
SoftwareSerial HC05(HC05_RX, HC05_TX);

void setup() {
  Serial.begin(9600);
  HC05.begin(9600); // Initialize HC-05 serial communication
  delay(1000); // Short delay after initializing HC-05

  HC05.println("WEBED scale demo");
  delay(1000); // Delay after printing the message

  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

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

  while (true) {
    float current_weight = scale.get_units(10); // Get the current weight readings

    // Display the current weight and weight restriction
    HC05.print("Current weight: ");
    HC05.print(current_weight, 1); // Display weight with one decimal place
    HC05.print(" grams, Weight restriction: ");
    // HC05.print(weight_percentage);
    // HC05.println("%");

    // Compare the current weight with the weight limit
    if (current_weight < weight_limit) {
      // Blue LED if lacking
      digitalWrite(LED_R_PIN, LOW);
      digitalWrite(LED_G_PIN, LOW);
      digitalWrite(LED_B_PIN, HIGH);
      HC05.println("Warning: Weight is below the restriction!");
    } else if (current_weight > desired_weight) {
      // Red LED if exceeds
      digitalWrite(LED_R_PIN, HIGH);
      digitalWrite(LED_G_PIN, LOW);
      digitalWrite(LED_B_PIN, LOW);
      HC05.println("Warning: Weight exceeds the desired weight!");
    } else {
      // Green LED if safe
      digitalWrite(LED_R_PIN, LOW);
      digitalWrite(LED_G_PIN, HIGH);
      digitalWrite(LED_B_PIN, LOW);
      HC05.println("Weight within acceptable range.");
    }

    // Delay to stabilize readings
    delay(0);
  }
  // The main logic is handled in the setup() function, so the loop() function remains empty
}