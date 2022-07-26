#pragma once
#include "utilities.h"
#include "Sprite2D.h"

class Bot
{
private:
	std::shared_ptr<Sprite2D> m_Bot;
	std::vector<Vector2>	m_vectoMove = { Vector2(112.0f, 342.0f), Vector2(368.0f, 342.0f), Vector2(368.0f, 543.0f), Vector2(176.0f, 543.0f), Vector2(176.0f, 662.0f),
	Vector2(240.0f, 662.0f), Vector2(240.0f, 726.0f)};
	int hp;
	bool active = false;
	bool complete = false;
	int i = 0;
	std::shared_ptr<Sprite2D> m_hp;

public:
	Bot(int h);
	~Bot();

	void SetBot(std::shared_ptr<Sprite2D> Bot);
	std::shared_ptr<Sprite2D> GetBot();
	void SetHP(std::shared_ptr<Sprite2D> hp);
	std::shared_ptr<Sprite2D> GetHP();
	void Update(float deltaTime, int &life);

	void SetActive(bool a);
	bool GetActive();
	bool GetComplete();
	void TakeDame(int damage, int &score);
};