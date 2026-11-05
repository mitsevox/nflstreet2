/* Host-file device stubs: every entry point is empty and reports nothing read or written. */

void FileHostInit(int count)
{
}

void FileHostShutdown(void)
{
}

int FileHostOpen(const char *pName, int mode)
{
    return 0;
}

void FileHostClose(int handle)
{
}

int FileHostRead(int handle, void *pDst, int size)
{
    return 0;
}

int FileHostWrite(int handle, const void *pSrc, int size)
{
    return 0;
}

int FileHostLSeek(int handle, int offset, int whence)
{
    return 0;
}

int FileHostGetSize(int handle)
{
    return 0;
}
