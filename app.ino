#include <SoftwareSerial.h>

/* Pins of row are connected with (+) of diode in dot display.
   And pins of column are connected with (-) of diode in dot display.
   So for emitting light, (+) voltage should be higher than (-)'s.
   That's the reason why 'ROW_ON' is 1 and 'COL_ON' is 0.
*/
;

// Define row and col on/off
#define ROW_ON 1
#define ROW_OFF 0
#define COL_ON 0
#define COL_OFF 1

// Size of dot display
#define DOT_W 8
#define DOT_H 8

// Mapping pin number between arduino and display module
byte rowPin[DOT_W] = {2, 7, 19, 5, 13, 18, 12, 16};
byte colPin[DOT_H] = {6, 11, 10, 3, 17, 4, 8, 9};
// Initial shape
byte shape_circle[DOT_W][DOT_H] = {
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
};
byte (*shape)[DOT_H] = shape_circle;

// For bluetooth
#define BT_RXD 15
#define BT_TXD 14
SoftwareSerial BTSerial(BT_RXD, BT_TXD);

// Time
unsigned long past = 0;

void setup()
{
    // Set serial for communicacting with computer and mobile device
    Serial.begin(115200);
    BTSerial.begin(9600);

    // Initialize all pin connected with dot display
    for (int i = 0; i < DOT_W; i++)
    {
        pinMode(rowPin[i], OUTPUT);
        digitalWrite(rowPin[i], ROW_OFF);
    }
    for (int i = 0; i < DOT_H; i++)
    {
        pinMode(colPin[i], OUTPUT);
        digitalWrite(colPin[i], COL_ON);
    }

    delay(1000);
}

void loop()
{
    unsigned long now = millis(); // 'now' and 'past' is a variable for call method at regular intervals without 'delay()'
    if (now - past > 100)
    {
        past = now;
        // Get data from mobile device
        read();
    }

    // Control the dot display
    draw_shape();
}

void read()
{
    if (BTSerial.available()) // If mobile device send data to arduino
    {
        Serial.println("received!");

        // Data validation
        byte header1 = BTSerial.read();
        byte header2 = BTSerial.read();
        if (!(header1 == 0xA5 && header2 == 0x5A))
        {
            Serial.println("Cause error in receiving data");
        }

        // Read data of paint to display
        for (int i = 0; i < 8; i++)
        {
            byte data = BTSerial.read();
            for (int j = 0; j < 8; j++)
            {
                // Decompose the data (1 byte -> 8 bits)
                shape[DOT_W - i - 1][j] = data % 2;
                data >>= 1;
            }
        }
    }
}

void dm_off_all()
{
    // 'dm_off_all' is method for turn off all diode of dot display
    for (int i = 0; i < DOT_W; i++)
    {
        digitalWrite(rowPin[i], ROW_OFF);
    }
    for (int i = 0; i < DOT_H; i++)
    {
        digitalWrite(colPin[i], COL_OFF);
    }
}

void draw_shape()
{
    for (int i = 0; i < DOT_W; i++)
    {
        // You can't make custom shape on dot display all at once due to circuit structure of dot dispaly.
        // Then emit lights of one row at a time.
        dm_off_all();
        digitalWrite(rowPin[i], ROW_ON);
        for (int j = 0; j < DOT_H; j++)
        {
            digitalWrite(colPin[j], shape[i][j] == 0 ? COL_OFF : COL_ON);
        }
        delay(2);
    }
}