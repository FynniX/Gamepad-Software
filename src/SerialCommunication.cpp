#include "SerialCommunication.h"

SerialTransfer transfer;

void SerialCommunication::setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
    transfer.begin(Serial1);
}

void SerialCommunication::send(GamepadMessage message)
{
    transfer.sendDatum(message);
}

GamepadMessage SerialCommunication::receive()
{
    GamepadMessage message;
    if (transfer.available())
        transfer.rxObj(message);
    return message;
}

void SerialCommunication::receiveAll(Vector<GamepadMessage> &messages)
{
    while (transfer.available())
    {
        GamepadMessage message;
        transfer.rxObj(message);
        messages.push_back(message);
    }
}