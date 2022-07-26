#pragma once
#include "utilities.h"
#include "Sprite2D.h"
#include "Bot.h"

class Gun 
{
protected:
	std::shared_ptr<Sprite2D> m_gun;
	std::shared_ptr<Sprite2D> m_fire;
	int damage;
	float delayTime = 0.f;
	bool attack = false;

public:
	Gun();
	~Gun();
	
	void SetGun(std::shared_ptr<Sprite2D> gun);
	std::shared_ptr<Sprite2D> GetGun();
	void SetFire(std::shared_ptr<Sprite2D> fire);
	std::shared_ptr<Sprite2D> GetFire();

	bool Attack(std::shared_ptr<Bot> bot);
	bool IsAttacking();
	void Update(float deltaTime);
	int GetDamage();
};