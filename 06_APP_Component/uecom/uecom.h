//=====================================================================
//文件名称：uecom.h
//功能概要：UE驱动构件头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2017-06-04   V1.0
//=====================================================================

#ifndef _UECOM_H    //防止重复定义（_COMMON_H  开头)
#define _UECOM_H

#include "common.h"   //包含公共要素头文件
#include "stdlib.h"
#include "uart.h"
#include "string.h"
#include "lcd.h"

#define UART_UE UART_1

uint_8 AT_re_buf[1100];//存放UE的AT指令的返回结果
uint_8 ATSendFlag;//标记一个AT指令已发送

//=====================================================================
//函数名称：uecom_init
//函数返回：0：成功
//      1：AT指令发送失败；2：GPRS模块的波特率设置失败；3：关闭回显失败；4：IMEI查询失败；
//      5：IMSI查询失败；6：设置模块的工作类型为B类失败；7：2：设置联网方式为net失败；8：激活PDP失败；
//      9：获得模块分得的IP地址失败；10：AT指令返回OK，但是并没有获取到IP地址；11:建立TCP连接失败
//参数说明：dest：返回数据的地址，总长74字节，IMEI,15个字节，0~14；IMSI,15个字节，15~29；
//            firmVer，25个字节，30~54；signalPower，2个字节，55~56；bsNum，2个字节，57~58；
//            UEIP，15个字节，59~73
//       IP:管理服务器IP地址
//       PORT:管理服务器端口号
//功能概要：uecom模块初始化
//内部调用：uart_init，uecom_sendCmd，uecom_getIMEI，uecom_getIMSI，
//  	    uecom_link，uecom_config
//修改日期：2017.08.11,QHJ,CC
//=====================================================================
uint_8 uecom_init(uint_8 *dest,uint_8 *IP,uint_8* PORT);

//=====================================================================
//函数名称：uecom_send
//函数返回：  0：发送成功；1：发送失败
//参数说明： data:待发送数据缓存区，传入参数
//		  length:待发送数据的长度
//功能概要：将数据通过已经建立的TCP/UDP通道发送出去
//=====================================================================
uint_8 uecom_send(uint_16 length, uint_8 *data);

//=====================================================================
//函数名称：uecom_recv
//函数返回：0：接收到了通过TCP/UDP发来的数据；1：未接收到
//参数说明：*data:将接收到的数据存放到该数组串中
//功能概要：将数据接收缓冲区的数据读出，并存入data数组之中
//=====================================================================
uint_8 uecom_recv(uint_16 *dataLen, uint_8 *data);


uint_8 uecom_deInit();

//=====================================================================
//函数名称：ue_internal_init
//函数返回：0：成功
//       1：全功能打开失败
//       2：获取IMEI号失败
//       3：获取IMSI号失败
//参数说明：*dest：总长30字节，存储IMEI和IMSI的数组，前面为IMEI，后面为IMSI，
//             各占15个字节，若信息获取失败则信息无效
//功能概要：uecom模块初始化
//=====================================================================
uint_8 ue_internal_init(uint_8 *dest);

//=====================================================================
//函数名称：uecom_link
//函数返回：0：成功与基站建立连接；1：失败
//参数说明：*dest：存放基站给本模块的ip地址，格式为字符串，中间用"."
//          连接，dest指向的数组至少要有15个字节
//功能概要：建立与基站的连接
//=====================================================================
uint_8 uecom_link(uint_8 *dest);


//=====================================================================
//函数名称：uecom_config
//函数返回：  0：成功建立TCP连接；1：失败
//参数说明： IP:待连接服务器的IP地址
//        port:待连接服务器的端口号
//功能概要：与指定的服务器端口建立TCP连接
//=====================================================================
uint_8 uecom_config(uint_8 *ip,uint_8* port);

//==================================================================
//函数名称：uecom_getIMEI
//函数返回：1：获取IMEI失败
//       0：获取IMEI成功
//参数说明：imei：存放返回的IMEI号，15位
//功能概要：获取设备IMEI号
//==================================================================
uint_8 uecom_getIMEI(uint_8 *dest);

//==================================================================
//函数名称：uecom_getIMSI
//函数返回：1：获取IMSI失败
//       0：获取IMSI成功
//参数说明：imsi：存放返回的IMSI号，15位
//功能概要：获取设备IMSI号
//==================================================================
uint_8 uecom_getIMSI(uint_8 *dest);

//===================================================================
//函数名称：uecom_getFirmVer
//函数返回：1：获取固件版本号失败
//       0：获取固件版本号成功
//参数说明：firmVer：存放返回的固件版本号，25位
//功能概要：获取固件版本号
//==================================================================
uint_8 uecom_getFirmVer(uint_8 *firmVer);

//=====================================================================
//函数名称：uecom_getSignalPower
//函数返回：1：获取基站信号强度失败
//       0：获取基站信号强度成功
//参数说明：signalPower：存放返回的基站信号强度号，2位
//功能概要：获取基站信号强度
//=====================================================================
uint_8 uecom_getSignalPower(uint_16 *signalPower);

//=====================================================================
//函数名称：uecom_getBSNum
//函数返回：1：获取基站号失败
//       0：获取基站号成功
//参数说明：bsNum：存放返回的基站号，2位
//功能概要：获取基站号
//=====================================================================
uint_8 uecom_getBSNum(uint_32 *bsNum);

//=====================================================================
//函数名称：uecom_getUEIP
//函数返回：1：获取基站分配UE的IP地址失败
//       0：获取基站分配UE的IP地址成功
//参数说明：ip：存放返回基站分配UE的IP地址，15位
//功能概要：获取基站分配UE的IP地址
//=====================================================================
uint_8 uecom_getUEIP(uint_8 *ip);

#endif
/*



 */
