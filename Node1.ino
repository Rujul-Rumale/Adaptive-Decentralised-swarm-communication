#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< I2C address for most 128x64 OLED displays

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DEVICE_ID 2
#define GAS_SENSOR_PIN A0 // Analog pin connected to MICS 5524 sensor
String sentData = "";       // Stores the data to be sent
String receivedData[4];     // Stores data from up to 4 devices
volatile bool newDisplayData = false; // Flag for new data to update display

// Function prototypes
void displaySentData(const String &data);
void displayReceivedData();

void setup() {
  // Initialize Serial Communication
  Serial.begin(9600);
  Serial1.begin(9600); // HC-12 communication

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // Halt execution
  }

  // Display startup message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("HC-12 Communication"));
  display.println(F("Device ID: 2"));
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // Read gas sensor value from MICS 5524
  int gasRawValue = analogRead(GAS_SENSOR_PIN);
  float gasVoltage = gasRawValue * (3.3 / 1023.0); // Convert to voltage

  // Prepare data string to send
  sentData = String(DEVICE_ID) + ",G:" + String(gasVoltage, 2) + "V";

  // Send data via HC-12
  Serial1.println(sentData);

  // Signal the second core to update the display
  newDisplayData = true;

  // Listen for incoming data
  if (Serial1.available()) {
    String received = Serial1.readStringUntil('\n');
    parseReceivedData(received);
  }

  delay(1000); // Repeat every second
}

void parseReceivedData(const String &data) {
  int deviceId = data.substring(0, data.indexOf(',')).toInt();
  if (deviceId >= 1 && deviceId <= 4) {
    receivedData[deviceId - 1] = data; // Store data for each device ID
  }
}

void setup1() {
  // Second core initialization
  // Nothing required here for now
}

void loop1() {
  // Continuously check for new data to update the display
  if (newDisplayData) {
    // Clear flag
    newDisplayData = false;

    // Update the display
    display.clearDisplay();
    display.setCursor(0, 0);
    displaySentData(sentData);    // Show sent data
    displayReceivedData();        // Show received data
    display.display();
  }
}

void displaySentData(const String &data) {
  display.println(F("Sent:"));
  display.println(data);
}

void displayReceivedData() {
  display.println(F("---------------------"));
  for (int i = 0; i < 4; i++) {
    if (receivedData[i].length() > 0) {
      display.println(receivedData[i]);
      display.println(F("---------------------"));
    }
  }
}
