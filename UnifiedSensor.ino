struct SensorData retrieveSensorData(void)
{  
  SensorData dat;
  dat = getBme280Readings();
  //dat = getFakeWeatherReadings();
  dat.light = getLdrReadings();
  dumpSensorDataToSerial(dat);
  return dat;
}


struct SensorData getFakeWeatherReadings(void) 
{  
  SensorData dat;
  dat.temperatureC = random(20, 30);
  dat.temperatureF = celciusToFarenheit(dat.temperatureC);
  dat.humidity = random(20, 60);
  dat.dewPointC = calculateDewPointC(dat.humidity, dat.temperatureC);
  dat.dewPointF = celciusToFarenheit(dat.dewPointC);
  dat.pressure = random(990,1040); 
  return dat;
}


void dumpSensorDataToSerial(struct SensorData dat) 
{ 
  Serial.println();
  Serial.println(" == Sensor Data ====================");  
  Serial.printf("  Temp:      %3.0f*C \n", dat.temperatureC);
  Serial.printf("  Temp:      %3.0f*F \n", dat.temperatureF);
  Serial.printf("  Humidity:  %3.0f%% \n", dat.humidity);
  Serial.printf("  Dew Point: %3.0f*C \n", dat.dewPointC);
  Serial.printf("  Dew Point: %3.0f*F \n", dat.dewPointF);
  Serial.printf("  Pressure: %4dhPa \n", dat.pressure);
  Serial.printf("  Light:     %3d \n", dat.light);
  Serial.println(" ===================================");
  Serial.println();
}



