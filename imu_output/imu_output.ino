#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Simple_AHRS.h>

// Create sensor instances.
Adafruit_ADXL345_Unified accel(12345);
Adafruit_HMC5883_Unified mag(12345);

// Create simple AHRS algorithm using the above sensors.
Adafruit_Simple_AHRS          ahrs(&accel, &mag);

const int  buttonPin = 2;    // the pin that the pushbutton is attached to
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int output = 0;

void setup()
{
  Serial.begin(9600);
  // Initialize the sensors.
  accel.begin();
  mag.begin();
}

void loop(void)
{
  sensors_vec_t   orientation;

  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      switch(buttonPushCounter%3) {
        case 0:
          output = 5;
          break;
        case 1:
          output = 4;
          break;
        case 2:
          output = 3;
          break;
        default:
          output = 0;
      }
    }

    else {
      output = 0;
    }
    delay(50);
    lastButtonState = buttonState;
  }

  // Use the simple AHRS function to get the current orientation.
  if (ahrs.getOrientation(&orientation))
  {
    /* 'orientation' should have valid .roll and .pitch fields */
     double phi = orientation.heading;

    if (orientation.roll < 0.0) {
      orientation.roll = map(orientation.roll, 0.0, -180.0, 359.9, 180.0);
    }
    if (orientation.pitch < 0.0) {
      orientation.pitch = map(orientation.pitch, 0.0, -179.9, 359.9, 180.0);
    }
    if (orientation.heading < 0.0) {
      orientation.heading = map(orientation.heading, 0.0, -179.9, 359.9, 180.0);
    }

    
    Serial.print(orientation.roll);
    Serial.print(",");
    Serial.print(orientation.pitch);
    Serial.print(",");
    Serial.print(orientation.heading);
    Serial.print(",");
    Serial.println(output);
  }
  delay(200);
}
