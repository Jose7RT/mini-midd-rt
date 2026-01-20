#pragma once

struct TelemetryFrame {
    double timestamp;    
    float altitude;      
    float velocity;      
    float acceleration;  
    float battery_level; 
    float temperature;   
    int flight_phase; // 0: RAMPA, 1: ASCENSO, 2: DESCENSO    
};