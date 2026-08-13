# HX711 Bluetooth Scale

Arduino firmware for a wireless weighing scale. An HX711 load cell amplifier reads weight, an HC-05 module streams readings to a paired Android device, and an RGB LED gives at-a-glance status against a configurable weight threshold.

Built as part of coursework at the Technological University of the Philippines – Visayas.

> **Note on the name:** the HC-05 module used here is Bluetooth Classic (SPP), not Bluetooth Low Energy, despite the `ble` in the repository name.

## Contents

| File | Description |
|---|---|
| [`hx711-ble-android.ino`](hx711-ble-android.ino) | Main firmware — load cell reading, threshold logic, Bluetooth output |
| [`android-ble-arduino.ino`](android-ble-arduino.ino) | Earlier test sketch — RGB LED control over Bluetooth only |
| `hx711` | Supporting file |
| `tupv.code-workspace` | VS Code workspace |

## Hardware

- **MCU:** Arduino Uno or Nano
- **Load cell:** any strain-gauge cell via an **HX711** amplifier breakout
- **Bluetooth:** HC-05 module (Bluetooth Classic, SPP profile)
- **Indicator:** common-cathode RGB LED

### Pin map

| Function | Pin |
|---|---|
| HX711 `DOUT` | 2 |
| HX711 `SCK` | 3 |
| RGB LED — red | 6 |
| RGB LED — green | 7 |
| RGB LED — blue | 8 |
| HC-05 `RX` | 10 |
| HC-05 `TX` | 11 |

HC-05 runs at **9600 baud**. Remember the HC-05's `RX` connects to the Arduino's `TX` and vice versa.

## Dependencies

Install via the Arduino Library Manager:

- `SoftwareSerial` (bundled)
- [`HX711`](https://github.com/bogde/HX711) — load cell amplifier driver

## Calibration

The sketch ships with a hardcoded calibration factor:

```cpp
#define calibration_factor -11000.0
```

This value is specific to the individual load cell and **must be recalibrated for yours**:

1. Run SparkFun's `SparkFun_HX711_Calibration` sketch.
2. Place a known reference weight on the cell.
3. Adjust the factor until the reading matches the known weight.
4. Replace the value above and re-flash.

The sketch converts pounds to grams internally (`calibration_factor / 453.59237`), so the calibration factor should be derived in pounds. `scale.tare()` runs on startup — keep the platform empty while powering on.

## Building and flashing

1. Install the `HX711` library.
2. Wire the load cell, HX711, HC-05 and RGB LED per the pin map.
3. Select **Arduino Uno** (or Nano) and your serial port.
4. Open [`hx711-ble-android.ino`](hx711-ble-android.ino) and upload.

Note that `Serial.begin()` is commented out in the main sketch — debug output goes to the HC-05, not USB serial. Uncomment it if you want to debug over USB.

## Pairing with Android

1. Power the board; the HC-05 LED blinks while unpaired.
2. Pair from Android Bluetooth settings — default PIN is usually `1234` or `0000`.
3. Connect with any Bluetooth SPP terminal app to read the weight stream.

## Roadmap

The main sketch contains commented-out prompts for interactively setting a target weight and a percentage tolerance over Bluetooth. Re-enabling and finishing that flow would make the threshold configurable without re-flashing.
