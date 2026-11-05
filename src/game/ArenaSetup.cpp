/* Sets up the memory pools when the game arena is created and releases them when it is destroyed. */

extern "C" {
void BootSetupMemPools(void);
void BootShutdownMemPools(void);
}

static unsigned char sInitialized = 0;

extern "C" void ArenaSetupInit(void)
{
    sInitialized = 1;
    BootSetupMemPools();
}

extern "C" void ArenaSetupShutdown(void)
{
    BootShutdownMemPools();
    sInitialized = 0;
}
