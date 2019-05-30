/////////////////////////////////////////////////////////////
//                                                         //
//                 ＦＯＮＫＳＩＹＯＮＬＡＲ                   //
//                                                         //
/////////////////////////////////////////////////////////////

void FUNC_SENSOR_OKU() {
  int chk = SENSOR_DHT11.read();
  SENSOR_DERECE_DEGER    =  (int)SENSOR_DHT11.temperature;
  SENSOR_NEM_DEGER       =  (int)SENSOR_DHT11.humidity;
  SENSOR_SU_DEGER        =  map(analogRead(SU_SENSOR_PIN), 0, 1023, 0, 100);
  SENSOR_TOPRAK_DEGER    =  map(analogRead(TOPRAK_SENSOR_PIN), 0, 1023, 100, 0);
  SENSOR_ISIK_DEGER      =  map(analogRead(ISIK_SENSOR_PIN), 0, 1023, 0, 100);
  SENSOR_ISIK_DEGER     -=  100;
  SENSOR_ISIK_DEGER      =  abs(SENSOR_ISIK_DEGER);
  digitalWrite(UZAKLIK_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(UZAKLIK_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(UZAKLIK_TRIG_PIN, LOW);
  SENSOR_UZAKLIK_SURE = pulseIn(UZAKLIK_ECHO_PIN, HIGH);
  SENSOR_MESAFE_DEGER = SENSOR_UZAKLIK_SURE * 0.034 / 2;
  if (SENSOR_MESAFE_DEGER <= -1) {
    SENSOR_MESAFE_DEGER = 1;
  } else if (SENSOR_MESAFE_DEGER >= 200) {
    SENSOR_MESAFE_DEGER = 1;
  }
}

//////////////////////////////////////////////////////////////

void FUNC_DEBUG( int DEBUG_TYPE) {
  switch (DEBUG_TYPE) {
    case 0: // Debug normal
      Serial.println("____________________");
      Serial.print("Derece: C ");
      Serial.println(SENSOR_DERECE_DEGER);
      Serial.print("Nem: % ");
      Serial.println(SENSOR_NEM_DEGER);
      Serial.print("Su Deger: % ");
      Serial.println(SENSOR_SU_DEGER);
      Serial.print("Toprak Deger: % ");
      Serial.println(SENSOR_TOPRAK_DEGER);
      Serial.print("Mesafe Deger: CM ");
      Serial.println(SENSOR_MESAFE_DEGER);
      Serial.print("Isik Deger: % ");
      Serial.println(SENSOR_ISIK_DEGER);
      break;

    case 1: // Debug SENSOR kontrol
      Serial.println("//    SENSOR KONTROL     //");
      Serial.print("Derece: C ");
      Serial.println(SENSOR_DERECE_DEGER);
      Serial.print("Nem: % ");
      Serial.println(SENSOR_NEM_DEGER);
      Serial.print("Su Deger: % ");
      Serial.println(SENSOR_SU_DEGER);
      Serial.print("Toprak Deger: % ");
      Serial.println(SENSOR_TOPRAK_DEGER);
      Serial.print("Mesafe Deger: CM ");
      Serial.println(SENSOR_MESAFE_DEGER);
      Serial.print("Isik Deger: % ");
      Serial.println(SENSOR_ISIK_DEGER);
      Serial.print("_____________________________");
      break;

    default:
      DEBUG_TYPE = 0;
      break;
  }
}

/////////////////////////////////////////////////////////////

void FUNC_SENSOR_TEST() {

  SENSOR_HATA_SAYISI = 0;

  SENSOR_ISIK_KONTROL     = true;
  SENSOR_SU_KONTROL       = true;
  SENSOR_MESAFE_KONTROL   = true;
  SENSOR_DERECE_KONTROL   = true;
  SENSOR_TOPRAK_KONTROL   = true;

  delay(1000); // Sensörler kendine gelsin.

  FUNC_SENSOR_OKU();
  FUNC_DEBUG(1);

  for (int i = 0; i <= 13; i++) {
    LCD.clear();
    LCD.setCursor(1, 0);
    LCD.print("SENSOR KONTROL");
    LCD.setCursor(1, 1);
    KONTROL_STRING += "-";
    LCD.print(KONTROL_STRING);
    FUNC_RGB_1(125, 125);
    FUNC_RGB_2(125, 125);
    FUNC_RGB_3(125, 125);
    delay(50);
  }

  if (SENSOR_ISIK_DEGER >= 94) {
    SENSOR_ISIK_KONTROL = false;
  } else if (SENSOR_DERECE_DEGER <= 0 || SENSOR_NEM_DEGER <= 0) {
    SENSOR_DERECE_KONTROL = false;
  } else if (SENSOR_MESAFE_DEGER <= 0) {
    SENSOR_MESAFE_KONTROL = false;
  } else if (SENSOR_TOPRAK_DEGER <= 5) {
    SENSOR_TOPRAK_KONTROL = false;
  } else if (SENSOR_SU_DEGER <= 10) {
    SENSOR_SU_KONTROL = false;
  }

  // Serial.println(SENSOR);

  if (SENSOR_ISIK_KONTROL == false) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("ISIK SENSORU");
    LCD.setCursor(0, 1);
    LCD.print("HATASI");
  } else if (SENSOR_DERECE_KONTROL == false) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("DHT11 SENSORU");
    LCD.setCursor(0, 1);
    LCD.print("HATASI");
  } else if (SENSOR_MESAFE_KONTROL == false) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("MESAFE SENSORU");
    LCD.setCursor(0, 1);
    LCD.print("HATASI");
  } else if (SENSOR_TOPRAK_KONTROL == false) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("TOPRAK SENSORU");
    LCD.setCursor(0, 1);
    LCD.print("HATASI");
  } else if (SENSOR_SU_KONTROL == false) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("SU SENSORU");
    LCD.setCursor(0, 1);
    LCD.print("HATASI");
  }

  if (SENSOR_TOPRAK_KONTROL == false) {
    FUNC_RGB_1(255, 0);
  } else if (SENSOR_DERECE_KONTROL == false) {
    FUNC_RGB_2(255, 0);
    FUNC_RGB_3(255, 0);
  } else if (SENSOR_SU_KONTROL == false) {
    FUNC_RGB_1(255, 0);
    FUNC_RGB_2(255, 0);
    FUNC_RGB_3(255, 0);
  } else if (SENSOR_MESAFE_KONTROL == false) {
    FUNC_RGB_1(255, 0);
    FUNC_RGB_2(255, 0);
    FUNC_RGB_3(255, 0);
  } else if (SENSOR_ISIK_KONTROL == false) {
    FUNC_RGB_1(255, 0);
    FUNC_RGB_2(255, 0);
    FUNC_RGB_3(255, 0);
  } else {
    FUNC_RGB_1(0, 255);
    FUNC_RGB_2(0, 255);
    FUNC_RGB_3(0, 255);
  }

  delay(SENSOR_KONTROL_SURE);

  LCD.clear();
  LCD.setCursor(1, 0);
  LCD.print("SENSOR KONTROL");
  LCD.setCursor(2, 1);
  LCD.print(SENSOR_HATA_SAYISI);
  delay(SENSOR_KONTROL_SURE);
  LCD.clear();
  FUNC_RGB_1(0, 0);
  FUNC_RGB_2(0, 0);
  FUNC_RGB_3(0, 0);
}

