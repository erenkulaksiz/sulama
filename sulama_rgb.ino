//////////////////////////////////////////////////////////////

void FUNC_RGB_1( int KIRMIZI_VALUE, int YESIL_VALUE) {
  if (KIRMIZI_VALUE >= 256 || KIRMIZI_VALUE <= -1) {
    Serial.println("RGB_1 KIRMIZI_VALUE HATA!");
    KIRMIZI_VALUE = 0;
  } else if (YESIL_VALUE >= 256 || YESIL_VALUE <= -1) {
    Serial.println("RGB_1 YESIL_VALUE HATA!");
    YESIL_VALUE = 0;
  }

  KIRMIZI_VALUE = KIRMIZI_VALUE - 255;
  KIRMIZI_VALUE = abs(KIRMIZI_VALUE);

  YESIL_VALUE = YESIL_VALUE - 255;
  YESIL_VALUE = abs(YESIL_VALUE);

  //Serial.println(YESIL_VALUE);

  analogWrite(RGB_LED_1_KIRMIZI_PIN, KIRMIZI_VALUE);
  analogWrite(RGB_LED_1_YESIL_PIN, YESIL_VALUE);
}

//////////////////////////////////////////////////////////////

void FUNC_RGB_2( int KIRMIZI_VALUE, int YESIL_VALUE) {
  if (KIRMIZI_VALUE >= 256 || KIRMIZI_VALUE <= -1) {
    Serial.println("RGB_2 KIRMIZI_VALUE HATA!");
    KIRMIZI_VALUE = 0;
  } else if (YESIL_VALUE >= 256 || YESIL_VALUE <= -1) {
    Serial.println("RGB_2 YESIL_VALUE HATA!");
    YESIL_VALUE = 0;
  }

  KIRMIZI_VALUE = KIRMIZI_VALUE - 255;
  KIRMIZI_VALUE = abs(KIRMIZI_VALUE);

  YESIL_VALUE = YESIL_VALUE - 255;
  YESIL_VALUE = abs(YESIL_VALUE);

  //Serial.println(YESIL_VALUE);

  analogWrite(RGB_LED_2_KIRMIZI_PIN, KIRMIZI_VALUE);
  analogWrite(RGB_LED_2_YESIL_PIN, YESIL_VALUE);
}

//////////////////////////////////////////////////////////////

void FUNC_RGB_3( int KIRMIZI_VALUE, int YESIL_VALUE) {
  if (KIRMIZI_VALUE >= 256 || KIRMIZI_VALUE <= -1) {
    Serial.println("RGB_3 KIRMIZI_VALUE HATA!");
    KIRMIZI_VALUE = 0;
  } else if (YESIL_VALUE >= 256 || YESIL_VALUE <= -1) {
    Serial.println("RGB_3 YESIL_VALUE HATA!");
    YESIL_VALUE = 0;
  }

  KIRMIZI_VALUE = KIRMIZI_VALUE - 255;
  KIRMIZI_VALUE = abs(KIRMIZI_VALUE);
  KIRMIZI_VALUE += 30; // Kalibrasyon.
  if (KIRMIZI_VALUE > 254) {
    KIRMIZI_VALUE = 255;
  }

  YESIL_VALUE = YESIL_VALUE - 255;
  YESIL_VALUE = abs(YESIL_VALUE);

  //Serial.println(YESIL_VALUE);

  analogWrite(RGB_LED_3_KIRMIZI_PIN, KIRMIZI_VALUE);
  analogWrite(RGB_LED_3_YESIL_PIN, YESIL_VALUE);
}

//////////////////////////////////////////////////////////////

