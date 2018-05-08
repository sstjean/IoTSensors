const char* uuidGeneratorFingerprint = "8f c6 bf d9 ed c1 24 d1 96 37 6e 48 57 7d 50 d6 fc db dd 81";
const char* uuidApiHost =  "www.uuidgenerator.net";  //173.255.225.224
const char* uuidApiUrl = "/api/guid"; 

String currentDateTime;

struct SensorData{
  float temperatureC;
  float temperatureF;
  float humidity;
  float dewPointC;
  float dewPointF;
  int pressure;
  int light;
};

