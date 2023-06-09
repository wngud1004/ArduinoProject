#include <ESP8266WiFi.h>
#include <DHT.h>

#define PIN_DHT D4

const char* ssid = "Galaxy Note20 Ultra 5G3378";
const char* password = "jh1004ben2686";

WiFiServer server(80);
WiFiClient client;
DHT DHTsensor(PIN_DHT, DHT11);
 
void setup() {
	DHTsensor.begin();
 
	Serial.begin(115200);
 
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
 
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connecting to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
 
	server.begin();
	Serial.println("Server started");
}
 
void loop() {
	client = server.available();
	if(!client) return;
 
	Serial.println("새로운 클라이언트");
	client.setTimeout(5000);
 
	String request = client.readStringUntil('\r');
	Serial.println("request: ");
	Serial.println(request);
 
	while(client.available()) {
		client.read();
	}
 
	float humidity = DHTsensor.readHumidity();
	float temp = DHTsensor.readTemperature();
	Serial.print("Humidity : ");
	Serial.print(humidity);
	Serial.print(" Temperature : ");
	Serial.print(temp);
	Serial.println(" ºC");
 
	client.print("HTTP/1.1 200 OK");
	client.print("Content-Type: text/html\r\n\r\n");
	client.print("<!DOCTYPE HTML>");
	client.print("<html>");
	client.print("<head>"); 
	client.print("<meta charset=\"UTF-8\" http-equiv=\"refresh\" content=\"1\">");
	client.print("<title>DHT senrsor test Webpage</title>");
	client.print("</head>");
	client.print("<body>");
	client.print("<h2>DHT senrsor test Webpage</h2>");
	client.print("<br>");
	client.print("Temperature : ");
	client.print(temp);
	client.print(" °C");
	client.print("<br>");
	client.print("Humidity : ");
	client.print(humidity);
	client.print(" %");
	client.print("</body>");
	client.print("</html>");
 
	Serial.println("클라이언트 연결 해제");
}
