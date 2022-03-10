#include <Arduino.h>
#include "Config.h"
#include "Encoder.h"
#include "TransferMessage.h"

Encoder Encoder::encoderList[encoderAmount];

void Encoder::configure()
{
    if (isMaster)
    {
        encoderList[0].setup(21, 22, 10, 16);
        encoderList[1].setup(23, 24, 15, A0);
        encoderList[2].setup(25, 26, A2, A3);
    }

    if (!isMaster)
    {
        encoderList[0].setup(27, 28, 9, 8);
        encoderList[1].setup(29, 30, 6, 5);
        encoderList[2].setup(31, 32, 3, 2);
    }
}

TransferMessage *Encoder::updateAll()
{
    static TransferMessage messages[encoderAmount * 2];
    for (int i = 0; i < encoderAmount; i++)
    {
        TransferMessage *updates = Encoder::encoderList[i].update();
        messages[((i + 1) * 2) - 2] = *updates;
        messages[((i + 1) * 2) - 1] = *(updates + 1);
    }

    return &messages[0];
}

void Encoder::setup(int id1, int id2, int pin1, int pin2)
{
    this->ids[0] = id1;
    this->ids[1] = id2;
    this->pins[0] = pin1;
    this->pins[1] = pin2;

    pinMode(this->pins[0], INPUT_PULLUP);
    pinMode(this->pins[1], INPUT_PULLUP);
}

void Encoder::setup(int id1, int id2, int pin1, int pin2, int debounce)
{
    this->ids[0] = id1;
    this->ids[1] = id2;
    this->pins[0] = pin1;
    this->pins[1] = pin2;
    this->debounce = debounce;

    pinMode(this->pins[0], INPUT_PULLUP);
    pinMode(this->pins[1], INPUT_PULLUP);
}

TransferMessage *Encoder::update()
{
    static TransferMessage messages[2];

    if (this->ids[0] == -1 || this->ids[1] == -1 || this->pins[0] == -1 || this->pins[1] == -1)
        return &messages[0];

    long delta = millis() - this->lastDebounce;

    int currentStates[2] = {digitalRead(this->pins[0]), digitalRead(this->pins[1])};

    if (delta > this->debounce)
    {
        messages[0].id = this->ids[0];
        messages[0].enabled = false;
        messages[1].id = this->ids[1];
        messages[1].enabled = false;
    }

    if ((currentStates[0] != this->states[0] || currentStates[2] != this->states[2]) && delta > this->debounce)
    {
        if (this->states[0] == 0 && this->states[1] == 0)
        {
            if (currentStates[0] == 0 && currentStates[1] == 1)
            {
                messages[0].id = this->ids[0];
                messages[0].enabled = false;
                messages[1].id = this->ids[1];
                messages[1].enabled = true;
            }

            if (currentStates[0] == 1 && currentStates[1] == 0)
            {
                messages[0].id = this->ids[0];
                messages[0].enabled = true;
                messages[1].id = this->ids[1];
                messages[1].enabled = false;
            }
        }

        if (this->states[0] == 0 && this->states[1] == 1)
        {
            if (currentStates[0] == 1 && currentStates[1] == 1)
            {
                messages[0].id = this->ids[0];
                messages[0].enabled = false;
                messages[1].id = this->ids[1];
                messages[1].enabled = true;
            }

            if (currentStates[0] == 0 && currentStates[1] == 0)
            {
                messages[0].id = this->ids[0];
                messages[0].enabled = true;
                messages[1].id = this->ids[1];
                messages[1].enabled = false;
            }
        }

        if (this->states[0] == 1 && this->states[1] == 1)
        {
            if (currentStates[0] == 1 && currentStates[1] == 0)
            {
                messages[0].id = this->ids[0];
                messages[0].enabled = false;
                messages[1].id = this->ids[1];
                messages[1].enabled = true;
            }

            if (currentStates[0] == 0 && currentStates[1] == 1)
            {
                messages[0].id = this->ids[0];
                messages[0].enabled = true;
                messages[1].id = this->ids[1];
                messages[1].enabled = false;
            }
        }

        if (this->states[0] == 1 && this->states[1] == 0)
        {
            if (currentStates[0] == 0 && currentStates[1] == 0)
            {
                messages[0].id = this->ids[0];
                messages[0].enabled = false;
                messages[1].id = this->ids[1];
                messages[1].enabled = true;
            }

            if (currentStates[0] == 1 && currentStates[1] == 1)
            {
                messages[0].id = this->ids[0];
                messages[0].enabled = true;
                messages[1].id = this->ids[1];
                messages[1].enabled = false;
            }
        }

        this->states[0] = currentStates[0];
        this->states[1] = currentStates[1];
        this->lastDebounce = millis();
    }

    return &messages[0];
}