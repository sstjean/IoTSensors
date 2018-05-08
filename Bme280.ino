#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>


int diyMallBme280I2CAddr = 0x76;
int adafruitBme20I2CAddr = 0x77;

Adafruit_BME280 bme280; // I2C
bool bme280Initialised = false;
float bme280Calibration = -0.5;


void initBme280() 
{
	if (bme280Initialised) { 
	    Serial.println("Bme280 already initialized");
	    return; 
	}
  
  Serial.println("    Initializing Bme280");
	bme280.begin(diyMallBme280I2CAddr);
	bme280Initialised = true;
  Serial.println("    Initialized Bme280");
}


struct SensorData getBme280Readings(void) 
{
	const int numberOfSamples = 4;
  SensorData sensorData;
  
	initBme280();
	sensorData.temperatureC = sensorData.temperatureF = sensorData.dewPointC = sensorData.dewPointF = sensorData.pressure = sensorData.humidity = 0;

	for (int c = 0; c < numberOfSamples; c++) {
		sensorData.temperatureC += bme280.readTemperature() + bme280Calibration;
		sensorData.pressure += (int)((int)(bme280.readPressure() + 0.5) / 100);
		sensorData.humidity += bme280.readHumidity();
		delay(500);
	}

	sensorData.temperatureC /= numberOfSamples;
  sensorData.temperatureF = celciusToFarenheit(sensorData.temperatureC);
	sensorData.pressure /= numberOfSamples;
	sensorData.humidity /= numberOfSamples;
  sensorData.dewPointC = calculateDewPointC(sensorData.humidity, sensorData.temperatureC);
  sensorData.dewPointF = celciusToFarenheit(sensorData.dewPointC);

 return sensorData;
}

