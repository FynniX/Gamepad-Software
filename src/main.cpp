#include <Arduino.h>
#include <Vector.h>
#include "Config.h"
#include "Button.h"
#include "Encoder.h"
#include "GamepadMessage.h"
#include "SerialCommunication.h"

#if isMaster
#include <HID-Project.h>
#endif

GamepadMessage storage_messages[32];
Vector<GamepadMessage> messages(storage_messages, 0);

void setup()
{
    // Setup serial communication
    SerialCommunication::setup();

    // Configure the hid gamepad
    Buttons::configure();
    Encoders::configure();

#if isMaster
    // Start the HID device
    Gamepad.begin();
#endif
}

void loop()
{
    // Clear all previous messages
    messages.clear();

    // Update encoders and buttons
    Buttons::updateAll(messages);
    Encoders::updateAll(messages);

#if isMaster
    // Receive messages
    SerialCommunication::receiveAll(messages);
#endif

    for (unsigned int i = 0; i < messages.size(); i++)
    {
        GamepadMessage message = messages.at(i);
        if (message.id == -1)
            continue;

#if isMaster
        if (message.state == State::Pressed)
            Gamepad.press(message.id);
        if (message.state == State::Released)
            Gamepad.release(message.id);
#else
        SerialCommunication::send(message);
#endif
    }

#if isMaster
    // Update the HID device
    Gamepad.write();
#endif
}