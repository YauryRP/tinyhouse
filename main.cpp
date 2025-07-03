#include "mbed.h"
//Servomotor und Ldrs
PwmOut motor(PA_6);
AnalogIn ldrLinks(PA_0);
AnalogIn ldrRechts(PA_1);

// LEDs
DigitalOut ledBlau(PB_10);
DigitalOut ledOrage(PA_9);
DigitalOut ledGruen(PB_5);
DigitalOut ledRot(PB_4);
DigitalOut ledHaus(PB_3);

// Schalter 
DigitalIn Schalter(D7, PullUp);

// LED Array
DigitalOut* leds[] = {&ledBlau, &ledOrage, &ledGruen, &ledRot, &ledHaus};
const int anzahlLeds = sizeof(leds) / sizeof(leds[0]);

bool lichtAn = false;  
bool letzterTasterZustand = 1; 


int main() {
    motor.period_ms(20);

    while (true) {
        
        bool aktuellerTaster = Schalter.read();

        if (letzterTasterZustand == 1 && aktuellerTaster == 0) {
            lichtAn = !lichtAn; 
        }

        letzterTasterZustand = aktuellerTaster;
        
        
        if (lichtAn) {
            for (int i = 0; i < anzahlLeds; i++) {
                for (int j = 0; j < anzahlLeds; j++) {
                    (*leds[j]) = (j == i); 
                    ledHaus = 1;
                }
                ThisThread::sleep_for(200ms);
            }
        } else {
          
            for (int i = 0; i < anzahlLeds; i++) {
                (*leds[i]) = 0;
                ledHaus = 0;
            }
        }

        //Solaranlageführung
        float rechts = ldrRechts.read();
        float links = ldrLinks.read();
        float diff = links - rechts;
        float pos = 0.075f + diff * 0.025f;

        if (pos < 0.05f) pos = 0.05f;
        if (pos > 0.10f) pos = 0.10f;

        motor.write(pos);

        ThisThread::sleep_for(300ms); 
    }
}