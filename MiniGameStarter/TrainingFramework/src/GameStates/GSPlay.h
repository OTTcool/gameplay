#pragma once
#include "GameStateBase.h"
#include "Gun.h"
#include "Bot.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;
class Gun;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	int m_KeyPress;
	float spawnTime = 0.0f;
	float endTime = 0.0f;

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Text>		m_result;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Sprite2D>>	m_listObj;

	std::vector<std::string> m_tileMatrix;
	std::vector<std::shared_ptr<Sprite2D>> m_listTile;
	std::vector<std::shared_ptr<Sprite2D>> m_listPlat;
	std::vector<std::shared_ptr<Sprite2D>> m_listGun;

	std::shared_ptr<Sprite2D>	m_uiBuild;
	std::vector<std::shared_ptr<Gun>> m_guns;

	std::list<std::shared_ptr<Bot>>	m_listBot;
	int score_Game;
	int life = 10;
	bool checkWin();

};

