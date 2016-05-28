#include "Player.h"

CPlayer::CPlayer() : CCharacter()
{
	mCamera = nullptr;
	mpCameraNode = nullptr;

	mCameraDragSpeed = 0.f;
	mOffsetMaxLength = 0.f;

	mOffsetCamera = Vector3::ZERO;
}

CPlayer::~CPlayer()
{
}

void CPlayer::buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName)
{
	mSceneMgr = pSceneMgr;
	mCharacterRoot = pSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerRoot");
	mCharacterYaw = mCharacterRoot->createChildSceneNode("PlayerYaw");

	//Entity* characterEntity = pSceneMgr->createEntity(objName, "DustinBody.mesh"); //"paladin.MESH.mesh");
	//mCharacterYaw->attachObject(characterEntity);
	//characterEntity->setCastShadows(true);

	_buildCamera(pRoot, pSceneMgr);

	mpNode = mCharacterRoot;
	//mpEntity = characterEntity;
}

void CPlayer::update(float frameTime)
{
	CCharacter::update(frameTime);

	if (mCameraDragSpeed == 0.f) return;

	if (mState == eWALKING)
	{
		if (mOffsetCamera.length() < mMaxSpeed)
		{
			const Vector3 direction = mVelocity.normalisedCopy();
			const Vector3 cameraMovVector = -direction * mCameraDragSpeed * frameTime;
			mCameraHolder->translate(cameraMovVector);
			mOffsetCamera += cameraMovVector;
		}
	}
	else
	{
		float fCameraOffsetLength = mOffsetCamera.length();
		if (fCameraOffsetLength > 0)
		{
			const static float minLength = 5.f;
			if (fCameraOffsetLength < minLength)
			{
				mCameraHolder->translate(-mOffsetCamera);
				mOffsetCamera = Vector3::ZERO;
			}
			else
			{
				const Vector3 cameraMovVector = -mOffsetCamera.normalisedCopy() * mCameraDragSpeed * frameTime;
				mCameraHolder->translate(cameraMovVector);
				mOffsetCamera += cameraMovVector;
			}
		}
	}
}

bool CPlayer::mouseMoved(const OIS::MouseEvent & evt)
{
	mCameraYaw->yaw(Degree(-evt.state.X.rel));
	mCameraPitch->pitch(Degree(-evt.state.Y.rel));

	mCameraHolder->translate(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.1f));
	return true;
}

void CPlayer::_buildCamera(Root * pRoot, SceneManager * pSceneMgr)
{
	mCamera = pSceneMgr->getCamera("main");
	setCamera(mCamera);

	mCameraYaw = mCharacterRoot->createChildSceneNode("CameraYaw", Vector3(0.0f, 120.0f, 0.0f));
	mCameraPitch = mCameraYaw->createChildSceneNode("CameraPitch");
	mCameraHolder = mCameraPitch->createChildSceneNode("CameraHolder", Vector3(0.0f, 80.0f, 500.0f));

	mCameraHolder->attachObject(mCamera);
	mCamera->lookAt(mCameraYaw->getPosition());
	mCameraYaw->setInheritOrientation(false);
}
