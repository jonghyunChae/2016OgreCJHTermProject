#pragma once

class PlayInfoStatus
{
public:
	PlayInfoStatus();
	~PlayInfoStatus();

public:
	void init();

private:
	int hp : 10;
	int hpMax : 10;
	int damage : 6;

	bool isDeath : 1;

	float attackRange;
	float attackSpeed;
};

