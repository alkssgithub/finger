void finger_Init(){
  Serial2.begin(57600);
  pinMode(V_Touch_EN, OUTPUT);
  Finger_ON(); 
  delay(300);
  Send_Data(Green_Blink,sizeof(Green_Blink));
  Receive_Data(12);
  delay(500);
}

void Finger_ON(){
  digitalWrite(V_Touch_EN,0);
}
void Finger_OFF(){
  digitalWrite(V_Touch_EN,1);
}


void Send_Data(uint8_t *data,uint8_t num){
  Serial2.flush();
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
  uint8_t i = 0;
  for(i=0;i<32;i++)
     Serial2.read();
}

void clear_Receive_Buffer(){
  for(uint8_t i = 0;i<32;i++){
    Receive_Buffer[i] = 0xFF;
  }
}


void search(func fun1){
  Send_Data(PS_AutoIdentify,sizeof(PS_AutoIdentify));
  Receive_Data(17);
  showData(Receive_Buffer,17);

  if(Receive_Buffer[9] == 0x00)                   //搜索到
  {
    Send_Data(Green_Blink,sizeof(Green_Blink));
    Receive_Data(12);
    fun1();
  }
  else if(Receive_Buffer[9] == 0x09)                   //未搜索到
  {
    Send_Data(Red_Blink,sizeof(Red_Blink));
    Receive_Data(12);
    delay(1000);
  }
}

uint8_t Read_FingerNum(){
  Send_Data(Read_TempleteNUM,6);
  Receive_Data(14);
  if(Receive_Buffer[9] == 0x00){
    return Receive_Buffer[11];
  }
  return 0xff;
}

void addfinger(void){
  uint8_t num = Read_FingerNum();
  if(num == 0xff){
    return;
  }
  PS_AutoEnroll[5] = num+1;
  uint8_t i;
  uint16_t sum=0;
  for(i=0;i<9;i++){
    sum += PS_AutoEnroll[i];
  }
  PS_AutoEnroll[9] = sum/256;
  PS_AutoEnroll[10] = sum%256;
  Send_Data(PS_AutoEnroll,sizeof(PS_AutoEnroll));
  Receive_Data(14);
  showData(Receive_Buffer,14);
  // if(Receive_Buffer[9] == 0x00)                   //搜索到
  // {
  //   Send_Data(Green_Blink,sizeof(Green_Blink));
  //   Receive_Data(12);
  //   delay(1000);
  // }
  // else{
  //   Send_Data(Red_Blink,sizeof(Red_Blink));
  //   Receive_Data(12);
  //   delay(1000);
  // }
}
void showData(uint8_t *data,uint8_t num)
{
  uint8_t i;
  uint8_t temp;
  for(i=0;i<num;i++)
  {
    Serial.print("0x");
    temp = (data[i]/16);
    if(temp<10)
      temp += '0';
    else
      temp = temp - 10 + 'a';
    Serial.write(temp);

    temp = (data[i]%16);
    if(temp<10){
      temp += '0';
    }
    else{
      temp = temp - 10 + 'a';
    }
    Serial.write(temp);
    Serial.print("  ");
  }
  Serial.println();
}
