/* Data-structure library module: init/shutdown and the shared size alignment. */

#include "engine/cu_801C665C.h"

extern unsigned char lbl_803EBC00;
extern int lbl_803EBC04;

void fn_801C6760(void);
void fn_801F7BD4(int error);

int fn_801C6634(int alignment);

int fn_801C6584(void)
{
    int error = 0;

    if (!lbl_803EBC00) {
        fn_801C6760();
        fn_801C6634(4);
        lbl_803EBC00 = 1;
    } else {
        error = 0x30001;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C65E4(void)
{
    int error = 0;

    if (lbl_803EBC00) {
        lbl_803EBC00 = 0;
    } else {
        error = 0x30002;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C6634(int alignment)
{
    int old = lbl_803EBC04;

    lbl_803EBC04 = alignment;
    return old;
}

int fn_801C6644(int size)
{
    return (size + (lbl_803EBC04 - 1)) & ~(lbl_803EBC04 - 1);
}
