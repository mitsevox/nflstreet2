#include "game/QueryStatus.h"
#include "game/fn_801FCE10.h"

/* Record filled by fn_8002A9B8; fn_8002ADE0 allocates and clears 0x100 bytes for it. */
struct Record_8002A9B8 {
    int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
    unsigned char mUnknownB;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    unsigned char mUnknown16;
    unsigned char mUnknown17;
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    unsigned char mUnknown1A;
    unsigned char mUnknown1B;
    unsigned short mUnknown1C;
    unsigned char mUnknown1E;
    unsigned char mUnknown1F;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
    unsigned char mUnknown2A;
    unsigned char mUnknown2B;
    unsigned char mUnknown2C;
    unsigned char mUnknown2D;
    unsigned char mUnknown2E;
    unsigned char mUnknown2F;
    unsigned char mUnknown30;
    unsigned char mUnknown31;
    unsigned short mUnknown32;
    unsigned char mUnknown34;
    unsigned char mUnknown35;
    unsigned char mUnknown36;
    unsigned char mUnknown37;
    unsigned char mUnknown38;
    unsigned char mUnknown39;
    unsigned char mUnknown3A;
    unsigned char mUnknown3B;
    unsigned char mUnknown3C;
    unsigned char mUnknown3D;
    unsigned char mUnknown3E;
    unsigned char mUnknown3F;
    unsigned char mUnknown40;
    unsigned char mUnknown41;
    unsigned char mUnknown42;
    unsigned char mUnknown43;
    unsigned short mUnknown44;
    unsigned char mUnknown46;
    unsigned char mUnknown47;
    unsigned char mUnknown48;
    unsigned char mUnknown49;
    unsigned char mUnknown4A;
    unsigned char mUnknown4B;
    unsigned char mUnknown4C;
    unsigned char mUnknown4D;
    unsigned char mUnknown4E;
    unsigned char mUnknown4F;
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    unsigned short mUnknown52;
    unsigned char mUnknown54;
    char mUnknown55[3];
    char mUnknown58[12];
    char mUnknown64[18];
    char mUnknown76[138];
};

