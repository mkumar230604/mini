
#include <EEPROM.h>
#include <LiquidCrystal.h>

#define led 13

// LCD connections: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Push button pins
const int incButton = 8;
const int resetButton = 9;

int count = 0;

void setup()
{
    pinMode(incButton, INPUT_PULLUP);
    pinMode(resetButton, INPUT_PULLUP);
    pinMode(led, OUTPUT);

    lcd.begin(16, 2);
    Serial.begin(9600);

    Serial.println("Digital Counter Started");

    // Read previous count from EEPROM
    EEPROM.get(0, count);

    // Check EEPROM value
    if (count < 0 || count > 999999)
    {
        count = 0;
        EEPROM.put(0, count);
    }

    displayCount();
}

void loop()
{
    // INCREMENT BUTTON
    if (digitalRead(incButton) == LOW)
    {
        delay(50);

        if (digitalRead(incButton) == LOW)
        {
            count++;

            EEPROM.put(0, count);

            displayCount();

            // Wait until button is released
            while (digitalRead(incButton) == LOW)
            {
                delay(10);
            }

            delay(50);
        }
    }

    // RESET BUTTON
    if (digitalRead(resetButton) == LOW)
    {
        delay(50);

        if (digitalRead(resetButton) == LOW)
        {
            count = 0;

            EEPROM.put(0, count);

            displayCount();

            // Wait until button is released
            while (digitalRead(resetButton) == LOW)
            {
                delay(10);
            }

            delay(50);
        }
    }
}

// DISPLAY FUNCTION
void displayCount()
{
    // LCD display
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Digital Counter");

    lcd.setCursor(0, 1);
    lcd.print("Count: ");
    lcd.print(count);

    // Serial Monitor
    Serial.print("Digital Counter: ");
    Serial.println(count);

    // LED indication
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
}
