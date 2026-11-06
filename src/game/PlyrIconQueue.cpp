/* Queue of player icons drawn in a frame: records each icon's screen
   position and state and draws it. */
extern "C" void fn_801A105C(float x, float y, void *p, unsigned char value);

struct PlyrIconQueueEntry {
    int mUnknown0[17];
    float mUnknown44;
    float mUnknown48;
    void *mUnknown4C;
    unsigned char mUnknown50;
};

static PlyrIconQueueEntry _PlyrIconQueue_aEntries[16];
static int _PlyrIconQueue_iCount;

extern "C" void PlyrIconQueueAdd(float x, float y, void *p, unsigned char value)
{
    PlyrIconQueueEntry *pRecord = &_PlyrIconQueue_aEntries[_PlyrIconQueue_iCount++];

    pRecord->mUnknown44 = x;
    pRecord->mUnknown48 = y;
    pRecord->mUnknown4C = p;
    pRecord->mUnknown50 = value;
    fn_801A105C(x, y, p, value);
}

extern "C" void PlyrIconQueueReset(void)
{
    _PlyrIconQueue_iCount = 0;
}
