#ifndef GAME_MODULE_H
#define GAME_MODULE_H

/* Game modules: classes with one static instance each, a dependency table and a link to
   another module. Names are descriptive; no original names are recovered. */

/* Non-polymorphic 12-byte base provided by library code. */
class LibraryNode {
public:
    LibraryNode();
    ~LibraryNode();

private:
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

class Module : public LibraryNode {
public:
    Module() {}
    virtual ~Module() {}
    virtual void Virtual_80025F24();
    virtual void Virtual_80025F28();
    virtual void Virtual_80025F5C();
    virtual void Virtual_80025F60();
    virtual int Init() = 0;
    virtual int Shutdown() = 0;
    virtual void *GetDependencies() = 0;
    virtual void *GetLink() = 0;
    virtual const char *GetName() = 0;
};

/* One entry of a module's zero-terminated dependency table. */
struct ModuleDependency {
    ModuleDependency(void *pTarget) : mpTarget(pTarget) {}
    void *mpTarget;
};

struct ModuleLinkState {
    ModuleLinkState() : mValue(0) {}
    int mValue;
};

struct ModuleLink {
    ModuleLink(Module *pModule) : mpModule(pModule) {}
    Module *mpModule;
    ModuleLinkState mState;
};

#define DECLARE_MODULE(Name)                    \
    class Name : public Module {                \
    public:                                     \
        virtual int Init();                     \
        virtual int Shutdown();                 \
        virtual void *GetDependencies();        \
        virtual void *GetLink();                \
        virtual const char *GetName();          \
    }

DECLARE_MODULE(AnmsCelebration);
DECLARE_MODULE(Celebration);

#endif
