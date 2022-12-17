/* 아두이노 - 도트 매트릭스 핀 연결
 */
#define ROW_ON 1
#define ROW_OFF 0
#define COL_ON 0
#define COL_OFF 1

byte rowPin[8] = {2, 7, 19, 5, 13, 18, 12, 16}; // {1행, 2행, 3행, 4행, 5행, 6행, 7행, 8행}
byte colPin[8] = {6, 11, 10, 3, 17, 4, 8, 9};   // {1열, 2열, 3열, 4열, 5열, 6열, 7열, 8열}
byte shape[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
};

void setup()
{

    for (int i = 0; i < 8; i++)
    {
        pinMode(rowPin[i], OUTPUT); // 모든 행 제어 핀 모드 OUTPUT 설정
        pinMode(colPin[i], OUTPUT); // 모든 열 제어 핀 모드 OUTPUT 설정
        digitalWrite(rowPin[i], ROW_OFF);
        digitalWrite(colPin[i], COL_ON);
    }
}

void dm_off_all()
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(rowPin[i], ROW_OFF);
        digitalWrite(colPin[i], COL_OFF);
    }
}

void loop()
{
    draw_shape(shape);
}

void draw_shape(byte shape[][8])
{
    for (int i = 0; i < 8; i++)
    {
        dm_off_all();
        digitalWrite(rowPin[i], ROW_ON);
        for (int j = 0; j < 8; j++)
        {
            digitalWrite(colPin[j], shape[i][j] == 0 ? COL_OFF : COL_ON);
        }
        delay(2);
    }
}