#include "Player.h"

CPlayer::CPlayer() : CCharacter()
{
	mCamera = nullptr;
}

CPlayer::~CPlayer()
{
}

void CPlayer::update(float fFrameTime)
{
	if (mpChildObject) mpChildObject->update(fFrameTime);
}
