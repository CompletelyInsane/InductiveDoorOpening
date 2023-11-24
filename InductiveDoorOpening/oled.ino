


void oled_display()
{
  
  if(State == 0x01 )
  { 
    Display.clear();
    Display.drawString(0, 0, "Open");  //X,Y,内容
  }
  else if(State == 0x02 && TIM_close == 0)
  {
    Display.clear();
    Display.drawString(0, 0, "Close");  //X,Y,内容
  }

  Display.display();  //将缓冲区写入内存


 
}