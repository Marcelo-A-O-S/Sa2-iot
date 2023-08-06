#include <Arduino.h>
#include <WifiWokwi.h>
#include <HTTPClient.h>

HttpClient client;

WifiWokwi *wifi = new WifiWokwi();

void setup() {
    wifi->setSSiD("Wokwi-GUEST");
    wifi->setPassword("");
    wifi->setChannel(6);
    wifi->init();
}
void loop() {

}
