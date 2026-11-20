#ifndef ENGINE_DBNIOMMODEFUNCS_H
#define ENGINE_DBNIOMMODEFUNCS_H

/* The table of five database functions of one game mode. */
typedef struct DbNiomModeFuncs_t {
    int (*mpUnknown0)(void);
    int (*mpUnknown4)(void **ppData, void *p);
    int (*mpUnknown8)(int a, int b);
    int (*mpUnknown12)(void);
    int (*mpUnknown16)(void);
} DbNiomModeFuncs_t;

#endif
