/* Partial source: the per-user databases and their 'FNIU' user-info table: create, load, find and update the user records. */

#include "engine/dbteams.h"
#include "engine/tdbext.h"
#include "engine/dbutil.h"
#include "engine/fn_801F9134.h"
#include "engine/cu_80229270.h"

#include "engine/Funcs_802FB3BC.h"
#include "engine/llmemory.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"
#include "engine/t3db.h"
#include "engine/t3db_cols.h"
#include "game/fn_8022F478.h"

#include <string.h>

struct CardStreamTarget;
struct SaveStreamOps_t;
#include "engine/Entry_802FB300.h"
extern char lbl_802B5C8C[];
extern char lbl_803A1C60[];
extern float lbl_803A20A4[][13];
extern char *lbl_803EC0A4;
extern int lbl_803EC0A8;
extern int lbl_803EC0A0;
extern char *lbl_803EC0B4;
extern int lbl_803EC0B8;
extern int lbl_803EC0B0;
extern int lbl_803EC0C8;
extern char *lbl_803EC0CC;
extern int lbl_803EC0D0;
extern int lbl_803EC0D4;
extern unsigned char lbl_803EC0D8;
extern Entry_802FB300 lbl_802FB300[];
extern int fn_801F91AC(int handle, int a, int b);
extern int fn_801F9718(int db, int tbl, TDbCol_801F9718 *pCols, void *pRes, int a);
extern int fn_801F9064(int db, int file, char *pName, int mode, TDbIODevice_t *pDevice);
extern TDbIODevice_t tdbiofioCallback;
extern int fn_801F967C(int db, int tbl);
int fn_8022F384(int key);

extern const unsigned char lbl_802AEF10[];
extern int fn_802297D8(void *p, int tag);
extern int fn_8022D8F8(int a, int *p, int c);
int fn_8022DB20(void);
extern int fn_8022F428(int key);
extern int fn_8022F4BC(void);
extern void fn_80231208(void);
int fn_8022F3D4(int key);
extern int lbl_803ED6E4[2];
extern char lbl_802B5D64[];
extern char lbl_802B56F4[];
extern char lbl_802B5744[];
extern char lbl_802B4EA0[];
extern char lbl_802B4EC4[];
extern char lbl_802B37E4[];
extern char lbl_802B3824[];
int fn_8022C0E0(struct QueryCursor cursor, int a);
extern int fn_801FA1C0(int ref, unsigned short *pCount);
extern int fn_80230D8C(int id, int a, int b);
extern char lbl_802B3610[];
extern char lbl_802B3698[];
extern char lbl_802B479C[];
extern char lbl_802B4828[];
extern char lbl_802B5CB4[];
extern char lbl_802B5CF0[];
extern int fn_801F9014(int db);
extern char lbl_802B3888[];
extern char lbl_802B36C4[];
extern int fn_801F9A90(int db, int tbl);
extern int fn_801F9AB8(int db, int tbl, TDbColInfo_801F9AB8 *pCols, unsigned int *pCount);
extern int fn_801F9C68(int db, int tbl, int col);
int fn_8022ED30(int db, int tbl);
extern char lbl_802B5A48[];
extern char lbl_802B5AB0[];
extern char lbl_802B5ACC[];
extern char lbl_802B5B34[];
extern char lbl_802B5B64[];
extern char lbl_802B5BDC[];
extern struct QueryCursor lbl_802FA8B0;
extern unsigned short lbl_803EC060;
extern int *lbl_803EC084;
extern unsigned short lbl_803EC088;
extern int (*lbl_803EC08C)[2];
extern unsigned short lbl_803EC090;
extern int (*lbl_803EC094)[3];
extern unsigned short lbl_803EC098;
extern int lbl_802FAA50[][10][2];
int fn_8022E568(void);
int fn_8022E6CC(void);
int fn_8022E834(void);
int fn_8022E9E4(void);
void fn_8022EA4C(void);

typedef struct Record_8022D5A4 {
    unsigned short mUnknown0;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
} Record_8022D5A4;

typedef struct Record_8022D874 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
} Record_8022D874;

extern Record_8022D874 lbl_802FA8C0[];
extern char lbl_802B48C4[];
extern char lbl_802B4A54[];
extern char lbl_802B4A9C[];
extern char lbl_802B4AE0[];
void fn_8022C9B8(void *pPairs);
void fn_8022CED8(void);
int fn_8022D5A4(int key, int mode);
int fn_8022D710(int a, int b, int c, int row, int value);
unsigned short fn_8022D6FC(int index);

#include "engine/Handlers_802294D8.h"

typedef struct Object_8022A59C {
    unsigned short mUnknown0;
    int mUnknown4;
} Object_8022A59C;

typedef struct Node_8022CC6C {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    short mUnknown6;
    unsigned short mUnknown8;
    char mUnknown10[2];
    struct Node_8022CC6C *mpUnknown12;
    struct Node_8022CC6C *mpUnknown16;
} Node_8022CC6C;

void fn_8022CAEC(Node_8022CC6C **ppHead);

extern int fn_8022A624(Object_8022A59C *p, struct QueryCursor cursor, int a, int b);
extern int fn_802303B4(int key, unsigned short *pId);
extern int fn_80230CC8(unsigned short id);
extern int DbLockAcquire(void);
extern int DbLockRelease(void);

