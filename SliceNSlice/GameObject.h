#pragma once
#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "common.h"

class CGameObject
{

public:
	CGameObject();
	virtual ~CGameObject();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName);
	virtual void update(float fFrameTime) = 0;

public:
	void basicRotate(Vector3 & toLook);
	Vector3& getBasicLookVector() { return mBasicLookVector; }

	void setChildObject(CGameObject * pChild) { mpChildObject = pChild; }
	CGameObject * getChildObject() { return mpChildObject; }

	const Vector3& getPosition() { return mpNode->getPosition(); }

	SceneNode * const getNode() { return mpNode; }
	void setNode(SceneNode * pNode) { mpNode = pNode; }

protected:
	SceneNode * mpNode;
	Entity    * mpEntity;

	CGameObject * mpChildObject;

private:
	Vector3  mBasicLookVector;
};

#endif