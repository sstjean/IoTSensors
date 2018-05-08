

void generatePayload(struct SensorData sData, String formattedTime, String messageId, char *payload)
{
    memset (payload, 0, MESSAGE_MAX_LEN);
    
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["deviceId"] = DEVICE_ID;
    root["messageDateTime"] = formattedTime;
    root["messageId"] = messageId;
    root["tempC"] = round(sData.temperatureC);
    root["tempF"] = round(sData.temperatureF);
    root["humidity"] = round(sData.humidity);
    root["dewPtC"] = round(sData.dewPointC);
    root["dewPtF"] = round(sData.dewPointF);
    root["pressure"] = sData.pressure;
    root["light"] = sData.light;

    root.printTo(payload, MESSAGE_MAX_LEN);
}

void parseTwinMessage(char *message)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(message);
    if (!root.success())
    {
        Serial.printf("parseTwinMessage: Parse %s failed.\r\n", message);
        return;
    }

    if (root["desired"]["interval"].success())
    {
       // sleepInterval = root["desired"]["interval"];
    }
    else if (root.containsKey("interval"))
    {
       // sleepInterval = root["interval"];
    }
}
