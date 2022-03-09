#ifndef SERIAL_COMMUNICATION_H
#define SERIAL_COMMUNICATION_H

#include "SerialTransfer.h"
#include "TransferMessage.h"

class SerialCommunication
{
public:
    static SerialTransfer transfer;
    static void send(int, bool);
    static TransferMessage receive();
};

#endif