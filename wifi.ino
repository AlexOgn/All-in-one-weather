#include "WiFiEsp.h"

WiFiEspClient server_conn;

int server_conn_status = 0;
int net_status = WL_IDLE_STATUS;

char ssid[] = "iPhone";
char pwd[] = "12345678";

int post_request(const char* server_url, String route, String data) {
  if(net_status != WL_CONNECTED) {
    return 1;
  }
  
  server_conn.stop();
  
  server_conn_status = server_conn.connect(server_url, 80);
  
  if(server_conn_status) {
    Serial.println("Connected successfully");
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

void wifi_setup() {
  WiFi.init(&Serial1);

  if(net_status != WL_CONNECTED) {
    Serial.println("Connecting to Wi-Fi...");
    net_status = WiFi.begin(ssid, pwd);
  }

  if(net_status == WL_CONNECTED) {
    Serial.println("Connection established...");
    
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.localIP());
  }
}

void send_data() {
  String data = MakeString(readPressure(), GetTemperature(), GetHumidity(), GetAltitude());
  
  if(post_request("all-in-one-weather.herokuapp.com", "/post_data", data) == 0){
    Serial.println("Successfully POSTed data");
  }else{
    Serial.println("Error sending POST request");
  }
}
