#ifndef ENGINE_TIBNEW_H
#define ENGINE_TIBNEW_H

void *operator new(unsigned int size, int heap);
void *operator new[](unsigned int size, int heap);

#endif
