#include <algorithm>

typedef void (*func)(void);

#define TXD PA_4
#define RXD PB_2
#define ServoPin PA_0
#define LED0 PA_13
#define LED1 PA_14
#define LED2 PB_3
#define LowpowerLED PA_7
#define ADC_Bat PA_1
#define V_Touch_EN PB_1
#define V_Servo_EN PF_1
#define Touch_EVENT PB_0

#define LED_ON(x) digitalWrite(x,0)
#define LED_OFF(x) digitalWrite(x,1)

uint8_t Receive_Buffer[32];
uint8_t Pack_Head[] = {0xef,0x01};
uint8_t Pack_ADD[] = {0xff,0xff,0xff,0xff};
uint8_t PS_AutoIdentify[] = {0x01,0x00,0x08,0x32,0x01,0xff,0xff,0x00,0x04,0x02,0x3e}; //自动验证
uint8_t PS_AutoEnroll[] = {0x01,0x00,0x08,0x31,0x00,0x00,0x04,0x00,0x65,0x00,0x00}; //自动注册
uint8_t Green_Blink[] = {0x01 ,0x00 ,0x07 ,0x3c ,0x02 ,0x00 ,0x02 ,0x04 ,0x00 ,0x4C};
uint8_t Read_TempleteNUM[] = {0x01 ,0x00 ,0x03 ,0x1d ,0x00 ,0x21};
uint8_t Sleep[] = {0x01 ,0x00 ,0x03 ,0x33 ,0x00 ,0x37};
uint8_t Red_Blink[] = {0x01 ,0x00 ,0x07 ,0x3c ,0x02 ,0x00 ,0x04 ,0x04 ,0x00 ,0x4E};
uint8_t Breathing_light[] = {0x01 ,0x00 ,0x07 ,0x3c ,0x01 ,0x02 ,0x01 ,0x00 ,0x00 ,0x48};

HardwareSerial Serial2(RXD, TXD);


void open(){
  LED_ON(LED0);
  LED_ON(LED1);
  LED_ON(LED2);
  LED_ON(LowpowerLED);
  Open_Door();
  LED_OFF(LED0);
  LED_OFF(LED1);
  LED_OFF(LED2);
  LED_OFF(LowpowerLED);
}


void setup() {
  Serial1.begin(115200);
  Serial1.write("Serial1 Begin\n");
  Servo_Init();
  LED_Init();
  finger_Init();
   
}

void loop() {
  delay(300);
  search(open);
}
