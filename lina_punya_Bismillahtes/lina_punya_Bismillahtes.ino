//#include <ESP8266WiFi.h>
#include <EEPROM.h>
//#include <DS3231.h>
//RTClib myRTC;
#include <Preferences.h> //https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences
Preferences preferences;
#include <ESP32Time.h>
ESP32Time rtc(0);  // offset in seconds GMT+8
#define SENSOR  4

//lora
#define RXD2 16
#define TXD2 17

void prosesData(void);
void SendDataSensor1(void);
void komunikasiSerial(void);
void SendDataSensor2(void);
void SendDataSensor3(void);
void SendMeteranON(void);
void SendMeteranOFF(void);
void water_flow(void);
char serialbuffer[100] = {0};
char receiver;

//aes argumetns
char * key = "abcdefghijklmnop";
unsigned char cipherTextOutput[16];
unsigned char decipheredTextOutput[16];

unsigned long DataJamEpprom[24];
unsigned long DataHariEpprom[32];
unsigned long DataBulanEpprom[13];

unsigned long alJam, alHari, alBulan;
int jam, hari, bulan, menit, detik;
int stat;
unsigned long dataJam,
         dataHari,
         dataBulan;
const int Selenoid = 14;

//flow
long currentMillis = 0;
long previousMillis = 0;
int interval = 100;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned long flowMilliLitres;
unsigned int totalMilliLitres;
float flowLitres;
unsigned long totalLitres;

int addressTotal = 0;
byte lastWater;

int i = 1;
int j = 2;

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}
int da;
void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  EEPROM.begin(512);

  //  Wire.begin();
  rtc.setTime(00, 00, 01, 01, 02, 2022);

  pinMode(SENSOR, INPUT_PULLUP);

  flowRate = 0.0;
  pulseCount = 0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);
  lastWater = EEPROM.get(addressTotal, totalLitres);
  Serial.println(lastWater);
}

void loop()
{
  preferences.begin("PDAM", false);
  water_flow();
  komunikasiSerial();
  //rtc internal
  detik = rtc.getSecond();
//  Serial.println("Detik : " + String(detik));
  menit = rtc.getMinute();
//  Serial.println("Menit : " + String(menit));
  jam = rtc.getHour();
  Serial.println("Jam : " + String(jam));
  hari = rtc.getDay();
  Serial.println("Hari : " + String(hari));
  bulan = rtc.getMonth();
  Serial.println("Bulan : " + String(bulan));
  struct tm timeinfo = rtc.getTimeStruct();

  //menginput total liter ke variabel
  dataJam = dataJam + totalLitres;
  dataHari = dataHari + totalLitres;
  dataBulan = dataBulan + totalLitres;


  //Menyimpan ke eeprom & mengambil data eeprom kedalam variabel jenis array
  if (jam <= 23) {
    preferences.putULong("jam" + char(jam), dataJam);
    DataJamEpprom[menit] = preferences.getULong("jam" + char(jam), dataJam);
  };

  if (hari <= 31) {
    preferences.putULong("hari" + char(hari), dataHari);
    DataHariEpprom[hari] = preferences.getULong("hari" + char(hari), dataHari);
  };

  if (bulan <= 12) {
    preferences.putULong("bulan" + char(bulan), dataBulan);
    DataBulanEpprom[bulan] = preferences.getULong("bulan" + char(bulan), dataBulan);
  };
  
  preferences.end();

  rnd();
  delay(1000);


}
