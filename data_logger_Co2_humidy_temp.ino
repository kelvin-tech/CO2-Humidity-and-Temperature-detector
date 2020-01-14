
///
#include  <virtuabotixRTC.h>
//Wiring SCLK -> 7, I/O -> 6, CE -> 5
//Or     CLK -> 7 , DAT -> 6, Reset -> 5

virtuabotixRTC myRTC(7, 6, 5); //If you change the wiring change the pins here also

  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year



#include <SPI.h>
#include <SD.h>
#include <dht.h>
dht DHT;
#define DHT22_PIN 2
const int chipSelect = 4;
int temp_reading = 0;
int hum_reading = 0;
String temp = "";
String hum = "";
String co2 = "";
String day_of_month = "";
String month = "";
String year = "";
String hours = "";
String minutes = "";
String seconds = "";
int count=0; 

void setup() {
    // Open serial communications and wait for port to open:
  Serial.begin(9600);
   myRTC.setDS1302Time(10, 53, 10, 07, 13, 01, 2020);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  myRTC.updateTime();
  
  //Reading Co2 values Assumed pin A0 is Co2 pin

  int Mq135ensor = analogRead(A0); 
  //Serial.print("DHT22, \t");
int chk = DHT.read22(DHT22_PIN);
 Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);             //You can switch between day and month if you're using American system
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
Serial.print("Humidity/(%):  ");
hum_reading = (DHT.humidity);
Serial.println(hum_reading);

//Serial.print(",\t");
Serial.print("Temperature/(°C):  ");
temp_reading = (DHT.temperature);
Serial.println(temp_reading);
//Serial.print("  Current Date / Time: ");
  //Serial.print(myRTC.dayofmonth);
Serial.print("Co2/(ppm): ");
Serial.println(Mq135ensor);
//Serial.print("  Current Date / Time: ");
  //Serial.print(myRTC.dayofmonth);
delay(2000);

if(temp_reading>0){
  
temp += String(temp_reading);
hum += String(hum_reading);
co2 += String(Mq135ensor);
day_of_month +=String(myRTC.dayofmonth);
month +=String(myRTC.month);
year +=String(myRTC.year);
hours +=String(myRTC.hours);
minutes +=String(myRTC.minutes);
seconds +=String(myRTC.seconds);
  // if the file is available, write to it:
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    
    count ++;
      
    dataFile.print("Data Reading number: ");
    
    dataFile.println(count);
    dataFile.print("Current Date / Time: ");
    dataFile.print(day_of_month);
    dataFile.print(month);
    dataFile.print(year);
    dataFile.print(hours);
    dataFile.print(minutes);
    dataFile.println(seconds);
    dataFile.print("Temperature/(°C):  ");
    dataFile.println(temp);
    //dataFile.print(" ");
    dataFile.print("Humidity/(%):  ");
    dataFile.println(hum);
    
    dataFile.print("Co2/(ppm): ");
    dataFile.println(co2);
    
    dataFile.close();
    
    temp = " ";
    hum = " ";
    co2 = " ";
    day_of_month= " ";
    month= " ";
    year= " ";
    hours= " ";
    minutes= " ";
    seconds= " ";
    Serial.println("sucess");
    
    
    // print to the serial port too:
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

}
