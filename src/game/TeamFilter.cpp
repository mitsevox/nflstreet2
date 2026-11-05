/* Holds the team id that filters team queries (0x3FF for no team). */

static int _TeamFilter_iTeam = 0x3FF;

extern "C" int TeamFilterGet(void)
{
    return _TeamFilter_iTeam;
}

extern "C" void TeamFilterSet(int value)
{
    _TeamFilter_iTeam = value;
}
