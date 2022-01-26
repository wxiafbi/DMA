#include "cat1.h"

/*-------------------------------------------------*/
/*函数名：复位4G模块                               */
/*参  数：timeout： 超时时间（1s的倍数）           */
/*返回值：无                                       */
/*-------------------------------------------------*/
char CAT1_Reset(int timeout)
{
    HAL_GPIO_WritePin(GPIOB, RST_Pin, GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOB, RST_Pin, GPIO_PIN_RESET);

    while (timeout--)
    {                                      //等待超时时间到0
        HAL_Delay(1000);                    //延时1s
        if (strstr(CAT1_RX_BUF, "WH-GM5")) //如果接收到WH-GM5表示成功
            break;                         //主动跳出while循环
        printf("%d ", timeout);         //串口输出现在的超时时间
    }
    printf("\r\n"); //串口输出信息
    if (timeout <= 0)
        return 1; //超时错误，返回1
    return 0;     //正确返回0
}
/*-------------------------------------------------*/
/*函数名：4G模块退出透传                           */
/*参  数：timeout： 超时时间（100ms的倍数）        */
/*返回值：无                                       */
/*-------------------------------------------------*/
char CAT1_ExitTrans(int timeout)
{
    CAT1_RxCounter = 0;                       //接收数据量变量清零
    memset(CAT1_RX_BUF, 0, CAT1_RXBUFF_SIZE); //清空接收缓冲区
    CAT1_printf("+++");                       //发送指令
    while (timeout--)
    {                                 //等待超时时间到0
        HAL_Delay(100);                //延时100ms
        if (strstr(CAT1_RX_BUF, "a")) //如果接收到a表示成功
            break;                    //主动跳出while循环
        printf("%d ", timeout);    //串口输出现在的超时时间
    }
    printf("\r\n"); //串口输出信息
    if (timeout <= 0)
        return 1; //如果timeout<=0，说明超时时间到了，也没能收到a，返回1
    else
    {
        CAT1_RxCounter = 0;                       //接收数据量变量清零
        memset(CAT1_RX_BUF, 0, CAT1_RXBUFF_SIZE); //清空接收缓冲区
        CAT1_printf("a");                         //发送指令
        while (timeout--)
        {                                   //等待超时时间到0
            HAL_Delay(100);                  //延时100ms
            if (strstr(CAT1_RX_BUF, "+ok")) //如果接收到+ok表示成功
                break;                      //主动跳出while循环
            printf("%d ", timeout);      //串口输出现在的超时时间
        }
        printf("\r\n"); //串口输出信息
        if (timeout <= 0)
            return 2; //如果timeout<=0，说明超时时间到了，也没能收到+ok，返回1
    }
    return 0; //正确 返回0
}
/*-------------------------------------------------*/
/*函数名：4G模块发送设置指令                       */
/*参  数：cmd：指令                                */
/*参  数：timeout： 超时时间（100ms的倍数）        */
/*返回值：无                                       */
/*-------------------------------------------------*/
char CAT1_SendCmd(char *cmd, int timeout)
{
    CAT1_RxCounter = 0;                       //CAT1接收数据量变量清零
    memset(CAT1_RX_BUF, 0, CAT1_RXBUFF_SIZE); //清空CAT1接收缓冲区
    CAT1_printf("%s\r\n", cmd);               //发送指令
    while (timeout--)
    {                                  //等待超时时间到0
        HAL_Delay(100);                 //延时100ms
        if (strstr(CAT1_RX_BUF, "OK")) //如果接收到OK表示指令成功
            break;                     //主动跳出while循环
        printf("%d ", timeout);     //串口输出现在的超时时间
    }
    printf("\r\n"); //串口输出信息
    if (timeout <= 0)
        return 1; //如果timeout<=0，说明超时时间到了，也没能收到OK，返回1
    else
        return 0; //反之，表示正确，说明收到OK，通过break主动跳出while
}
/*-------------------------------------------------*/
/*函数名：4G模块信号检测                           */
/*参  数：timeout： 超时时间（100ms的倍数）        */
/*返回值：无                                       */
/*-------------------------------------------------*/
char CAT1_CSQ(int timeout)
{
    char temp[20];
    char csq[20];

    CAT1_RxCounter = 0;                       //CAT1接收数据量变量清零
    memset(CAT1_RX_BUF, 0, CAT1_RXBUFF_SIZE); //清空CAT1接收缓冲区
    CAT1_printf("AT+CSQ\r\n");                //发送指令
    while (timeout--)
    {                                 //等待超时时间到0
        HAL_Delay(100);                //延时100ms
        if (strstr(CAT1_RX_BUF, ",")) //如果接收到,表示指令成功
            break;                    //主动跳出while循环
        printf("%d ", timeout);    //串口输出现在的超时时间
    }
    printf("\r\n"); //串口输出信息
    if (timeout <= 0)
        return 1; //如果timeout<=0，说明超时时间到了，也没能收到,返回1
    else
    {
        sscanf(CAT1_RX_BUF, "%[^:]:%[^,],%[^,],%[^\r]", temp, csq, temp, temp); //拆分数据
        printf("信号强度:%s\r\n", csq);                                      //串口显示信息
    }
    return 0; //正确 返回0
}
/*-------------------------------------------------*/
/*函数名：4G模块查询网络信息                       */
/*参  数：timeout： 超时时间（100ms的倍数）        */
/*返回值：无                                       */
/*-------------------------------------------------*/
char CAT1_SYSINFO(int timeout)
{
    char temp[20];
    char info[20];

    CAT1_RxCounter = 0;                       //CAT1接收数据量变量清零
    memset(CAT1_RX_BUF, 0, CAT1_RXBUFF_SIZE); //清空CAT1接收缓冲区
    CAT1_printf("AT+SYSINFO\r\n");            //发送指令
    while (timeout--)
    {                                 //等待超时时间到0
        HAL_Delay(100);                //延时100ms
        if (strstr(CAT1_RX_BUF, ",")) //如果接收到,表示指令成功
            break;                    //主动跳出while循环
        printf("%d ", timeout);    //串口输出现在的超时时间
    }
    printf("\r\n"); //串口输出信息
    if (timeout <= 0)
        return 1; //如果timeout<=0，说明超时时间到了，也没能收到,返回1
    else
    {
        sscanf(CAT1_RX_BUF, "%[^:]:%[^,],%[^\r]", temp, temp, info); //拆分数据
        printf("当前网络形式:%s\r\n", info);                      //串口显示信息
    }
    return 0; //正确 返回0
}
/*-------------------------------------------------*/
/*函数名：4G模块连接服务器                         */
/*参  数：timeout： 超时时间（100ms的倍数）        */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
char CAT1_Connect_IoTServer(int timeout)
{
    char temp[256];

    printf("准备复位模块\r\n"); //串口提示数据
    if (CAT1_Reset(20))
    {                                        //复位，1s超时单位，总计20s超时时间
        printf("复位失败，准备重启\r\n"); //返回非0值，进入if，串口提示数据
        return 1;                            //返回1
    }
    else
        printf("复位成功\r\n"); //串口提示数据

    printf("准备退出透传\r\n"); //串口提示数据
    if (CAT1_ExitTrans(50))
    {                                            //退出透传，100ms超时单位，总计5s超时时间
        printf("退出透传失败，准备重启\r\n"); //返回非0值，进入if，串口提示数据
        return 2;                                //返回2
    }
    else
        printf("退出透传成功\r\n"); //串口提示数据

    printf("准备设置NET模式\r\n"); //串口提示数据
    if (CAT1_SendCmd("AT+WKMOD=NET", 50))
    {                                               //设置NET模式，100ms超时单位，总计5s超时时间
        printf("设置NET模式失败，准备重启\r\n"); //返回非0值，进入if，串口提示数据
        return 5;                                   //返回5
    }
    else
        printf("设置NET模式成功\r\n"); //串口提示数据

    printf("准备使能链接A\r\n"); //串口提示数据
    if (CAT1_SendCmd("AT+SOCKAEN=ON", 50))
    {                                             //使能链接A，100ms超时单位，总计5s超时时间
        printf("使能链接A失败，准备重启\r\n"); //返回非0值，进入if，串口提示数据
        return 6;                                 //返回6
    }
    else
        printf("使能链接A成功\r\n"); //串口提示数据

    printf("准备关闭链接B\r\n"); //串口提示数据
    if (CAT1_SendCmd("AT+SOCKBEN=OFF", 50))
    {                                             //关闭链接B，100ms超时单位，总计5s超时时间
        printf("关闭链接B失败，准备重启\r\n"); //返回非0值，进入if，串口提示数据
        return 7;                                 //返回7
    }
    else
        printf("关闭链接B成功\r\n"); //串口提示数据

    printf("准备设置链接A长连接\r\n"); //串口提示数据
    if (CAT1_SendCmd("AT+SOCKASL=LONG", 50))
    {                                                   //设置链接A长连接，100ms超时单位，总计5s超时时间
        printf("设置链接A长连接失败，准备重启\r\n"); //返回非0值，进入if，串口提示数据
        return 8;                                       //返回8
    }
    else
        printf("设置链接A长连接成功\r\n"); //串口提示数据

    printf("准备关闭自带心跳功能\r\n"); //串口提示数据
    if (CAT1_SendCmd("AT+HEARTEN=OFF", 50))
    {                                                    //关闭自带心跳功能，100ms超时单位，总计5s超时时间
        printf("关闭自带心跳功能失败，准备重启\r\n"); //返回非0值，进入if，串口提示数据
        return 9;                                        //返回9
    }
    else
        printf("关闭自带心跳功能成功\r\n"); //串口提示数据

    printf("准备设置链接A链接服务器\r\n");                  //串口提示数据
    sprintf(temp, "AT+SOCKA=TCP,%s,%d", ServerIP, ServerPort); //构建命令
    if (CAT1_SendCmd(temp, 50))
    {                                                       //设置链接A链接服务器，100ms超时单位，总计5s超时时间
        printf("设置链接A链接服务器失败，准备重启\r\n"); //返回非0值，进入if，串口提示数据
        return 10;                                          //返回10
    }
    else
        printf("设置链接A链接服务器成功\r\n"); //串口提示数据

    printf("保存设置，然后重启模块\r\n"); //串口提示数据
    if (CAT1_SendCmd("AT+S", 50))
    {                                            //保存设置，然后重启模块，100ms超时单位，总计5s超时时间
        printf("保存设置失败，准备重启\r\n"); //返回非0值，进入if，串口提示数据
        return 11;                               //返回11
    }
    else
        printf("保存设置成功\r\n"); //串口提示数据

    printf("等待重启并连接服务器\r\n"); //串口提示数据
    while (timeout--)
    {                              //等待超时时间到0
        HAL_Delay(1000);            //延时1s
        if (LA_Pin == 0)        //如LINKA_STA PC1是低电平了，表示连接成功
            break;                 //跳出while循环
        printf("%d ", timeout); //串口输出现在的超时时间
    }
    printf("\r\n"); //串口输出信息
    if (timeout <= 0)
        return 12; //超时错误，返回12

    HAL_Delay(500); //延时
    return 0;      //正确返回0
}
