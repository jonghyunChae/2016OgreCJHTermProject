#include "Player.h"

CPlayer::CPlayer() : CCharacter()
{
	mCamera = nullptr;
	mpCameraNode = nullptr;
}

CPlayer::~CPlayer()
{
}

void CPlayer::buildObject(Root* pRoot, SceneManager* pSceneMgr, const char * objName)
{
	_buildCamera(pRoot, pSceneMgr);

	mCharacterRoot = pSceneMgr->getRootSceneNode()->createChildSceneNode("ProfessorRoot");
	mCharacterYaw = mCharacterRoot->createChildSceneNode("ProfessorYaw");

	mCameraYaw = mCharacterRoot->createChildSceneNode("CameraYaw", Vector3(0.0f, 120.0f, 0.0f));
	mCameraPitch = mCameraYaw->createChildSceneNode("CameraPitch");
	mCameraHolder = mCameraPitch->createChildSceneNode("CameraHolder", Vector3(0.0f, 80.0f, 500.0f));

	Entity* mCharacterEntity = pSceneMgr->createEntity(objName, "DustinBody.mesh"); //"paladin.MESH.mesh");
	SceneNode* playerNode = pSceneMgr->getRootSceneNode()->createChildSceneNode(objName, Vector3::ZERO);
	//playerNode->attachObject(mCharacterEntity);

	//mCharacterEntity = pSceneMgr->createEntity("Professor", "DustinBody.mesh");
	mCharacterYaw->attachObject(mCharacterEntity);
	//mCharacterEntity->setCastShadows(true);

	mCameraHolder->attachObject(mCamera);
	mCamera->lookAt(mCameraYaw->getPosition());

	setNode(mCharacterRoot);

	CCharacter::buildObject(pRoot, pSceneMgr, objName);
//	Entity* entity2 = pSceneMgr->createEntity("Camera", "DustinBody.mesh");
	//mpCameraNode          = mCharacterYaw
	mCameraHolder->setInheritOrientation(true);
//	mpCameraNode->attachObject(entity2);

}

void CPlayer::update(float frameTime)
{
	CCharacter::update(frameTime);

	const Vector3& vecPos = mpNode->getPosition();
	const Vector3& vecCamera = mCameraHolder->getPosition();

	mCamera->setPosition(vecPos + vecCamera);
	mCamera->lookAt(vecPos - vecCamera);
}

void CPlayer::_buildCamera(Root * pRoot, SceneManager * pSceneMgr)
{
	mCamera = pSceneMgr->getCamera("main");

	//mCamera->setPosition(0.0f, 150.0f, 500.0f);
	//mCamera->lookAt(0.0f, 50.0f, 0.0f);

	setCamera(mCamera);

}
