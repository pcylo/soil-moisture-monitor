#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pins configuration for LCD board connection via I2C interface: 
// address, en, rw, rs, d4, d5, d6, d7, bl, blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Configure custom characters maps
uint8_t high[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
};

uint8_t mid[8] = {
  B00000,
  B10000,
  B11000,
  B11100,
  B11110,
  B11111,
  B00000,
};

uint8_t low[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
};

void setup() {
  lcd.begin(20,4);

  // Create custom characters
  lcd.createChar(0, high);
  lcd.createChar(1, mid);
  lcd.createChar(2, low);

  // Print constant elements of the LCD display
  lcd.setCursor(1,0);
  lcd.print("Soil Moisture: --");
}

void loop() {
  int current_read = random(0, 100);
  delay(5000);
  printCurrentReadValue(current_read);
  printProgressBar(current_read);
  printStatus(current_read);
}

/*
 * Prints text status based on the provided percentage read value.
 */
void printStatus(int percentage) {
  lcd.setCursor(0,3);
  
  if (percentage > 60) {
    lcd.print("All systems nominal");
  } else if (percentage > 30) {
    lcd.print(" Watering suggested ");
  } else {
    lcd.print(" WATERING REQUIRED! ");
    flashScreen();
  }
}

/*
 * Prints numerical read value based on the provided percentage value.
 */
void printCurrentReadValue(int percentage) {
  lcd.setCursor(16,0);
  lcd.print(percentage);
  lcd.print("%   ");
}

/*
 * Prints progress bar based on the provided percentage value.
 * Uses the custom characters.
 */
void printProgressBar(int percentage) {
  int value = percentage / 5;
  
  lcd.setCursor(0,1);
  
  for(int i = 0; i< value; i++) {
    lcd.print(char(0));
  }
  
  if (value < 20) {
    lcd.print(char(1));
  }
  
  for(int i = 0; i< (19-value); i++) {
    lcd.print(char(2));
  }
}

/*
 * Flash the backlight two times rapidly.
 */ 
void flashScreen() {
  for(int i = 0; i< 2; i++) {
    lcd.noBacklight();
    delay(100);
    
    lcd.backlight();
    delay(100);
  }
}

