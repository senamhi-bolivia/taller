#include <SensorDriverb.h>
char driver[]="I2C";         // driver name
char type[]="TMP";           // driver name
int address=0x48;            // i2c address

char* json;
aJsonObject* aj;
SensorDriver* sd;

void setup()
{

  // start up the serial interface
  Serial.begin(115200);
  Serial.println("started");

  // start up the i2c interface
  Wire.begin();

    sd=SensorDriver::create(driver,type);
    if (sd == NULL){
      Serial.print(driver);
      Serial.println(": driver not created !");
    }else{
      sd->setup(driver,address);
    }
}

void loop()
{
  long unsigned int waittime,maxwaittime=0;

  // prepare sensors to measure
  if (!sd == NULL){
    if (sd->prepare(waittime) == SD_SUCCESS){
      Serial.print(driver);
      Serial.print(" : ");
      Serial.print(type);
      Serial.println(" : Prepare OK");
    }else{
      Serial.print(driver);
      Serial.print(" : ");
      Serial.print(type);
      Serial.println(" : Prepare failed !");
    }
  }
  
  //wait sensors to go ready
  Serial.print("# wait sensors for ms:");  Serial.println(waittime);
  delay(waittime);  // 500 for tmp and 250 for adt and 2500 for davis
  
  if (!sd == NULL){
    
    // get integers values 
#define LENVALUES 2
    long values[LENVALUES];
    size_t lenvalues=LENVALUES;
    
    for (int ii = 0; ii < lenvalues; ii++) {
      //values[ii]=4294967296;
      values[ii]=2147483647;
    }
    
    if (sd->get(values,lenvalues) == SD_SUCCESS){
      for (int ii = 0; ii < lenvalues; ii++) {
	Serial.println(values[ii]);
      }
    }else{
      Serial.println("Error");
    }
    
    Serial.print(driver);
    Serial.print(" : ");
    Serial.print(type);
    Serial.print(" : "); 
    // get values in json format
    aj=sd->getJson();
    json=aJson.print(aj,50);
    Serial.println(json);
    free(json);
    aJson.deleteItem(aj);
  }

  // sleep some time to do not go tired ;)
  Serial.println("#sleep for 1s to do not go tired");
  delay(1000);

}
