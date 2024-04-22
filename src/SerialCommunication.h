#ifndef SERIALTRANSFER_H
#define SERIALTRANSFER_H

#include <SerialTransfer.h>
#include <Vector.h>
#include "GamepadMessage.h"

namespace SerialCommunication {
    void setup();
    void send(GamepadMessage message);
    GamepadMessage receive();
    void receiveAll(Vector<GamepadMessage> &messages);
}

#endif