extern char lbl_802B2138[];
extern char lbl_802B2178[];
extern char lbl_802B21B8[];
extern char lbl_802B21FC[];
extern char lbl_802B2268[];
extern char lbl_802B231C[];
extern char lbl_802B238C[];
extern char lbl_802B2F64[];
extern char lbl_802B3010[];
extern char lbl_802B30D0[];
extern char lbl_802B3180[];
extern char lbl_802B3524[];
extern char lbl_802B35D4[];
extern char lbl_802B35E4[];
extern char lbl_802B35F8[];
extern char lbl_802B45F0[];
extern char lbl_802B4650[];
extern char lbl_802B5080[];
extern char lbl_802B50A0[];
extern char lbl_802B50C0[];
extern char lbl_802B50E0[];
extern char lbl_802B5100[];
extern char lbl_802B5120[];
extern char lbl_802B519C[];
extern char lbl_802B51BC[];
extern int lbl_802FA600[];
extern unsigned short lbl_802FAA1C[];
typedef struct Entry_803A2390 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
} Entry_803A2390;

typedef struct Record_8022A304 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    char mUnknownF[1];
    unsigned short mUnknown10;
    unsigned short mUnknown12;
    unsigned short mUnknown14;
    char mUnknown16[2];
} Record_8022A304;

/* Ends a column list for fn_801F9718. */
static inline void fn_801F9718_SetEnd(TDbCol_801F9718 *pCol)
{
    pCol->mCol = -1;
    pCol->mUnk4 = -1;
    pCol->mUnk0 = 0;
}

extern Record_8022A304 lbl_802FA180[21];
extern Record_8022A304 lbl_802FA378[17];
extern Record_8022A304 lbl_802FA510[10];

typedef struct Callbacks_8022B02C {
    int (*mpUnknown0)(int a, int b, int c, int d);
    int (*mpUnknown4)(int a);
} Callbacks_8022B02C;

typedef struct Callbacks_8022C214 {
    int (*mpUnknown0)(int a);
    int (*mpUnknown4)(int a);
} Callbacks_8022C214;

extern Entry_803A2390 lbl_803A2390[];
extern char lbl_803A23E8[];
extern char lbl_803A2474[];
extern struct QueryCursor lbl_803A25E0;
extern int (*lbl_803EBFD8)(void);
extern void *lbl_803EBFDC;
extern void *lbl_803EBFE0;
extern void (*lbl_803EBFE4)(int);
extern int lbl_803EBFE8;
extern unsigned char lbl_803EBFEC;
extern unsigned char lbl_803EBFED;
extern Object_8022A59C *lbl_803EBFF0;
extern int (*lbl_803EBFF8)(void);
extern int (*lbl_803EBFFC)(void **ppData, void *p);
extern int (*lbl_803EC000)(int a, int b);
extern int (*lbl_803EC004)(void);
extern int (*lbl_803EC008)(void);
extern int lbl_803EC020[2];
extern int *lbl_803EC010[1];
extern unsigned char lbl_803EC014[1];
extern TDbCol_801F9718 **lbl_803EC018[1];
extern unsigned char *lbl_803EC01C[1];
extern TDbCol_801F9718 *lbl_803EC024[1];
extern unsigned char lbl_803ED01C[1];
extern int fn_802311C8(int a);
extern int (*lbl_803EC028)(int a, int b, int c, int d);
extern int (*lbl_803EC02C)(int a);
extern unsigned char lbl_803EC030;
extern int (*lbl_803EC034)(int a);
extern int (*lbl_803EC038)(int a);
extern int (*lbl_803EC048)(int a);
extern int (*lbl_803EC04C)(int a);
extern Node_8022CC6C *lbl_803EC050;
extern Node_8022CC6C *lbl_803EC054;
extern Node_8022CC6C *lbl_803EC058;
extern Record_8022D5A4 *lbl_803EC05C;
extern unsigned short lbl_803EC060;
extern int lbl_803EC064;
extern int lbl_803EC068;
extern int lbl_803EC06C;
extern int lbl_803EC070;
extern int lbl_803EC074;
extern int lbl_803EC07C;
extern int lbl_803EC080;

int fn_80229674(void);
int fn_8022A59C(int a, Object_8022A59C **ppOut);
int fn_8022AB6C(Object_8022A59C *p, int a, int b);
int fn_8022AC80(Object_8022A59C *p);
int fn_8022BF60(void);
int fn_8022BF68(void);
void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void *fn_8022C9A8(void);
void fn_8022C9B4(void *p);
void fn_8022CADC(void);
Node_8022CC6C *fn_8022CC6C(Node_8022CC6C **ppHead, unsigned char key);
void *fn_8022CD30(void);
void fn_8022CD3C(void *p);
void fn_8022CDA0(void);
int fn_8022D14C(int a);
int fn_8022D250(int (*pCallback)(int a));
int fn_8022D25C(int (*pCallback)(int a));































































































































































