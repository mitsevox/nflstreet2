/* An orange pulse drawn on the ground that grows and then disappears. */

extern "C" {
extern char lbl_8031B7D0[];
extern unsigned char gParticles_bInit;

void fn_80196F48(float scale, void *pObject);

void GroundPulseUpdate(void);
void GroundPulseDraw(void);
}

static float _GroundPulse_fScale = 0.05f;
static unsigned char _GroundPulse_bActive = 0;
unsigned char gParticles_bInit = 0;

void GroundPulseUpdate(void)
{
    _GroundPulse_fScale += 0.14750001f;
    if (_GroundPulse_fScale > 3.0f) {
        _GroundPulse_bActive = 0;
        _GroundPulse_fScale = 0.05f;
    }
}

void GroundPulseDraw(void)
{
    if (_GroundPulse_bActive == 1) {
        fn_80196F48(_GroundPulse_fScale, lbl_8031B7D0);
    }
}
