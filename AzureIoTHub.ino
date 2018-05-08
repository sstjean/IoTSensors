


IOTHUB_CLIENT_LL_HANDLE configureAzureIoTHubConnection(void)
{
    iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
    if (iotHubClientHandle == NULL)
    {
        Serial.println("Failed on IoTHubClient_CreateFromConnectionString.");
        while (1);
    }

    IoTHubClient_LL_SetOption(iotHubClientHandle, "product_info", "IoTSensors");
    IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, receiveMessageCallback, NULL);
    IoTHubClient_LL_SetDeviceMethodCallback(iotHubClientHandle, deviceMethodCallback, NULL);
    IoTHubClient_LL_SetDeviceTwinCallback(iotHubClientHandle, twinCallback, NULL);
}



void sendSensorDataToAzureIoTHub(struct SensorData dat, String formattedTime, String messageId) 
{
  if (!messagePending && messageSending)
  {
      char messagePayload[MESSAGE_MAX_LEN];
      generatePayload(data, formattedTime, messageId, messagePayload);
      sendMessage(iotHubClientHandle, messagePayload);
      ThreadAPI_Sleep(sendRetryInterval);
  }
  
  int i = 1;
  while(messagePending && messageSending){
    Serial.printf("    Waiting for the sendCallback to be triggered: %d \n", i);
    IoTHubClient_LL_DoWork(iotHubClientHandle);
    yield();
    ThreadAPI_Sleep(sendRetryInterval);
    i++;
  }


}

