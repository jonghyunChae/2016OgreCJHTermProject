#include "PlayInfoStatus.h"



PlayInfoStatus::PlayInfoStatus()
{
	hp = hpMax = 0;
	damage = 0;

	attackRange = 0.f;
	attackSpeed = 0.f;

	isDeath = false;
}


PlayInfoStatus::~PlayInfoStatus()
{
}

void PlayInfoStatus::init()
{
	hp = hpMax;
	isDeath = false;
}
