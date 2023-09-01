#include "DeviceLoraABP.h"

void setup()
{
  Serial.begin(115200);

  /*
  int arrayVal[4] = {66, 28, 91, 234};

  int dec = 0;
  int res = 0;
  String hex = "";
  String finalhex = "";

  for (int i = 0; i < sizeof(arrayVal); i++) {
    dec = arrayVal[i];

    while (dec != 0) {
      res = dec % 16;
      dec = dec / 16;

      if (res >= 0 && res <= 9) {
        res = res + 48;

      } else if (res >= 10 && res <= 15) {
        res = res + 55;
      }

      hex += (char) res;
    }

    for (int i = hex.length() - 1; i != -1; i--) {
      finalhex += hex[i];
    }

    hex = "";

  }

  Serial.println(finalhex);
  */
}

void loop()
{
  delay(5000); //!!!

  DeviceLoraABP deviceLoraABP("021c38e7", "421ce74d9cd8cb17d9bae5a68f1f1afd", "85e270057406be1097720b304d181f84", "ac1f09fffe090b61");

  Serial.println(deviceLoraABP.GetNwkskey());

  delay(2000);
}