/* prototypes of the functions defined in the original src/engine/cu_80229270.c */
int fn_80229270(void);
int fn_802293A8(void);
void fn_802293B0(void);
int fn_802293B4(int a, int b);
int fn_802293FC(void);
int fn_8022942C(void);
void fn_80229434(void);
int fn_80229438(int column, int value);
int fn_80229470(void);
void fn_80229494(void);
void fn_802294D8(Handlers_802294D8 *p);
int fn_802294F4(void);
int fn_802294FC(int *p);
int fn_80229554(void);
int fn_802295C0(void);
int fn_802295F8(int a);
int fn_80229644(int a, int b);
int fn_80229674(void);
int fn_802296B4(int a, int b);
void fn_80229718(Funcs_802FB3BC *pFuncs);
void fn_80229744(void);
int fn_80229760(void **ppData, void *p);
int fn_80229788(int a, int b);
int fn_802297B0(void);
int fn_802299FC(void);
int fn_80229A70(void);
float fn_80229C98(int index);
float fn_80229CB0(int index);
float fn_80229CC4(int index, int item);
float fn_80229CE4(int index);
int fn_80229E78(void);
int fn_80229E80(void);
void fn_8022A304(void);
int fn_8022A428(int a);
int fn_8022A490(unsigned int count);
int fn_8022A508(int a, int b, int c, int d, int e);
int fn_8022A558(int a, int b, int c, int d);
int fn_8022A59C(int a, Object_8022A59C **ppOut);
int fn_8022AB6C(Object_8022A59C *p, int a, int b);
int fn_8022AC80(Object_8022A59C *p);
int fn_8022ACEC(int key, int unused, int col, int value, int index);
int fn_8022AD64(int db, TDbCol_801F9718 **ppCols, unsigned char *pCount);
int fn_8022AEFC(unsigned int value);
int fn_8022AF54(int a, int b);
int fn_8022AF5C(int key, int unused, int col, int value, int set, int index);
int fn_8022B02C(Callbacks_8022B02C *pCallbacks);
void fn_8022B200(void);
int fn_8022BF60(void);
int fn_8022BF68(void);
int fn_8022C02C(int a, int b, int c, int d);
int fn_8022C098(int a);
int fn_8022C0E0(struct QueryCursor cursor, int a);
int fn_8022C214(Callbacks_8022C214 *pCallbacks);
void fn_8022C3C8(void);
int fn_8022C410(int a);
int fn_8022C518(int a);
int fn_8022C628(int db, int tbl, int *pIds, unsigned short *pCount);
int fn_8022C81C(int a);
int fn_8022C858(int a);
void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void DbUtilSetHeap(int a);
void *DbUtilAlloc(int size, int a);
void DbUtilFree(void *p);
void *fn_8022C9A8(void);
void fn_8022C9B4(void *p);
void fn_8022C9B8(void *pPairs);
void fn_8022CADC(void);
void fn_8022CAEC(Node_8022CC6C **ppHead);
Node_8022CC6C *fn_8022CC6C(Node_8022CC6C **ppHead, unsigned char key);
Node_8022CC6C *fn_8022CC98(Node_8022CC6C **ppHead, unsigned short key);
void fn_8022CCC4(Node_8022CC6C **ppHead, Node_8022CC6C *p);
void fn_8022CD0C(Node_8022CC6C **ppHead, Node_8022CC6C *p);
void *fn_8022CD30(void);
void fn_8022CD3C(void *p);
int fn_8022CD40(int a, int b, int c);
void fn_8022CDA0(void);
void fn_8022CDF8(void);
int fn_8022D14C(int a);
int fn_8022D154(void);
int fn_8022D1B8(void);
int fn_8022D23C(void);
int fn_8022D250(int (*pCallback)(int a));
int fn_8022D25C(int (*pCallback)(int a));
int fn_8022D268(int a, int b, int c, void *pPairs, int action, int mode);
int fn_8022D2F4(int a, int b, int c, void *pPairs, int mode);
int fn_8022D3AC(void);
unsigned short fn_8022D3D4(unsigned char key);
int fn_8022D418(int a, int b, int mode);
int fn_8022D540(void);
int fn_8022D5A4(int key, int mode);
int fn_8022D6E8(void);
void fn_8022D6F0(void);
unsigned short fn_8022D6FC(int index);
int fn_8022D710(int a, int b, int c, int row, int value);
int fn_8022D834(int row, int column);
int fn_8022D864(void);
int fn_8022D86C(void);
int fn_8022D874(int a, int b, int c, int key);
int fn_8022D8F8(int a, int *p, int tag);
int fn_8022DA44(int a, int *b, int c, int *d, int e);
int fn_8022DA90(int *p);
void fn_8022DB08(void);
int fn_8022DB20(void);
int fn_8022DBF4(int value);
int fn_8022DC38(int value);
int fn_8022DC7C(int value);
int fn_8022DCB0(int value);
int fn_8022DCE4(int value);
int fn_8022DD18(int value);
int fn_8022DD4C(int value);
int fn_8022DD80(int value);
int fn_8022DDB4(int a, void *p);
int fn_8022E21C(int a, int b);
int fn_8022E558(void);
int fn_8022E560(void);
int fn_8022E568(void);
void fn_8022E694(void);
int fn_8022E6CC(void);
void fn_8022E7FC(void);
int fn_8022E834(void);
void fn_8022E96C(void);
int fn_8022E9A4(void);
void fn_8022E9C4(void);
int fn_8022E9E4(void);
void fn_8022EA4C(void);
int fn_8022EA74(void);
void fn_8022EA7C(void);
int fn_8022EA80(int a, const char *pName, int b);
void fn_8022EAD8(void);
int fn_8022EB10(void);
int fn_8022EB5C(struct CardStreamTarget *pTarget, struct SaveStreamOps_t *pOps);
int fn_8022EB94(void *pTarget, struct SaveStreamOps_t *pOps);
int fn_8022EBC8(void);
int fn_8022EBF0(int a, const char *pName, int b);
void fn_8022EC48(void);
int fn_8022EC80(void);
int fn_8022ECCC(void);
int fn_8022ECF4(int a, int b);
int fn_8022ED30(int db, int tbl);
int fn_8022ED50(int db, int a, int b);
int DbFileInit(const char *pName);
void DbFileShutdown(void);
int DbFileTblLoad(int db, int file);
int DbFileTblDestroy(int db, int tbl);
int fn_8022EFDC(void);
int fn_8022F028(int a, const char *pName, int b);
void fn_8022F094(void);
int fn_8022F0D4(void);
void fn_8022F1BC(int key);
void fn_8022F294(int key);
int fn_8022F34C(void);
int fn_8022F358(int index);
int fn_8022F384(int key);
int fn_8022F3D4(int key);

