#include "game/PreGamePhase.h"
#include "game/PreSnapPhase.h"

class Class_802A1DC8 : public PreGamePhase {
public:
    virtual void OnEnter();
    virtual ~Class_802A1DC8();
};

class Class_802A1D58 : public PreSnapPhase {
public:
    virtual void OnEnter(float dt);
    virtual ~Class_802A1D58();
};

Class_802A1DC8::~Class_802A1DC8()
{
}

Class_802A1D58::~Class_802A1D58()
{
}
