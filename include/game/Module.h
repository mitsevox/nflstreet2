#ifndef GAME_MODULE_H
#define GAME_MODULE_H

/* Abstract base: its constructor registers the object in a global table. */
class ModuleNode {
public:
    ModuleNode();
    virtual ~ModuleNode();
    virtual void fn_80025F24() = 0;
    virtual void fn_80025F28(void *pArg) = 0;
    virtual void fn_80025F5C() = 0;
    virtual void fn_80025F60() = 0;
    virtual int Init() = 0;
    virtual int Shutdown() = 0;
    virtual struct ModuleDependency *GetDependencies() = 0;
    virtual struct ModuleDependency *GetLinks() = 0;
    virtual const char *GetName() = 0;

    int fn_801CC96C();

private:
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
};

class Module : public ModuleNode {
public:
    virtual ~Module() {}
    virtual void fn_80025F24();
    virtual void fn_80025F28(void *pArg);
    virtual void fn_80025F5C();
    virtual void fn_80025F60();
};

/* A module table entry holding a target pointer. */
struct ModuleDependency {
    ModuleDependency(void *pTarget) : mpTarget(pTarget) {}
    void *mpTarget;
};

#define DECLARE_MODULE(Name)                            \
    class Name : public Module {                        \
    public:                                             \
        virtual int Init();                             \
        virtual int Shutdown();                         \
        virtual ModuleDependency *GetDependencies();    \
        virtual ModuleDependency *GetLinks();           \
        virtual const char *GetName();                  \
    }

DECLARE_MODULE(AnmsCelebration);
DECLARE_MODULE(Celebration);
DECLARE_MODULE(Font);
DECLARE_MODULE(Mat);
DECLARE_MODULE(Obj);
DECLARE_MODULE(Res);
DECLARE_MODULE(Tex);
DECLARE_MODULE(Vec);
DECLARE_MODULE(Vpt);
DECLARE_MODULE(GRender);
DECLARE_MODULE(Debug);
DECLARE_MODULE(Snd);
DECLARE_MODULE(Sys);
DECLARE_MODULE(GLIB);
DECLARE_MODULE(FileIO);
DECLARE_MODULE(FEDLL);
DECLARE_MODULE(Audmon);
DECLARE_MODULE(GRand);
DECLARE_MODULE(MemAudit);
DECLARE_MODULE(ScrmRule);
DECLARE_MODULE(UIS);
DECLARE_MODULE(Rumble);
DECLARE_MODULE(Timg);
DECLARE_MODULE(LoadingFE);
DECLARE_MODULE(LoadingFEToInGame);

extern AnmsCelebration gAnmsCelebration;
extern Celebration gCelebration;
extern FileIO gFileIO;
extern Vpt gVpt;
extern GLIB gGLIB;
extern Sys gSys;
extern GRender gGRender;
extern Mat gMat;
extern Obj gObj;
extern Res gRes;

#endif
