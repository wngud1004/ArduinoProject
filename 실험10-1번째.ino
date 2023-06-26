#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "Galaxy Note20 Ultra 5G3378";
const char* password = "jh1004ben2686";

int ledPin= D0;
WiFiServer server(80); //NODE MCU를 서버로 사용하겠다 // 포트번호는 80

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.print("CONNECTING TO ");
  Serial.println(ssid);
  
  //WiFi.mode(WIFI_STA)
  WiFi.begin(ssid, password); // 와이파이 이름과 비밀번호를 통해 WIFI연결을 시작하겠다.
  // WL_CONNECTED라는 값을 돌려준다

  while (WiFi.status() != WL_CONNECTED) { // 네트워크의 연결 상태, 8개의 리턴값 
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi connected!");

  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  //서버 IP주소를 알려준다. 브라우저의 주소란에 치면 NODE MCU가 서버로 있는 것으로 접근할 수 있다.
  Serial.println("/");
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  //서버와 연결된 클라이언트가 있으면 다음으로 넘어가라

  String request = client.readStringUntil('\r');
   // \r 명령어, 즉 줄 바꿈 명령어가 나오기 전까지 계속 데이터를 읽어라

  Serial.println(request);
  client.flush();
  //버퍼에 남은것을 없애라

  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  // 읽어들인 문자에 /LED=ON 이 있는지 없는지 확인하라, (즉 /LED=ON 이 -1 인 상태) 
  //그리고 digitalWrite에 적용되는 핀에 맞추어서 값을 HIGH로 가져라 ==> 불을 켜라

  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
  // 읽어들인 문자에 /LED=OFF 이 있는지 없는지 확인하라, (즉 /LED=OFF 이 -1 인 상태) 
  //그리고 digitalWrite에 적용되는 핀에 맞추어서 값을 LOW로 가져라 ==> 불을 꺼라

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("LED is turned ");
  if (value) {
    client.println("On");
  } else {
    client.print("Off");
  }

  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"><button>Turn On</button></a>");

  client.println("<a href=\"/LED=OFF\"><button>Turn Off</button></a>");
  client.println("</html>");
  //HTML로 서버에 버튼을 생성하고 사이트를 만들어라
  delay(1);

  Serial.println("Client disconnected!!");
  Serial.print
