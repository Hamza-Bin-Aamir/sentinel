// WARNING: MAKE SURE TO USE THE ARDUINO IDE FOR THIS CODE TO WORK
#include "MPU9250.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid = "Sentinel";
const char* password = "KyunWorkNahinKarti";

AsyncWebServer server(80);
// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire, 0x68);
int status;

String getPitch(){
  return String(IMU.getGyroX_rads());
}

String getRoll(){
  return String(IMU.getGyroY_rads());
}

String getYaw(){
  return String(IMU.getGyroZ_rads());
}


void setup() {
  // serial to display data
  Serial.begin(115200);
  while (!Serial) {}
  

  // start communication with IMU
  status = IMU.begin();
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
  // read the sensor
  IMU.readSensor();
  // display the data
  Serial.print(IMU.getAccelX_mss(), 6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(), 6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(), 6);
  Serial.print("\t");
  Serial.print(IMU.getGyroX_rads(), 6);
  Serial.print("\t");
  Serial.print(IMU.getGyroY_rads(), 6);
  Serial.print("\t");
  Serial.print(IMU.getGyroZ_rads(), 6);
  Serial.print("\t");
  Serial.print(IMU.getMagX_uT(), 6);
  Serial.print("\t");
  Serial.print(IMU.getMagY_uT(), 6);
  Serial.print("\t");
  Serial.print(IMU.getMagZ_uT(), 6);
  Serial.print("\t");
  Serial.println(IMU.getTemperature_C(), 6);
  delay(100);
}