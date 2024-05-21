float ReadADC_BAT(){
  float ADC_Num[20];
  for(int i=0;i<20;i++){
    ADC_Num[i] = analogReadMillivolts(ADC_Bat)*11 / 1000;
  }
  std::sort(ADC_Num, ADC_Num + 20);
  float ADC_Ret = 0.0;
  for(int i=5;i<15;i++){
    ADC_Ret += ADC_Num[i];
  }
  ADC_Ret /= 10;
  return ADC_Ret;
}