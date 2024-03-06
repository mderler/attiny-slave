#include <TinyWireS.h>

#define I2C_SLAVE_ADDRESS 0x4

uint16_t adc_value = 0;
bool first_byte = true;

void requestEvent()
{
    if (first_byte)
    {
        TinyWireS.send(adc_value & 0xFF);
        first_byte = false;
        return;
    }

    TinyWireS.send(adc_value >> 8);
    first_byte = true;
}

void setup()
{
    TinyWireS.begin(I2C_SLAVE_ADDRESS);
    TinyWireS.onRequest(requestEvent);
}

void loop()
{
    TinyWireS_stop_check();

    // read adc
    adc_value = 0x43;
}