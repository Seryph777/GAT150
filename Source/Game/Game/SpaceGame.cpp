#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"


bool SpaceGame::Initialize()
{
	// Create Font / Text Objects
	//m_font = GET_RESOURCE(kiko::Font, "ArcadeClassic.ttf", 24); //std::make_shared<kiko::Font>("ArcadeClassic.ttf", 24);
	kiko::setFilePath("Assets");
	m_scoreText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "ArcadeClassic.ttf", 24));
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_gameoverText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "ArcadeClassic.ttf", 24));
	m_gameoverText->Create(kiko::g_renderer, "Game Over", kiko::Color{ 1, 1, 1, 1 });

	// Load Audio
	kiko::g_audioSystem.AddAudio("Player_Death", "Audio/StarWars_DeathSound.wav");
	kiko::g_audioSystem.AddAudio("Enemy_Death", "Audio/hit.wav");
	kiko::g_audioSystem.AddAudio("Music_Loop", "Audio/ClassicArdaceMusic.wav");

	// Create Scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("Scenes/SpaceScene.json");
	m_scene->Initialize();

	// Add Events
	EVENT_SUBSCRIBE("OnAddPoints", SpaceGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

	return true;
}

void SpaceGame::Shutdown()
{
	//
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			this->m_state = eState::StartGame;
			//auto actor = m_scene->GetActorByName("Background")->active;
		}
		break;
	case SpaceGame::StartGame:
		this->m_score = 0;
		this->m_lives = 3;
		this->m_state = eState::StartLevel;
		break;
	case SpaceGame::StartLevel:
	{
		m_scene->RemoveAll();

		// Create Player
		auto player = INSTANTIATE(Player, "Player");
		player->m_game = this;

		// Create Components From Json File

		player->Initialize();
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
	break;
	case SpaceGame::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0.0f;

			// Create Enemy
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->transform = kiko::Transform{ {kiko::randomf((float)kiko::g_renderer.GetWidth()), kiko::randomf((float)kiko::g_renderer.GetHeight())}, kiko::randomf(kiko::TwoPi), 0.5f };
			enemy->m_game = this;

			// Create Components From Json File

			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		break;
	case eState::PlayerDeadStart:
		kiko::g_audioSystem.PlayOneShot("Music_Loop", false);
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;

		break;
	case SpaceGame::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}


	m_scoreText->Create(kiko::g_renderer, "SCORE " + std::to_string(m_score), { 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 400, 300);
	}
	m_scoreText->Draw(renderer, 40, 40);
}

void SpaceGame::OnAddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const kiko::Event& event)
{
	m_state = eState::PlayerDeadStart;
}