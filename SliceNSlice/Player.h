#pragma once

#ifndef __PLAYER_H
#define __PLAYER_H

#include "Character.h"

class CPlayer : public CCharacter
{
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName);
	virtual void update(float fFrameTime);

public:
	Ogre::SceneNode* getYawNode() { return mCharacterYaw; }
	Ogre::SceneNode* getRootNode() { return mCharacterRoot; }

	void setCamera(Camera * pCamera) { mCamera = pCamera; }
	Camera* getCamera() { return mCamera; }

	bool mouseMoved(const OIS::MouseEvent &evt);

	void setCanRotate(bool rot) { mCanRotate = rot; }
	bool getCanRotate() { return mCanRotate; }

protected :
	void setCameraDragSpeed(float speed) { mCameraDragSpeed = speed; }
	void setCameraOffsetMaxLength(float length) { mOffsetMaxLength = length; }

private:
	void _buildCamera(Root* pRoot, SceneManager * pSceneMgr);
	void _updateCamera(float frameTime);
	
private:
	Vector3 mOffsetCamera;
	Camera * mCamera;
	SceneNode * mpCameraNode;

	Ogre::SceneNode* mCharacterRoot;
	Ogre::SceneNode* mCharacterYaw;
	Ogre::SceneNode* mCameraHolder;
	Ogre::SceneNode* mCameraYaw;
	Ogre::SceneNode* mCameraPitch;

private:
	float mCameraDragSpeed;
	float mOffsetMaxLength;

	bool mCanRotate;
};

#endif