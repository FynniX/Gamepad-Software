#include "Button.h"

Button *storage_buttons[32];
Vector<Button *> buttons(storage_buttons, 0);

Button::Button(__UINT8_TYPE__ id, __UINT8_TYPE__ pin)
{
    this->id = id;
    this->pin = pin;

    // Set pin mode
    pinMode(this->pin, INPUT_PULLUP);
}

Button::Button(__UINT8_TYPE__ id, __UINT8_TYPE__ pin, __UINT16_TYPE__ debounce)
{
    this->id = id;
    this->pin = pin;
    this->debounce = debounce;

    // Set pin mode
    pinMode(this->pin, INPUT_PULLUP);
}

GamepadMessage Button::update()
{
    GamepadMessage message;
    message.id = -1;
    message.state = State::Released;

    // If not setup return
    if (id == -1 || pin == -1)
        return message;

    State currentState = (State) digitalRead(pin);
    unsigned long delta = millis() - lastUpdate;
    
    if (currentState == state || delta < debounce)
        return message;

    state = currentState;
    lastUpdate = millis();
    message.id = id;
    message.state = state;

    return message;
}

void Buttons::configure()
{
#if isMaster
    buttons.push_back(new Button(1, 9));
    buttons.push_back(new Button(2, 8));
    buttons.push_back(new Button(3, 7));
    buttons.push_back(new Button(4, 6));
    buttons.push_back(new Button(9, 5));
    buttons.push_back(new Button(10, 4));
    buttons.push_back(new Button(11, 3));
    buttons.push_back(new Button(15, 2));
    buttons.push_back(new Button(17, 14));
    buttons.push_back(new Button(18, A1));
#else
    buttons.push_back(new Button(5, 10));
    buttons.push_back(new Button(6, 16));
    buttons.push_back(new Button(7, 14));
    buttons.push_back(new Button(8, 15));
    buttons.push_back(new Button(12, A0));
    buttons.push_back(new Button(13, A1));
    buttons.push_back(new Button(14, A2));
    buttons.push_back(new Button(16, A3));
    buttons.push_back(new Button(19, 7));
    buttons.push_back(new Button(20, 4));
#endif
}

void Buttons::updateAll(Vector<GamepadMessage> &messages)
{
    for (unsigned int i = 0; i < buttons.size(); i++) {
        GamepadMessage message = buttons.at(i)->update();
        if (message.id != -1)
            messages.push_back(message);
    }
}