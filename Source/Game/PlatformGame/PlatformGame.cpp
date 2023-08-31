#include "PlatformGame.h"

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


bool PlatformGame::Initialize()
{
    

    // add audio
    kiko::setFilePath("Assets");
    kiko::g_audioSystem.AddAudio("hit", "Hit.wav");
    kiko::g_audioSystem.AddAudio("death", "StarWars_DeathSound.wav");
    kiko::g_audioSystem.AddAudio("Music", "ClassicArcadeMusic.wav");

    //Scene & Players
    m_scene = std::make_unique<kiko::Scene>();
    m_scene->Load("Scene\SpaceScene.json");
    m_scene->Initialize();

    //add events
    EVENT_SUBSCRIBE("AddPoints", PlatformGame::OnAddPoints);  //// kiko::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&PlatformGame::OnAddPoints, this, std::placeholders::_1));
    EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead); //// kiko::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&PlatformGame::OnPlayerDead, this, std::placeholders::_1));




    return false;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
    switch (m_state)
    {
    case PlatformGame::eState::Title:
    {
        
        break;
    }
    case PlatformGame::eState::StartGame:
        
        break;
    case PlatformGame::eState::StartLevel:
    {
       
    }
    m_state = eState::Game;
    break;
    case PlatformGame::eState::Game:
       

        break;
    case eState::PlayerDeadStart:
        
        break;
    case PlatformGame::eState::PlayerDead:
       
        break;
    case PlatformGame::eState::GameOver:
       
        break;

    }

    m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
    m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{
    kiko::g_particleSystem.Draw(kiko::g_renderer);
    m_scene->Draw(kiko::g_renderer);

    m_titleText->Draw(kiko::g_renderer, 100, 100);

    m_scoreText->Draw(kiko::g_renderer, 100, 200);


}

void PlatformGame::OnAddPoints(const kiko::Event& event)
{
    m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const kiko::Event& event)
{
    m_lives--;
    m_state = eState::PlayerDeadStart;
}