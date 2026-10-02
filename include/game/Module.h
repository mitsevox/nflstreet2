#ifndef GAME_MODULE_H
#define GAME_MODULE_H

/* Abstract base: its constructor registers the object in a global table. */
class ModuleNode {
public:
    ModuleNode();
    virtual ~ModuleNode();
    virtual void Virtual_80025F24() = 0;
    virtual int Virtual_80025F28(void *pArg) = 0;
    virtual void Virtual_80025F5C() = 0;
    virtual void Virtual_80025F60() = 0;
    virtual int Init() = 0;
    virtual int Shutdown() = 0;
    virtual struct ModuleDependency *GetDependencies() = 0;
    virtual struct ModuleDependency *GetLinks() = 0;
    virtual const char *GetName() = 0;

private:
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
};

class Module : public ModuleNode {
public:
    Module() {}
    virtual ~Module() {}
    virtual void Virtual_80025F24();
    virtual int Virtual_80025F28(void *pArg);
    virtual void Virtual_80025F5C();
    virtual void Virtual_80025F60();
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

extern AnmsCelebration gAnmsCelebration;
extern Celebration gCelebration;

#endif
