#include "wiringPi.h"
#include "wiringSerial.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char **argv)
{
    char revbuf[1024] = {0};
    wiringPiSetup();//wiringPi库初始化
    int serialFD = serialOpen("/dev/ttyS3",1500000);
    if(-1 == serialFD){
        perror("serial open error");
        exit(EXIT_FAILURE);
    }
    serialPrintf(serialFD,"来自香橙派的第一条消息\n");
    while(1){
        if(0 <  serialDataAvail(serialFD)){
            read(serialFD,revbuf,1024);
            serialPrintf(serialFD,"%s\n",revbuf);
            printf("%s\n",revbuf);
            memset(revbuf,0,1024);
        }
    }
    return 0;
}