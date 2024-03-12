# attiny-slave

## Flashen

Wenn es Probleme beim Flashen mit PlatformIO gibt, kann man das Projekt mal nur mit PlatformIO
builden und mittels avrdude flashen.

Die compelierte Datei ist in `.pio/build/attiny` als `firmware.hex` zu finden.

Zum flashen wird folgender Command benutzt:

```sh
avrdude -p attiny45 -c STK500 -U flash:w:firmware.hex:i -F -P <COM PORT>
```

## Code

```cpp
void setup()
{
    TinyWireS.begin(I2C_SLAVE_ADDRESS);  // Setzt Register um I2C zu konfigurieren
    TinyWireS.onRequest(requestEvent);   // Bei Anfragen vom Master wird requestEvent aufgerufen    
}
```

```cpp
void requestEvent()
{
    if (first_byte)
    {
        TinyWireS.send(adc_value & 0xFF);  // Sendet ersten Byte
        first_byte = false;
        return;
    }

    TinyWireS.send(adc_value >> 8); // Sendet zweiten Byte
    first_byte = true;
}
```