#include "engine/fn_801F8D60.h"
#include "engine/tdbext.h"
#include "engine/dbutil.h"
#include "engine/fn_801F9134.h"

#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>
#include "engine/Funcs_802FB3BC.h"
#include "game/fn_8022F478.h"
#include "game/fn_80233CBC.h"
#include "game/fn_801FCE10.h"
#include "engine/texfile.h"
#include "game/Object_80233EAC.h"
#include "game/Object_80235588.h"
#include "game/QueryStatus.h"

#include "engine/Entry_802FB300.h"

#include "engine/Handlers_802294D8.h"
#include "game/Request_802329F0.h"

typedef struct Block_80233588 {
    int mUnknown0;
    char *mpUnknown4;
    int mUnknown8;
} Block_80233588;

extern Handlers_802294D8 lbl_802FB38C;
int fn_80233588(Block_80233588 *p);
int fn_802336BC(void);

typedef struct Block_802336C4 {
    void *mpUnknown0;
    unsigned int mUnknown4;
    char mUnknown8[8];
    char mUnknown10[0x34];
} Block_802336C4;

typedef struct Model_802337D4 {
    char mUnknown0[12];
    int *mpUnknown12;
    void *mpUnknown16;
} Model_802337D4;

typedef struct Joints_802337D4 {
    int mUnknown0;
    int mUnknown4;
} Joints_802337D4;

typedef struct Values_80233C7C {
    unsigned int mUnknown0[2];
    unsigned char mUnknown8[64];
} Values_80233C7C;

typedef struct List_80233BE4 {
    unsigned int mUnknown0;
} List_80233BE4;

typedef struct Model_80233BE4 {
    char mUnknown0[20];
    List_80233BE4 *mpUnknown20;
} Model_80233BE4;

typedef struct Box_80234070 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknown12[4];
    float mUnknown16;
    float mUnknown20;
    char mUnknown24[8];
} Box_80234070;

/* Record updated by 0x8023424C and searched by 0x80234394; partial layout. */
typedef struct Instance_8023424C {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    unsigned int mUnknown20;
    Object_80233EAC *mpUnknown24;
    float *mpUnknown28;
    void *mpUnknown32;
    void *mpUnknown36;
} Instance_8023424C;

typedef struct Desc_802345F8 {
    const char *mpUnknown0;
    char mUnknown4[16];
    void *mpUnknown20;
    struct Resource_802347EC *mpUnknown24;
    void *mpUnknown28;
} Desc_802345F8;

typedef struct Resource_802347EC {
    char mUnknown0[36];
    void *mpUnknown36;
} Resource_802347EC;

typedef struct Entry_8023465C {
    char mUnknown0[8];
    short mUnknown8;
    char mUnknown10[2];
    const char *mpUnknown12;
    char mUnknown16[32];
} Entry_8023465C;

typedef struct List_8023465C {
    int mUnknown0;
    Entry_8023465C *mpUnknown4;
} List_8023465C;

typedef struct Model_8023465C {
    char mUnknown0[24];
    List_8023465C *mpUnknown24;
} Model_8023465C;

typedef struct Object_8023465C {
    unsigned int mUnknown0;
} Object_8023465C;

typedef struct Array_8023491C {
    unsigned int mUnknown0;
    float *mpUnknown4;
    int mUnknown8;
} Array_8023491C;

typedef struct Part_80234A30 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    void *mpUnknown12;
    int mUnknown16;
    Values_80233C7C mUnknown20;
    int mUnknown92;
    short mUnknown96[64];
    void *mpUnknown224;
    void *mpUnknown228;
    void *mpUnknown232[2];
} Part_80234A30;

typedef struct Object_80234B20 {
    char mUnknown0[64];
    Mtx44 mUnknown64;
} Object_80234B20;

typedef struct Header_80234DFC {
    char mUnknown0[8];
    int mUnknown8;
} Header_80234DFC;

typedef struct Sprite_80234DFC {
    char mUnknown0[40];
    void *mpUnknown40;
    void *mpUnknown44;
} Sprite_80234DFC;

typedef struct Holder_80234EEC {
    char mUnknown0[88];
    Sprite_80234DFC *mpUnknown88;
} Holder_80234EEC;

typedef struct Table_803E96E8 {
    char mUnknown0[12];
    struct Group_803E96E8 *mpUnknown12;
} Table_803E96E8;

typedef struct Group_803E96E8 {
    char mUnknown0[12];
    unsigned short *mpUnknown12;
} Group_803E96E8;

typedef struct Range_80216190 {
    char mUnknown0[16];
    unsigned short mUnknown16;
    unsigned short mUnknown18;
} Range_80216190;

typedef struct Source_80235328 {
    char *mpUnknown0;
} Source_80235328;

typedef struct Owner_80235328 {
    char mUnknown0[8];
    Source_80235328 *mpUnknown8;
} Owner_80235328;

typedef struct Cache_8022F8A8 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    int mUnknown4;
    int mUnknown8;
    void *mpUnknown12[2];
    void *mpUnknown20[2];
    void *mpUnknown28[2];
    union {
        int mWord;
        unsigned char mBytes[4];
    } mUnknown36;
    char mUnknown40[56];
    struct Cache_8022F8A8 *mpUnknown96;
    struct Cache_8022F8A8 *mpUnknown100;
} Cache_8022F8A8;

typedef struct Entry_802FB310 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
} Entry_802FB310;