/////////////////////////////////////////////////////////////

void FUNC_ROLE_1( bool ROLE1_STATE) {
  switch (ROLE1_STATE) {
    case true:
      digitalWrite(ROLE1_CIKIS_PIN, LOW);
      break;

    case false:
      digitalWrite(ROLE1_CIKIS_PIN, HIGH);
      break;
  }
}

/////////////////////////////////////////////////////////////

void FUNC_ROLE_2( bool ROLE1_STATE) {
  switch (ROLE1_STATE) {
    case true:
      digitalWrite(ROLE2_CIKIS_PIN, LOW);
      break;

    case false:
      digitalWrite(ROLE2_CIKIS_PIN, HIGH);
      break;
  }
}

/////////////////////////////////////////////////////////////

void FUNC_LCD_SAYFA( int SAYFA_VALUE) {
  switch (SAYFA_VALUE) {
    case 1:
      LCD.clear();
      LCD.setCursor(1, 0);
      LCD.print("Sicaklik: ");
      LCD.print(SENSOR_DERECE_DEGER);
      LCD.print("C*");
      LCD.setCursor(4, 1);
      LCD.print("Nem: ");
      LCD.print(SENSOR_NEM_DEGER);
      LCD.print("%");
      break;

    case 2:
      LCD.clear();
      LCD.setCursor(1, 0);
      LCD.print("Mesafe: ");
      LCD.print(SENSOR_MESAFE_DEGER);
      LCD.print("CM");
      LCD.setCursor(4, 1);
      LCD.print("Isik: ");
      LCD.print(SENSOR_ISIK_DEGER);
      LCD.print("%");
      break;

    case 3:
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Toprak Nem: ");
      LCD.print(SENSOR_TOPRAK_DEGER);
      LCD.print("%");
      LCD.setCursor(0, 1);
      LCD.print("Su Miktari: ");
      LCD.print(SENSOR_SU_DEGER);
      LCD.print("%");
      break;
  }
}

