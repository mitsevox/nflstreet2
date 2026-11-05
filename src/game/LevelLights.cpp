/* Level lighting: picks the light scene and light colours for the current
   level (twelve sets) or for the front end and hands them to the engine's
   light code. */
extern "C" {
extern char lbl_802EEDD0[];
extern char lbl_802EEE7C[];
extern char lbl_802EEEE0[];
extern char lbl_802EF31C[];
extern char lbl_802EF7A0[];
extern char lbl_802EFC24[];
extern char lbl_802F00A8[];
extern char lbl_802F052C[];
extern char lbl_802F09B0[];
extern char lbl_802F0E34[];
extern char lbl_802F12B8[];
extern char lbl_802F173C[];
extern char lbl_802F1BC0[];
extern char lbl_802F2044[];
extern char lbl_802F24C8[];

void fn_802353CC(void *p);
void fn_802353D0(void *p);
void fn_8023633C(void *p);
int fn_800A3444(void);

void LevelLightsInit(void);
void LevelLightsSelect(int id);
void LevelLightsSelectFrontEnd(void);
void LevelLightsApplyColors(void);
}

static int _LevelLights_iCurrent = -1;
static char *_LevelLights_pColors = 0;

extern "C" {

void LevelLightsInit(void)
{
    LevelLightsSelect(fn_800A3444());
}

void LevelLightsSelect(int id)
{
    switch (id) {
    case 0:
        fn_8023633C(lbl_802EF31C);
        _LevelLights_iCurrent = id;
        break;
    case 2:
        fn_8023633C(lbl_802F052C);
        _LevelLights_iCurrent = 1;
        break;
    case 3:
        fn_8023633C(lbl_802EF7A0);
        _LevelLights_iCurrent = 2;
        break;
    case 1:
        fn_8023633C(lbl_802EFC24);
        _LevelLights_iCurrent = 3;
        break;
    case 4:
        fn_8023633C(lbl_802F00A8);
        _LevelLights_iCurrent = id;
        break;
    case 5:
        fn_8023633C(lbl_802F09B0);
        _LevelLights_iCurrent = id;
        break;
    case 6:
        fn_8023633C(lbl_802F0E34);
        _LevelLights_iCurrent = id;
        break;
    case 9:
        fn_8023633C(lbl_802F12B8);
        _LevelLights_iCurrent = 9;
        break;
    case 7:
        fn_8023633C(lbl_802F173C);
        _LevelLights_iCurrent = id;
        break;
    case 8:
        fn_8023633C(lbl_802F1BC0);
        _LevelLights_iCurrent = id;
        break;
    case 10:
        fn_8023633C(lbl_802F2044);
        _LevelLights_iCurrent = id;
        break;
    case 11:
        fn_8023633C(lbl_802F24C8);
        _LevelLights_iCurrent = id;
        break;
    }
    _LevelLights_pColors = lbl_802EEE7C;
    LevelLightsApplyColors();
}

void LevelLightsSelectFrontEnd(void)
{
    _LevelLights_pColors = lbl_802EEEE0;
    fn_8023633C(lbl_802EEDD0);
    _LevelLights_iCurrent = 0;
    LevelLightsApplyColors();
}

void LevelLightsApplyColors(void)
{
    fn_802353CC(_LevelLights_pColors + 64);
    fn_802353D0(_LevelLights_pColors);
}

}
