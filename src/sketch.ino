#include <SimpleTimer.h> // Found here: http://playground.arduino.cc/Code/SimpleTimer

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

int DISPLAY_TIME = 100;  // In milliseconds

int lightsOn = 1;

SimpleTimer timer;

void flash()
{
    lightsOn = 0;
    int i;
    for (i = 0; i < 5; i++) {
        showRGB(512);
        delay(300);
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        delay(300);
    }
}

void setup()
{
    // Here we'll configure the Arduino pins we're using to
    // drive the LED to be outputs:

    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    timer.setTimeout(1000 * 60 * 60, flash);
}


void loop()
{
    timer.run();
    if (lightsOn == 1) {
        showSpectrum();
    }
}

// Not in use
void mainColors()
{
    // Off (all LEDs off):

    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);

    delay(1000);

    // Red (turn just the red LED on):

    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);

    delay(1000);

    // Green (turn just the green LED on):

    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);

    delay(1000);

    // Blue (turn just the blue LED on):

    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);

    delay(1000);

    // Yellow (turn red and green on):

    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);

    delay(1000);

    // Cyan (turn green and blue on):

    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);

    delay(1000);

    // Purple (turn red and blue on):

    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);

    delay(1000);

    // White (turn all the LEDs on):

    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);

    delay(1000);
}


// showSpectrum()

// This function steps through all the colors of the RGB LED.
// It does this by stepping a variable from 0 to 768 (the total
// number of colors), and repeatedly calling showRGB() to display
// the individual colors.

void showSpectrum()
{
    int x;

    for (x = 0; x < 768; x++) {
        showRGB(x);  // Call RGBspectrum() with our new x
        delay(10);   // Delay for 10 ms (1/100th of a second)
    }
}

void showRGB(int color)
{
    int redIntensity;
    int greenIntensity;
    int blueIntensity;

    if (color <= 255) {
        redIntensity = 255 - color;    // red goes from on to off
        greenIntensity = color;        // green goes from off to on
        blueIntensity = 0;             // blue is always off
    } else if (color <= 511) {
        redIntensity = 0;                     // red is always off
        greenIntensity = 255 - (color - 256); // green on to off
        blueIntensity = (color - 256);        // blue off to on
    } else {
        redIntensity = (color - 512);         // red off to on
        greenIntensity = 0;                   // green is always off
        blueIntensity = 255 - (color - 512);  // blue on to off
    }

    // Now that the brightness values have been set, command the LED
    // to those values

    analogWrite(RED_PIN, redIntensity);
    analogWrite(BLUE_PIN, blueIntensity);
    analogWrite(GREEN_PIN, greenIntensity);
}
