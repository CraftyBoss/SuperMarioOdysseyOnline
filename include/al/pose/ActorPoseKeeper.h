#pragma once

#include "sead/math/seadMatrix.h"
#include "sead/math/seadQuat.h"
#include "sead/math/seadVector.h"

namespace al
{
    class ActorPoseKeeperBase
    {
    public:
        ActorPoseKeeperBase();

        virtual const sead::Vector3<float>& getRotate() const;
        virtual const sead::Vector3<float>& getScale() const;
        virtual const sead::Vector3<float>& getVelocity() const;
        virtual const sead::Vector3<float>& getFront() const;
        virtual const sead::Vector3<float>& getUp() const;
        virtual const sead::Quat<float>& getQuat() const;
        virtual const sead::Vector3<float>& getGravity() const;
        virtual const sead::Matrix34<float>& getMtx() const;
        virtual sead::Vector3<float>* getRotatePtr();
        virtual sead::Vector3<float>* getScalePtr();
        virtual sead::Vector3<float>* getVelocityPtr();
        virtual sead::Vector3<float>* getFrontPtr();
        virtual sead::Vector3<float>* getUpPtr();
        virtual sead::Quat<float>* getQuatPtr();
        virtual sead::Vector3<float>* getGravityPtr();
        virtual sead::Matrix34<float>* getMtxPtr();
        virtual void updatePoseTrans(const sead::Vector3<float> &) = 0;
        virtual void updatePoseRotate(const sead::Vector3<float> &) = 0;
        virtual void updatePoseQuat(const sead::Quat<float> &) = 0;
        virtual void updatePoseMtx(const sead::Matrix34<float> *) = 0;
        virtual void copyPose(const al::ActorPoseKeeperBase *);
        virtual void calcBaseMtx(sead::Matrix34<float> *) = 0;

        sead::Vector3<float> mTranslation; // _8

        static const sead::Vector3<float> sDefaultVelocity;
    };

    class ActorPoseKeeperTRSV : public ActorPoseKeeperBase
    {
    public:
        virtual const sead::Vector3<float>& getRotate() const;
        virtual const sead::Vector3<float>& getScale() const;
        virtual const sead::Vector3<float>& getVelocity() const;

        virtual sead::Vector3<float>* getRotatePtr();
        virtual sead::Vector3<float>* getScalePtr();
        virtual sead::Vector3<float>* getVelocityPtr();

        virtual void updatePoseTrans(const sead::Vector3<float> &);
        virtual void updatePoseRotate(const sead::Vector3<float> &);
        virtual void updatePoseQuat(const sead::Quat<float> &);
        virtual void updatePoseMtx(const sead::Matrix34<float> *);

        virtual void calcBaseMtx(sead::Matrix34<float> *);

        sead::Vector3<float> mRotation; // _14
        sead::Vector3<float> mScale; // _20
        sead::Vector3<float> mVelocity; // _2C
    };
};