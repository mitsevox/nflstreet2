/* 32-byte lock taken by fn_801F8014 and released by fn_801F809C. */
struct Lock_801F8014 {
    int mUnknown0[8];
};

/* Buffer owned by Class_80054EDC; fn_80054F50 releases it. */
struct Buffer_80054EDC {
    bool IsOpen() const { return mpData != 0; }

    void *mpData;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC;
};

class Class_80054EDC {
public:
    virtual ~Class_80054EDC();
    void fn_80054F50();

    Buffer_80054EDC mBuffer;
    Lock_801F8014 mLock;
};

extern "C" {
int fn_801D2BD0(void *p);
void fn_801F8014(Lock_801F8014 *pLock);
void fn_801F809C(Lock_801F8014 *pLock);
void fn_801F80D0(Lock_801F8014 *pLock);
}

Class_80054EDC::~Class_80054EDC()
{
    if (mBuffer.IsOpen()) {
        fn_80054F50();
    }
    fn_801F80D0(&mLock);
}

void Class_80054EDC::fn_80054F50()
{
    fn_801F8014(&mLock);
    if (mBuffer.IsOpen()) {
        fn_801D2BD0(mBuffer.mpData);
        mBuffer.mUnknown8 = 0;
        mBuffer.mUnknown4 = 0;
        mBuffer.mpData = 0;
        mBuffer.mUnknownC = 0;
    }
    fn_801F809C(&mLock);
}
