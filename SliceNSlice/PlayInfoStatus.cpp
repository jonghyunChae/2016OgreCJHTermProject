#include "PlayInfoStatus.h"
#include "Character.h"

PlayInfoStatus::PlayInfoStatus()
{
	hp = hpMax = 0;
	damage = 0;

	attackRange = 0.f;
	attackSpeed = 0.f;

	bDeath = false;
}

PlayInfoStatus::~PlayInfoStatus()
{
}

void PlayInfoStatus::init()
{
	hp = hpMax;
	bDeath = false;
}

bool PlayInfoStatus::damaged(int dmg)
{
	hp -= dmg;
	hp = max(0, hp);

	if (hp <= 0)
		bDeath = true;

	return bDeath;
}

void PlayInfoStatus::healHP(int val)
{
	hp += val;
	hp = min(hpMax, hp);
}
