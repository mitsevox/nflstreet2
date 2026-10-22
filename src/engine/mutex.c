extern void fn_801F80E8(void **ppSemaphore);
extern int fn_801F8128(void **ppSemaphore);
extern void fn_801F8150(void **ppSemaphore);
extern void fn_801F8174(void **ppSemaphore);

void fn_801F7738(void)
{
}

void *fn_801F773C(void)
{
    void *semaphore;

    fn_801F80E8(&semaphore);
    return semaphore;
}

void fn_801F7764(void *semaphore)
{
    fn_801F8174(&semaphore);
}

void fn_801F778C(void *semaphore)
{
    fn_801F8128(&semaphore);
}

void fn_801F77B4(void *semaphore)
{
    fn_801F8150(&semaphore);
}
