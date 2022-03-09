#include <Arduino.h>
#include <HID-Project.h>
#include "Config.h"
#include "SerialCommunication.h"
#include "TransferMessage.h"
#include "Button.h"
#include "Encoder.h"

void setup()
{
  // Serial Communication
  Serial.begin(115200);
  Serial1.begin(115200);
  SerialCommunication::transfer.begin(Serial1);

  // Gamepad Configuration
  Button::configure();
  Encoder::configure();

  if (isMaster)
    Gamepad.begin();
}

void loop()
{
  // Buttons
  TransferMessage *messagesPointer;
  messagesPointer = Button::updateAll();

  for (int i = 0; i < buttonAmount; i++)
  {
    TransferMessage message = (*(messagesPointer + i));

    if (isMaster && message.id != -1)
      message.enabled ? Gamepad.press(message.id) : Gamepad.release(message.id);

    if (!isMaster && message.id != -1)
      SerialCommunication::send(message.id, message.enabled);
  }

  // Encoders
  messagesPointer = Encoder::updateAll();

  for (int i = 0; i < encoderAmount * 2; i++)
  {
    TransferMessage message = (*(messagesPointer + i));

    if (isMaster && message.id != -1)
      message.enabled ? Gamepad.press(message.id) : Gamepad.release(message.id);

    if (!isMaster && message.id != -1)
      SerialCommunication::send(message.id, message.enabled);
  }

  // Receive from Slave
  for (int i = 0; i < (buttonAmount + (encoderAmount * 2)); i++)
  {
    TransferMessage message = SerialCommunication::receive();

    if (isMaster && message.id != -1)
      message.enabled ? Gamepad.press(message.id) : Gamepad.release(message.id);
  }

  if (isMaster)
    Gamepad.write();
}