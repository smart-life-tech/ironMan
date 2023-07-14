#include <Servo.h>

// Constants
const int hallSensorPin = 2; // Pin connected to the Hall sensor
const int eyeLEDPin1 = 7;    // Pin connected to the first eye LED
const int eyeLEDPin2 = 8;    // Pin connected to the second eye LED
const int faceServoPin1 = 3; // Pin connected to the first face servo
const int faceServoPin2 = 5; // Pin connected to the second face servo
const int lipServoPin = 6;   // Pin connected to the lip servo

// Variables
bool faceOpen = false; // Flag to track the face state

Servo faceServo1; // Face servo 1 object
Servo faceServo2; // Face servo 2 object
Servo lipServo;   // Lip servo object

void setup()
{
    pinMode(hallSensorPin, INPUT); // Set Hall sensor pin as input
    pinMode(eyeLEDPin1, OUTPUT);   // Set first eye LED pin as output
    pinMode(eyeLEDPin2, OUTPUT);   // Set second eye LED pin as output

    faceServo1.attach(faceServoPin1); // Attach face servo 1 to its pin
    faceServo2.attach(faceServoPin2); // Attach face servo 2 to its pin
    lipServo.attach(lipServoPin);     // Attach lip servo to its pin

    // Initial position for the servos (adjust as needed)
    faceServo1.write(0);
    faceServo2.write(180);
    lipServo.write(0);

    Serial.begin(9600); // Initialize serial communication
    Serial.println("Ironman Helmet Initialized");
}

void loop()
{
    // Read the Hall sensor value
    int hallSensorValue = digitalRead(hallSensorPin);

    // Check if the face state has changed
    if (hallSensorValue == HIGH && !faceOpen)
    {
        faceOpen = true;
        openFace();
        closeLip();
        digitalWrite(eyeLEDPin1, HIGH); // Turn on first eye LED
        digitalWrite(eyeLEDPin2, HIGH); // Turn on second eye LED
        Serial.println("Helmet Face Closed");
    }
    else if (hallSensorValue == LOW && faceOpen)
    {
        faceOpen = false;
        closeFace();
        openLip();
        digitalWrite(eyeLEDPin1, LOW); // Turn off first eye LED
        digitalWrite(eyeLEDPin2, LOW); // Turn off second eye LED
        Serial.println("Helmet Face Opened");
    }

    delay(100); // Delay for stability
}

void openFace()
{
    // Open the face gradually by moving the servos
    for (int angle = 0; angle <= 180; angle += 5)
    {
        faceServo1.write(angle);
        faceServo2.write(180 - angle);
        delay(15);
    }
}

void closeFace()
{
    // Close the face gradually by moving the servos
    for (int angle = 180; angle >= 0; angle -= 5)
    {
        faceServo1.write(angle);
        faceServo2.write(180 - angle);
        delay(15);
    }
}

void openLip()
{
    // Open the lip gradually by moving the servo
    for (int angle = 0; angle <= 180; angle += 5)
    {
        lipServo.write(angle);
        delay(15);
    }
}

void closeLip()
{
    // Close the lip gradually by moving the servo
    for (int angle = 180; angle >= 0; angle -= 5)
    {
        lipServo.write(angle);
        delay(15);
    }
}
