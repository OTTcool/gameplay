#include "Bot.h"

Bot::Bot(int h)
{
	hp = h;
}

Bot::~Bot()
{
}

void Bot::SetBot(std::shared_ptr<Sprite2D> Bot)
{
	m_Bot = Bot;
}

std::shared_ptr<Sprite2D> Bot::GetBot()
{
	return m_Bot;
}

void Bot::SetHP(std::shared_ptr<Sprite2D> hp)
{
	m_hp = hp;
	m_hp->SetSize(64, 10);
	m_hp->Set2DPosition(m_Bot->GetPosition().x - 16, m_Bot->GetPosition().y - 20);
}

std::shared_ptr<Sprite2D> Bot::GetHP()
{
	return m_hp;
}

void Bot::SetActive(bool a)
{
	active = a;
}
bool Bot::GetActive()
{
	return active;
}

bool Bot::GetComplete()
{
	return complete;
}

void Bot::TakeDame(int damage, int &score)
{
	hp -= damage;

	m_hp->SetSize(64 * hp / 100, 10);
	if (hp <= 0)
	{
		active = false;
		complete = true;
		
		score++;
	}
}

void Bot::Update(float deltaTime, int &life)
{
	//x, y
	if (abs(m_vectoMove.at(i).x - m_Bot->GetPosition().x) > 1.f)
	{
		if (m_vectoMove.at(i).x - m_Bot->GetPosition().x < 0.f) {
			m_Bot->Set2DPosition(m_Bot->GetPosition().x - deltaTime * 60, m_Bot->GetPosition().y); 
			m_hp->Set2DPosition(m_hp->GetPosition().x - deltaTime * 60, m_hp->GetPosition().y);
		}
			
		else {
			m_Bot->Set2DPosition(m_Bot->GetPosition().x + deltaTime * 60, m_Bot->GetPosition().y);
			m_hp->Set2DPosition(m_hp->GetPosition().x + deltaTime * 60, m_hp->GetPosition().y);
		}

	}

	if (abs(m_vectoMove.at(i).y - m_Bot->GetPosition().y) > 1.f)
	{
		m_Bot->Set2DPosition(m_Bot->GetPosition().x, m_Bot->GetPosition().y + deltaTime * 60);
		m_hp->Set2DPosition(m_hp->GetPosition().x, m_hp->GetPosition().y + deltaTime * 60);
	}
	if ((abs(m_vectoMove.at(i).y - m_Bot->GetPosition().y) <= 1.f) && (abs(m_vectoMove.at(i).x - m_Bot->GetPosition().x) <= 1.f)) i++;
	

	if (i >= m_vectoMove.size()) {
		active = false;
		complete = true;
		life--;
	}	
}