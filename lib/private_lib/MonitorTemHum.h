#include <DHTesp.h>
#include <HTTPClient.h>
class MonitorTemHum
{
private:
    /* data */
    HTTPClient http;
    String urlTemperatura = "https://api.thingspeak.com/update?api_key=ALWFZTNL7L1FOI9Y&field1=";
    String urlHumidade = "https://api.thingspeak.com/update?api_key=ALWFZTNL7L1FOI9Y&field2=";
    int pinoutTemp;
    int pinoutHum;
    float temperatura;
    float humidade;
public:
    DHTesp sensor;
    MonitorTemHum();
    void setPinTemp(int pin);
    void setPinHum(int pin);
    void avaliableTempAndHum();
    void setupSensor(int pin, DHTesp::DHT_MODEL_t model);
};
MonitorTemHum::MonitorTemHum()
{
}
void MonitorTemHum::setupSensor(int pin, DHTesp::DHT_MODEL_t model){
  this->sensor.setup(pin,model);
  pinMode(pin,INPUT);
}
void MonitorTemHum::setPinTemp(int pin){
    this->pinoutTemp = pin;
    pinMode(this->pinoutTemp,OUTPUT);
}
void MonitorTemHum::setPinHum(int pin){
    this->pinoutHum = pin;
    pinMode(this->pinoutHum,OUTPUT);
}
void MonitorTemHum::avaliableTempAndHum(){
    this->temperatura = this->sensor.getTemperature();
    this->humidade = this->sensor.getHumidity();
    Serial.print("Temperatura atual: ");
    Serial.println(this->temperatura);
    Serial.print("Humidade atual: ");
    Serial.println(this->humidade);
    Serial.println(this->urlTemperatura+String(this->temperatura));
    this->http.begin(this->urlHumidade+String(this->humidade));
    this->http.GET();
    this->http.end();
    this->http.begin(this->urlTemperatura+String(this->temperatura));
    this->http.GET();
    this->http.end();
    if(this->humidade >= 70.00f && this->temperatura < 30.00f){
      digitalWrite(this->pinoutHum,HIGH);
      digitalWrite(this->pinoutTemp,LOW);
    }else if(this->humidade < 70.00f && this->temperatura >=  30.00f){
      digitalWrite(this->pinoutTemp,HIGH);
      digitalWrite(this->pinoutHum,LOW);
    }else if(this->humidade >= 70.00f && this->temperatura >=  30.00f){
      digitalWrite(this->pinoutTemp,HIGH);
      digitalWrite(this->pinoutHum,HIGH);
    }else{
      digitalWrite(this->pinoutTemp,LOW);
      digitalWrite(this->pinoutHum,LOW);
    }
}
