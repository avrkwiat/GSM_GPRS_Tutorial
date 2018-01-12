#include <A6lib.h>

#ifndef ESP8266
#define D0 0
#define D5 8 //rx
#define D6 7 //tx
#endif

// Instantiate the library with TxPin, RxPin.
A6lib A6l(D6, D5);

void setup() {
    Serial.begin(115200);

    delay(1000);

    // Power-cycle the module to reset it.
    A6l.powerCycle(D0);
    A6l.blockUntilReady(115200);
}

void loop() {
    Serial.println("Checking call status...");
    callInfo cinfo = A6l.checkCallStatus();
    Serial.println("Call status checked.");
    delay(1000);
    delay(1000);
    delay(1000);
    delay(1000);
    int sigStrength = A6l.getSignalStrength();
    Serial.print("Signal strength percentage: ");
    Serial.println(sigStrength);

    delay(1000);
    delay(1000);
    delay(1000);
    delay(1000);
    delay(1000);
    if (cinfo.number != NULL) {
        if (cinfo.direction == DIR_INCOMING && cinfo.number == "508609804") {
            A6l.answer();
        } else {
            A6l.hangUp();
        }
        delay(1000);
    } else {
        Serial.println("No number yet.");
        delay(1000);
    }
}