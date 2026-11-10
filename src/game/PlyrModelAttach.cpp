/* Player model assembly step: hands a pair of a player's model levels of detail to the
   LOD attach routine. */

extern "C" {
void PlyrModelLodAttach(void *a, void *b);

void PlyrModelAttachLod(void *a, void *b)
{
    PlyrModelLodAttach(a, b);
}
}
