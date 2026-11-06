/* Reports the team ids of the two sides to a front-end screen. */
struct TeamPairArgs_t {
    int *mpUnknown0;
    int *mpUnknown4;
};

extern "C" {
int fn_800C8744(int team);

void TeamPairGetIds(int *pFirst, int *pSecond);
int TeamPairHandleMessage(int id, TeamPairArgs_t *pArgs);
}

extern "C" {

void TeamPairGetIds(int *pFirst, int *pSecond)
{
    *pFirst = fn_800C8744(1);
    *pSecond = fn_800C8744(0);
}

int TeamPairHandleMessage(int id, TeamPairArgs_t *pArgs)
{
    if (id == 0x80000001) {
        TeamPairGetIds(pArgs->mpUnknown0, pArgs->mpUnknown4);
        return 1;
    }
    return 0;
}

}
