#include "GameObject.h"



CGameObject::CGameObject()
{
	mpChildObject = nullptr;
	mpNode        = nullptr;
}


CGameObject::~CGameObject()
{
	if (mpChildObject) delete mpChildObject;
}