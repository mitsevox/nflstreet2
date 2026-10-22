/* Chunk identifiers handled by the MAD codec: 'MADm', 'MADe', 'MADk'. */
static const int lbl_802B0054[3] = { 0x4D41446D, 0x4D414465, 0x4D41446B };

int fn_801DA4F8(int id)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (lbl_802B0054[i] == id) {
            return 1;
        }
    }
    return 0;
}
