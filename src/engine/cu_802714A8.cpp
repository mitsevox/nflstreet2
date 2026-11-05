/* Audio decoder classes (neutral file name): a base and a derived decoder class with their
   virtual functions; the base class reads MPEG-audio frame headers. */

#include "engine/sndlib.h"


void Class_80271640::vfn_05(unsigned char *data)
{
    m20 = data;
    m24 = data;
    m28 = data;
    m2C = 0;
    m30 = 0;
}

Class_80271640::~Class_80271640()
{
    if (m43 != 0) {
        vfn_04();
    }
}

void Class_80271640::fn_80271698()
{
    if (lbl_80300044 == 0) {
        m4C = lbl_803B53E4(m44 * 0x900);
        memset(m4C, 0, m44 * 0x900);
    }
}

void Class_80271640::fn_80271710()
{
    lbl_803B53E8(m4C);
}

int Class_80271640::vfn_02(unsigned int header)
{
    unsigned int id;
    int channels;
    unsigned int rate;
    int layer;
    int lsf;

    if ((header & 0xFFE00000) != 0xFFE00000) {
        return -1;
    }
    id = (header >> 19) & 1;
    m14 = 4 - ((header >> 17) & 3);
    m3A = id;
    m3B = (header >> 16) & 1;
    m3C = (header >> 12) & 0xF;
    m3E = (header >> 9) & 1;
    m3F = (header >> 6) & 3;
    m40 = (header >> 4) & 3;
    m41 = (header >> 3) & 1;
    m42 = (header >> 2) & 1;
    if (header & 0x100000) {
        m37 = id ^ 1;
        m36 = 0;
    } else {
        m36 = 1;
        m37 = 1;
    }
    if (m36 != 0) {
        m3D = ((header >> 10) & 3) + 6;
    } else {
        m3D = ((header >> 10) & 3) + m37 * 3;
        if (m37 == 0) {
            m38 = ((header >> 10) & 3) + 3;
        } else {
            m38 = (header >> 10) & 3;
        }
    }
    channels = 2;
    if (m3F == 3) {
        channels = 1;
    }
    m44 = channels;
    rate = lbl_802B7A98[m3D];
    m4 = rate;
    m0 = rate;
    if (m3C == 0) {
        return -1;
    }
    lsf = m37;
    layer = m14;
    mC = lbl_802B7AF0[lsf][layer - 1][m3C];
    if (layer == 1) {
        m10 = (mC * 12000 / (int)rate + m3E) * 4 - 4;
    } else {
        m10 = mC * 144000 / (int)rate;
        if (layer == 3 && lsf != 0) {
            m10 >>= 1;
        }
        if (m3E != 0) {
            m10++;
        }
        m10 -= 4;
    }
    return 0;
}

int Class_80271640::fn_80271918()
{
    unsigned int header;
    unsigned char *p = m20;

    if (p == 0) {
        header = m48;
    } else {
        header = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
    }
    if (vfn_02(header) == -1) {
        return -1;
    }
    return 0;
}

int Class_80271640::vfn_06()
{
    if (m14 == 1) {
        m8 = m44 * 768;
    } else {
        m8 = m44 * 2304;
        if (m14 == 3 && m37 != 0) {
            m8 >>= 1;
        }
    }
    m34 = 1;
    m35 = 1;
    return 0;
}

int fn_80271A04(void)
{
    return 0;
}

int Class_80271640::vfn_03(unsigned char *data)
{
    if (m43 != 0) {
        vfn_04();
    }
    m43 = 1;
    m20 = data;
    m24 = data;
    if (data == 0) {
        return -1;
    }
    if (fn_80271918() != 0) {
        return -1;
    }
    fn_80271698();
    vfn_06();
    fn_80271AB8();
    return 0;
}

void Class_80271640::fn_80271AB8()
{
    m28 = m20;
    m2C = 0;
    m30 = 0;
}

int Class_80271640::vfn_04()
{
    if (m43 != 0) {
        m43 = m48 = 0;
        fn_80271A04();
        fn_80271710();
    }
    return 0;
}

Class_80271B74::~Class_80271B74()
{
    if (m1B0 != 0) {
        lbl_803B53E8(m1B0);
    }
}
