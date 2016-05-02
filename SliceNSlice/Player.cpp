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

	Entity* entity1 = pSceneMgr->createEntity(objName, "DustinBody.mesh"); //"paladin.MESH.mesh");
	SceneNode* playerNode = pSceneMgr->getRootSceneNode()->createChildSceneNode(objName, Vector3::ZERO);
	playerNode->attachObject(entity1);
	setNode(playerNode);

	CCharacter::buildObject(pRoot, pSceneMgr, objName);
//	Entity* entity2 = pSceneMgr->createEntity("Camera", "DustinBody.mesh");
	mpCameraNode          = playerNode->createChildSceneNode("Camera", Vector3(0.0f, 200.0f, 400.0f));
	mpCameraNode->setInheritOrientation(true);
//	mpCameraNode->attachObject(entity2);

}

void CPlayer::update(float frameTime)
{
	CCharacter::update(frameTime);

	const Vector3& vecPos = mpNode->getPosition();
	const Vector3& vecCamera = mpCameraNode->getPosition();

	mCamera->setPosition(vecPos + vecCamera);
	mCamera->lookAt(vecPos - vecCamera);
}

void CPlayer::_buildCamera(Root * pRoot, SceneManager * pSceneMgr)
{
	mCamera = pSceneMgr->createCamera("PlayerCamera");

	mCamera->setPosition(0.0f, 150.0f, 500.0f);
	mCamera->lookAt(0.0f, 50.0f, 0.0f);

	setCamera(mCamera);
}
