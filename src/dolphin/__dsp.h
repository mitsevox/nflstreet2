#ifndef __DSP_H__
#define __DSP_H__

#include <dolphin/dsp.h>

#define DSP_TASK_FLAG_CLEARALL 0x00000000
#define DSP_TASK_FLAG_ATTACHED 0x00000001
#define DSP_TASK_FLAG_CANCEL 0x00000002

#define DSP_TASK_STATE_INIT 0
#define DSP_TASK_STATE_RUN 1
#define DSP_TASK_STATE_YIELD 2
#define DSP_TASK_STATE_DONE 3

extern DSPTaskInfo* __DSP_curr_task;
extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* __DSP_last_task;
extern DSPTaskInfo* __DSP_tmp_task;
extern DSPTaskInfo* __DSP_rude_task;
extern BOOL __DSP_rude_task_pending;

void __DSPHandler(__OSInterrupt interrupt, OSContext* context);
void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next);
void __DSP_boot_task(DSPTaskInfo* task);
void __DSP_insert_task(DSPTaskInfo* task);
void __DSP_add_task(DSPTaskInfo* task);
void __DSP_remove_task(DSPTaskInfo* task);
void __DSP_debug_printf(const char* fmt, ...);

#endif
