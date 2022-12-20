#include <SoftwareSerial.h>

// For dot matrix
#define ROW_ON 1
#define ROW_OFF 0
#define COL_ON 0
#define COL_OFF 1
#define DOT_W 8
#define DOT_H 8

byte rowPin[DOT_W] = {2, 7, 19, 5, 13, 18, 12, 16};
byte colPin[DOT_H] = {6, 11, 10, 3, 17, 4, 8, 9};
byte shape_circle[DOT_W][DOT_H] = {
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
};
byte (*shape)[DOT_H] = shape_circle;
byte gauge = 0;

// For bluetooth
#define BT_RXD 15
#define BT_TXD 14
SoftwareSerial BTSerial(BT_RXD, BT_TXD);

// Time
unsigned long past_draw = 0;

void setup()
{
    Serial.begin(115200);
    BTSerial.begin(9600);

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
    unsigned long now = millis();

    read();

    draw_shape();
}

void read()
{
    if (BTSerial.available())
    {
        Serial.println("received!");

        byte header1 = BTSerial.read();
        byte header2 = BTSerial.read();
        Serial.println(header1);
        Serial.println(header2);
        if (!(header1 == 0xA5 && header2 == 0x5A))
        {
            Serial.println("Cause error in receiving data");
        }

        for (int i = 0; i < 8; i++)
        {
            byte data = BTSerial.read();
            Serial.println(data);
            for (int j = 0; j < 8; j++)
            {
                shape[DOT_W - i - 1][j] = data % 2;
                data >>= 1;
            }
        }
    }
}

void dm_off_all()
{
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
    // for (int i = 0; i < DOT_W * DOT_H; i++)
    // {
    //     shape[i / DOT_W][i % DOT_H] = (i < gauge) ? 1 : 0;
    // }

    for (int i = 0; i < DOT_W; i++)
    {
        dm_off_all();
        digitalWrite(rowPin[i], ROW_ON);
        for (int j = 0; j < DOT_H; j++)
        {
            digitalWrite(colPin[j], shape[i][j] == 0 ? COL_OFF : COL_ON);
        }
        delay(2);
    }
}