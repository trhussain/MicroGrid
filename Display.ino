/*
DISPLAY 

Utility functions for OLED 128x64 module 

*/
#include "config.h"


void displaySetup() {
  Wire.begin(SDA, SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED init failed");
    while (true)
      ;  // Halt
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);  // Default size
  display.setCursor(0, 0);
  display.display();
}





void playBouncingEarsAnimation() {

  int earX = 10;   // Initial X position
  int earY = 10;   // Initial Y position
  int xSpeed = 2;  // Speed in X direction
  int ySpeed = 2;  // Speed in Y direction

  display.clearDisplay();

  // Draw ears (two circles)
  display.fillCircle(earX, earY, 8, SSD1306_WHITE);       // Left Ear
  display.fillCircle(earX + 20, earY, 8, SSD1306_WHITE);  // Right Ear

  // Draw face
  display.fillCircle(earX + 10, earY + 15, 10, SSD1306_WHITE);

  // Bouncing logic
  earX += xSpeed;
  earY += ySpeed;

  if (earX <= 0 || earX + 20 >= SCREEN_WIDTH) xSpeed = -xSpeed;
  if (earY <= 0 || earY + 15 >= SCREEN_HEIGHT) ySpeed = -ySpeed;

  display.display();
  delay(50);
}




void oledPrintCentered(String text, int y = 0, int size = 1) {
  display.clearDisplay();
  display.setTextSize(size);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;
  display.setCursor(x, y);
  display.println(text);
  display.display();
}
void oledPrintMultiline(String line1, String line2, int size = 1) {
  display.clearDisplay();
  display.setTextSize(size);
  display.setCursor(0, 0);
  display.println(line1);
  display.println(line2);
  display.display();
}
void testdrawrect(void) {
  display.clearDisplay();

  for (int16_t i = 0; i < display.height() / 2; i += 2) {
    display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, SSD1306_WHITE);
    display.display();  // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}


void infoPage()  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Hello! Write down or save the following information");
  display.display();
}