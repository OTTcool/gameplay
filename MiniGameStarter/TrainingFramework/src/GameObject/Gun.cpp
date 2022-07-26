#include "Gun.h"

Gun::Gun()
{
	damage = 20;
}

Gun::~Gun()
{
}

void Gun::SetGun(std::shared_ptr<Sprite2D> gun)
{
	m_gun = gun;
}

std::shared_ptr<Sprite2D> Gun::GetGun()
{
	return m_gun;
}

void Gun::SetFire(std::shared_ptr<Sprite2D> f)
{
	m_fire = f;
}

std::shared_ptr<Sprite2D> Gun::GetFire()
{
	return m_fire;
}

bool Gun::IsAttacking()
{
	return attack;
}

bool Gun::Attack(std::shared_ptr<Bot> bot)
{
	if (delayTime > 1.2f)
	{
		if ((bot->GetBot()->GetPosition().x > m_gun->GetPosition().x - 64 * 3 / 2) && (bot->GetBot()->GetPosition().x < m_gun->GetPosition().x + 64 * 3 / 2)
			&& (bot->GetBot()->GetPosition().y > m_gun->GetPosition().y - 64 * 3 / 2) && (bot->GetBot()->GetPosition().y < m_gun->GetPosition().y + 64 * 3 / 2))
		{
			m_gun->SetRotation(Vector3(0.f, 0.f, 0.f));
			m_fire->SetRotation(Vector3(0.f, 0.f, 0.f));
			Vector2 v1 = Vector2(0.f, -64.f);
			Vector2 v2 (bot->GetBot()->GetPosition().x - m_gun->GetPosition().x, bot->GetBot()->GetPosition().y - m_gun->GetPosition().y);
			double cosAngle = (v1.x * v2.x + v1.y * v2.y) / (64) / sqrt(pow(v2.x, 2) + pow(v2.y, 2));

			if (bot->GetBot()->GetPosition().x < m_gun->GetPosition().x)
			{
				m_gun->SetRotation(Vector3(0.f, 0.f, 2*PI - acos(cosAngle)));
				m_fire->SetRotation(Vector3(0.f, 0.f, 2*PI - acos(cosAngle)));
			}
			else {
				m_gun->SetRotation(Vector3(0.f, 0.f, acos(cosAngle)));
				m_fire->SetRotation(Vector3(0.f, 0.f, acos(cosAngle)));
			}
			
			delayTime = 0.f;
			attack = true;
			return true;
		}
	}
	return false;
}

int Gun::GetDamage()
{
	return damage;
}

void Gun::Update(float deltaTime)
{
	delayTime += deltaTime;
	if (attack && delayTime > 0.2f)
	{
		attack = false;
	}
}