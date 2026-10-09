/* Record fields exchanged by fn_80148424; only their extents are known. */
struct Block04_80148424 { char mUnknown[4]; };
struct Block28_80148424 { char mUnknown[0x28]; };
struct Block58_80148424 { char mUnknown[0x58]; };
struct Block0C_80148424 { char mUnknown[0xC]; };
struct Block4D8_80148424 { char mUnknown[0x4D8]; };
struct Block194_80148424 { char mUnknown[0x194]; };

struct Record_80148424 {
    char mPad000[0x150];
    Block58_80148424 mUnknown150;
    char mPad1A8[0x334];
    Block0C_80148424 mUnknown4DC;
    Block4D8_80148424 mUnknown4E8;
    Block194_80148424 mUnknown9C0;
    char mPadB54[0x90];
    Block04_80148424 mUnknownBE4;
    Block28_80148424 mUnknownBE8;
};

extern "C" {
void fn_801D31F0(void *pDst, const void *pSrc, int size);

/* Exchanges six fields of two records through fn_801D31F0. */
void fn_80148424(Record_80148424 *pA, Record_80148424 *pB)
{
    Block04_80148424 t0;
    Block28_80148424 t1;
    Block58_80148424 t2;
    Block0C_80148424 t3;
    Block4D8_80148424 t4;
    Block194_80148424 t5;

    fn_801D31F0(&t0, &pA->mUnknownBE4, sizeof(t0));
    fn_801D31F0(&pA->mUnknownBE4, &pB->mUnknownBE4, sizeof(t0));
    fn_801D31F0(&pB->mUnknownBE4, &t0, sizeof(t0));
    fn_801D31F0(&t1, &pA->mUnknownBE8, sizeof(t1));
    fn_801D31F0(&pA->mUnknownBE8, &pB->mUnknownBE8, sizeof(t1));
    fn_801D31F0(&pB->mUnknownBE8, &t1, sizeof(t1));
    fn_801D31F0(&t2, &pA->mUnknown150, sizeof(t2));
    fn_801D31F0(&pA->mUnknown150, &pB->mUnknown150, sizeof(t2));
    fn_801D31F0(&pB->mUnknown150, &t2, sizeof(t2));
    fn_801D31F0(&t3, &pA->mUnknown4DC, sizeof(t3));
    fn_801D31F0(&pA->mUnknown4DC, &pB->mUnknown4DC, sizeof(t3));
    fn_801D31F0(&pB->mUnknown4DC, &t3, sizeof(t3));
    fn_801D31F0(&t4, &pA->mUnknown4E8, sizeof(t4));
    fn_801D31F0(&pA->mUnknown4E8, &pB->mUnknown4E8, sizeof(t4));
    fn_801D31F0(&pB->mUnknown4E8, &t4, sizeof(t4));
    fn_801D31F0(&t5, &pA->mUnknown9C0, sizeof(t5));
    fn_801D31F0(&pA->mUnknown9C0, &pB->mUnknown9C0, sizeof(t5));
    fn_801D31F0(&pB->mUnknown9C0, &t5, sizeof(t5));
}
}
