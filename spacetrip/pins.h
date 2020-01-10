#define AIN1 1
#define AIN2 2
#define PWMA 3
#define STBY 0
#define LED 13

#define SensorAngle 0
#define SensorLost 0
#define SensorScored 0
#define SensorJoyAUp 0
#define SensorJoyADown 0
#define SensorJoyBUp 0
#define SensorJoyBDown 0

void setupPins()
{
    pinMode(LED, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(STBY, OUTPUT);
}
