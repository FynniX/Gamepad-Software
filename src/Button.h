#ifndef BUTTON_H
#define BUTTON_H

#include <Vector.h>
#include "Config.h"
#include "GamepadMessage.h"

/**
 * @class
 * @name Button
 */
class Button
{
private:
    /**
     * @private
     * @name id;
     * @description The id of the button on the hid gamepad.
     */
    __UINT8_TYPE__ id;

    /**
     * @private
     * @name pin;
     * @description The pin of the button on the arduino.
     */
    __UINT8_TYPE__ pin;

    /**
     * @private
     * @name debounce;
     * @description The debounce of the button.
     */
    __UINT16_TYPE__ debounce = 50;

    /**
     * @private
     * @name state;
     * @description The current state of the button.
     */
    State state = State::Released;

    /**
     * @private
     * @name lastUpdate;
     * @description The last time the button was updated.
     */
    unsigned long lastUpdate = 0;

public:
    /**
     * @constructor
     * @param id The id of the button on the hid gamepad.
     * @param pin The pin of the button on the arduino.
     * @param debounce? The debounce of the button.
     */
    Button(__UINT8_TYPE__ id, __UINT8_TYPE__ pin);
    Button(__UINT8_TYPE__ id, __UINT8_TYPE__ pin, __UINT16_TYPE__ debounce);

    /**
     * @name update
     * @description Updates the button.
     * @returns The current GamepadMessage of the button.
     */
    GamepadMessage update();
};

namespace Buttons
{
    /**
     * @name configure
     * @description Configures the buttons.
     */
    void configure();

    /**
     * @name updateAll
     * @description Updates all buttons.
     * @returns The current GamepadMessage of all buttons.
     */
    void updateAll(Vector<GamepadMessage> &messages);
}

#endif