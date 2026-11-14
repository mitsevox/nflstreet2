/*
 * The lock pair of the game database's cursor holder. The holder takes the lock before it
 * allocates itself and opens its cache handle, and gives it back after closing that handle;
 * in this build both calls do nothing and report success.
 */
int DbLockAcquire(void)
{
    return 0;
}

int DbLockRelease(void)
{
    return 0;
}
