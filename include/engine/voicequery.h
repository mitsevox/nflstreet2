#ifndef ENGINE_VOICEQUERY_H
#define ENGINE_VOICEQUERY_H

#ifdef __cplusplus
extern "C" {
#endif

int AudioVoiceForwardData(int key, int value, void *data, int offset);
int AudioVoiceGetMaxMetric(int key);

#ifdef __cplusplus
}
#endif

#endif
