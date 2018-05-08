 
void configureWiFi() 
{ 
  WiFiManager wifiManager;
  wifiManager.autoConnect("IoTSensors", "IoTSensors" );
  //wifiManager.startConfigPortal("IoTSensors", "IoTSensors");
  checkForWiFiStatus();
  dumpWiFiInfoToSerial(WiFi);
}


void checkForWiFiStatus()
{    
    while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}


void dumpWiFiInfoToSerial(ESP8266WiFiClass wifi) 
{  
  Serial.println();
  Serial.println(" == WiFi Dump =================================================");
  Serial.print("   IP ADDR: ");
  Serial.println(wifi.localIP());
  Serial.println("   MAC ADDR: " + String(wifi.macAddress()));
  Serial.println("   SSID: " + String(wifi.SSID()));
  Serial.println("   Channel: " + String(wifi.channel()));
  Serial.println("   Is Connected: " + String(wifi.isConnected()));
  Serial.println(" ==============================================================");
  Serial.println();
}

