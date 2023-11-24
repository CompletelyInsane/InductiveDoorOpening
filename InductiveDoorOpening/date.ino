/*
   存放雷达数据接收和解析函数   
*/

/* void getLidarData( TF* Lidar) 
   串口获取一帧数据，并计算距离，信号强度和记录成功计算的标志。
*/
void getLidarData( TF* Lidar)  
{ 
  //59 59 03 00 E9 09 68 09 18  一帧数据
  static char i = 0;
  char j = 0;
  int checksum = 0;
  Lidar->receiveComplete = false; 
  static int rx[9] ;//= {0x59 ,0x59 ,0x2F ,0x00 ,0xC9 ,0x0B ,0x70 ,0x09 ,0x2E};
  while (Serial2.available() > 0) {
     rx[i] = Serial2.read();
    if (rx[0] != 0x59) {
      i = 0;
    } else if (i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if (i == 8) {
      for (j = 0; j < 8; j++) {
        checksum += rx[j];      //计算校验和
      }
      if (rx[8] == (checksum % 256)) {
        Lidar->distance = rx[2] + rx[3] * 256;  //距离
        Lidar->strength = rx[4] + rx[5] * 256;  //信号强度
        Lidar->receiveComplete = true;          //接收完成
      }
      i = 0;
    } else 
      i++;
    }
} 




void Action_detection()
{
    
    getLidarData(&Lidar);   //读雷达1数据

   if( abs(Lidar.distance - Lidarinit) > 8 )  //如果和设定的测量范围的差值超过五厘米 
      {
        ReferenceNum --;
       // digitalWrite(LED_PIN, HIGH);
      }
  else 
  {
      ReferenceNum = ReferenceNumVal;    
     // digitalWrite(LED_PIN, LOW);
  } 

   if(ReferenceNum < 1)  //差值超过5厘米，每次减一，100次检查差值都超过5厘米，就更新设定的范围
    {
      Lidarinit =  Lidar.distance;
      ReferenceNum = ReferenceNumVal;
    }

 
//
  if(Lidar.distance < (Lidarinit*Low) )  //被遮挡
  { 
    State = 0x01;  

    ActionFlag = 1 ;
  } 
  else
  {
    State = 0x02;
    TIM_close = closetime ;
    ActionFlag = 1 ;
  }
    Serial.print(ReferenceNum);
   Serial.print("  ");
   Serial.print(State);
    Serial.print("  ");
   Serial.print(State);
   Serial.println();
 

}



bool  Errorback()
{
    if(TIM_refer%2 == 0) //检查传感器错误频率
   {
        if(Lidar.receiveComplete == false)          //接收失败
        { 
          Errornum++;
          if(Errornum>3) //两秒未检测到雷达
          {            
              Display.clear();
              Display.drawString(0, 20, "Lidar1 Error");  //X,Y,内容
              Display.display();  //将缓冲区写入内存
              ErrorFlag = 1;
          }
        }
       TIM_refer++;    
  } 
    
      if(Lidar.receiveComplete == true) 
        {
          Errornum = 0;
        }
      
      if(Errornum == 0 )
        {
         if(ErrorFlag == 1)
            oled_display();   
         ErrorFlag = 0;   
        }
     return ErrorFlag ;
}


