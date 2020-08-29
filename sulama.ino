
/////////////////////////////////////////
/////Bilim Engel Tanımaz/////
/////////////////////////////////////////
///////                          ////////
///////  - １9．１０．２０１８ -    ///////
///////  ｒｏｙｊｃｅ － ｖ０．1    ////////
///////                          ////////
/////////////////////////////////////////
/////////////////////////////////////////


/////////////////////////////////////////////////////////////
#include <dht11.h>                                         //
#include <Wire.h>                                          //
#include <LiquidCrystal_I2C.h>                             //
dht11 SENSOR_DHT11;                                        //
LiquidCrystal_I2C LCD(0x27, 16, 2);                        //
/////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//                                                          //
//                      Ayarlar                        //
//                                                          //
//////////////////////////////////////////////////////////////
#define RGB_LED_1_KIRMIZI_PIN  3              //  TOPRAK    //
#define RGB_LED_1_YESIL_PIN    5              //  SENSÖRÜ   // 
//                                            //    LED     //
//////////////////////////////////////////////////////////////
#define RGB_LED_2_KIRMIZI_PIN  6              //  SICAKLIK  //
#define RGB_LED_2_YESIL_PIN    9              //    LED     //
//////////////////////////////////////////////////////////////
#define RGB_LED_3_KIRMIZI_PIN  10             //    NEM     //
#define RGB_LED_3_YESIL_PIN    11             //    LED     //
//////////////////////////////////////////////////////////////
#define MAX_NEM_AYAR           70             //            //
#define MIN_NEM_AYAR           40             //            //                                  
#define MAX_DERECE_AYAR        32             //            //  
#define MIN_DERECE_AYAR        15             //            //
#define MAX_SU_AYAR            100            //            //
#define MIN_SU_AYAR            30             //            //
#define MAX_ISIK_AYAR          0              //            //
#define MIN_ISIK_AYAR          0              //            //
#define MAX_TOPRAK_NEM_AYAR    70             //            //
#define MIN_TOPRAK_NEM_AYAR    40             //            //
#define MAX_MESAFE_AYAR        0              //            //
#define MIN_MESAFE_AYAR        0              //            //
#define SENSOR_KONTROL_SURE    2000           //  AYARLAR   //
#define LCD_GECIS_SURE         7000           //            //
#define YENILEME_HIZI          500            //            //
#define LCD_MAX_SAYFA_SAYISI   3              //            //
////////////////////////////////////////////////            //
#define DHT11_PIN              2              //            //
#define UZAKLIK_ECHO_PIN       4              //            // 
#define UZAKLIK_TRIG_PIN       7              //            //
#define SU_SENSOR_PIN          A0             //            //
#define ISIK_SENSOR_PIN        A1             //            //
#define TOPRAK_SENSOR_PIN      A2             //            //
#define ROLE1_CIKIS_PIN        8              //            //
#define ROLE2_CIKIS_PIN        12              //           //
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//                                                          //
//                  Değişkenler                     //
//                                                          //
//////////////////////////////////////////////////////////////
int    RGB_LED_1_KIRMIZI_PARLAKLIK,
       RGB_LED_2_KIRMIZI_PARLAKLIK,
       RGB_LED_3_KIRMIZI_PARLAKLIK,
       RGB_LED_1_YESIL_PARLAKLIK,
       RGB_LED_2_YESIL_PARLAKLIK,
       RGB_LED_3_YESIL_PARLAKLIK,
       SENSOR_ISIK_DEGER,
       SENSOR_DERECE_DEGER,
       SENSOR_NEM_DEGER,
       SENSOR_SU_DEGER,
       SENSOR_MESAFE_DEGER,
       SENSOR_TOPRAK_DEGER,
       LCD_SAYFA,
       SENSOR_HATA_SAYISI;
long   SENSOR_UZAKLIK_SURE;
long   LCD_ONCEKI_SURE;
bool   SENSOR_ISIK_KONTROL,
       SENSOR_SU_KONTROL,
       SENSOR_MESAFE_KONTROL,
       SENSOR_DERECE_KONTROL,
       SENSOR_TOPRAK_KONTROL;
String KONTROL_STRING = "";
//////////////////////////////////////////////////////////////


void setup() {
  pinMode(RGB_LED_1_KIRMIZI_PIN, OUTPUT);
  pinMode(RGB_LED_2_KIRMIZI_PIN, OUTPUT);
  pinMode(RGB_LED_3_KIRMIZI_PIN, OUTPUT);
  pinMode(RGB_LED_1_YESIL_PIN,   OUTPUT);
  pinMode(RGB_LED_2_YESIL_PIN,   OUTPUT);
  pinMode(RGB_LED_3_YESIL_PIN,   OUTPUT);
  pinMode(UZAKLIK_TRIG_PIN,      OUTPUT);
  pinMode(UZAKLIK_ECHO_PIN,      INPUT);
  pinMode(ROLE1_CIKIS_PIN,       OUTPUT);
  pinMode(ROLE2_CIKIS_PIN,       OUTPUT);
  SENSOR_DHT11.attach(DHT11_PIN);
  LCD.begin();
  LCD.clear();
  LCD.setCursor(3, 0);
  LCD.print("BILIM ENGEL");
  LCD.setCursor(4, 1);
  LCD.print("TANIMAZ!");
  FUNC_ROLE_1(false);
  FUNC_ROLE_2(false);
  delay(1000);
  Serial.begin(9600);
  FUNC_SENSOR_TEST();
}

void loop() {

  FUNC_SENSOR_OKU();
  FUNC_DEBUG(0);

  unsigned long LCD_MEVCUT_SURE = millis();

  if (LCD_MEVCUT_SURE - LCD_ONCEKI_SURE > LCD_GECIS_SURE) {
    LCD_ONCEKI_SURE = LCD_MEVCUT_SURE;
    LCD_SAYFA++;
    if (LCD_SAYFA > LCD_MAX_SAYFA_SAYISI) {
      LCD_SAYFA = 1;
    }
  }

  if (SENSOR_TOPRAK_DEGER <= MIN_TOPRAK_NEM_AYAR || SENSOR_TOPRAK_DEGER >= MAX_TOPRAK_NEM_AYAR) {
    FUNC_RGB_1(255, 0);
  } else {
    FUNC_RGB_1(0, 255);
  }

  if (SENSOR_DERECE_DEGER <= MIN_DERECE_AYAR || SENSOR_DERECE_DEGER >= MAX_DERECE_AYAR) {
    FUNC_RGB_2(255, 0);
  } else {
    FUNC_RGB_2(0, 255);
  }

  if (SENSOR_NEM_DEGER <= MIN_NEM_AYAR || SENSOR_NEM_DEGER >= MAX_NEM_AYAR) {
    FUNC_RGB_3(255, 0);
  } else {
    FUNC_RGB_3(0, 255);
  }

  if (LCD_SAYFA == 1) {
    FUNC_LCD_SAYFA(1);
  } else if (LCD_SAYFA == 2) {
    FUNC_LCD_SAYFA(2);
  } else if (LCD_SAYFA == 3) {
    FUNC_LCD_SAYFA(3);
  }
  
  delay(YENILEME_HIZI);
}




