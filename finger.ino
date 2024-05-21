void finger_Init(){
  Serial2.begin(57600);
  pinMode(V_Touch_EN, OUTPUT);
  pinMode(Touch_EVENT, INPUT_PULLDOWN);
  Finger_ON(); 
  delay(300);
  Send_Data(Green_Blink,sizeof(Green_Blink));
  Receive_Data(12);

  //Sleep_Mode();
  //attachInterrupt(digitalPinToInterrupt(Touch_EVENT), onChange, RISING);
}

void onChange(){
  detachInterrupt(Touch_EVENT);
  Finger_ON();
  delay(300);
  search(open);
  //open();
  while(digitalRead(Touch_EVENT) == 1);
  Sleep_Mode();
  attachInterrupt(digitalPinToInterrupt(Touch_EVENT), onChange, RISING);
}

void Finger_ON(){
  digitalWrite(V_Touch_EN,0);
}
void Finger_OFF(){
  digitalWrite(V_Touch_EN,1);
}
void Send_Data(uint8_t *data,uint8_t num){
  Serial2.write(Pack_Head,sizeof(Pack_Head));
  Serial2.write(Pack_ADD,sizeof(Pack_ADD));
  Serial2.write(data,num);
}
void Receive_Data(uint8_t num){
  while(Serial2.available() < num);
  clear_Receive_Buffer();
  for(uint8_t i=0;i<num;i++)
    Receive_Buffer[i] = Serial2.read();
  Serial2.flush();
}

void clear_Receive_Buffer(){
  for(uint8_t i = 0;i<32;i++){
    Receive_Buffer[i] = 0xFF;
  }
}
void search(func fun1){
  Send_Data(PS_AutoIdentify,sizeof(PS_AutoIdentify));
  Receive_Data(17);
  if(Receive_Buffer[9] == 0x00)                   //搜索到
  {
  //  uint8_t surprise = Receive_Buffer[12];
    Send_Data(Green_Blink,sizeof(Green_Blink));
    Receive_Data(12);
    // if(surprise == 0x00){
    //   Send_Data(Breathing_light,sizeof(Breathing_light));
    //   Receive_Data(12);
    // }
    fun1();
  }
  else if(Receive_Buffer[9] == 0x09)                   //未搜索到
  {
    Send_Data(Red_Blink,sizeof(Red_Blink));
    Receive_Data(12);
    delay(1000);
  }
  // else if(Receive_Buffer[9] == 0x26)                   //超时
  // {
  //   Finger_OFF();
  //   attachInterrupt(digitalPinToInterrupt(Touch_EVENT), onChange, RISING);
  // }
}
uint8_t Read_FingerNum(){
  Send_Data(Read_TempleteNUM,6);
  Receive_Data(14);
  if(Receive_Buffer[9] == 0x00){
    return Receive_Buffer[11];
  }
  return 0xff;
}

void Sleep_Mode(){
  Send_Data(Sleep,sizeof(Sleep));
    Receive_Data(12);
  // if(Receive_Buffer[9] = 0x00)
  //   Finger_OFF();
  // else 
  //   Sleep_Mode();
  Finger_OFF();
}

// uint8_t Add_Finger(){
//   uint8_t FingerNum = Read_FingerNum();
//   if(FingerNum != 0xff)
//     PS_AutoEnroll[11] = FingerNum + 1;
//   else
//     return 0xff;
//   uint16_t sum = 0;
//   for(uint8_t i=0;i<9;i++)
//     sum += PS_AutoEnroll[i];
//   PS_AutoEnroll[9] = sum / 0x100;
//   PS_AutoEnroll[10] = sum % 0x100;
//   Send_Data(Green_Blink,sizeof(Green_Blink));
//   Receive_Data(12);
//   Send_Data(PS_AutoEnroll,sizeof(PS_AutoEnroll));
//   Receive_Data(14);
//   if(Receive_Buffer[9] == 0x00){
//     Send_Data(Green_Blink,sizeof(Green_Blink));
//     Receive_Data(12);
//   }

//   return FingerNum + 1;
// }