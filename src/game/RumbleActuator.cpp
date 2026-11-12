/* Controller rumble: per-port motor state, starting steady or pulsing rumble on a controller,
   stopping it, and the per-frame update that sends motor levels to the controllers. */
#include "game/GameOptions.h"

extern "C" {
int ConGetChannelInfo(int a, int b);
int fn_801E1884(int channel, void *state);
}

struct RumbleMotor_t {
    unsigned short mLevel;
    unsigned short mTimer;
    unsigned char mPulse;
    signed char mCount;
    unsigned short mOffTime;
    unsigned short mOnTime;
};

struct RumbleOutput_t {
    int mChannel;
    int m04;
    unsigned char mLevel[2];
};

struct RumblePort_t {
    RumbleMotor_t mMotor[2];
    RumbleOutput_t mState;
};

static RumblePort_t _Rumble_aPorts[4];
static unsigned char _Rumble_bEnabled = 0;
static unsigned char _Rumble_abPortActive[4];

extern "C" {

void _RumbleStartActuator(int port, int motor, unsigned int level, int duration)
{
    RumbleMotor_t *m = &_Rumble_aPorts[port].mMotor[motor];

    if (level < m->mLevel && !m->mPulse) {
        return;
    }
    m->mLevel = level;
    m->mTimer = duration;
    m->mPulse = 0;
}

void _RumbleStopActuator(int port, int motor)
{
    RumbleMotor_t *m = &_Rumble_aPorts[port].mMotor[motor];

    m->mLevel = 0;
    m->mTimer = 0;
}

void _RumbleSetup(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < 4; i++) {
        _Rumble_aPorts[i].mState.mChannel = i;
        _Rumble_aPorts[i].mState.m04 = 0;
        for (j = 0; j < 2; j++) {
            _RumbleStopActuator(i, j);
            _Rumble_aPorts[i].mState.mLevel[j] = 0;
        }
    }
}

void RumbleStart(int channel, int level, int duration)
{
    int port = ConGetChannelInfo(channel, 0);

    if (_Rumble_bEnabled && _Rumble_abPortActive[port]) {
        _RumbleStartActuator(port, 1, level, duration);
    }
}

void RumbleStopAll(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < 4; i++) {
        if (_Rumble_abPortActive[i]) {
            for (j = 0; j < 2; j++) {
                _RumbleStopActuator(i, j);
            }
        }
    }
}

void RumbleInit(void)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        _Rumble_abPortActive[i] = GameOptionsGet(9);
    }
    _Rumble_bEnabled = 0;
    _RumbleSetup();
}

void RumbleInitAllPorts(void)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        _Rumble_abPortActive[i] = 1;
    }
    _Rumble_bEnabled = 1;
    _RumbleSetup();
}

void RumbleProcess(void);

void RumbleShutdown(void)
{
    unsigned int i;

    RumbleStopAll();
    RumbleProcess();
    for (i = 0; i < 4; i++) {
        _Rumble_abPortActive[i] = 0;
    }
    _Rumble_bEnabled = 0;
}

void RumbleProcess(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < 4; i++) {
        if (!_Rumble_abPortActive[i]) {
            continue;
        }
        for (j = 0; j < 2; j++) {
            RumbleMotor_t *m = &_Rumble_aPorts[i].mMotor[j];
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
                    _RumbleStopActuator(i, j);
                }
            }
        }
        _Rumble_aPorts[i].mState.mLevel[0] = _Rumble_aPorts[i].mMotor[0].mLevel;
        _Rumble_aPorts[i].mState.mLevel[1] = _Rumble_aPorts[i].mMotor[1].mLevel;
        fn_801E1884(i, &_Rumble_aPorts[i].mState);
    }
}

void RumbleEnable(unsigned char enabled)
{
    _Rumble_bEnabled = enabled;
}

unsigned char RumbleIsEnabled(void)
{
    return _Rumble_bEnabled;
}

void RumbleStartPulse(int channel, int onTime, int offTime, int duration, int force)
{
    int port = ConGetChannelInfo(channel, 0);

    if ((_Rumble_bEnabled || force) && _Rumble_abPortActive[port]) {
        RumbleMotor_t *m = &_Rumble_aPorts[port].mMotor[0];
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
