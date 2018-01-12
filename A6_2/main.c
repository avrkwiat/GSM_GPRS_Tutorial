#define TINY_GSM_MODEM_A6

#include <TinyGsmClient.h>
const char apn[]  = "internet";
const char user[] = "";
const char pass[] = "";
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(D5, D6); // RX, TX

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

long lastReconnectAttempt = 0;

void setup() {
  pinMode(D0, OUTPUT);
  digitalWrite(D0,HIGH);

  Serial.begin(115200);
  delay(10);
  SerialAT.begin(9600);
  delay(3000);
  Serial.println("Initializing modem...");
  modem.restart();

  Serial.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    Serial.println(" fail");
    while (true);
  }
  Serial.println(" OK");

  Serial.print("Connecting to ");
  Serial.print(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    Serial.println(" fail");
    while (true);
  }
  Serial.println(" OK");
  SerialAT.println("at+cifsr");
  delay(3000);
  SerialAT.println("at+cifsr");

}
void loop() {

}