extern char lbl_802B5D88[];
extern char lbl_802B5DB0[];
extern char lbl_802B6520[];
extern char lbl_802B6E10[];
extern char lbl_802B6E34[];
extern char lbl_802B6E74[];
extern char lbl_802B6E90[];
extern char lbl_802B6EA0[];
extern char lbl_802B6EE0[];
extern char lbl_802B6F00[];
extern char lbl_802B6F30[];
extern char lbl_802B6F54[];
extern char lbl_802B6F78[];
extern char lbl_802B6FB0[];
extern char lbl_802B6FF4[];
extern char lbl_802B7050[];
extern char lbl_802B706C[];
extern char lbl_802B709C[];
extern char lbl_802B70DC[];
extern char lbl_802B70FC[];
extern char lbl_802B7128[];
extern char lbl_802B7130[];
extern char lbl_802B7154[];
extern char lbl_802B715C[];
extern Entry_802FB300 lbl_802FB300[];
extern Entry_802FB310 lbl_802FB310[];
extern int lbl_802FB398[];
extern int lbl_802FB3A4[];
extern int lbl_802FB3B0[];
extern Funcs_802FB3BC lbl_802FB3BC;
extern Funcs_802FB3BC lbl_802FB3D0;
extern Funcs_802FB3BC lbl_802FB3E4;
extern int lbl_802FB3F8[];
extern void *lbl_803A2648[];
extern Table_803E96E8 lbl_803E96E8;
extern int lbl_803EC0C8;
extern char *lbl_803EC0CC;
extern int lbl_803EC0D0;
extern int lbl_803EC0D4;
extern unsigned char lbl_803EC0D8;
extern Cache_8022F8A8 *lbl_803EC0E0;
extern int lbl_803EC0E4;
extern int lbl_803EC0E8;
extern int lbl_803EC0F0;
extern void *lbl_803EC0F4;
extern int lbl_803ED020;
extern int lbl_803ED024;
extern int lbl_803ED6E4[2];

double fabs(double);

extern void MatPush(void);
extern void MatPushUnit(void);
extern void MatPop(void);
extern void MatCat(Mtx44 m);
extern void MatStore(Mtx44 m);
extern void MatLoadSlot(int a);
extern void *fn_801D2B7C(int size, int a, int b);
extern int fn_801D2BD0(void *p);
extern int ResLoad(void *pData, int index, int a);
extern int ResCopyToBuffer(void *pArchive, int id, void *pDest);
extern int ResUnLoad(void *pData, int index);
extern int ResIsLoaded(void *pData, int index);
extern int fn_801F9014(int handle);
extern int fn_801F91AC(int handle, int a, int b);
extern int fn_801F9430(int a, int *pTable4, int *pTable8);
extern int fn_801F9574(void);
extern int fn_801F9980(int handle, int *pTable);
extern int fn_801F9A90(int handle, int table);
extern int fn_801F9D0C(int handle, int table, int a);
extern int fn_801FA68C(void *pCallback, int tag);
extern int fn_801FA740(int tag);
extern void LLTexCopyFlush(void *pDst, void *pSrc, unsigned int size);
extern void TMModelResRelocate(void *p);
extern void *TMModelResGetChunk(void *p, unsigned int tag, void *pOut);
extern void TMModelReset(void *p);
extern void TMModelClone(void *pDst, void *pSrc);
extern void TMModelBindModelRes(void *p, void *pData);
extern void TMModelRemapMaterials(void *p, void *pRef);
extern void TMModelRemapClusters(void *p, void *q);
extern void TMModelResetChannels(void *p);
extern void TMModelAllocChannels(void *p);
extern void TMModelFreeChannels(void *p);
extern void TMModelAddExtent(void *p, void *q, int a, int b);
extern void TMMaterialBindTextureClut(const char *pName, void *pTexture, void *pPalette);
extern void TMMaterialBindShader(int handle);
extern void TMMaterialListAlloc(void *p, int a);
extern void TMMaterialListFree(void *p);
extern void TMMaterialListSelect(void *p, int a);
extern void TMRenderBindModel(void *p);
extern void TMRenderBindClusterObj(void *p);
extern void TMRenderBindMaterialList(void *p);
extern void TMRenderGeomList(short *pValues, int count);
extern void TMRenderGeomListDirect(short *pValues, int count);
extern int TMShaderLibGetShader(const char *pName);
extern void TMTexLibLoad(void *p, int a);
extern void TMTexLibUnload(void *p);
extern void *TMTexLibGetTextureByTexNode(void *p);
extern void *TMTexLibGetClutByTexNode(void *p, int a);
extern void TMClusterObjInitObj(void *p);
extern void TMClusterObjAllocMatrices(Joints_802337D4 *pJoints, int a);
extern void TMClusterObjSynthesizeMatrices(Joints_802337D4 *pJoints, void *p, int *q, void *pPose);
extern void TMClusterObjSynthesizeMatricesSlerp(Joints_802337D4 *pJoints, void *p, int *q, void *pPose, unsigned char *pFlags);
extern void TMTevSetTevOp(int a, int b, int c);
extern void TMClipProjection(int a);
extern void TMClipMatrix(int a);
extern void TMClipMatrixWorld(int a, void *p, void *q);
extern unsigned int TMClipBBox(void *p, void *q, int a);
extern void TMClipResetExtent(void *p);
extern void TMBufferNew(void *p, int a, int b);
extern void TMBufferDelete(void *p);
extern void TMBufferReset(void *p);
extern void TMBlendSetWeights(short *pValues, int count);
extern void TMBlendBegin(void *p);
extern void TMBlendEnd(void);
extern void TMBlendBindModel(void *p);
extern void TMBlendGeomAll(void);
extern Range_80216190 *TMSwapGetState(Group_803E96E8 *pGroup, int a, int key);
extern int TMSwapGetGeomRefs(List_80233BE4 *pList, short *pOut, unsigned int index, int value);
extern int fn_802293A8(void);
extern void fn_802293B0(void);
extern int fn_8022942C(void);
extern void fn_80229434(void);
extern int fn_80229554(void);
extern int fn_802296B4(int a, int b);
extern void fn_80229718(Funcs_802FB3BC *pFuncs);
extern void fn_80229744(void);
extern int fn_80229760(void **ppData, void *p);
extern int fn_80229788(int a, int b);
extern int fn_802299FC(void);
extern int fn_80229A70(void);
extern int fn_80229E88(void);
extern void fn_8022A304(void);
extern void fn_8022B200(void);
extern void fn_8022C3C8(void);
extern int fn_8022C410(int a);
extern int fn_8022C518(int a);
extern int fn_8022D154(void);
extern int fn_8022D1B8(void);
extern int fn_8022D6E8(void);
extern void fn_8022D6F0(void);
extern int fn_8022DA90(int *p);
extern void fn_8022DB08(void);
extern int fn_8022DB20(void);
extern int fn_8022DBF4(int a);
extern int fn_8022DC38(int a);
extern int fn_8022E28C(int a, int b, unsigned char *p, int *pA, int *pB);
extern int fn_8022E484(void);
extern int fn_8022E9A4(void);
extern void fn_8022E9C4(void);
extern int fn_8022E9E4(void);
extern int fn_8022EA74(void);
extern void fn_8022EA7C(void);
extern int fn_8022ED50(int a, int b, int c);
extern int fn_8022F384(int key);
extern int fn_8022F3D4(int key);
extern int fn_8022F8A8(int key, Cache_8022F8A8 **ppCache);
extern int fn_80230400(unsigned short id, int a, int b, int c, int d, int e, int f);
extern void fn_802349CC(void *p);
extern void fn_80235010(Table_803E96E8 *pTable, void *pEntry);
extern void fn_80236F00(void);

