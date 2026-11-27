/* C library reentrancy data: the code-less file that holds the runtime's single reentrancy
   block (standard streams, "C" locale name, random seed and the exit-registration block) and
   the pointer through which printf, atexit and the multibyte conversion reach it. */

#include "engine/Reent_802622DC.h"

static Reent_802622DC impure_data = {
  0,
  &impure_data.mFiles[0],
  &impure_data.mFiles[1],
  &impure_data.mFiles[2],
  "",
  0,
  "C",
  "",
  1
};

Reent_802622DC *_impure_ptr = &impure_data;
