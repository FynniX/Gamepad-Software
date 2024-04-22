#ifndef GAMEPADMESSAGE_H
#define GAMEPADMESSAGE_H

enum State {
    Released = HIGH,
    Pressed = LOW
};

struct GamepadMessage {
    int id;
    State state;
};

#endif