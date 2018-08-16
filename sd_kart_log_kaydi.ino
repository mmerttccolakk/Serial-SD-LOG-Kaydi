//kutuphaneler
#include <SD.h>
#include <SPI.h>
#include <EEPROM.h>

//minumum 25 ms doğru veri kaydediliyor
//15 dede doğru ancak 2 kez tekrarlanıyor


//sd kart ayarları
File dosyam;
int pinCS = 53;

//serial ayarlar
boolean ok=false;
String real_data;

//log kaydi icin degiskenler
unsigned long log_kaydi_say;
String dosya_ismi;

//led kayit icin
boolean led_durum=LOW;

void setup() {
  //serial  
  Serial.begin(115200);
  
  //led kayıt
  pinMode(LED_BUILTIN, OUTPUT);
  
  //sd kart icin
  pinMode(pinCS, OUTPUT);
  
  //sd kart kontrol ediliyor
  if (SD.begin()){
    Serial.println("SD kart yazilmaya hazir.!");
  } else{
    Serial.println("SD kartta sorun var.!");
    return;
  }
  //epromm kaydından son sayısal deger okunuyor
  EEPROM.get(0,log_kaydi_say); //dikkat 4 byte kapliyor
  log_kaydi_say++; //log degiskeni bir sonraki log kaydı icin ayarlanıyor
  EEPROM.put(0,log_kaydi_say);//yeni log kaydının say degeri

  
  //dosya ismi ayarlanıyor
  dosya_ismi=String(log_kaydi_say);
  dosya_ismi = "log"+dosya_ismi+".txt";
  Serial.println(dosya_ismi);
}
void loop() {
  unsigned long zaman = millis();
  zaman=zaman/1000;
  if (ok) {
  dosyam = SD.open(dosya_ismi, FILE_WRITE);
  if (dosyam) {  
    dosyam.print(zaman);
    dosyam.print(","); 
    dosyam.println(real_data);
    dosyam.close();
    led_durum=!led_durum;
    digitalWrite(LED_BUILTIN, led_durum);
      }
     real_data = ""; ok = false;}
  }
void serialEvent(){
  while (Serial.available()){
    char temp = (char)Serial.read();
    real_data += temp;
    if (temp == '\n'){ok = true;}}}
