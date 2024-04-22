#include "Encoder.h"

Encoder *storage_encoder[16];
Vector<Encoder *> encoders(storage_encoder, 0);

Encoder::Encoder(__UINT8_TYPE__ id1, __UINT8_TYPE__ id2, __UINT8_TYPE__ pin1, __UINT8_TYPE__ pin2)
{
    this->ids[0] = id1;
    this->ids[1] = id2;
    this->pins[0] = pin1;
    this->pins[1] = pin2;

    // Set pin mode
    pinMode(this->pins[0], INPUT_PULLUP);
    pinMode(this->pins[1], INPUT_PULLUP);

    // Create default messages
    GamepadMessage message1;
    message1.id = -1;
    message1.state = State::Released;

    GamepadMessage message2;
    message2.id = -1;
    message2.state = State::Released;

    // Push new messages
    messages.push_back(message1);
    messages.push_back(message2);
}

Encoder::Encoder(__UINT8_TYPE__ id1, __UINT8_TYPE__ id2, __UINT8_TYPE__ pin1, __UINT8_TYPE__ pin2, __UINT16_TYPE__ debounce)
{
    this->ids[0] = id1;
    this->ids[1] = id2;
    this->pins[0] = pin1;
    this->pins[1] = pin2;
    this->debounce = debounce;

    // Set pin mode
    pinMode(this->pins[0], INPUT_PULLUP);
    pinMode(this->pins[1], INPUT_PULLUP);

    // Create default messages
    GamepadMessage message1;
    message1.id = -1;
    message1.state = State::Released;

    GamepadMessage message2;
    message2.id = -1;
    message2.state = State::Released;

    // Push new messages
    messages.push_back(message1);
    messages.push_back(message2);
}

Vector<GamepadMessage> Encoder::update()
{
    GamepadMessage &message1 = messages.at(0);
    message1.id = -1;
    message1.state = State::Released;

    GamepadMessage &message2 = messages.at(1);
    message2.id = -1;
    message2.state = State::Released;

    // If not setup return
    if (ids[0] == -1 || ids[1] == -1 || pins[0] == -1 || pins[1] == -1)
        return messages;

    int currentStates[2] = {
        digitalRead(pins[0]),
        digitalRead(pins[1])};
    unsigned long delta = millis() - lastUpdate;

    if (delta > debounce && active == State::Pressed)
    {
        active = State::Released;
        message1.id = ids[0];
        message2.id = ids[1];
        return messages;
    }

    if ((currentStates[0] == states[0] && currentStates[1] == states[1]) || delta < debounce)
        return messages;

    lastUpdate = millis();
    unsigned int state = states[1] | states[0] << 1;
    unsigned int nextState = currentStates[1] | currentStates[0] << 1;
    states[0] = currentStates[0];
    states[1] = currentStates[1];

    // Set ids of messages
    message1.id = ids[0];
    message2.id = ids[1];

    // State 0
    if (state == 0 && nextState == 2)
        message1.state = State::Pressed;
    if (state == 0 && nextState == 1)
        message2.state = State::Pressed;

    // State 1
    if (state == 1 && nextState == 0)
        message1.state = State::Pressed;
    if (state == 1 && nextState == 3)
        message2.state = State::Pressed;

    // State 3
    if (state == 3 && nextState == 1)
        message1.state = State::Pressed;
    if (state == 3 && nextState == 2)
        message2.state = State::Pressed;

    // State 2
    if (state == 2 && nextState == 3)
        message1.state = State::Pressed;
    if (state == 2 && nextState == 0)
        message2.state = State::Pressed;

    active = State::Pressed;

    return messages;
}

void Encoders::configure()
{
#if isMaster
    encoders.push_back(new Encoder(21, 22, 10, 16));
    encoders.push_back(new Encoder(23, 24, 15, A0));
    encoders.push_back(new Encoder(25, 26, A2, A3));
#else
    encoders.push_back(new Encoder(27, 28, 9, 8));
    encoders.push_back(new Encoder(29, 30, 6, 5));
    encoders.push_back(new Encoder(31, 32, 3, 2));
#endif
}

void Encoders::updateAll(Vector<GamepadMessage> &messages)
{
    for (unsigned int i = 0; i < encoders.size(); i++)
    {
        Vector<GamepadMessage> encoderMessages = encoders.at(i)->update();
        for (unsigned int j = 0; j < encoderMessages.size(); j++)
        {
            GamepadMessage message = encoderMessages.at(j);
            if (message.id == -1)
                continue;
            messages.push_back(message);
        }
    }
}