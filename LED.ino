void LED_Init(){
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LowpowerLED, OUTPUT_OPEN_DRAIN);
  LED_OFF(LED0);
  LED_OFF(LED1);
  LED_OFF(LED2);
  LED_OFF(LowpowerLED);
}
