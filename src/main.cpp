#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 2048 
#define DATA_PIN 25
CRGB leds[NUM_LEDS];

int XY(int x, int y) {
  if (x >= 64 || y >= 32 || x < 0 || y < 0) return 0;
  return y * 64 + x; 
}

// Hàm vẽ ký tự 5x3
void drawSprite(int x, int y, const byte data[5], CRGB color) {
  for(int i=0; i<5; i++) 
    for(int j=0; j<3; j++) 
      if((data[i] >> (2-j)) & 1) leds[XY(x+j, y+i)] = color;
}

// Font số và chữ
const byte f5[5] = {0x7,0x4,0x7,0x4,0x4}; // F
const byte u5[5] = {0x5,0x5,0x5,0x5,0x7}; // U
const byte l5[5] = {0x4,0x4,0x4,0x4,0x7}; // L
const byte digits[10][5] = {
  {0x7,0x5,0x5,0x5,0x7}, {0x2,0x2,0x2,0x2,0x2}, {0x7,0x1,0x7,0x4,0x7},
  {0x7,0x1,0x7,0x1,0x7}, {0x5,0x5,0x7,0x1,0x1}, {0x7,0x4,0x7,0x1,0x7},
  {0x7,0x4,0x7,0x5,0x7}, {0x7,0x1,0x1,0x1,0x1}, {0x7,0x5,0x7,0x5,0x7}, {0x7,0x5,0x7,0x1,0x7}
};

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  randomSeed(analogRead(0)); // Khởi tạo bộ tạo số ngẫu nhiên
}

int soNguoi = 0;

void loop() {
  FastLED.clear();
  
  // 1. Vẽ khung viền Xanh Dương
  for(int x = 0; x < 64; x++) {
    leds[XY(x, 0)] = leds[XY(x, 31)] = CRGB::Blue;
  }

  // 2. Màu sắc (Dưới 50 Xanh, từ 50 trở đi Đỏ)
  CRGB mauSac = (soNguoi >= 50) ? CRGB::Red : CRGB::Green;

  // 3. Vẽ số đếm "XX/50" (Căn giữa)
  drawSprite(22, 6, digits[soNguoi/10], mauSac); 
  drawSprite(26, 6, digits[soNguoi%10], mauSac); 
  leds[XY(31, 10)] = leds[XY(32, 9)] = leds[XY(33, 8)] = leds[XY(34, 7)] = leds[XY(35, 6)] = CRGB::White;
  drawSprite(37, 6, digits[5], CRGB::White); 
  drawSprite(41, 6, digits[0], CRGB::White); 

  // 4. Nếu đạt 50 người thì hiện chữ FULL (Căn giữa)
  if (soNguoi >= 50) {
    int startX = 24; 
    int startY = 18;
    drawSprite(startX,     startY, f5, CRGB::Red);
    drawSprite(startX + 5, startY, u5, CRGB::Red);
    drawSprite(startX + 10, startY, l5, CRGB::Red);
    drawSprite(startX + 15, startY, l5, CRGB::Red);
    
    FastLED.show();
    // Dừng tại đây khi đã đầy
    while(true) { delay(1000); }
  }

  FastLED.show();

  // 5. Logic biến động ngẫu nhiên
  // 70% cơ hội tăng người, 30% cơ hội giảm người (để xu hướng chung vẫn là đi lên)
  int xacSuat = random(0, 100);
  if (xacSuat < 70) {
    soNguoi++; 
  } else {
    if (soNguoi > 0) soNguoi--; // Không để số người âm
  }

  delay(300); // Tốc độ cập nhật (300ms một lần biến động)
}