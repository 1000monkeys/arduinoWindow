#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

int dataPin = 12;
int value = 0;

//WIFI
char ssid[] = "REA-SW Gast";
char pass[] = "password";

//char ssid[] = "Galaxy KVHS";
//char pass[] = "password";

WiFiClient wifi;
HTTPClient http; //Declare an object of class HTTPClient

void setup() {
  Serial.begin(115200);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(dataPin, INPUT);
  pinMode(dataPin, OUTPUT);

  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();
  Serial.print("Number of available WiFi networks discovered:");
  Serial.println(numSsid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  value = digitalRead(dataPin);
  //Serial.println(value);
  digitalWrite(LED_BUILTIN, value);
  //delay(100);
  //yield();

  if(WiFi.status() == WL_CONNECTED){ //Check WiFi connection status  
    http.begin(wifi, "http://10.0.1.60/arduinoWindow/saveState.php?windowId=1&state=" + String(value)); //Specify request destination
    
    int httpCode = http.GET(); //Send the request
    Serial.println(httpCode);
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    
    http.end(); //Close connection
  } else {
    Serial.println("Error in WiFi connection");   
  }
}