void fn_8023123C(void *p, int mode, unsigned char *pDone);
int fn_80232DE0(void);
int fn_80232EB4(void);
int fn_80232EF4(void);
int fn_802331BC(void);
void fn_802334F0(int mode, Funcs_802FB3BC *pFuncs);
int fn_80233604(void **ppData, void *p);
int fn_80233660(int a, int b);
int fn_80233694(void);
int fn_80233BE4(short *pOut, Model_80233BE4 *pModel, Values_80233C7C *pValues);
void fn_80233C7C(Values_80233C7C *pValues);
float fn_80234070(Box_80234070 *pBox);
unsigned int fn_80234D4C(float *pBox, void *m, void *p, void *q);
extern int TMClipVertex(float *pNdc, float *pClip, float *pPos);
void fn_80234094(Box_80234070 *pBox);
int fn_80234098(Object_80233EAC *pObject, float value);
Desc_802345F8 *fn_802345F8(Desc_802345F8 *pDescs, const char *pName);
void fn_8023472C(void *p, int a, int b, Desc_802345F8 *pA, Desc_802345F8 *pB, int c);
void fn_80234A14(Part_80234A30 *pPart, int mask);
void fn_80234A94(Part_80234A30 *pPart, void *pRecord);
void fn_80234B88(Part_80234A30 *pPart);
void fn_80234DFC(int a, Sprite_80234DFC *pSprite, int c, int d, const char *pName, int e);


































































































































