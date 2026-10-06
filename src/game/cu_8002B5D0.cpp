#include "game/Object_800785C0.h"
#include "game/fn_8007F828.h"

extern "C" {
int fn_8002B5B0(void);
void fn_8002B5B8(int value);
void fn_8002B5C0(int value);
void fn_8002B714(int value);
int fn_80025700(void);
int fn_800634E4(void);
void fn_800634F8(void);
void fn_80077F24(void);
int fn_80078620(int id, int *pA, int *pB);
void fn_80078738(int id, int a, int b, int c);
void fn_80078844(int value);
void fn_8007897C(int value);
int fn_8007984C(Object_800785C0 *pRecord);
int fn_80079864(Object_800785C0 *pRecord, int id);

void fn_8002B5D0(int mode, int side)
{
    if (fn_8002B5B0() == 2) {
        switch (fn_80025700()) {
        case 0: {
            Object_800785C0 *pRecord = fn_800785C0();

            if (mode == 2) {
                mode = 1;
                if (fn_8007984C(pRecord)) {
                    mode = side > 2;
                }
            }
            fn_8002B5B8(mode);
            if (mode == 0) {
                int a;
                int b;
                int result;

                if (fn_80078620(pRecord->mUnknown0, &a, &b) != 2) {
                    fn_80078844(-pRecord->mUnknown196);
                }
                if (fn_8007984C(pRecord)) {
                    fn_8002B5C0(side);
                }
                result = 2;
                if (fn_80079864(pRecord, 4)) {
                    result = 3;
                }
                fn_80078738(pRecord->mUnknown0, result, side, fn_8007F828(0));
            }
            break;
        }
        case 1:
            fn_8002B5B8(mode);
            if (mode == 0) {
                fn_800634F8();
                if (fn_800634E4()) {
                    fn_8007897C(1);
                    fn_8002B714(34);
                }
            }
            break;
        }
        fn_80077F24();
    }
}

}
