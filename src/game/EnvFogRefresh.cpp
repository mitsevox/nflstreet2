/* Reapplies the level fog settings once per frame. */

extern "C" {
void EnvApplyFog(void);

void EnvFogRefresh(void)
{
    EnvApplyFog();
}
}
