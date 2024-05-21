void finger_Init(){
  Serial2.begin(57600);
  pinMode(V_Touch_EN, OUTPUT);
  Finger_ON(); 
  delay(300);
  Send_Data(Green_Blink,sizeof(Green_Blink));
  Receive_Data(12);

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

