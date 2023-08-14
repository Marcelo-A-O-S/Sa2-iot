#include <DHTesp.h>
#include <HTTPClient.h>



class MonitorTemHum
{
private:
    /* data */
    HTTPClient http;
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
    String urlHumidade = "https://api.thingspeak.com/update?api_key=ALWFZTNL7L1FOI9Y&field2=";
    String urlTemperatura = "https://api.thingspeak.com/update?api_key=ALWFZTNL7L1FOI9Y&field1=";
    this->temperatura = this->sensor.getTemperature();
    this->humidade = this->sensor.getHumidity();
    if(this->humidade >= 70.00f && this->temperatura < 30.00f){
      Serial.print("Temperatura atual: ");
      Serial.println(this->temperatura);
      Serial.print("Humidade atual: ");
      Serial.println(this->humidade);
      urlHumidade.concat(this->humidade);
      this->http.begin(urlHumidade);
      this->http.GET();
      this->http.end();
      urlTemperatura.concat(this->temperatura);
      this->http.begin(urlTemperatura);
      this->http.GET();
      this->http.end();
      digitalWrite(this->pinoutHum,HIGH);
      digitalWrite(this->pinoutTemp,LOW);

    }else if(this->humidade < 70.00f && this->temperatura >=  30.00f){
      Serial.print("Temperatura atual: ");
      Serial.println(this->temperatura);
      Serial.print("Humidade atual: ");
      Serial.println(this->humidade);
      urlTemperatura.concat(this->temperatura);
      this->http.begin(urlTemperatura);
      this->http.GET();
      this->http.end();
      urlHumidade.concat(this->humidade);
      this->http.begin(urlHumidade);
      this->http.GET();
      this->http.end();
      digitalWrite(this->pinoutTemp,HIGH);
      digitalWrite(this->pinoutTemp,LOW);
    }else if(this->humidade >= 70.00f && this->temperatura >=  30.00f){
      Serial.print("Temperatura atual: ");
      Serial.println(this->temperatura);
      Serial.print("Humidade atual: ");
      Serial.println(this->humidade);
      urlHumidade.concat(this->humidade);
      urlTemperatura.concat(this->temperatura);
      this->http.begin(urlHumidade);
      this->http.GET();
      this->http.end();
      this->http.begin(urlTemperatura);
      this->http.GET();
      this->http.end();
      digitalWrite(this->pinoutTemp,HIGH);
      digitalWrite(this->pinoutHum,HIGH);
    }else{
      Serial.print("Temperatura atual: ");
      Serial.println(this->temperatura);
      Serial.print("Humidade atual: ");
      Serial.println(this->humidade);
      urlHumidade.concat(this->humidade);
      urlTemperatura.concat(this->temperatura);
      this->http.begin(urlHumidade);
      this->http.GET();
      this->http.end();
      this->http.begin(urlTemperatura);
      this->http.GET();
      this->http.end();
      digitalWrite(this->pinoutTemp,LOW);
      digitalWrite(this->pinoutHum,LOW);
    }
}
