#include "DynamicObject.h"



CDynamicObject::CDynamicObject() : CGameObject()
{
	mState			= eIDLE;

	mVelocity       = Vector3::ZERO;
	mDir            = Vector3::ZERO;
	mMaxSpeed       = 0.f;

	mRotatingTime   = 0.f;

	mTargetPos      = Vector3::ZERO;
	mTargetDistance = 0.f;
}

CDynamicObject::~CDynamicObject()
{
}

void CDynamicObject::buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName)
{
	CGameObject::buildObject(pRoot, pSceneMgr, objName);
}

void CDynamicObject::update(float frameTime)
{
	if (mpChildObject) mpChildObject->update(frameTime);

	SceneNode * rotNode = getRotateNode();

	if (mState == eROTATING)
	{
		static const float ROTATION_TIME = 0.3f;
		mRotatingTime = (mRotatingTime > ROTATION_TIME) ? ROTATION_TIME : mRotatingTime;
		mRotatingTime += frameTime;
		const Quaternion delta = Quaternion::Slerp(mRotatingTime / ROTATION_TIME, mSrcQuat, mDestQuat, true);

		rotNode->setOrientation(delta);
		if (mRotatingTime >= ROTATION_TIME)
		{
			mRotatingTime = 0.f;
			mState = eWALKING;
			rotNode->setOrientation(mDestQuat);
		}
	}
	else if (mState == eWALKING)
	{
		if (isMovingToPoint())
		{
			mTargetDistance -= mMaxSpeed * frameTime;
			if (mTargetDistance < 0.1f)
			{
				rotNode->setPosition(mTargetPos);
				mTargetDistance = 0.f;
				changeState(mVelocity, Vector3::ZERO);
				return;
			}
		}
		rotNode->translate(mDir * mMaxSpeed * frameTime);
		
		auto after = rotNode->getPosition();
		if (after.z >= 400.f)
		{
			after.z = 400.f;
			rotNode->setPosition(after);
		}
		else if (after.z <= -400.f)
		{
			after.z = -400.f;
			rotNode->setPosition(after);
		}

		Quaternion rot = getBasicLookVector().getRotationTo(mDir);
		rotNode->setOrientation(rot);
	}
}

bool CDynamicObject::changeState(const Vector3 & before, const Vector3 & afterVelocity)
{
	if (afterVelocity == Vector3::ZERO)
	{
		mState = eIDLE;
		return false;
	}
	else
	{
		mState = eWALKING;
	}

	Vector3 MoveDir = afterVelocity;
	MoveDir.normalise();

	Vector3 Before = before;
	Before.normalise();

	if (Before == MoveDir)
		return false;

	mSrcQuat      = mpNode->getOrientation();
	mDestQuat     = getBasicLookVector().getRotationTo(MoveDir);

	mState        = eROTATING;
	mRotatingTime = 0.f;
	return true;
}

void CDynamicObject::moveToPoint(const Vector3 & pos)
{
	mTargetPos        = pos;
	const Vector3 mypos = mpNode->getPosition();
	Vector3 Direction = mTargetPos - mypos;
	mTargetDistance   = Direction.normalise();

	changeState(mDir, Direction);

	mDir              = Direction;
	mVelocity         = Vector3::ZERO;
}

void CDynamicObject::move(const Vector3 & addVelocity)
{
	Vector3 before  = mVelocity;
	mVelocity	    += addVelocity;

	const Vector3 after = mVelocity;
	mDir = after.normalisedCopy();
	changeState(before, mDir);

	mTargetDistance = 0.f;
}
