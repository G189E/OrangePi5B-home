#include <wiringPi.h>

int main(int argc,char **argv)
{
    wiringPiSetup();//wiringpi库初始化
    pinMode(15,PWM_OUTPUT);//15号引脚 PWMOUT模式
    pwmSetRange();
}