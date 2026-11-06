/* Front-end sound: starts, services every frame and stops the audio of the menus. */

struct Struct_8006C2C8;

extern "C" {
extern Struct_8006C2C8 lbl_802D62A0;

void fn_8006C2C8(Struct_8006C2C8 *pInit);
void fn_8006C454(void);
void fn_8006D314(void);
void fn_8006D338(void);
void fn_8006EC24(void);
void fn_800728F8(void);
void SpchIGInitFrontEnd(void);
void fn_801F4B20(void);

void FESndInit(void)
{
    fn_8006C2C8(&lbl_802D62A0);
    fn_8006D314();
    SpchIGInitFrontEnd();
    fn_8006EC24();
}

void FESndUpdate(int a)
{
    fn_800728F8();
    fn_801F4B20();
}

void FESndShutdown(void)
{
    fn_8006D338();
    fn_8006C454();
}

}
