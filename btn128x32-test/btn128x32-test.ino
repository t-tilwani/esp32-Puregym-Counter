#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Local Storage
#include <Preferences.h>
Preferences prefs;


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#define LEFT_BTN 6
#define RIGHT_BTN 7

int leftIterator = 0;
int rightIterator = 0;

bool first = true;
void drawScreen() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Left: ");
  display.println(leftIterator);

  display.setCursor(0, 20);
  display.print("Right: ");
  display.println(rightIterator);

  display.display();
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(12, 11);

  prefs.begin("mydata", false);
  
  leftIterator = prefs.getInt("left", 0);
  rightIterator = prefs.getInt("right", 0);


  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    for(;;);
  }

  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);

  Serial.println("Button + OLED test is ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  bool updated = false;

  if(first) {
    first = false;
    drawScreen();
  }
  
  if(digitalRead(LEFT_BTN) == LOW && digitalRead(RIGHT_BTN) == LOW) {
    Serial.println("Screen has been reset");
    leftIterator = 0;
    rightIterator = 0;
    prefs.putInt("right", 0);
    prefs.putInt("left", 0);
    drawScreen();
    delay(500);
  } else {
    if(digitalRead(LEFT_BTN) == LOW) {
      Serial.println("Left button was pressed");
      leftIterator++;
      prefs.putInt("left", leftIterator);
      drawScreen();
      delay(200);
    }

    if(digitalRead(RIGHT_BTN) == LOW) {
      Serial.println("Right Button was pressed");
      rightIterator++;
      prefs.putInt("right", rightIterator);
      drawScreen();
      delay(200);
    }
  }
  
}
