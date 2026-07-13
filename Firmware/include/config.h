#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// --- Motor Driver Pins (L298N) ---
#define MOTOR_LEFT_FORWARD   12
#define MOTOR_LEFT_BACKWARD  13
#define MOTOR_RIGHT_FORWARD  14
#define MOTOR_RIGHT_BACKWARD 27

// --- Servo & Pump Pins ---
#define SERVO_NOZZLE_PIN     25
#define PUMP_RELAY_PIN       26

// --- Sensor Pins ---
#define FLAME_SENSOR_PIN     34
#define ULTRASONIC_TRIG      32
#define ULTRASONIC_ECHO      33

// --- Navigation Settings ---
const float TARGET_LAT = 8.7520;  // Target GPS Lat
const float TARGET_LON = 80.4930; // Target GPS Lon
const float ALLOWED_ERROR = 1.0;  // 1 meter accuracy

#endif
