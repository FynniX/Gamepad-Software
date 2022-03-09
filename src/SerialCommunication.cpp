#include "SerialCommunication.h"

#include "SerialTransfer.h"
#include "TransferMessage.h"

SerialTransfer SerialCommunication::transfer;

void SerialCommunication::send(int id, bool enabled)
{
    TransferMessage message;
    message.id = id;
    message.enabled = enabled;
    SerialCommunication::transfer.sendDatum(message);
}

TransferMessage SerialCommunication::receive()
{
    TransferMessage message;

    if (SerialCommunication::transfer.available())
        SerialCommunication::transfer.rxObj(message);

    return message;
}