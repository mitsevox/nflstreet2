#ifndef GAME_DEMOLAUNCH_H
#define GAME_DEMOLAUNCH_H

extern "C" void DemoLaunchSetFlag(unsigned char value);
extern "C" bool DemoLaunchIsFlagSet(void);
extern "C" int DemoLaunchIsAllowed(void);

#endif
