#include "game/fn_8007F828.h"

extern "C" {
int fn_801C6458(int a, int b);
int fn_801E1884(int channel, void *state);
}

struct Motor_803650A8 {
    unsigned short mLevel;
    unsigned short mTimer;
    unsigned char mPulse;
    signed char mCount;
    unsigned short mOffTime;
    unsigned short mOnTime;
};

struct MotorState_803650BC {
    int mChannel;
    int m04;
    unsigned char mLevel[2];
};

struct Port_803650A8 {
    Motor_803650A8 mMotor[2];
    MotorState_803650BC mState;
};

static Port_803650A8 sPorts[4];
static unsigned char sEnabled = 0;
static unsigned char sPortActive[4];

extern "C" {

void fn_80194B6C(int port, int motor, unsigned int level, int duration)
{
    Motor_803650A8 *m = &sPorts[port].mMotor[motor];

    if (level < m->mLevel && !m->mPulse) {
        return;
    }
    m->mLevel = level;
    m->mTimer = duration;
    m->mPulse = 0;
}

void fn_80194BB0(int port, int motor)
{
    Motor_803650A8 *m = &sPorts[port].mMotor[motor];

    m->mLevel = 0;
    m->mTimer = 0;
}

void fn_80194BD8(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < 4; i++) {
        sPorts[i].mState.mChannel = i;
        sPorts[i].mState.m04 = 0;
        for (j = 0; j < 2; j++) {
            fn_80194BB0(i, j);
            sPorts[i].mState.mLevel[j] = 0;
        }
    }
}

void fn_80194C5C(int channel, int level, int duration)
{
    int port = fn_801C6458(channel, 0);

    if (sEnabled && sPortActive[port]) {
        fn_80194B6C(port, 1, level, duration);
    }
}

void fn_80194CBC(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < 4; i++) {
        if (sPortActive[i]) {
            for (j = 0; j < 2; j++) {
                fn_80194BB0(i, j);
            }
        }
    }
}

void fn_80194D20(void)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        sPortActive[i] = fn_8007F828(9);
    }
    sEnabled = 0;
    fn_80194BD8();
}

void fn_80194D70(void)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        sPortActive[i] = 1;
    }
    sEnabled = 1;
    fn_80194BD8();
}

void fn_80194E04(void);

void fn_80194DB8(void)
{
    unsigned int i;

    fn_80194CBC();
    fn_80194E04();
    for (i = 0; i < 4; i++) {
        sPortActive[i] = 0;
    }
    sEnabled = 0;
}

void fn_80194E04(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < 4; i++) {
        if (!sPortActive[i]) {
            continue;
        }
        for (j = 0; j < 2; j++) {
            Motor_803650A8 *m = &sPorts[i].mMotor[j];
            if (m->mPulse) {
                if (--m->mCount < 0) {
                    if (m->mLevel) {
                        m->mLevel = 0;
                        m->mCount = m->mOffTime;
                    } else {
                        m->mLevel = 1;
                        m->mCount = m->mOnTime;
                    }
                }
            }
            if (m->mLevel) {
                if (--m->mTimer == 0xFFFF) {
                    fn_80194BB0(i, j);
                }
            }
        }
        sPorts[i].mState.mLevel[0] = sPorts[i].mMotor[0].mLevel;
        sPorts[i].mState.mLevel[1] = sPorts[i].mMotor[1].mLevel;
        fn_801E1884(i, &sPorts[i].mState);
    }
}

void fn_80194F1C(unsigned char enabled)
{
    sEnabled = enabled;
}

unsigned char fn_80194F24(void)
{
    return sEnabled;
}

void fn_80194F2C(int channel, int onTime, int offTime, int duration, int force)
{
    int port = fn_801C6458(channel, 0);

    if ((sEnabled || force) && sPortActive[port]) {
        Motor_803650A8 *m = &sPorts[port].mMotor[0];
        if (!m->mPulse || onTime != m->mOnTime || offTime != m->mOffTime || m->mTimer == 0) {
            m->mPulse = 1;
            m->mLevel = 1;
            m->mOffTime = offTime;
            m->mOnTime = onTime;
            m->mTimer = duration;
        }
    }
}

}
