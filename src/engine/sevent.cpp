/* AEMS 1 compatibility events (sevent.cpp): when a sound bank image of AEMS 1 classes is added,
   each class description in it is bound by name to its CSIS class and to up to three CSIS
   functions (create, member data, destroy). Every instance the class constructs then gets a small
   record that forwards its member-data updates and its destruction to those functions. */

#include "engine/csis.h"
#include "engine/sevent.h"

namespace Snd {

struct A1cClassDesc {
    Csis::ClassHandle mClass;
    Csis::FunctionHandle mCreate;
    Csis::FunctionHandle mMemberData;
    Csis::FunctionHandle mDestroy;
    Csis::ClassConstructorClient mConstructorClient;
    unsigned char mHasCreate;
    unsigned char mHasMemberData;
    unsigned char mHasDestroy;
    Csis::InterfaceId mClassId;
    Csis::InterfaceId mCreateId;
    Csis::InterfaceId mMemberDataId;
    Csis::InterfaceId mDestroyId;
};

struct A1cSystemDesc {
    unsigned char unk_0x0[10];
    unsigned short mNumClasses;
    A1cClassDesc *mpClasses;
};

struct A1cInstance {
    A1cClassDesc *mpDesc;
    Csis::FunctionClient mMemberDataClient;
    Csis::ClassDestructorClient mDestructorClient;
};

A1cSystemDesc *gpA1cSystemDesc = 0;
Allocator *gpA1cAllocator = 0;

void A1cMemberDataCallBack(Csis::Parameter *params, void *context)
{
    A1cInstance *instance = (A1cInstance *)context;

    Csis::Function::CallFast(&instance->mpDesc->mMemberData, params);
}

void A1cDestructorCallBack(Csis::Class *object, void *context)
{
    A1cInstance *instance = (A1cInstance *)context;
    A1cClassDesc *desc = instance->mpDesc;

    Csis::Function::CallFast(&desc->mDestroy, 0);
    if (desc->mHasMemberData) {
        object->AddRef();
        object->UnsubscribeMemberDataFast(&instance->mMemberDataClient);
    }
    object->AddRef();
    object->UnsubscribeDestructorFast(&instance->mDestructorClient);
    gpA1cAllocator->Free(instance, 0);
}

void A1cConstructorCallBack(Csis::Class *object, Csis::Parameter *params, void *context)
{
    A1cClassDesc *desc = (A1cClassDesc *)context;
    A1cInstance *instance = (A1cInstance *)gpA1cAllocator->Alloc(sizeof(A1cInstance), AllocParams());

    if (instance != 0) {
        if (desc->mHasCreate) {
            Csis::Function::CallFast(&desc->mCreate, 0);
        }
        if (desc->mHasMemberData) {
            Csis::Function::CallFast(&desc->mMemberData, params);
        }
        instance->mpDesc = desc;
        if (desc->mHasMemberData) {
            instance->mMemberDataClient.mCallback = A1cMemberDataCallBack;
            instance->mMemberDataClient.mContext = instance;
            object->SubscribeMemberDataFast(&instance->mMemberDataClient);
            object->DecRef();
        }
        instance->mDestructorClient.mCallback = A1cDestructorCallBack;
        instance->mDestructorClient.mContext = instance;
        object->SubscribeDestructorFast(&instance->mDestructorClient);
        object->DecRef();
    }
}

int Aems::AddAems1CompatibilitySystem(void *system)
{
    A1cSystemDesc *desc = (A1cSystemDesc *)system;
    A1cClassDesc *classes;
    int i;

    gpA1cSystemDesc = desc;
    classes = (A1cClassDesc *)(desc + 1);
    desc->mpClasses = classes;
    Csis::System::GetAllocator(&gpA1cAllocator);
    Csis::System::Lock();
    for (i = 0; i < gpA1cSystemDesc->mNumClasses; i++) {
        classes[i].mClassId.mName += (int)desc;
        if (classes[i].mClass.SetFast(&classes[i].mClassId) >= 0) {
            if (classes[i].mHasCreate) {
                classes[i].mCreateId.mName += (int)desc;
                classes[i].mCreate.SetFast(&classes[i].mCreateId);
            }
            if (classes[i].mHasMemberData) {
                classes[i].mMemberDataId.mName += (int)desc;
                classes[i].mMemberData.SetFast(&classes[i].mMemberDataId);
            }
            if (classes[i].mHasDestroy) {
                classes[i].mDestroyId.mName += (int)desc;
                classes[i].mDestroy.SetFast(&classes[i].mDestroyId);
            }
            classes[i].mConstructorClient.mCallback = A1cConstructorCallBack;
            classes[i].mConstructorClient.mContext = &classes[i];
            Csis::Class::SubscribeConstructorFast(&classes[i].mClass, &classes[i].mConstructorClient);
        }
    }
    Csis::System::Unlock();
    return 0;
}

int Aems::RemoveAems1CompatibilitySystem(void)
{
    A1cClassDesc *classes;
    int i;

    if (gpA1cSystemDesc == 0) {
        return -4;
    }
    classes = gpA1cSystemDesc->mpClasses;
    Csis::System::Lock();
    for (i = 0; i < gpA1cSystemDesc->mNumClasses; i++) {
        Csis::Class::UnsubscribeConstructorFast(&classes[i].mClass, &classes[i].mConstructorClient);
    }
    Csis::System::Unlock();
    gpA1cSystemDesc = 0;
    gpA1cAllocator = 0;
    return 0;
}

}
