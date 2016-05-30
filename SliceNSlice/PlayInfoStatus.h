#pragma once

class CCharacter;
class PlayInfoStatus
{
public:
	PlayInfoStatus();
	~PlayInfoStatus();

public:
	void init();
	bool damaged(int dmg);

public:
	bool isDeath() { return bDeath; }
	CCharacter * getOwner() { return mpOwner; }

private:
	int hp : 10;
	int hpMax : 10;
	int damage : 6;

	bool bDeath : 1;

	float attackRange;
	float attackSpeed;

	CCharacter * mpOwner;
};

