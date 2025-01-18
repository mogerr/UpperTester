#ifndef __UPPER_H__
#define __UPPER_H__

#include "main.h"
#include "usb_device.h"

#define  _UpperTX_USE_16BIT_  1

#if _UpperTX_USE_16BIT_
struct TX_FRAME_Integrated_Control  // 向上位机发送信息
{
    unsigned char SYNC[2];
    unsigned char ID;
    unsigned char txcnt;
    unsigned char DATA[84];     // 16bit版本
    unsigned char crc16[2];
};
#endif



typedef struct _SAMPLE_VARIABLE
{
    float Temp;
    float Filtered;
    float Calibrate;
}Sample_Variable;

typedef struct _PROPORTIONAL_CONTROLLER
{
    float target_val;   //目标值
    float feedback_val; //反馈值
    float err;          //偏差值
    float Kp;           //比例系数
}controller;

typedef struct _MOTOR
{
    enum Motor_ID {
        A = 0,
        B = 1,
        C = 2,
        D = 3,
    } ID;
    Sample_Variable u_sys;
    Sample_Variable i_sys;
    Sample_Variable ia;
    Sample_Variable ib;
    Sample_Variable ic;
    union _STATE {
        Uint16               all;
        struct STATE_BITS {               // bits   description
            Uint16 power_ready   :1;       // 0  power_ready flag
            Uint16 enable        :1;       // 1  enable flag
            Uint16 overvoltage   :1;       // 2  overvoltage flag
            Uint16 overcurrent   :1;       // 3  overcurrent flag
            Uint16 undervoltage  :1;       // 4  undervoltage flag
            Uint16 overtempe     :1;       // 5  overtempe flag
            Uint16 lockedRotor   :1;       // 6  lockedRotor flag
            Uint16 loseFeedback  :1;       // 7  loseFeedback flag
            Uint16 touchground   :1;
            Uint16 touchgroundFinish :1;
            Uint16 isClosedASR   :1;
        } bit;
    } state;
    struct motor_touchground {
        int status;
        int XiaoDouCnt;
        float iq1;
    } touchground_var;
    float i_alpha;
    float i_beta;
    float i_q;
    float i_d;
    float u_q;
    float u_d;
    float u_alpha;
    float u_beta;
    Sample_Variable omega;
    Sample_Variable theta_ele;
    Sample_Variable theta_mech;
    Sample_Variable temperature;
    controller speedASR;
    controller i_qACR;
    controller i_dACR;
    struct _PROTECT {
        float USYS_Max;
        float USYS_Min;
        float SPEED_LIM;
        float CURRENT_LIM;
        float TEMPERATURE_LIM;
        Uint16 CNT_Voltage_Over;
        Uint16 CNT_Voltage_Low;
        Uint16 CNT_Current_Lim;
        Uint16 CNT_Temp_Lim;
        Uint16 CNT_Locked;
        Uint16 CNT_Touch;
    } protect;
}Motor;


#if _UpperTX_USE_16BIT_
extern int Variable1[10];
#endif
#if !_UpperTX_USE_16BIT_
extern Uint16 Variable1[10];
#endif
extern int Variable2[10];
extern int Variable3;
extern int Variable4;
extern int Variable5;
extern int Variable6;
extern int Variable7;
extern int Variable8[10];
extern int Variable9;
extern int Variable10;
extern int Variable11;
extern int Variable12;
extern int Variable13;
extern int Variable14;
extern int Variable15;

#if _UpperTX_USE_16BIT_
extern volatile struct TX_FRAME_Integrated_Control TX_FRAME_Upper;
void User_Upper_TX_FRAME_Set(void);
#endif

#endif
