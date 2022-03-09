#ifndef ENCODER_H
#define ENCODER_H

#include "TransferMessage.h"

class Encoder
{
private:
    static Encoder encoderList[];
    int ids[2] = {-1, -1};
    int pins[2] = {-1, -1};
    int states[2] = {-1, -1};
    long lastDebounce = 0;
    int debounce = 100;

public:
    static void configure();
    static TransferMessage *updateAll();
    void setup(int, int, int, int);
    void setup(int, int, int, int, int);
    TransferMessage *update();
};

#endif