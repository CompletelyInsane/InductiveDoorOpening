#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include "HardwareSerial.h"   
#include "com.h"
#include "date.h"
#include <Wire.h>               
#include "HT_SSD1306Wire.h"
#include "oled.h"

char str[20]; // 为字符串分配足够的空间 oled 
hw_timer_t* Timer= NULL;              //定义存放定时器的指针 
SSD1306Wire  Display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst  oled初始化参数
//定时器中断
void IRAM_ATTR onTimer();


void setup() {

 Serial.begin(115200);
 Serial2.begin(115200, SERIAL_8N1, 45, 46);             //开启串口2 用作雷达数据读取
   /*TIM_init*/
  Timer = timerBegin(0, 80, true);             //设置定时器0，80分频，定时器是否上下计数
  timerAttachInterrupt(Timer, onTimer, true);  //定时器地址指针，中断函数，触发类型
  timerAlarmWrite(Timer, 1000000, true);       //us，自动重装载 
  timerAlarmEnable(Timer);                     //打开定时器
  
  /*OLED_init*/
  Display.init(); //oled 初始化
  Display.setFont(ArialMT_Plain_16);//设置字体

   pinMode(LED_PIN, OUTPUT);                              //LED指示灯
   //等待正确地接收雷达的数据，读取一个值，作为距离参考
    while(Lidar.receiveComplete == false )    //
    {
       getLidarData(&Lidar) ; 
       Lidarinit =  Lidar.distance;
       Display.drawString(0, 20, "Lidar1 Error");  //屏幕显示雷达状态 
       Display.display();  //将缓冲区写入内存
    }
}

void loop() {
  Action_detection(); //动作检测

  if(!Errorback())         //循环检测错误，无错误时才可进行下一步
    if( ActionFlag == 1)   //数据刷新标志位，只有数据刷新时才刷新屏幕显示
    {
      oled_display();      //oled显示
      ActionFlag = 0;      //清除标志位
    }

}


//定时器中断函数
void IRAM_ATTR onTimer()
{
  TIM_refer++;   //报错检测间隔参数
  if(TIM_refer>65536)//限制范围
   {
    TIM_refer = 0;
   }

  TIM_close --;  //开门延迟，门开后，计时一段时间后才关闭
   if(TIM_close < 0)//限制范围
   {
    TIM_close = 0;
   }
}


