/* Shader parameters of the TM renderer: the byte size of each parameter type. */

#include "engine/tmlib.h"

/* The size of each shader parameter type. */
static unsigned char _TMShaderParm_SizeTable[] = { 0, 2, 1, 1, 1, 1, 1, 2, 3, 4, 1, 1, 0 };

int TMShaderParmGetSize(int type)
{
    return _TMShaderParm_SizeTable[type];
}
