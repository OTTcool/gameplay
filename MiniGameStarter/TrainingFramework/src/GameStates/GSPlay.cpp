#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	score_Game = 6;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	//tile
	std::ifstream fileInput("TileMap.txt");
	int i = 0;
	while (!fileInput.eof())
	{
		std::string s;
		if (fileInput >> s)
		{
			m_tileMatrix.push_back(s);
		}
	}
	fileInput.close();

	texture = ResourceManagers::GetInstance()->GetTexture("tile.tga");
	std::shared_ptr<Sprite2D> tileTemp = std::make_shared<Sprite2D>(model, shader, texture);
	tileTemp->SetSize(64, 64);
	m_listTile.push_back(tileTemp);

	texture = ResourceManagers::GetInstance()->GetTexture("tile_gtt.tga");
	tileTemp = std::make_shared<Sprite2D>(model, shader, texture);
	tileTemp->SetSize(64, 64);
	m_listTile.push_back(tileTemp);

	texture = ResourceManagers::GetInstance()->GetTexture("tile_tn.tga");
	tileTemp = std::make_shared<Sprite2D>(model, shader, texture);
	tileTemp->SetSize(64, 64);
	m_listTile.push_back(tileTemp);

	texture = ResourceManagers::GetInstance()->GetTexture("tile_gun.tga");
	tileTemp = std::make_shared<Sprite2D>(model, shader, texture);
	tileTemp->SetSize(64, 64);
	m_listTile.push_back(tileTemp);

	texture = ResourceManagers::GetInstance()->GetTexture("ui_build.tga");
	m_uiBuild = std::make_shared<Sprite2D>(model, shader, texture);
	m_uiBuild->SetSize(192, 64);

	//list foundation
	texture = ResourceManagers::GetInstance()->GetTexture("tile_gun.tga");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (m_tileMatrix[i][j] == '7')
			{			
				tileTemp = std::make_shared<Sprite2D>(model, shader, texture);
				tileTemp->SetSize(64, 64);
				tileTemp->Set2DPosition(48 + j * 64, 150 + i * 64);

				m_listPlat.push_back(tileTemp);
			}
		}
	}
	texture = ResourceManagers::GetInstance()->GetTexture("Plane.tga");
	tileTemp = std::make_shared<Sprite2D>(model, shader, texture);
	tileTemp->SetSize(96, 96);
	tileTemp->Set2DPosition(120, 120);
	m_listObj.push_back(tileTemp);
	texture = ResourceManagers::GetInstance()->GetTexture("tower.tga");
	tileTemp = std::make_shared<Sprite2D>(model, shader, texture);
	tileTemp->SetSize(128, 128);
	tileTemp->Set2DPosition(240, 730);
	m_listObj.push_back(tileTemp);
	//bot
	std::shared_ptr<Bot> bot;
	for (int i = 0; i < 10; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("bot1.tga");
		bot = std::make_shared<Bot>(100);
		bot->SetBot(std::make_shared<Sprite2D>(model, shader, texture));
		bot->GetBot()->Set2DPosition(112, 150);
		bot->GetBot()->SetSize(64, 64);
		texture = ResourceManagers::GetInstance()->GetTexture("health.tga");
		std::shared_ptr<Sprite2D> hp = std::make_shared<Sprite2D>(model, shader, texture);
		bot->SetHP(hp);
		m_listBot.push_back(bot);
	}

	for (int i = 0; i < 10; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("bot2.tga");
		bot = std::make_shared<Bot>(140);
		bot->SetBot(std::make_shared<Sprite2D>(model, shader, texture));
		bot->GetBot()->Set2DPosition(112, 150);
		bot->GetBot()->SetSize(64, 64);
		texture = ResourceManagers::GetInstance()->GetTexture("health.tga");
		std::shared_ptr<Sprite2D> hp = std::make_shared<Sprite2D>(model, shader, texture);
		bot->SetHP(hp);
		m_listBot.push_back(bot);
	}

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
			GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	m_result = std::make_shared< Text>(shader, font, "", TextColor::RED, 3.0);
	m_result->Set2DPosition(Vector2(90, 400));
	m_KeyPress = 0;

}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress |= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress |= 1<<1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress |= 1<<2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress |= 1<<3;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}
bool isClickUI = false;
void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}

	if (!isClickUI)
	{
		for (auto it : m_listPlat)
		{
			if ((x > it->GetPosition().x - 64 / 2) && (x < it->GetPosition().x + 64 / 2)
				&& (y > it->GetPosition().y - 64 / 2) && (y < it->GetPosition().y + 64 / 2))
			{
				// action 
				if (it->GetHaveGun() != 0)
				{

				}
				else {
					m_uiBuild->Set2DPosition(it->GetPosition().x, it->GetPosition().y - 64);
					it->SetUiBuild(true);
					isClickUI = true;
				}
			}
		}
	}
	
	else {
		for (auto it : m_listPlat)
		{
			if (it->IsUiBuild() && score_Game >= 3)
			{				
				if ((x > m_uiBuild->GetPosition().x - 64 * 3 / 2) && (x < m_uiBuild->GetPosition().x - 64 / 2)
					&& (y > m_uiBuild->GetPosition().y - 64 / 2) && (y < m_uiBuild->GetPosition().y + 64 / 2) )
				{
					// The button is being pressed down -> gun1
					it->SetHaveGun(1);
					std::shared_ptr<Gun> gun = std::make_shared<Gun>();
					m_guns.push_back(gun);

					auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
					auto texture = ResourceManagers::GetInstance()->GetTexture("gun1.tga");
					auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

					m_guns.back()->SetGun(std::make_shared<Sprite2D>(model, shader, texture));
					m_guns.back()->GetGun()->SetSize(64, 64);
					m_guns.back()->GetGun()->Set2DPosition(it->GetPosition().x, it->GetPosition().y);
					texture = ResourceManagers::GetInstance()->GetTexture("gun1fire.tga");
					m_guns.back()->SetFire(std::make_shared<Sprite2D>(model, shader, texture));
					m_guns.back()->GetFire()->SetSize(64, 96);
					m_guns.back()->GetFire()->Set2DPosition(it->GetPosition().x, it->GetPosition().y);
					score_Game -= 3;
					it->SetUiBuild(false);
					isClickUI = false;
				}
				else if ((x > m_uiBuild->GetPosition().x - 64 / 2) && (x < m_uiBuild->GetPosition().x + 64 / 2)
					&& (y > m_uiBuild->GetPosition().y - 64 / 2) && (y < m_uiBuild->GetPosition().y + 64 / 2) )
				{
					// The button is being pressed down -> gun2
					it->SetHaveGun(2);
					std::shared_ptr<Gun> gun = std::make_shared<Gun>();
					m_guns.push_back(gun);
					auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
					auto texture = ResourceManagers::GetInstance()->GetTexture("gun2.tga");
					auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

					m_guns.back()->SetGun(std::make_shared<Sprite2D>(model, shader, texture));
					m_guns.back()->GetGun()->SetSize(64, 64);
					m_guns.back()->GetGun()->Set2DPosition(it->GetPosition().x, it->GetPosition().y);
					texture = ResourceManagers::GetInstance()->GetTexture("gun2fire.tga");
					m_guns.back()->SetFire(std::make_shared<Sprite2D>(model, shader, texture));
					m_guns.back()->GetFire()->SetSize(64, 96);
					m_guns.back()->GetFire()->Set2DPosition(it->GetPosition().x, it->GetPosition().y);
					score_Game -= 3;
					it->SetUiBuild(false);
					isClickUI = false;
			
				}
				else if ((x > m_uiBuild->GetPosition().x + 64 / 2) && (x < m_uiBuild->GetPosition().x + 64 * 3 / 2)
					&& (y > m_uiBuild->GetPosition().y - 64 / 2) && (y < m_uiBuild->GetPosition().y + 64 / 2))
				{
					// The button is being pressed down -> gun3
					it->SetHaveGun(3);
					std::shared_ptr<Gun> gun = std::make_shared<Gun>();
					m_guns.push_back(gun);
					auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
					auto texture = ResourceManagers::GetInstance()->GetTexture("gun3.tga");
					auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

					m_guns.back()->SetGun(std::make_shared<Sprite2D>(model, shader, texture));
					m_guns.back()->GetGun()->SetSize(64, 64);
					m_guns.back()->GetGun()->Set2DPosition(it->GetPosition().x, it->GetPosition().y);
					texture = ResourceManagers::GetInstance()->GetTexture("gun3fire.tga");
					m_guns.back()->SetFire(std::make_shared<Sprite2D>(model, shader, texture));
					m_guns.back()->GetFire()->SetSize(64, 96);
					m_guns.back()->GetFire()->Set2DPosition(it->GetPosition().x, it->GetPosition().y);
					score_Game -= 3;
					it->SetUiBuild(false);
					isClickUI = false;
			
				}
				else {
					it->SetUiBuild(false);
					isClickUI = false;
				}
			}
			else {
				it->SetUiBuild(false);
				isClickUI = false;
			}
		}
	}
	
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	if (life > 0)
	{		
		if (checkWin())
		{
			m_result->SetText("You Win!");
			endTime += deltaTime;
			if (endTime > 3.0f)
			{
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
				ResourceManagers::GetInstance()->StopSound("sound_track.mp3");
			}
		}
		else
		{
			std::string gold = std::to_string(score_Game);
			std::string li = std::to_string(life);
			m_score->SetText("Gold: " + gold + "        " + "Life: " + li);
			switch (m_KeyPress)//Handle Key event
			{
			default:
				break;
			}
			for (auto it : m_listButton)
			{
				it->Update(deltaTime);
			}
			spawnTime += deltaTime;
			for (auto bot : m_listBot)
			{
				if (spawnTime > 2.2f && !bot->GetActive() && !bot->GetComplete())
				{
					bot->SetActive(true);
					spawnTime = 0.0f;
				}
				if (bot->GetActive() && !bot->GetComplete())
				{
					bot->Update(deltaTime, life);
				}

			}
			// check can gun attack
			for (auto gun : m_guns)
			{
				gun->Update(deltaTime);
				for (auto bot : m_listBot)
				{
					if (bot->GetActive() && gun->Attack(bot))
					{
						bot->TakeDame(gun->GetDamage(), score_Game);
						break;
					}
				}
			}
		}
	}
	else 
	{
		m_result->SetText("You Lose!");
		endTime += deltaTime;
		if (endTime > 3.0f) 
		{
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
			ResourceManagers::GetInstance()->StopSound("sound_track.mp3");
		}
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	//tile
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (m_tileMatrix[i][j] == '0')
			{
				m_listTile.at(0)->Set2DPosition(48 + j*64, 150 + i*64);
				m_listTile.at(0)->Draw();
			}
			if (m_tileMatrix[i][j] == '1')
			{
				m_listTile.at(2)->Set2DPosition(48 + j * 64, 150 + i * 64);
				m_listTile.at(2)->SetRotation(Vector3(0.0f, 0.0f, PI / 2));
				m_listTile.at(2)->Draw();
			}
			if (m_tileMatrix[i][j] == '2')
			{
				m_listTile.at(2)->Set2DPosition(48 + j * 64, 150 + i * 64);
				m_listTile.at(2)->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
				m_listTile.at(2)->Draw();
			}
			if (m_tileMatrix[i][j] == '3')
			{
				m_listTile.at(1)->Set2DPosition(48 + j * 64, 150 + i * 64);
				m_listTile.at(1)->SetRotation(Vector3(PI, 0.0f, 0.0f));
				m_listTile.at(1)->Draw();
			}
			if (m_tileMatrix[i][j] == '4')
			{
				m_listTile.at(1)->Set2DPosition(48 + j * 64, 150 + i * 64);
				m_listTile.at(1)->SetRotation(Vector3(0.0f, PI, 0.0f));
				m_listTile.at(1)->Draw();
			}
			if (m_tileMatrix[i][j] == '5')
			{
				m_listTile.at(1)->Set2DPosition(48 + j * 64, 150 + i * 64);
				m_listTile.at(1)->SetRotation(Vector3(0.0f, 0.0f, PI));
				m_listTile.at(1)->Draw();
			}
			if (m_tileMatrix[i][j] == '6')
			{
				m_listTile.at(1)->Set2DPosition(48 + j * 64, 150 + i * 64);
				m_listTile.at(1)->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
				m_listTile.at(1)->Draw();
			}		
		}
	}

	for (auto it : m_listPlat)
	{
		it->Draw();
		if (it->IsUiBuild() && it->GetHaveGun() == 0)
		{
			m_uiBuild->Draw();
		}

	}
	if (m_guns.size())
	{
		for (auto it : m_guns)
		{
			if (it->IsAttacking()) {
				it->GetFire()->Draw();
			}
			else it->GetGun()->Draw();
		}
	}
	for (auto bot : m_listBot)
	{
		if (bot->GetActive())
		{
			bot->GetBot()->Draw();
			bot->GetHP()->Draw();
		}
	}
	for (auto it : m_listPlat)
	{
		if (it->IsUiBuild() && it->GetHaveGun() == 0)
		{
			m_uiBuild->Draw();
		}
	}
	
	for (auto i : m_listObj)
	{
		i->Draw();
	}
	if (life <= 0 || checkWin())
	{
		m_result->Draw();
	}
}

bool GSPlay::checkWin()
{
	for (auto i : m_listBot)
	{
		if (!i->GetComplete())
		{
			return false;
		}
	}
	return true;
}
