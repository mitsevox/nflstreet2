/* File I/O device for the T3DB game database: open, close, read, write and seek callbacks
   that load a database from, or save it to, a file on a file device. */
#include "engine/tdbiofio.h"

extern int FileOpenFileDevice(const char *pName, int device);
extern int FileClose(int handle);
extern int FileSeek(int handle, int offset, unsigned int whence);
extern int FileReadCallback(int handle, void *pBuffer, int size, void (*pCallback)(int, int, int));
extern int FilePerformWrite(int handle, int pos, void *pBuffer, int size);

typedef struct TDbIOFioFile_t {
    int mHandle;
    int mPos;
    unsigned int mSize;
} TDbIOFioFile_t;

/* Open the named file for writing or reading and start at its beginning. */
static int _IOFio_Open(void *pHandle, unsigned int size, void *pName, int mode)
{
    TDbIOFioFile_t *pFile = pHandle;
    int handle;

    if (mode)
        handle = FileOpenFileDevice(pName, 44);
    else
        handle = FileOpenFileDevice(pName, 36);
    if (handle < 0)
        return 36;
    pFile->mHandle = handle;
    pFile->mPos = 0;
    pFile->mSize = size;
    return 0;
}

/* Close the file. */
static int _IOFio_Close(void *pHandle)
{
    TDbIOFioFile_t *pFile = pHandle;

    if (pFile->mHandle < 0)
        return 3;
    if (FileClose(pFile->mHandle) != 0)
        return 36;
    return 0;
}

/* Write bytes at the current position and advance it by the count written. */
static int _IOFio_Write(void *pHandle, void *pSrc, unsigned int size, unsigned int *pWritten)
{
    TDbIOFioFile_t *pFile = pHandle;
    int count;

    if (pFile->mHandle < 0)
        return 3;
    count = FilePerformWrite(pFile->mHandle, pFile->mPos, pSrc, size);
    if (count < 0) {
        *pWritten = 0;
        return 36;
    }
    *pWritten = count;
    pFile->mPos += count;
    return 0;
}

/* Read bytes from the file and advance the position by the count read. */
static int _IOFio_Read(void *pHandle, void *pDst, unsigned int size, unsigned int *pRead)
{
    TDbIOFioFile_t *pFile = pHandle;
    int count;

    if (pFile->mHandle < 0)
        return 3;
    count = FileReadCallback(pFile->mHandle, pDst, size, 0);
    if (count < 0) {
        *pRead = 0;
        return 36;
    }
    *pRead = count;
    pFile->mPos += count;
    return 0;
}

/* Move the file position relative to the current one. */
static int _IOFio_Seek(void *pHandle, int offset)
{
    TDbIOFioFile_t *pFile = pHandle;

    if (pFile->mHandle < 0)
        return 3;
    if (FileSeek(pFile->mHandle, offset, 1) != 0)
        return 36;
    pFile->mPos += offset;
    return 0;
}

/* Report no padding beyond the serialized database bytes. */
static unsigned int _IOFio_CalcPadding(unsigned int size)
{
    return 0;
}

TDbIODevice_t tdbiofioCallback = {
    _IOFio_Open,
    _IOFio_Close,
    _IOFio_Read,
    _IOFio_Write,
    _IOFio_Seek,
    _IOFio_CalcPadding,
    12
};
