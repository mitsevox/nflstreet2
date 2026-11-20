#ifndef ENGINE_EVMONADDLISTENER_H
#define ENGINE_EVMONADDLISTENER_H
#include "engine/Callback_80238570.h"
#ifdef __cplusplus
extern "C" {
#endif
void EvMonAddListener(int index, AudmonEventFn_t callback);
void EvMonRemoveListener(int index, AudmonEventFn_t callback);
#ifdef __cplusplus
}
#endif
#endif
