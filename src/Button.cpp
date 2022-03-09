#include <Arduino.h>
#include "Config.h"
#include "Button.h"
#include "TransferMessage.h"

Button Button::buttonList[buttonAmount];

void Button::configure()
{
    if (isMaster)
    {
        buttonList[0].setup(1, 9);
        buttonList[1].setup(2, 8);
        buttonList[2].setup(3, 7);
        buttonList[3].setup(4, 6);
        buttonList[4].setup(9, 5);
        buttonList[5].setup(10, 4);
        buttonList[6].setup(11, 3);
        buttonList[7].setup(15, 2);
        buttonList[8].setup(17, 14);
        buttonList[9].setup(18, A1);
    }

    if (!isMaster)
    {
        buttonList[0].setup(5, 10);
        buttonList[1].setup(6, 16);
        buttonList[2].setup(7, 14);
        buttonList[3].setup(8, 15);
        buttonList[4].setup(12, A0);
        buttonList[5].setup(13, A1);
        buttonList[6].setup(14, A2);
        buttonList[7].setup(16, A3);
        buttonList[8].setup(19, 7);
        buttonList[9].setup(20, 4);
    }
}

TransferMessage *Button::updateAll()
{
    static TransferMessage messages[buttonAmount];
    for (int i = 0; i < buttonAmount; i++)
        messages[i] = Button::buttonList[i].update();

    return &messages[0];
}

void Button::setup(int id, int pin)
{
    this->id = id;
    this->pin = pin;

    pinMode(this->pin, INPUT_PULLUP);
    this->state = digitalRead(this->pin);
}

void Button::setup(int id, int pin, int debounce)
{
    this->id = id;
    this->pin = pin;
    this->debounce = debounce;

    pinMode(this->pin, INPUT_PULLUP);
    this->state = digitalRead(this->pin);
}

TransferMessage Button::update()
{
    TransferMessage message;

    if (this->id == -1 || this->pin == -1)
        return message;

    long delta = millis() - this->lastDebounce;

    int currentState = digitalRead(this->pin);

    if (currentState != this->state && delta > this->debounce)
    {
        this->state = currentState;

        if (currentState == LOW)
            this->lastDebounce = millis();
    }

    switch (this->state)
    {
    case -1:
        message.id = this->id;
        message.enabled = false;
        break;
    case 0:
        message.id = this->id;
        message.enabled = true;
        break;
    case 1:
        message.id = this->id;
        message.enabled = false;
        break;
    }

    return message;
}