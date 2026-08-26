#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- WIFI ----------------
const char* ssid = "Cebin's Galaxy S23";
const char* password = "11111111";

WebServer server(80);

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- BUTTON ----------------
#define BUTTON_PIN 4

// ---------------- MEDICINE COUNTS ----------------
int paraCount = 10;
int cetiCount = 10;
int omepCount = 10;
int amoxCount = 10;
int vitdCount = 10;
int ibuCount  = 10;
int doloCount = 10;
int azithromycinCount = 10;
int insulinCount = 10;

String currentMedicine = "";
int* currentCount = NULL;
int currentPin = -1;
int quantityToSubtract = 0; // Stores the number requested from the website

// ------------------------------------------------
// STATUS HANDLER
// ------------------------------------------------
void handleStatus() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ONLINE");
}

// ------------------------------------------------
// ORDER HANDLER
// ------------------------------------------------
void handleOrder() {

  server.sendHeader("Access-Control-Allow-Origin", "*");

  if (server.hasArg("item")) {

    String med = server.arg("item");
    
    // Read the quantity sent from the website
    if (server.hasArg("qty")) {
      quantityToSubtract = server.arg("qty").toInt();
    } else {
      quantityToSubtract = 1; 
    }

    currentPin = -1;
    currentCount = NULL;

    if (med == "paracetamol") {
      currentPin = 13;
      currentMedicine = "Paracetamol";
      currentCount = &paraCount;
    }
    else if (med == "cetirizine") {
      currentPin = 25;
      currentMedicine = "Cetirizine";
      currentCount = &cetiCount;
    }
    else if (med == "omeprazole") {
      currentPin = 14;
      currentMedicine = "Omeprazole";
      currentCount = &omepCount;
    }
    else if (med == "amoxicillin") {
      currentPin = 27;
      currentMedicine = "Amoxicillin";
      currentCount = &amoxCount;
    }
    else if (med == "vitamin d3") {
      currentPin = 26;
      currentMedicine = "Vitamin D3";
      currentCount = &vitdCount;
    }
    else if (med == "ibuprofen") {
      currentPin = 33;
      currentMedicine = "Ibuprofen";
      currentCount = &ibuCount;
    }
    else if (med == "dolo") {
      currentPin = 32;
      currentMedicine = "Dolo";
      currentCount = &doloCount;
    }
    else if (med == "azithromycin") {
      currentPin = 15;
      currentMedicine = "Azithromycin";
      currentCount = &azithromycinCount;
    }
    else if (med == "insulin") {
      currentPin = 2;
      currentMedicine = "Insulin";
      currentCount = &insulinCount;
    }

    if (currentPin != -1 && currentCount != NULL) {

      // Check if requested amount is greater than what we have in stock
      if (quantityToSubtract > *currentCount) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(currentMedicine);
        lcd.setCursor(0, 1);
        lcd.print("Insufficient Stock");
        
        // Reset so the button doesn't do anything
        currentPin = -1; 
      }
      else if (*currentCount > 0) {
        digitalWrite(currentPin, HIGH);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(currentMedicine);
        lcd.setCursor(0, 1);
        lcd.print("Qty to take: ");
        lcd.print(quantityToSubtract);
      }
      else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(currentMedicine);
        lcd.setCursor(0, 1);
        lcd.print("Out of Stock");
      }
    }
  }

  server.send(200, "text/plain", "OK");
}

// ------------------------------------------------
// SETUP
// ------------------------------------------------
void setup() {

  Serial.begin(115200);

  int pins[] = {13, 25, 14, 27, 26, 33, 32, 15 ,2};
  for (int i = 0; i < 9; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  lcd.clear();
  lcd.print("WiFi Connected");

  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/order", handleOrder);
  server.on("/status", handleStatus);

  server.begin();
}

// ------------------------------------------------
// LOOP
// ------------------------------------------------
void loop() {

  server.handleClient();

  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(BUTTON_PIN);

  // Detect button press (HIGH -> LOW)
  if (lastButtonState == HIGH && buttonState == LOW) {

    if (currentPin != -1 && currentCount != NULL && *currentCount >= quantityToSubtract) {

      // Turn OFF LED 
      digitalWrite(currentPin, LOW);

      // Decrease count by the quantity requested from the website
      (*currentCount) = (*currentCount) - quantityToSubtract;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(currentMedicine);
      lcd.setCursor(0, 1);
      lcd.print("Remaining: ");
      lcd.print(*currentCount);

      // Reset selection
      currentPin = -1;
      currentCount = NULL;
      quantityToSubtract = 0;
    }

    delay(250); // debounce
  }

  lastButtonState = buttonState;
}