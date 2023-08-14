#include <Arduino.h>
#include <WifiWokwi.h>
#include <MonitorTemHum.h>

MonitorTemHum *monitor = new MonitorTemHum();
WifiWokwi *wifi = new WifiWokwi();

void setup() {

    wifi->setSSiD("Wokwi-GUEST");
    wifi->setPassword("");
    wifi->setChannel(6);
    wifi->init();
    monitor->setPinHum(2);
    monitor->setPinTemp(12);
    monitor->setupSensor(14, monitor->sensor.DHT22);
}
void loop() {
    monitor->avaliableTempAndHum();
    delay(2000);
}
