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

void fn_8019B460(int id);
void fn_8019B5D4(void);
void fn_8019B614(void);
}

static int lbl_803EB7B8 = -1;
static char *lbl_803EB7BC = 0;

extern "C" {

void fn_8019B460(int id)
{
    switch (id) {
    case 0:
        fn_8023633C(lbl_802EF31C);
        lbl_803EB7B8 = id;
        break;
    case 2:
        fn_8023633C(lbl_802F052C);
        lbl_803EB7B8 = 1;
        break;
    case 3:
        fn_8023633C(lbl_802EF7A0);
        lbl_803EB7B8 = 2;
        break;
    case 1:
        fn_8023633C(lbl_802EFC24);
        lbl_803EB7B8 = 3;
        break;
    case 4:
        fn_8023633C(lbl_802F00A8);
        lbl_803EB7B8 = id;
        break;
    case 5:
        fn_8023633C(lbl_802F09B0);
        lbl_803EB7B8 = id;
        break;
    case 6:
        fn_8023633C(lbl_802F0E34);
        lbl_803EB7B8 = id;
        break;
    case 9:
        fn_8023633C(lbl_802F12B8);
        lbl_803EB7B8 = 9;
        break;
    case 7:
        fn_8023633C(lbl_802F173C);
        lbl_803EB7B8 = id;
        break;
    case 8:
        fn_8023633C(lbl_802F1BC0);
        lbl_803EB7B8 = id;
        break;
    case 10:
        fn_8023633C(lbl_802F2044);
        lbl_803EB7B8 = id;
        break;
    case 11:
        fn_8023633C(lbl_802F24C8);
        lbl_803EB7B8 = id;
        break;
    }
    lbl_803EB7BC = lbl_802EEE7C;
    fn_8019B614();
}

void fn_8019B5D4(void)
{
    lbl_803EB7BC = lbl_802EEEE0;
    fn_8023633C(lbl_802EEDD0);
    lbl_803EB7B8 = 0;
    fn_8019B614();
}

void fn_8019B614(void)
{
    fn_802353CC(lbl_803EB7BC + 64);
    fn_802353D0(lbl_803EB7BC);
}

}
