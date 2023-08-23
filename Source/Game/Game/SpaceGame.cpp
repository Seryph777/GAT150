#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
//#include "StaticModel.h"

#include "Framework/Scene.h"
#include "Framework/ResourceManager.h"
#include "Framework/SpriteComponent.h"
#include "Framework/ModelRenderComponent.h"
#include "Framework/EnginePhysicsComponent.h"
#include "Framework/CircleCollisionComponent.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/ModelManager.h"


bool SpaceGame::Initialize()
{
	// create font & text objects
    //m_font = std::make_shared<kiko::Font>("ArcadeClassic.ttf", 50);
    m_font = GET_RESOURCE(kiko::Font,"ArcadeClassic.ttf", 50);
    m_titleText = std::make_unique<kiko::Text>(m_font);
    m_titleText->Create(kiko::g_renderer, "SpaceGame", kiko::Color{ 1, 1, 1, 1 });

    m_scoreText = std::make_unique<kiko::Text>(m_font);
    m_scoreText->Create(kiko::g_renderer, "Score" + std::to_string(m_score), kiko::Color{ 1, 1, 1, 1 });

	// add audio
    kiko::setFilePath("Assets");
	kiko::g_audioSystem.AddAudio("hit", "Hit.wav");
	kiko::g_audioSystem.AddAudio("death", "StarWars_DeathSound.wav");
    kiko::g_audioSystem.AddAudio("Music", "ClassicArcadeMusic.wav");

	//Scene & Players
    m_scene = std::make_unique<kiko::Scene>();
    m_scene->Load("scene.json");
    m_scene->Initialize();

    //add events
    EVENT_SUBSCRIBE("AddPoints", SpaceGame::OnAddPoints);  //// kiko::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&SpaceGame::OnAddPoints, this, std::placeholders::_1));
    EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead); //// kiko::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&SpaceGame::OnPlayerDead, this, std::placeholders::_1));
    
    


	return false;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
    switch (m_state)
    {
    case SpaceGame::eState::Title:
    {
        //std::unique_ptr<StaticModel> Title = std::make_unique<StaticModel>(200.0f, kiko::Pi, kiko::Transform{ {400, 300}, 0, 6 }, kiko::g_modelManager.Get("Title.txt"));
        //m_scene->Add(std::move(Title));
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_G))
        {
            m_state = eState::StartGame;
            /*auto actor = m_scene->GetActorByName("Background");
            if(actor) actor->active = false;*/
            kiko::g_audioSystem.PlayOneShot("death");
        }
        
        break;
    }
    case SpaceGame::eState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_scene->RemoveAll(false);
        m_state = eState::StartLevel;
        break;
    case SpaceGame::eState::StartLevel:
    {
        // Create Play
        kiko::setFilePath("Assets");
        std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ {400, 300}, 0, 3 });
        player->tag = "Player";
        player->m_game = this;

        // Create Components -- Need to copy to Enemy // replace with CREATE_CLASS macro
        std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
        kiko::res_t<kiko::Texture> m_model = GET_RESOURCE(kiko::Texture,"Ship_1_A_Large.png", kiko::g_renderer);
        player->AddComponent(std::move(component));

        auto physicsComponent = std::make_unique<kiko::EnginePhysicsComponent>();
        //physicsComponent->m_damping = 0.9f;
        player->AddComponent(std::move(physicsComponent));

        auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
        collisionComponent->radius = 30.0f;

        player->Initialize();
        m_scene->Add(std::move(player));

        
    }
    m_state = eState::Game;
        break;
    case SpaceGame::eState::Game:
        m_spawnTimer += dt;
        if (m_spawnTimer >= m_spawnTime) {
            m_spawnTimer = 0;
            kiko::setFilePath("Assets");
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{{400, 300}, kiko::randomf(kiko::TwoPi), 5});
            enemy->tag = "Enemy";
            enemy->m_game = this;
            std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
            kiko::res_t<kiko::Texture> texture = GET_RESOURCE(kiko::Texture,"Ship_1_A_Large.png", kiko::g_renderer);
            enemy->AddComponent(std::move(component));

            m_scene->Add(std::move(enemy));
        }
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_G))
        {
            kiko::g_audioSystem.PlayOneShot("hit", false);
        }
        m_scene->Draw(kiko::g_renderer);
        
        break;
    case eState::PlayerDeadStart:
        m_stateTimer = 3.0f;
        m_lives -= 1;
        if (m_lives == 0) m_state = eState::GameOver;
        else m_state = eState::PlayerDead;
        kiko::g_audioSystem.PlayOneShot("death");
        break;
    case SpaceGame::eState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0.0f)
        {
            m_state = eState::StartLevel;
        }
        break;
    case SpaceGame::eState::GameOver:
        m_stateTimer -= dt;
        {
            m_scene->RemoveAll();
            m_state = eState::Title;
        }
        break;

    }

    m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), {1, 1, 1, 1});
    m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
    kiko::g_particleSystem.Draw(kiko::g_renderer);
    m_scene->Draw(kiko::g_renderer);

    m_titleText->Draw(kiko::g_renderer, 100, 100);

    m_scoreText->Draw(kiko::g_renderer, 100, 200);
    

}

void SpaceGame::OnAddPoints(const kiko::Event& event)
{
    m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const kiko::Event& event)
{
    m_lives--;
    m_state = eState::PlayerDeadStart;
}
