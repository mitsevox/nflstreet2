/* Lays out the memory pools in the OS arena when the system module starts and releases them when it shuts down. */

extern "C" {
void BootSetupMemPools(void);
void BootShutdownMemPools(void);
}

static unsigned char _ArenaSetup_bInitialized = 0;

extern "C" void ArenaSetupInit(void)
{
    _ArenaSetup_bInitialized = 1;
    BootSetupMemPools();
}

extern "C" void ArenaSetupShutdown(void)
{
    BootShutdownMemPools();
    _ArenaSetup_bInitialized = 0;
}
