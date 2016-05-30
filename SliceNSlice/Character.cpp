#include "Character.h"

CCharacter::CCharacter() : CDynamicObject()
{
	mSceneMgr = nullptr;

	mAutoChangeAnim = true;
	mOffsetSpeed = 0.f;

	mAnimationState = nullptr;
	mCurrentNode = nullptr;
	mBeforeState = eIDLE;


	mOffsetVector = Vector3::ZERO;
}

CCharacter::~CCharacter()
{
}

void CCharacter::buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName)
{
	CDynamicObject::buildObject(pRoot, pSceneMgr, objName);
}

void CCharacter::update(float frameTime)
{
	CDynamicObject::update(frameTime);

	_animUpdate(frameTime);
#if 0
	if (mDir != Vector3::ZERO && mState == eWALKING)
	{
		if (getAnimState()->hasEnded())
		{
			_initNodeOffset();
		}
		else
		{
			Vector3 offset = -mDir * mOffsetSpeed * getAnimState()->getTimePosition();
			mOffsetVector += offset;
			mCurrentNode->setPosition(-offset);
		}
	}
#endif
}

bool CCharacter::damaged(int dmg)
{
	return mStatus.damaged(dmg);
}

void CCharacter::insertAnimationState(SceneNode * bodyRoot, OBJ_STATE state, string & meshName, string & animName)
{
	Entity * entity = mSceneMgr->createEntity(animName, meshName);
	entity->setCastShadows(true);

	SceneNode * node = bodyRoot->createChildSceneNode(animName, Vector3::ZERO);
	node->attachObject(entity);
	node->rotate(Vector3(1, 0, 0), Degree(90));
	//node->setInheritScale(false);
	node->setVisible(false);
	mCurrentNode = mpNode;

	mAnimList[state] = animName; 
}

void CCharacter::setAnimation(string name, bool loop)
{
	if (mAnimationState) mAnimationState->setEnabled(false);

	//mpEntity->setVisible(false);
	mpEntity = mSceneMgr->getEntity(name);
	mpEntity->setCastShadows(true);
	//mpEntity->setVisible(true);

	mCurrentNode->setVisible(false);
	mCurrentNode = mSceneMgr->getSceneNode(name);
	mCurrentNode->setVisible(true);

	mAnimationState = mpEntity->getAnimationState("Anim");
	mAnimationState->setEnabled(true);
	mAnimationState->setLoop(loop);
	mAnimationState->setTimePosition(0);
}

void CCharacter::setAnimation(OBJ_STATE stat, bool loop)
{
	setAnimation(mAnimList[stat], loop);
}

void CCharacter::_rotate(float frameTime)
{
}

void CCharacter::_walking(float frameTime)
{
}

void CCharacter::_checkAnimState(OBJ_STATE before, OBJ_STATE after)
{
	if (before != eIDLE && after == eIDLE)
	{
		_initNodeOffset();
		//mOffsetVector = Vector3::ZERO;
		setAnimation(mAnimList[eIDLE]);
	}
	if (before == eIDLE && after != eIDLE) 
		setAnimation(mAnimList[eWALKING]);
}

void CCharacter::_initNodeOffset()
{
	mCurrentNode->setPosition(Vector3(0, 0, 0));
	//mCurrentNode->translate(-mOffsetVector);
	mOffsetVector = Vector3::ZERO;
}

void CCharacter::_animUpdate(float frameTime)
{
	if (mAutoChangeAnim)
	{
		if (false == getAnimState()->getLoop() && getAnimState()->hasEnded())
			setAnimation(eIDLE);

		_checkAnimState(mBeforeState, mState);
		mBeforeState = mState;
	}
	mAnimationState->addTime(frameTime);
}
