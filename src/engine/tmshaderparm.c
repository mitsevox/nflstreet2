/* Shader parameters of the TM renderer: the byte size of each parameter type. */

#include "engine/tmlib.h"

extern unsigned char lbl_802F9D7C[];

int TMShaderParmGetSize(int type)
{
    return lbl_802F9D7C[type];
}
