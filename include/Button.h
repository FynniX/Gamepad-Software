#ifndef BUTTON_H
#define BUTTON_H

#include "TransferMessage.h"

class Button
{
private:
    static Button buttonList[];
    int id = -1;
    int pin = -1;
    int state = -1;
    long lastDebounce = 0;
    int debounce = 100;

public:
    static void configure();
    static TransferMessage *updateAll();
    void setup(int, int);
    void setup(int, int, int);
    TransferMessage update();
};

#endif