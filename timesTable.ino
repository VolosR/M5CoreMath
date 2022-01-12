#include <M5Core2.h>
#include "font.h"
#include "images.h"

int answer[4]={0,0,0,0};
int firstN=0;
int secondN=0;
int res=0;

int  correct=0;
int wrong=0;
int fase=0;
int pos=0;

int space=2;

int uT=1000;
int cT=0;
int t=0;
void setup(void)
{
    M5.begin();
    M5.Axp.SetLcdVoltage(3000);
    M5.Lcd.setFreeFont(&Dialog_plain_52);
    
    M5.Lcd.setSwapBytes(true); 
    M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);
}

void loop(void)
{
if(fase==0)
  {
    firstN=random(1,10);
    secondN=random(1,10);
    res=firstN*secondN;
    pos=random(3);
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextColor(LIGHTGREY ,TFT_BLACK);
    M5.Lcd.setFreeFont(&Dialog_plain_52);
    M5.Lcd.drawString(String(firstN)+" x "+String(secondN)+"=      ",60,80);
    M5.Lcd.setTextColor( ORANGE,TFT_BLACK);
    M5.Lcd.drawString("correct: "+String(correct)+"    ",4,2,4);
    M5.Lcd.drawString("wrong: "+String(wrong)+"    ",4,30,4);
    
    answer[pos]=res;
    for(int i=0;i<4;i++){
    if(answer[i]==0)
    answer[i]=random(1,82);
    M5.Lcd.fillRoundRect((space+(i*78)+(i*space)),160,78,78,5,0x0187);
    M5.Lcd.drawRoundRect((space+(i*78)+(i*space)),160,78,78,5,LIGHTGREY);
     M5.Lcd.setTextColor(TFT_ORANGE,0x0187);
    M5.Lcd.drawString(String(answer[i]),(8+space+(i*78)+(i*space)),180,6);

    M5.Lcd.setTextColor(TFT_ORANGE,BLACK);  
    M5.Lcd.drawString("time: "+String(t),200,2,4);
    }
    fase=1;
  }

if(fase==1)
{

  TouchPoint_t pos= M5.Touch.getPressPoint();
  int y=pos.y;
  int x=pos.x;

  for(int i=0;i<4;i++)
  if(x>(space+(i*78)+(i*space)) && x<(space+(i*78)+(i*space))+78 && y>158)
  if(answer[i]==res)
  {
    correct++;
    M5.Lcd.pushImage(240,80,48,48,corr);
    delay(400);
    for(int i=0;i<4;i++)
    answer[i]=0;
    fase=0;
    }
  else
  {
    wrong++;
    M5.Lcd.pushImage(240,80,48,48,wrrong);
    delay(400);
    for(int i=0;i<4;i++)
    answer[i]=0;
    fase=0;
    }  
}
if(millis()>cT+uT){
  t++;
 M5.Lcd.setTextColor(TFT_ORANGE,BLACK);  
M5.Lcd.drawString("time: "+String(t),200,2,4);
cT=millis();
}
}
