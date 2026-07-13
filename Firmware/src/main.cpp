#include <Arduino.h>
#include <ESP32Servo.h>
#include "../include/config.h"

// Function declarations from other files
float calculateDistance(float lat1, float lon1, float lat2, float lon2);
void checkAndAvoidObstacles();
void stopRobot();

Servo nozzleServo;

void setup() {
    Serial.begin(115200);

    // Initialize Motor Pins
    pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
    pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
    pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
    pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);

    // Initialize Fire Suppression Pins
    pinMode(PUMP_RELAY_PIN, OUTPUT);
    pinMode(FLAME_SENSOR_PIN, INPUT);
    digitalWrite(PUMP_RELAY_PIN, LOW); // Keep pump off initially

    // Initialize Ultrasonic Sensor
    pinMode(ULTRASONIC_TRIG, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);

    // Attach Servo
    nozzleServo.attach(SERVO_NOZZLE_PIN);
    nozzleServo.write(90); // Center position

    Serial.println("Project S.A.F.E.R. System Initialized Successfully.");
}

void loop() {
    // 1. Run Obstacle Avoidance and Navigation loop
    checkAndAvoidObstacles();

    // 2. Check for Fire Hazard
    int fireDetected = digitalRead(FLAME_SENSOR_PIN);
    
    if (fireDetected == HIGH) { // If flame is locked
        stopRobot();
        Serial.println("🔥 FIRE DETECTED! Activating Suppression System.");
        
        // Sweep Nozzle and Spray Water
        digitalWrite(PUMP_RELAY_PIN, HIGH); // Turn Pump ON
        for (int pos = 45; pos <= 135; pos += 5) {
            nozzleServo.write(pos);
            delay(50);
        }
        for (int pos = 135; pos >= 45; pos -= 5) {
            nozzleServo.write(pos);
            delay(50);
        }
        
        digitalWrite(PUMP_RELAY_PIN, LOW); // Turn Pump OFF
        nozzleServo.write(90); // Reset nozzle
    }

    delay(100); // Small stability delay
}
