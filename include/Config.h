// true = master, false = slave
constexpr bool isMaster = true;

// You have 32 buttons on the hid gamepad. Keep in mind that encoders uses two buttons.
// You also need to edit the Button.cpp and Encoder.cpp configure() part to your needs.
constexpr int buttonAmount = 10;
constexpr int encoderAmount = 3;