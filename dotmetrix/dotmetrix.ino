/* 아두이노 - 도트 매트릭스 핀 연결
*/ 
byte rowPin[8] = {2, 7, 19, 5, 13, 18, 12, 16};  // {1행, 2행, 3행, 4행, 5행, 6행, 7행, 8행} 
byte colPin[8] = {6, 11, 10, 3, 17, 4, 8, 9};        // {1열, 2열, 3열, 4열, 5열, 6열, 7열, 8열} 

void setup() { 

  for (int i = 0; i < 8; i++) { 
    pinMode(rowPin[i], OUTPUT); // 모든 행 제어 핀 모드 OUTPUT 설정  
    pinMode(colPin[i], OUTPUT); // 모든 열 제어 핀 모드 OUTPUT 설정  
  }

  Serial.begin(9600);

  on(3, 3);
} 

void loop()
{

}

int getValue(float f) {
  return floor(0.5 * (sin(f) + 1.0) * 256);
}

void on(int x, int y) {
  digitalWrite(rowPin[x], HIGH);
  digitalWrite(colPin[y], LOW);
}

void off(int x, int y) {
  digitalWrite(rowPin[x], LOW);
  digitalWrite(colPin[y], HIGH);
}