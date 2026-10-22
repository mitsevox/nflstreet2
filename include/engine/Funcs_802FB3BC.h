#ifndef ENGINE_FUNCS_802FB3BC_H
#define ENGINE_FUNCS_802FB3BC_H

/* Five-word function tables 0x802FB3BC, 0x802FB3D0 and 0x802FB3E4: copied whole
   by 0x802334F0 and word by word by 0x80229718. The slots at +4, +8 and +12 are
   called through blrl by 0x80229760, 0x80229788 and 0x802297B0; parameter types
   follow those call sites (register use only). */
typedef struct Funcs_802FB3BC {
    int (*mpUnknown0)(void);
    int (*mpUnknown4)(void **ppData, void *p);
    int (*mpUnknown8)(int a, int b);
    int (*mpUnknown12)(void);
    int (*mpUnknown16)(void);
} Funcs_802FB3BC;

#endif
