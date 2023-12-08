


void oled_display()
{
  
  if( TIM_close != 0)
  { 
    Display.clear();
    Display.drawString(0, 0, "Open");  //X,Y,内容
    analogWrite(LED_PIN, 25);
  }
  else if(State == 0x02 )
  {
    Display.clear();
    Display.drawString(0, 0, "Close");  //X,Y,内容
    analogWrite(LED_PIN, 0);
  }

  Display.display();  //将缓冲区写入内存


 
}