#include "GameObject.h"



CGameObject::CGameObject()
{
	mpChildObject = nullptr;
	mpNode        = nullptr;
	mBasicLookVector = Vector3::UNIT_Z;
}


CGameObject::~CGameObject()
{
	if (mpChildObject) delete mpChildObject;
}

void CGameObject::buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName)
{
	mpNode = pSceneMgr->getSceneNode(objName);
	mpEntity = pSceneMgr->getEntity(objName);
}

void CGameObject::basicRotate(Vector3 & toLook)
{
	Quaternion rot = Vector3::UNIT_Z.getRotationTo(toLook);
	mpNode->rotate(rot);
	mBasicLookVector = mpNode->getOrientation().zAxis().normalisedCopy();
}
