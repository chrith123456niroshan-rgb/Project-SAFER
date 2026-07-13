#include <Arduino.h>
#include <math.h>
#include "../include/config.h"

// Earth radius in kilometers
const float EARTH_RADIUS = 6371.0;

// Convert degrees to radians
float toRadians(float degree) {
    return degree * M_PI / 180.0;
}

// Calculate distance using Haversine Formula
float calculateDistance(float lat1, float lon1, float lat2, float lon2) {
    float dLat = toRadians(lat2 - lat1);
    float dLon = toRadians(lon2 - lon1);

    float a = sin(dLat / 2) * sin(dLat / 2) +
              cos(toRadians(lat1)) * cos(toRadians(lat2)) *
              sin(dLon / 2) * sin(dLon / 2);
              
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS * c * 1000.0; // Returns distance in meters
}

// Calculate Bearing (Direction to travel)
float calculateBearing(float lat1, float lon1, float lat2, float lon2) {
    float dLon = toRadians(lon2 - lon1);
    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    float y = sin(dLon) * cos(lat2);
    float x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
    
    float bearing = atan2(y, x) * 180.0 / M_PI;
    if (bearing < 0) bearing += 360.0;
    
    return bearing; // Returns angle in degrees
}
