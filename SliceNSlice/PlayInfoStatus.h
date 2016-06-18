#pragma once

class CCharacter;
class PlayInfoStatus
{
public:
	PlayInfoStatus();
	~PlayInfoStatus();

public:
	void init();

public:
	bool isDeath() { return bDeath; }
	CCharacter * getOwner() { return mpOwner; }

	int getHP() { return hp; }
	float getHPRate() { return (float)hp / (float)hpMax; }
	void healHP(int val); 
	bool damaged(int dmg);
	void setHP(int val) { hpMax = hp = val; }
	void resetHP() { hp = hpMax; }

private:
	int hp : 10;
	int hpMax : 10;
	int damage : 6;

	bool bDeath : 1;

	float attackRange;
	float attackSpeed;

	CCharacter * mpOwner;
};

