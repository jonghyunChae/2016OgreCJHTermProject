#pragma once

#include "GameObject.h"
class AbsorbMarble : public CGameObject
{
public:
	AbsorbMarble();
	~AbsorbMarble();

	virtual void buildObject(Root* pRoot, SceneManager* pSceneMgr, int index);
	virtual void update(float fFrameTime);

public:
	bool allocMarble(Vector3 & pos);

private:

};

