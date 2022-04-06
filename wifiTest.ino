#include "WiFiEsp.h"

WiFiEspClient server_conn;

int server_conn_status = 0;
int net_status = WL_IDLE_STATUS;

char ssid[] = "Alex Wifi";     // your network SSID (name)
char pwd[] = "7805136080";  // your network password

int post_request(const char* server_url, String route, String data) {
  if(net_status != WL_CONNECTED) {
    return 1;
  }
  
  server_conn.stop();
  
  server_conn_status = server_conn.connect(server_url, 80);
  
  if(server_conn_status) {
    //POST request form
    server_conn.print("POST " + route + " HTTP/1.0\r\n");
    server_conn.print("Host: " + String(server_url) + "\r\n");
    server_conn.print("Connection: close\r\n");
    server_conn.print("Content-Length: " + String(data.length()) + "\r\n");
    server_conn.print("\r\n");
    server_conn.print(data);
    server_conn.print("\r\n\r\n");
  } else {
    Serial.println("Connection could not be established...");
    return -1;
  }

  return 0;
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  WiFi.init(&Serial1);

  if(net_status != WL_CONNECTED) {
    net_status = WiFi.begin(ssid, pwd);
  }

  if(net_status == WL_CONNECTED) {
    Serial.println("Connection established...");
    
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  String test_data = "'date':'1975-08-19T12:15:30.000Z','pressure':'1000','temperature':'20','humidity':'50','altitude':'550'";
  if(post_request("all-in-one-weather.herokuapp.com", "/post_data/", test_data) == 0){
    Serial.println("Gotovo"); 
  };

  delay(60000);
  
}
