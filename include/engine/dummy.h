#ifndef ENGINE_DUMMY_H
#define ENGINE_DUMMY_H

/* The SN runtime console writers of src/engine/dummy.c. */

#ifdef __cplusplus
extern "C" {
#endif

int __sn_serialp(void *buf, int len);
int _write(int fd, void *buf, int len);
int write(int fd, void *buf, int len);

#ifdef __cplusplus
}
#endif

#endif
