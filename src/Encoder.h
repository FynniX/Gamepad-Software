#ifndef ENCODER_H
#define ENCODER_H

#include <Vector.h>
#include "Config.h"
#include "GamepadMessage.h"

/**
 * @class
 * @name Encoder
 */
class Encoder
{
private:
    /**
     * @private
     * @name ids;
     * @description The ids of the encoder on the hid gamepad.
     */
    __UINT8_TYPE__ ids[2];

    /**
     * @private
     * @name pins;
     * @description The pins of the encoder on the arduino.
     */
    __UINT8_TYPE__ pins[2];

    /**
     * @private
     * @name debounce;
     * @description The debounce of the encoder.
     */
    __UINT16_TYPE__ debounce = 50;

    /**
     * @private
     * @name states;
     * @description The current state of the encoder.
     */
    int states[2] = {0, 0};

    /**
     * @private
     * @name active;
     * @description The state of the encoder.
     */
    State active = State::Released;

    /**
     * @private
     * @name lastUpdate;
     * @description The last time the button was updated.
     */
    unsigned long lastUpdate = 0;

    /**
     * @private
     * @name storage_messages;
     * @description The storage of the messages.
     */
    GamepadMessage storage_messages[2];

    /**
     * @private
     * @name messages;
     * @description The messages.
     */
    Vector<GamepadMessage> messages = Vector<GamepadMessage>(storage_messages, 0);

public:
    /**
     * @constructor
     * @param id1 The first id of the encoder on the hid gamepad.
     * @param id2 The second id of the encoder on the hid gamepad.
     * @param pin1 The first pin of the encoder on the arduino.
     * @param pin2 The second pin of the encoder on the arduino.
     * @param debounce? The debounce of the encoder.
     */
    Encoder(__UINT8_TYPE__ id1, __UINT8_TYPE__ id2, __UINT8_TYPE__ pin1, __UINT8_TYPE__ pin2);
    Encoder(__UINT8_TYPE__ id1, __UINT8_TYPE__ id2, __UINT8_TYPE__ pin1, __UINT8_TYPE__ pin2, __UINT16_TYPE__ debounce);

    /**
     * @name update
     * @description Updates the encoder.
     */
    Vector<GamepadMessage> update();
};

namespace Encoders
{
    /**
     * @name configure
     * @description Configures the encoders.
     */
    void configure();

    /**
     * @name updateAll
     * @description Updates all buttons.
     * @returns The current GamepadMessages of all encoders.
     */
    void updateAll(Vector<GamepadMessage> &messages);
}

#endif