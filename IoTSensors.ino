
#include <AzureIoTHub.h>
#include <AzureIoTUtility.h>
#include <AzureIoTProtocol_MQTT.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include <NTPClient.h>
#include <Timezone.h>

#include "config.h"
#include "globals.h"

// Variables
SensorData data;
static IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;
static bool messagePending = false;
static bool messageSending = true;

static int sleepInterval = DEEP_SLEEP_SECS;
static int sendRetryInterval = RETRY_INTERVAL;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedTime;
String theUUID;
  
//US Eastern Time Zone (New York, Detroit)
TimeChangeRule myDST = {"EDT", Second, Sun, Mar, 2, -240};    //Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"EST", First, Sun, Nov, 2, -300};     //Standard time = UTC - 5 hours
Timezone myTZ(myDST, mySTD);

void setup() {
  pinMode(LED_PIN, OUTPUT);

  initSerial();
  configureWiFi();
  timeClient.begin();
  configureAzureIoTHubConnection();
}


void loop() {

  timeClient.update();
  formattedTime = getFormattedTime(timeClient);
  data = retrieveSensorData();
  theUUID = getUUID();
  sendSensorDataToAzureIoTHub(data, formattedTime, theUUID);
   
  Serial.println("DeepSleep begin for " + String(sleepInterval) + " seconds");
  ESP.deepSleep(1000000 * sleepInterval, WAKE_RF_DEFAULT); // GPIO16 needs to be tied to RST to wake from deepSleep. Execute restarts from beginning of sketch
}
