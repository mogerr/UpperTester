#include "upper.h"

Motor Motor_1 = {0}; // 支撑左电机
volatile struct TX_FRAME_Integrated_Control TX_FRAME_Upper;
Uint16 crc16(unsigned char *data, unsigned char len);


#if _UpperTX_USE_16BIT_
#if _UpperTX_NoneHighSpeed_
int Variable1 = 0;
#else
int Variable1[10] = {0};
#endif
#endif
#if !_UpperTX_USE_16BIT_
Uint16 Variable1[10] = {0};
#endif
#if _UpperTX_NoneHighSpeed_
int Variable2 = 0;
#else
int Variable2[10] = {0};
#endif
int Variable3 = 0;
int Variable4 = 0;
int Variable5 = 0;
int Variable6 = 0;
int Variable7 = 0;
#if _UpperTX_NoneHighSpeed_
int Variable8 = 0;
#else
int Variable8[10] = {0};
#endif
int Variable9 = 0;
int Variable10 = 0;
int Variable11 = 0;
int Variable12 = 0;
int Variable13 = 0;
int Variable14 = 0;
int Variable15 = 0;


#if _UpperTX_USE_16BIT_

// 定值发送的时候 (过年前)
// EB90 3600 003D 0003 003E 0004 003F 0005 0040 0006 0041 0007 0042 0008 0043 0009 0044 000A 0045 000B 0046 000C
// 000F 002A 0020 0020 0000 0000 0001 0002 0003 0004 0005 0006 0007 0008 0009 0069 0307 0008 FFFC FFFB 0010 0010 177F
// 定值发送的时候 (3月7号)
// EB90 3600 003D 0003 003D 0003 003D 0003 003D 0003 003D 0003 003D 0003 003D 0003 003D 0003 003D 0003 003D 0003 
// 000F 002A 0020 0020 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0069 0307 0008 FFFC FFFB 0010 0010 3BA2

// 做测试，定值
void User_SetManual(void)
{
    TX_FRAME_Upper.SYNC[0] = 0xEB;
    TX_FRAME_Upper.SYNC[1] = 0x90;
    TX_FRAME_Upper.ID = 0x36;
    TX_FRAME_Upper.txcnt = 0x00;

    Motor_1.ID = C;
    Motor_1.theta_mech.Calibrate = 6.1f;
    Motor_1.theta_ele.Calibrate = 3.22232f;
    Motor_1.omega.Calibrate = 1542.0f;
    Motor_1.i_q = 0.0f;
    Motor_1.u_q = 10.5f;
    Motor_1.i_qACR.target_val = 1550.0f;
    Motor_1.ia.Filtered = 8.02f;
    Motor_1.ib.Filtered = -4.55f;
    Motor_1.ic.Filtered = -5.02f;
    Motor_1.i_sys.Filtered = 0.1642f;
}
#endif

#if _UpperTX_USE_16BIT_
void User_UppdataDataToUpper(void)
{
#if _UpperTX_NoneHighSpeed_
    Variable1 = (int16)(Motor_1.theta_mech.Calibrate * 10.0f) ;
    Variable2 = (int16)(Motor_1.theta_ele.Calibrate) ;
    Variable8 = -5;
#else
    unsigned int group;
    for(group =0; group < 10; group++)
    {
        // 变量 1、2、8 高速通道
        // 每帧里十个值都一样，相当于当做低速通道用
        Variable1[group] = (Uint16)(Motor_1.theta_mech.Calibrate * 10.0f) ;
        // 每帧里十个值都一样，相当于当做低速通道用
        Variable2[group] = (int16)(Motor_1.theta_ele.Calibrate) ;
        // 每帧里十个值都一样，相当于当做低速通道用
        Variable8[group] = -5;
    }
#endif

    Variable3 = (int16)(Motor_1.omega.Calibrate * 0.01f) ;
    Variable4 = (int16)(Motor_1.omega.Calibrate) - Variable3 * 100.0f ;
    Variable5 = (int16)(Motor_1.theta_ele.Calibrate * 10.0f);
    Variable6 = (int16)(Motor_1.theta_ele.Calibrate * 10.0f);

    Variable7 = (int16)(Motor_1.i_q );
    
    Variable9 = (int16)(Motor_1.u_q * 10.0f);
    Variable10 = (int16)(Motor_1.i_qACR.target_val *0.5f);

    Variable11 = (int16)(Motor_1.ia.Filtered);
    Variable12 = (int16)(Motor_1.ib.Filtered);
    Variable13 = (int16)(Motor_1.ic.Filtered);

    Variable14 = (int16)(Motor_1.i_sys.Filtered * 100.0f);
    Variable15 = (int16)(Motor_1.i_sys.Filtered * 100.0f);
}
#endif