/* prototypes of the functions defined in the original src/engine/cu_8022F428.c */
int fn_8022F428(int key);
int fn_8022F478(int value);
int fn_8022F488(int value);
int fn_8022F4BC(void);
int fn_8022F4C4(void);
int fn_8022F53C(int a);
int fn_8022F744(void);
int fn_8022F794(int value, char *pName);
unsigned short fn_8022F80C(void);
Cache_8022F8A8 *fn_8022F858(unsigned short id);
Cache_8022F8A8 *fn_8022F880(int key);
int fn_8022FBAC(Cache_8022F8A8 *pCache);
int fn_802303A0(int index);
int fn_802303B4(int key, unsigned short *pId);
int fn_80230CC8(unsigned short id);
int fn_80230CEC(int a, int b, int c, int key, int e, int f);
int fn_802311C8(int handle);
void fn_80231208(void);
int fn_80231A84(void);
int fn_80231A8C(const char *pWhere, int b, int c, int d, int e, struct QueryCursor *pCursor);
int fn_802328A8(void);
void fn_80232950(void);
int fn_80232998(void);
int fn_802329D0(void);
int fn_802329F0(struct Request_802329F0 *p);
int fn_80232A98(void);
int fn_80232AF8(void **ppData, void *p);
int fn_80232B8C(int a, int b);
int fn_80232DE0(void);
int fn_80232E20(void);
int fn_80232E70(void);
int fn_80232E78(void);
int fn_80232E80(void);
int fn_80232EAC(void);
int fn_80232EB4(void);
int fn_80232EF4(void);
int fn_80232F44(void);
int fn_80232F4C(void);
int fn_80232F54(void);
int fn_80232F74(void);
int fn_80232FD4(int *pRecord0, int *pRecord1);
int fn_802331BC(void);
int fn_80233344(void);
int fn_8023334C(int a, int b);
int fn_80233454(void);
int fn_802334C4(void);
void fn_802334F0(int mode, Funcs_802FB3BC *pFuncs);
int fn_80233568(int a, int b, unsigned char *pDone);
int fn_80233578(void);
int fn_80233580(void);
int fn_80233588(Block_80233588 *p);
int fn_80233604(void **ppData, void *p);
int fn_80233660(int a, int b);
int fn_80233694(void);
int fn_802336BC(void);
void fn_802336C4(Block_802336C4 *pBlock, void *pSource, int a);
void fn_80233728(Block_802336C4 *pBlock);
void fn_80233760(Block_802336C4 *pBlock, short *pValues, int count);
void fn_802337D4(Model_802337D4 *pModel, Joints_802337D4 *pJoints, void *pPose, unsigned int mask);
void fn_80233850(Model_802337D4 *pModel, Joints_802337D4 *pJoints, void *pPose, unsigned int mask, unsigned char *pFlags);
void fn_80233BB8(void *pJoints, int a, int b);
void fn_80233BD8(void *pJoints);
void fn_80233BDC(void *pJoints, void *pSkeleton);
void fn_80233BE0(void);
int fn_80233BE4(short *pOut, Model_80233BE4 *pModel, Values_80233C7C *pValues);
void fn_80233C7C(Values_80233C7C *pValues);
void fn_80233CBC(void *p, int index, int value);
void fn_80233CF0(ModelLod_802DF190 *pLod, void *pData, void *p);
void fn_80233D64(Object_80233EAC *pObject, ModelLod_802DF190 *pLods, const char *pName, int a, void *pData, void *p);
void fn_80233EAC(Object_80233EAC *pObject, ModelLod_802DF190 *pLods, const char *pName, int a, void *pArchive, AnimSkeleton_t *pSkeleton, void **ppData, int load);
void fn_80233FCC(Object_80233EAC *pObject);
float fn_80234070(Box_80234070 *pBox);
void fn_80234094(Box_80234070 *pBox);
int fn_80234098(Object_80233EAC *pObject, float value);
int fn_80234144(Object_80233EAC *pObject, void *pBox);
Object_8023417C *fn_8023417C(Object_80233EAC *pObject, int index);
void fn_802341AC(void);
void fn_802341B8(void);
void fn_802341C4(void *p);
void fn_802341E8(void *p);
void fn_8023424C(Instance_8023424C *p, int *pCounts, Box_80234070 *pClip);
int fn_80234394(Instance_8023424C **ppList, unsigned int count, int key);
void fn_802345BC(void *p);
void fn_802345C4(void *pSource, int count);
Desc_802345F8 *fn_802345F8(Desc_802345F8 *pDescs, const char *pName);
void fn_8023465C(Object_8023465C *pObject, Model_8023465C *pModel, Desc_802345F8 *pDescs);
void fn_8023472C(void *p, int a, int b, Desc_802345F8 *pA, Desc_802345F8 *pB, int c);
void fn_802347EC(void *pData, Desc_802345F8 *pDesc, int a, int b);
void fn_80234844(Desc_802345F8 *pDesc);
void fn_8023488C(void *p, int a);
void fn_802348AC(void *p);
void fn_802348CC(int a);
void fn_80234908(void);
void fn_80234994(Array_8023491C *pArray);
void fn_802349B8(Array_8023491C *pArray, int value);
void fn_80234A14(Part_80234A30 *pPart, int mask);
void fn_80234A30(Part_80234A30 *pPart, int a);
void fn_80234A90(Part_80234A30 *pPart);
void fn_80234A94(Part_80234A30 *pPart, void *pRecord);
void fn_80234AD8(Part_80234A30 *pPart, Block_802336C4 *pBlock);
void fn_80234AFC(void *p);
void fn_80234B1C(void *p);
void fn_80234B20(Object_80234B20 *pObject, Mtx44 a, Mtx44 b);
int fn_80234B80(void *p);
void fn_80234B88(Part_80234A30 *pPart);
void fn_80234BF4(int a, Part_80234A30 *pPart, int mode);
void fn_80234CA4(Part_80234A30 *pPart, void *p);
void fn_80234CAC(Part_80234A30 *pPart, void *p);
void fn_80234CF0(Part_80234A30 *pPart, int index, void *p);
void fn_80234D00(void *pIn, void *pOut);
unsigned int fn_80234D4C(float *pBox, void *m, void *p, void *q);
void fn_80234DC0(void *p, int a);
void fn_80234DC4(void *p, int a);
void fn_80234DC8(void *p, unsigned int a);
void fn_80234DCC(int a, Sprite_80234DFC *pSprite, const char *pName, int b);
void fn_80234DFC(int a, Sprite_80234DFC *pSprite, int c, int d, const char *pName, int e);
void fn_80234EA0(Sprite_80234DFC *pSprite, int keep);
void fn_80234EEC(Holder_80234EEC *pHolder, int index, void *pData, unsigned char sourceIndex);
void fn_80234F74(Sprite_80234DFC *pSprite, int index, void *pData, unsigned char sourceIndex, int offset);
void fn_80235328(Owner_80235328 *pOwner, int key);
void fn_802353CC(void *p);
void fn_802353D0(void *p);
void fn_802353D4(Object_80235588 *p, int flags);
void fn_802353D8(Object_80235588 *p, int flags);
void fn_802353E8(Object_80235588 *p, int flags);
void fn_802353F8(Object_80235588 *p, int flags);
void fn_80235510(Object_80235588 *p, int mode);
void fn_80235588(Object_80235588 *p, int a);

int fn_8022EFDC(void)
{
    int key;
    do {
        key = DbUtilRandomRange(0, 0x7FFFFFFA) & 0x7FFFFFFF;
    } while (fn_8022F384(key) != -1);
    return key;
}

