/* The table of cheats active in the current game, gathered from the cheats each participating user
   has enabled. */
extern "C" {
void CheatSelectSlot(int a);
int CheatIsEnabled(int index);
}

static unsigned char _CheatFlags_abSet[55];

extern "C" void CheatFlagsAddUser(int a)
{
    unsigned int i = 0;

    CheatSelectSlot(a);
    while (i < 55) {
        _CheatFlags_abSet[i] |= CheatIsEnabled(i);
        i++;
    }
}

extern "C" void CheatFlagsClear(void)
{
    unsigned int i;

    for (i = 0; i < 55; i++) {
        _CheatFlags_abSet[i] = 0;
    }
}

extern "C" unsigned char CheatFlagsIsSet(int index) { return _CheatFlags_abSet[index]; }