#if _UpperTX_USE_16BIT_
#if _UpperTX_NoneHighSpeed_
void User_Presend_Var(void)
{
    TX_FRAME_Upper.DATA[0] =  (Variable1 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[1] = Variable1 & 0x00FF;

    TX_FRAME_Upper.DATA[2] = (Variable2 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[3] = Variable2 & 0x00FF;

    TX_FRAME_Upper.DATA[4] = (Variable3 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[5] = Variable3 & 0x00FF;

    TX_FRAME_Upper.DATA[6] = (Variable4 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[7] = Variable4 & 0x00FF;

    TX_FRAME_Upper.DATA[8] = (Variable5 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[9] = Variable5 & 0x00FF;

    TX_FRAME_Upper.DATA[10] = (Variable6 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[11] = Variable6 & 0x00FF;

    TX_FRAME_Upper.DATA[12] = (Variable7 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[13] = Variable7 & 0x00FF;

    TX_FRAME_Upper.DATA[14] = (Variable8 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[15] = Variable8 & 0x00FF;

    TX_FRAME_Upper.DATA[16] = (Variable9 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[17] = Variable9 & 0x00FF;

    TX_FRAME_Upper.DATA[18] = (Variable10 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[19] = Variable10 & 0x00FF;

    TX_FRAME_Upper.DATA[20] = (Variable11 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[21] = Variable11 & 0x00FF;

    TX_FRAME_Upper.DATA[22] = (Variable12 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[23] = Variable12 & 0x00FF;

    TX_FRAME_Upper.DATA[24] = (Variable13 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[25] = Variable13 & 0x00FF;

    TX_FRAME_Upper.DATA[26] = (Variable14 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[27] = Variable14 & 0x00FF;

    TX_FRAME_Upper.DATA[28] = (Variable15 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[29] = Variable15 & 0x00FF;
}
#else
void User_Presend_Var(void)
{
    int u;
    for (u = 0; u < 10; u++)
    {
        TX_FRAME_Upper.DATA[4 * u] =  (Variable1[u] >> 8) & 0x00FF;
        TX_FRAME_Upper.DATA[4 * u + 1] = Variable1[u] & 0x00FF;

        TX_FRAME_Upper.DATA[4 * u + 2] = (Variable2[u] >> 8) & 0x00FF;
        TX_FRAME_Upper.DATA[4 * u + 3] = Variable2[u] & 0x00FF;

        TX_FRAME_Upper.DATA[2 * u + 50] = (Variable8[u] >>8 ) & 0x00FF;
        TX_FRAME_Upper.DATA[2 * u + 51] = Variable8[u] & 0x00FF;
    }

    TX_FRAME_Upper.DATA[40] = (Variable3 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[41] = Variable3 & 0x00FF;

    TX_FRAME_Upper.DATA[42] = (Variable4 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[43] = Variable4 & 0x00FF;

    TX_FRAME_Upper.DATA[44] = (Variable5 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[45] = Variable5 & 0x00FF;

    TX_FRAME_Upper.DATA[46] = (Variable6 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[47] = Variable6 & 0x00FF;

    TX_FRAME_Upper.DATA[48] = (Variable7 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[49] = Variable7 & 0x00FF;

    TX_FRAME_Upper.DATA[70] = (Variable9 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[71] = Variable9 & 0x00FF;

    TX_FRAME_Upper.DATA[72] = (Variable10 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[73] = Variable10 & 0x00FF;

    TX_FRAME_Upper.DATA[74] = (Variable11 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[75] = Variable11 & 0x00FF;

    TX_FRAME_Upper.DATA[76] = (Variable12 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[77] = Variable12 & 0x00FF;

    TX_FRAME_Upper.DATA[78] = (Variable13 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[79] = Variable13 & 0x00FF;

    TX_FRAME_Upper.DATA[80] = (Variable14 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[81] = Variable14 & 0x00FF;

    TX_FRAME_Upper.DATA[82] = (Variable15 >> 8) & 0x00FF;
    TX_FRAME_Upper.DATA[83] = Variable15 & 0x00FF;
}
#endif
#endif

#if _UpperTX_USE_16BIT_
void User_Upper_TX_FRAME_Set(void)
{
    //static unsigned int i;
    static Uint16 CRC16D_T = 0;

    // 准备发送数据
    User_SetManual();
    User_UppdataDataToUpper();
    User_Presend_Var();

    // CRC 校验
    CRC16D_T = crc16( (unsigned char*) &TX_FRAME_Upper.ID, 32);

    TX_FRAME_Upper.crc16[0] = (CRC16D_T & 0xff00) >> 8 ;
    TX_FRAME_Upper.crc16[1] = CRC16D_T & 0x00ff;
}

void User_Upper_TX_FRAME_Set_Loop(float interval)
{
    //static unsigned int i;
    static Uint16 CRC16D_T = 0;

    /// 原始数据每次都改变一下
    // 改变变量1
    Motor_1.theta_mech.Calibrate += 0.1f * interval;
    if(Motor_1.theta_mech.Calibrate > 6.2f){
        Motor_1.theta_mech.Calibrate = 0.0f;
    }
    // 改变变量7 (低速通道)
    Motor_1.i_q += interval;
    if(Motor_1.i_q > 32767.0f){
        Motor_1.i_q = -32768.0f;
    }

    // 准备发送数据
    User_UppdataDataToUpper();
    User_Presend_Var();

    // CRC 校验
    CRC16D_T = crc16( (unsigned char*) &TX_FRAME_Upper.ID, 32);

    TX_FRAME_Upper.crc16[0] = (CRC16D_T & 0xff00) >> 8 ;
    TX_FRAME_Upper.crc16[1] = CRC16D_T & 0x00ff;
}
#endif



// 生成多项式：0x04C11DB7
static const Uint16 crc16tab[] = {0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
                                  0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
                                  0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
                                  0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
                                  0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
                                  0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
                                  0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
                                  0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
                                  0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
                                  0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
                                  0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
                                  0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
                                  0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
                                  0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
                                  0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
                                  0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
                                  0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
                                  0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
                                  0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
                                  0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
                                  0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
                                  0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
                                  0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
                                  0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
                                  0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
                                  0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
                                  0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
                                  0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
                                  0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
                                  0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
                                  0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
                                  0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

Uint16 crc16(unsigned char *data, unsigned char length)
{
    int i = 0;
    Uint16 crc_fb = 0;
    Uint16 crc = 0xffff;
    for (i = 0; i < length; i++)
        crc = (crc >> 8) ^ crc16tab[(crc ^ *data++) & 0xff];
    crc_fb = (~crc & 0xffff);

    return crc_fb;
}

