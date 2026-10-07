#ifndef GAME_RECORD_80082B18_H
#define GAME_RECORD_80082B18_H

/* 0x120-byte record initialised by fn_80082B18, filled from the 'ECAF' and
   'YALP' tables by fn_80082D30 and fn_80082E48, and written back by
   fn_8008318C. Each word holds the column named in the comments. */
struct Record_80082B18 {
    int mUnknown00;   /* 'DIGP', 'DIOP' */
    char *mUnknown04; /* 'ANFP' */
    char *mUnknown08; /* 'ANLP' */
    char *mUnknown0C;
    int mUnknown10; /* 'SOPP' */
    int mUnknown14; /* 'OPBP' */
    int mUnknown18; /* 'NEJP' */
    int mUnknown1C; /* 'RVOP' */
    int mUnknown20; /* 'EGAP' */
    int mUnknown24; /* 'LILP' */
    int mUnknown28; /* 'IKSP' */
    int mUnknown2C; /* 'CFRP' */
    int mUnknown30; /* 'XELP' */
    int mUnknown34; /* 'PTEP' */
    int mUnknown38; /* 'THLP' */
    int mUnknown3C; /* 'HFFP' */
    int mUnknown40; /* 'BEFP' */
    int mUnknown44; /* 'AEFP' */
    int mUnknown48; /* 'OMFP' */
    int mUnknown4C; /* 'PLFP' */
    int mUnknown50; /* 'CJFP' */
    int mUnknown54; /* 'YEFP' */
    int mUnknown58; /* 'ONFP' */
    int mUnknown5C; /* 'RAHP' */
    int mUnknown60; /* '1AHP' */
    int mUnknown64; /* 'CHFP' */
    int mUnknown68; /* 'PXSP' */
    int mUnknown6C; /* 'TAHP' */
    int mUnknown70; /* 'ROHP' */
    int mUnknown74; /* 'RWEP' */
    int mUnknown78; /* 'APSP' */
    int mUnknown7C; /* 'TRSP' */
    int mUnknown80; /* 'TNPP' */
    int mUnknown84; /* 'RAUP' */
    int mUnknown88; /* 'LULP' */
    int mUnknown8C; /* 'WBEP' */
    int mUnknown90; /* 'DNHP' */
    int mUnknown94; /* 'DHRP' */
    int mUnknown98; /* 'TRWP' */
    int mUnknown9C; /* 'LWLP' */
    int mUnknownA0; /* 'COSP' */
    int mUnknownA4; /* 'OHSP' */
    int mUnknownA8; /* 'TARP' */
    int mUnknownAC; /* 'OTAP' */
    int mUnknownB0; /* 'TLRP' */
    int mUnknownB4; /* 'OTLP' */
    int mUnknownB8; /* 'DBTP' */
    int mUnknownBC; /* 'DFTP' */
    int mUnknownC0; /* 'CDHP' */
    int mUnknownC4; /* 'DPSP' */
    int mUnknownC8; /* 'IGAP' */
    int mUnknownCC; /* 'MUJP' */
    int mUnknownD0; /* 'HTCP' */
    int mUnknownD4; /* 'KTBP' */
    int mUnknownD8; /* 'KATP' */
    int mUnknownDC; /* 'SSPP' */
    int mUnknownE0; /* 'KLBP' */
    int mUnknownE4; /* 'VOCP' */
    int mUnknownE8; /* 'TFDP' */
    int mUnknownEC; /* 'PMIP' */
    int mUnknownF0; /* 'NSPP' */
    int mUnknownF4; /* 'LECP' */
    int mUnknownF8; /* 'LCUP' */
    int mUnknownFC; /* '1TGS' */
    int mUnknown100; /* '2TGS' */
    int mUnknown104; /* '3TGS' */
    int mUnknown108; /* '4TGS' */
    int mUnknown10C; /* 'TGHP' */
    int mUnknown110; /* 'TGWP' */
    int mUnknown114; /* 'NAHP' */
    int mUnknown118; /* 'TBYP' */
    int mUnknown11C; /* 'TLFP' */
};


#endif