extern "C" {
int fn_8002A9B8(int id, void *pBuffer)
{
    Record_8002A9B8 *pRecord = (Record_8002A9B8 *)pBuffer;
    int found = 0;
    int result = fn_801FCE10(0,
        "use 'TATS' select 'EGAP' into \x83 and "
        "'IGAP' into \x83 and "
        "'OTAP' into \x83 and "
        "'KLBP' into \x83 and "
        "'OPBP' into \x83 and "
        "'KTBP' into \x83 and "
        "'OTBP' into \x83 and "
        "'LECP' into \x83 and "
        "'VOCP' into \x83 and "
        "'HTCP' into \x83 and "
        "'TFDP' into \x83 and "
        "'WBEP' into \x83 and "
        "'PTEP' into \x83 and "
        "'RWEP' into \x83 and "
        "'AEFP' into \x83 and "
        "'BEFP' into \x83 and "
        "'YEFP' into \x83 and "
        "'HFFP' into \x83 and "
        "'CHFP' into \x83 and "
        "'CJFP' into \x83 and "
        "'PLFP' into \x83 and "
        "'TLFP' into \x83 and "
        "'OMFP' into \x83 and "
        "'ONFP' into \x83 and "
        "'DIGP' into \x84 and "
        "'1AHP' into \x83 and "
        "'NAHP' into \x83 and "
        "'RAHP' into \x83 and "
        "'TAHP' into \x83 and "
        "'CDHP' into \x83 and "
        "'TGHP' into \x83 and "
        "'DNHP' into \x83 and "
        "'ROHP' into \x83 and "
        "'PMIP' into \x83 and "
        "'TCJP' into \x83 and "
        "'NEJP' into \x83 and "
        "'MUJP' into \x83 and "
        "'XELP' into \x83 and "
        "'THLP' into \x83 and "
        "'GILP' into \x83 and "
        "'LILP' into \x83 and "
        "'OTLP' into \x83 and "
        "'LULP' into \x83 and "
        "'LWLP' into \x83 and "
        "'DEMP' into \x80 and "
        "'DIOP' into \x84 and "
        "'RVOP' into \x83 and "
        "'TNPP' into \x83 and "
        "'SOPP' into \x83 and "
        "'NSPP' into \x83 and "
        "'SSPP' into \x83 and "
        "'TARP' into \x83 and "
        "'CFRP' into \x83 and "
        "'DHRP' into \x83 and "
        "'TLRP' into \x83 and "
        "'YTRP' into \x83 and "
        "'OHSP' into \x83 and "
        "'IKSP' into \x83 and "
        "'COSP' into \x83 and "
        "'APSP' into \x83 and "
        "'DPSP' into \x83 and "
        "'TRSP' into \x83 and "
        "'PXSP' into \x84 and "
        "'KATP' into \x83 and "
        "'DBTP' into \x83 and "
        "'DFTP' into \x83 and "
        "'RAUP' into \x83 and "
        "'LCUP' into \x83 and "
        "'TGWP' into \x83 and "
        "'TRWP' into \x83 and "
        "'TBYP' into \x83 and "
        "'1TGS' into \x83 and "
        "'2TGS' into \x83 and "
        "'3TGS' into \x83 and "
        "'4TGS' into \x83 and "
        "'DIGT' into \x84 and "
        "'ITGT' into \x83 and "
        "'ANFP' into \x88 and "
        "'ANLP' into \x88 and "
        "'NKNP' into \x88 from 'YALP' where ('DIGP' = \x85)\n",
        &pRecord->mUnknown4, &pRecord->mUnknown5, &pRecord->mUnknown6,
        &pRecord->mUnknown7, &pRecord->mUnknown8, &pRecord->mUnknown9,
        &pRecord->mUnknownA, &pRecord->mUnknownB, &pRecord->mUnknownC,
        &pRecord->mUnknownD, &pRecord->mUnknownE, &pRecord->mUnknownF,
        &pRecord->mUnknown10, &pRecord->mUnknown11, &pRecord->mUnknown12,
        &pRecord->mUnknown13, &pRecord->mUnknown14, &pRecord->mUnknown15,
        &pRecord->mUnknown16, &pRecord->mUnknown17, &pRecord->mUnknown18,
        &pRecord->mUnknown19, &pRecord->mUnknown1A, &pRecord->mUnknown1B,
        &pRecord->mUnknown1C, &pRecord->mUnknown1E, &pRecord->mUnknown1F,
        &pRecord->mUnknown20, &pRecord->mUnknown21, &pRecord->mUnknown22,
        &pRecord->mUnknown23, &pRecord->mUnknown24, &pRecord->mUnknown25,
        &pRecord->mUnknown26, &pRecord->mUnknown27, &pRecord->mUnknown28,
        &pRecord->mUnknown29, &pRecord->mUnknown2A, &pRecord->mUnknown2B,
        &pRecord->mUnknown2C, &pRecord->mUnknown2D, &pRecord->mUnknown2E,
        &pRecord->mUnknown2F, &pRecord->mUnknown30, &pRecord->mUnknown31,
        &pRecord->mUnknown32, &pRecord->mUnknown34, &pRecord->mUnknown35,
        &pRecord->mUnknown36, &pRecord->mUnknown37, &pRecord->mUnknown38,
        &pRecord->mUnknown39, &pRecord->mUnknown3A, &pRecord->mUnknown3B,
        &pRecord->mUnknown3C, &pRecord->mUnknown3D, &pRecord->mUnknown3E,
        &pRecord->mUnknown3F, &pRecord->mUnknown40, &pRecord->mUnknown41,
        &pRecord->mUnknown42, &pRecord->mUnknown43, &pRecord->mUnknown44,
        &pRecord->mUnknown46, &pRecord->mUnknown47, &pRecord->mUnknown48,
        &pRecord->mUnknown49, &pRecord->mUnknown4A, &pRecord->mUnknown4B,
        &pRecord->mUnknown4C, &pRecord->mUnknown4D, &pRecord->mUnknown4E,
        &pRecord->mUnknown4F, &pRecord->mUnknown50, &pRecord->mUnknown51,
        &pRecord->mUnknown52, &pRecord->mUnknown54, pRecord->mUnknown58,
        pRecord->mUnknown64, pRecord->mUnknown76, id);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        pRecord->mUnknown0 = 1;
        found = 1;
    }
    return found;
}
}
