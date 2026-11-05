/* Start and stop of the ball-following camera mode. */

struct CamBallCamera_t {
    char mPad00[0xDC];
    void (*mUnknownDC)(CamBallCamera_t *pCamera, int msg);
};

static unsigned char _CamBall_bActive = 0;

extern "C" {
void fn_80142A64(CamBallCamera_t *pCamera, int msg);

void CamBallInit(CamBallCamera_t *pCamera)
{
    pCamera->mUnknownDC = fn_80142A64;
    _CamBall_bActive = 1;
}

void CamBallUninit(CamBallCamera_t *pCamera)
{
    _CamBall_bActive = 0;
}
}
