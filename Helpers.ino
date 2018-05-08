

String getUUID(void)
{
  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;
  const int httpsPort = 443;
  String theUUID;
  
  Serial.println();
  Serial.printf("getUUID: Connecting to %s over port %d.\n", uuidApiHost, httpsPort); 
  
  if (!client.connect(uuidApiHost, httpsPort)) {
    Serial.println("getUUID: connection failed");
    return "connection failed";
  }else{
    Serial.println("getUUID: connection succeeded");
  }

  if (client.verify(uuidGeneratorFingerprint, uuidApiHost)) {
    Serial.println("getUUID: certificate matches");
  } else {
    Serial.println("getUUID: certificate doesn't match");
  }

  // We now create a URI for the request
  String url = uuidApiUrl;


  // This will send the request to the server
  String request = String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + uuidApiHost + "\r\n" +
                   "User-Agent: ESP8266Sensors\r\n" +
                   "Connection: close\r\n\r\n";
  Serial.println("getUUID: " + request);
  client.print(request);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("getUUID: >>> Client Timeout !");
      client.stop();
      return "Client Timeout";
    }
  }

  // Read all the lines of the reply from server grab the uuid
  while (client.available()) {
    String line = client.readStringUntil('\r');
    char firstChar = line[1];
    if ((line.length() > 5) && (isLowerCase(firstChar) || isDigit(firstChar))){
      theUUID = line.substring(1);
      Serial.println("getUUID: " + theUUID);
    }
  }

  Serial.println("getUUID: closing connection");
  Serial.println();
  
  return theUUID;
}


void initSerial(void)
{ 
  String devId = DEVICE_ID;
  Serial.begin(115200);
  //Serial.setDebugOutput(true);
  Serial.println("Starting...");
  Serial.println("I am " + devId);
  delay(2000);
}


String getFormattedTime(NTPClient curTime)
{
    TimeChangeRule *tcr;        //pointer to the time change rule, use to get TZ abbrev
    time_t utc, local;
    //time_t  currentTime;
    struct tm * ts;
    char timeBuf[80];

    // Get current time
    utc = (time_t)curTime.getEpochTime();
    local = myTZ.toLocal(utc, &tcr);
    
    ts = localtime(&local);
    int tYear = ts->tm_year + 1900;
    int tMonth = ts->tm_mon + 1; 
    int tDay = ts->tm_mday;
    int tHour = ts->tm_hour;
    int tMin = ts->tm_min;
    int tSec = ts->tm_sec;

    sprintf(timeBuf, "%4d-%02d-%02dT%02d:%02d:%02d.000Z",tYear, tMonth, tDay, tHour, tMin, tSec);
    return String(timeBuf);
}


void blinkLED()
{
    Serial.println("blink");
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
}

float celciusToFarenheit(float tempC)
{
  return tempC * 9/5 + 32; 
}

float calculateDewPointC(float humidity, float tempC)
{
    
    float humi = 34;
    float ans =  (tempC - (14.55 + 0.114 * tempC) * (1 - (0.01 * humi)) - pow(((2.5 + 0.007 * tempC) * (1 - (0.01 * humi))),3) - (15.9 + 0.117 * tempC) * pow((1 - (0.01 * humi)), 14));

    return ans;           // returns dew Point in Celsius
}

