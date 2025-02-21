#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char **argv)
{
    struct termios tty;//串口控制参数结构体
    int serialFD = open("/dev/ttyS3",O_RDWR | O_NOCTTY | O_NDELAY);//打开串口UART0,波特率115200
    if(-1 == serialFD){
        printf("serialOpen error\n");
        exit(EXIT_FAILURE);
    }
    cfsetispeed(&tty,115200);//输入波特率115200
    cfsetospeed(&tty,115200);//输出波特率115200
    //配置数据位，校验位，停止位
    tty.c_cflag &= ~PARENB;//关闭奇偶检验
    tty.c_cflag &= ~CSTOPB;//1停止位
    tty.c_cflag &= ~CSIZE;//清除数据位掩码
    tty.c_cflag |= CS8;//8数据位
    
    //控制模式设置
    tty.c_cflag |= CREAD | CLOCAL;//启用接收，忽略控制线

    //输入模式设置
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);//关软件流控
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    //输出模式设置
    tty.c_oflag &= ~OPOST;//原始输出模式
    tty.c_oflag &= ~ONLCR;//禁止换行符转换

    //本地模式设置
    tty.c_lflag &= ~(ECHO | ECHOE | ECHONL | ICANON | ISIG | IEXTEN);

    //非阻塞读取，超时时间设置
    tty.c_cc[VMIN] = 0;//最小读取字符为0
    tty.c_cc[VTIME] = 10;   // 等待时间（10*0.1秒=1秒）

    //应用配置
    if(tcsetattr(serialFD,TCSANOW,&tty) != 0){
        perror("init error");
        exit(EXIT_FAILURE);
    }

    //刷新输入输出缓冲区
    tcflush(serialFD,TCIOFLUSH);

    //发送数据
    char *buf = "第一条香橙派串口信息\n";
    write(serialFD,buf,strlen(buf));
    close(serialFD);
    return 0;
}