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
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
};
byte shape_heart[DOT_W][DOT_H] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
};
byte shape_plus[DOT_W][DOT_H] = {
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

// For bluetooth
#define BT_RXD 15
#define BT_TXD 14
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

void setup()
{
    Serial.begin(9600);
    bluetooth.begin(9600);

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

void loop()
{
    char val = bluetooth.read();

    if (bluetooth.available())
    {
        Serial.write(bluetooth.read());
    }
    if (Serial.available())
    {
        bluetooth.write(Serial.read());
    }

    switch (val)
    {
    case 'a':
        shape = shape_heart;
        break;
    case 'b':
        shape = shape_circle;
        break;
    case 'c':
        shape = shape_plus;
        break;

    default:
        break;
    }
    draw_shape(shape);
}

void draw_shape(byte shape[][DOT_H])
{
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