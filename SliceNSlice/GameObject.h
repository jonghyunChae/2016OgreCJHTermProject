#pragma once
#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "common.h"

class CGameObject
{

public:
	CGameObject();
	virtual ~CGameObject();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr) = 0;
	virtual void update(float fFrameTime) = 0;

public:
	void setChildObject(CGameObject * pChild) { mpChildObject = pChild; }
	CGameObject * getChildObject() { return mpChildObject; }

	const Vector3& getPosition() { return mpNode->getPosition(); }

	SceneNode * const getNode() { return mpNode; }
	void setNode(SceneNode * pNode) { mpNode = pNode; }

protected:
	SceneNode * mpNode;
	SceneNode * mpCameraNode;

	CGameObject * mpChildObject;

};

#endif