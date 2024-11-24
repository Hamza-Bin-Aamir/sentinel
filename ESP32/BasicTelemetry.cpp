#include "mpu9250.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid = "Sentinel";
const char* password = "Password1";

AsyncWebServer server(80);
// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
bfs::Mpu9250 IMU(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);
int status;

String getPitch(){
  return String(IMU.gyro_x_radps());
}

String getRoll(){
  return String(IMU.gyro_y_radps());
}

String getYaw(){
  return String(IMU.gyro_z_radps());
}


void setup() {
  // serial to display data
  Serial.begin(115200);
  while (!Serial) {}
  Wire.begin();
  Wire.setClock(400000);
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while (1) {}
  }

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/Pitch", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getPitch().c_str());
  });
  server.on("/Roll", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getRoll().c_str());
  });
  server.on("/Yaw", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getYaw().c_str());
  });

  server.begin();
}

void loop() {
}