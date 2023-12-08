#ifndef __COM_H
#define __COM_H
/*
  |  存放全局变量，雷达数据、标志位等
*/


// 定义按钮所连接的数字引脚
const int LED_PIN = 35;
//ActionFlag：判断是否刷新OLED显示的标志，State：记录雷达是否被遮挡的标志
uint8_t  ActionFlag = 1, State  =  0x00;   
//TIM_refer:定时器传出的用于雷达数据错误时间计算的参数；   Lidarinit：预设检测范围  ReferenceNum；检测范围更新所使用的参数
int  TIM_refer = 0 ,  TIM_close = 3, Lidarinit = 0 ,  ReferenceNum = 10000;

uint8_t Errornum = 0 ; //连续错误数量
bool ErrorFlag = 0;  //雷达是否检测成功的标志

#define  ReferenceNumVal  10000 //连续检测多少次才更新检测范围
#define  high  0.95    //雷达值高于无遮挡状态的90% 算无遮挡
#define  Low   0.85    //雷达值低于无遮挡状态的70% 算有遮挡
#define  closetime   4  //开门保持多久


//雷达数据结构体
 struct TF{
  int distance = 0;        //距离
  int strength = 0;        //信号强度
  int ID   = 0;            //雷达 ID

  long int BaudRate = 0;

  boolean LidarFlag = false;
  boolean receiveComplete = false;
  boolean IO = 0;
} ;

struct TF Lidar;


#endif  