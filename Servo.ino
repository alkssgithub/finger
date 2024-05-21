void Servo_Init(){
  //pinMode(V_Servo_EN, OUTPUT_OPEN_DRAIN);
  //Servo_ON();

  analogWriteFrequency(50);
//  analogWrite(ServoPin,18);
  analogWriteResolution(10);
  analogWrite(ServoPin,75);
}

void Servo_ON(){
  digitalWrite(V_Servo_EN,0);
}
void Servo_OFF(){
  digitalWrite(V_Servo_EN,1);
}

void Open_Door(){
  Servo_ON();

  analogWrite(ServoPin,100);
  delay(2000);
  analogWrite(ServoPin,75);

  delay(3000);

  analogWrite(ServoPin,50);
  delay(1500);
  analogWrite(ServoPin,75);
  
  Servo_OFF();
}