int fn_8022F028(int a, const char *pName, int b)
{
    lbl_803EC0C8 = a;
    lbl_803EC0CC = DbUtilAlloc(strlen(pName) + 1, 1);
    strcpy(lbl_803EC0CC, pName);
    lbl_803EC0D0 = b;
    lbl_803EC0D4 = -1;
    lbl_803EC0D8 = 0;
    return 0;
}

void fn_8022F094(void)
{
    DbUtilFree(lbl_803EC0CC);
    lbl_803EC0C8 = 0;
    lbl_803EC0CC = 0;
    lbl_803EC0D0 = -1;
    lbl_803EC0D4 = -1;
    lbl_803EC0D8 = 0;
}

int fn_8022F0D4(void)
{
    unsigned char i;
    int id;
    int key;
    int old;

    id = -1;
    if ((signed char)lbl_803EC0D8 <= 1) {
        for (i = 0; fn_8022F428(key = lbl_803ED6E4[i]) != -1; i++) {
        }
        id = fn_8022EFDC();
        lbl_802FB300[(signed char)lbl_803EC0D8].mUnknown0 = id;
        lbl_802FB300[(signed char)lbl_803EC0D8].mUnknown4 = key;
        TDbExtLoadFromResource(key, lbl_803EC0CC, lbl_803EC0D0, 0);
        lbl_803EC0D8++;
        old = fn_8022F478(id);
        fn_801FCE10(0, lbl_802B5D64, fn_8022F3D4(fn_8022F4BC()), id);
        fn_8022F478(old);
    }
    return id;
}

void fn_8022F1BC(int key)
{
    signed char index;

    if (key != -1) {
        index = fn_8022F384(key);
        if (index != -1) {
            lbl_803EC0D8--;
            TDbExtLoadFromResource(lbl_802FB300[index].mUnknown4, lbl_803EC0CC, lbl_803EC0D0, 0);
            for (; index < (signed char)lbl_803EC0D8; index++) {
                lbl_802FB300[index] = lbl_802FB300[index + 1];
            }
            lbl_802FB300[(signed char)lbl_803EC0D8].mUnknown0 = -1;
            lbl_802FB300[(signed char)lbl_803EC0D8].mUnknown4 = -1;
        }
    }
}

void fn_8022F294(int key)
{
    int index;
    int id;
    int old;

    if (key != -1) {
        index = fn_8022F384(key);
        if (index != -1) {
            TDbExtLoadFromResource(lbl_802FB300[index].mUnknown4, lbl_803EC0CC, lbl_803EC0D0, 0);
            id = fn_8022EFDC();
            old = fn_8022F478(key);
            fn_801FCE10(0, lbl_802B5D64, fn_8022F3D4(fn_8022F4BC()), id);
            lbl_802FB300[index].mUnknown0 = id;
            if (old == key) {
                fn_8022F478(id);
            } else {
                fn_8022F478(old);
            }
        }
    }
}

int fn_8022F34C(void)
{
    return (signed char)lbl_803EC0D8;
}

int fn_8022F358(int index)
{
    int value = -1;
    if (index < (signed char)lbl_803EC0D8) {
        value = lbl_802FB300[index].mUnknown0;
    }
    return value;
}

int fn_8022F384(int key)
{
    signed char i;
    for (i = 0; i < (signed char)lbl_803EC0D8; i++) {
        if (key == lbl_802FB300[i].mUnknown0) {
            return i;
        }
    }
    return -1;
}

int fn_8022F3D4(int key)
{
    int value = -1;
    if (key != -1) {
        int index = fn_8022F384(key);
        if (index != -1) {
            value = lbl_802FB300[index].mUnknown4;
        }
    }
    return value;
}

int fn_8022F428(int key)
{
    unsigned char i = lbl_803EC0D8;

    while (--i != 255) {
        if (lbl_802FB300[i].mUnknown4 == key) {
            return lbl_802FB300[i].mUnknown0;
        }
    }
    return -1;
}

int fn_8022F478(int value)
{
    int old = lbl_803EC0D4;

    lbl_803EC0D4 = value;
    return old;
}

int fn_8022F488(int value)
{
    fn_8022F478(value);
    return fn_8022F3D4(value);
}

int fn_8022F4BC(void)
{
    return lbl_803EC0D4;
}

int fn_8022F4C4(void)
{
    int err = 0;
    unsigned int i;

    for (i = 0; i <= 1 && (err = fn_801F8D60(lbl_803ED6E4[i], lbl_803EC0C8)) == 0; i++) {
        err = TDbExtLoadFromResource(lbl_803ED6E4[i], lbl_803EC0CC, lbl_803EC0D0, 0);
        if (err != 0) {
            break;
        }
    }
    return err;
}

int fn_8022F53C(int a)
{
    int key;
    int err;

    if (a == 0) {
        err = fn_801FCE10(0, lbl_802B5D88, fn_8022F3D4(fn_8022F4BC()), &key);
        if (key != fn_8022F4BC()) {
            if (fn_8022F384(key) == -1) {
                (lbl_802FB300 + fn_8022F384(fn_8022F4BC()))->mUnknown0 = key;
                lbl_803EC0D4 = key;
            } else {
                err = 1;
            }
        }
    } else {
        err = 36;
    }
    return err;
}

int fn_8022F744(void)
{
    int err = 0;
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        err = fn_801F8EEC(lbl_803ED6E4[i]);
        if (err != 0) {
            break;
        }
    }
    return err;
}

int fn_8022F794(int value, char *pName)
{
    int err = 0;
    int old = fn_8022F478(value);

    if (fn_8022F3D4(fn_8022F4BC()) != -1) {
        err = fn_801FCE10(0, lbl_802B5DB0, fn_8022F3D4(fn_8022F4BC()), pName);
    }
    fn_8022F478(old);
    return err;
}
