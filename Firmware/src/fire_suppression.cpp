#include <Arduino.h>
#include <ESP32Servo.h>
#include "../include/config.h"

extern Servo nozzleServo; // Uses the servo instance declared in main.cpp

// Function to handle the fire suppression mechanism
void extinguishFire() {
    Serial.println("🔥 EMERGENCY: Flame Sensor Triggered! Initiating Suppression.");
    
    // 1. Activate the Water Pump via Relay
    digitalWrite(PUMP_RELAY_PIN, HIGH); 
    Serial.println("💧 Water Pump Activated.");

    // 2. Sweep the Nozzle left and right to spray water over the fire zone
    // Sweeping from 45 degrees to 135 degrees
    for (int pos = 45; pos <= 135; pos += 5) {
        nozzleServo.write(pos);
        delay(60); // Time for the servo to reach the position
    }
    
    // Sweeping back from 135 degrees to 45 degrees
    for (int pos = 135; pos >= 45; pos -= 5) {
        nozzleServo.write(pos);
        delay(60);
    }

    // 3. Turn off the pump after the sweeping cycles
    digitalWrite(PUMP_RELAY_PIN, LOW); 
    Serial.println("✅ Fire Suppression Cycle Completed. Pump Turned OFF.");

    // 4. Reset nozzle back to center position (90 degrees)
    nozzleServo.write(90); 
}

// Function to constantly monitor the flame sensor status
bool isFirePresent() {
    // Reads digital input from the IR Flame Sensor
    int sensorValue = digitalRead(FLAME_SENSOR_PIN);
    
    // Depending on the sensor module type, HIGH or LOW indicates fire.
    // Assuming HIGH logic for fire detection based on main loop configuration.
    if (sensorValue == HIGH) {
        return true;
    }
    return false;
}
