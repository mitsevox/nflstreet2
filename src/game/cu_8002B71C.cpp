#include "game/Object_800785C0.h"
#include "game/Object_8017886C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801FCE10.h"

extern "C" {
void fn_8002B5B8(int value);
int fn_80025708(void);
void fn_8007CAEC(int index, int value);
void fn_800A7A0C(int a);
void fn_80177F88(int a);
void fn_8017833C(int value);
void fn_80178354(int value);
void fn_801787FC(int which, short value);
void fn_8017885C(void);
void fn_80178878(const Object_8017886C *p);
void fn_80179150(void);
float fn_80237260(int stream);

void fn_8002B71C(void)
{
    Object_8017886C info;

    fn_80179150();
    if (fn_80025708()) {
        fn_801787FC(0, fn_800785C0()->mUnknown1AC);
        fn_801787FC(1, fn_800785C0()->mUnknown1A8);
        fn_801FCE10(0, "update 'FNIG' set 'CSAG' = \x82 and 'CSHG' = \x82\n",
                    fn_800785C0()->mUnknown1A8, fn_800785C0()->mUnknown1AC);
        fn_8017885C();
        fn_801C1F94(&info, 0, sizeof(info));
        fn_80178878(&info);
        fn_80177F88(fn_800785C0()->mUnknown1C1);
        if (fn_800785C0()->mUnknown1B8 == 0) {
            fn_8017833C(1);
            fn_80178354(1);
        } else if (fn_800785C0()->mUnknown1B8 == 1) {
            fn_8017833C(0);
            fn_80178354(0);
        } else if (fn_80237260(1) < 0.5f) {
            fn_8017833C(1);
            fn_80178354(1);
            fn_8007CAEC(2, 1);
        } else {
            fn_8017833C(0);
            fn_80178354(0);
            fn_8007CAEC(2, 0);
        }
        fn_800A7A0C(0);
        fn_800A7A0C(1);
        fn_8002B5B8(2);
    } else {
        fn_801787FC(0, 0);
        fn_801787FC(1, 0);
        fn_8017885C();
        fn_801FCE10(0, "update 'FNIG' set 'CSAG' = \x82 and 'CSHG' = \x82\n", 0, 0);
        fn_801C1F94(&info, 0, sizeof(info));
        fn_80178878(&info);
        fn_80177F88(1);
        fn_8017833C(1);
        fn_80178354(1);
        fn_8007CAEC(2, 1);
        fn_8002B5B8(2);
    }
}

}
