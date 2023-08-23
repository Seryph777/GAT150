#include "Input/InputSystem.h"
#include "Framework/Framework.h"

#include "Renderer/Renderer.h"
#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Renderer/Texture.h"

bool Player::Initialize()
{
    Actor::Initialize();

    // cache off
    m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
    auto collisionComponent = GetComponent<kiko::CollisionComponent>();
    if (collisionComponent)
    {
        auto renderComponent = GetComponent<kiko::RenderComponent>();
        if (renderComponent)
        {
            float scale = transform.scale;
            //collisionComponent->m_radius = renderComponent->GetRadius() * scale;;
        }
    }
}

void Player::Update(float dt)
{
    Actor::Update(dt);

    //movement
    float rotate = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
    transform.rotation += rotate * m_turnRate * kiko::g_time.getDeltaTime();

    float thrust = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

    kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(transform.rotation);
    transform.position += forward * m_speed * thrust * kiko::g_time.getDeltaTime();

    auto physicsComponent = GetComponent<kiko::PhysicsComponent>();
    physicsComponent->ApplyForce(forward * m_speed * thrust)


    //tranform position
    transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
    transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

    //fire weapon
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
    {
        auto weapon = INSTANTIATE(Weapon, "Rocket");
        weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
        weapon->Initialize();
        m_scene->Add(std::move(weapon));

        // create weapon
        /*kiko::Transform transform1{m_transform.position, (m_transform.rotation + kiko::DegreesToRadians(10.0f)), m_transform.scale};
        std::unique_ptr<Weapon> weapon1 = std::make_unique<Weapon>( 400.0f, transform1, m_model );
        weapon1->m_tag = "PlayerBullet";
        std::unique_ptr<kiko::SpriteComponent> component1 = std::make_unique<kiko::SpriteComponent>();
        component1->m_texture = GET_RESOURCE(kiko::Texture,"Ship_1_A_Large.png", kiko::g_renderer);
        weapon1->AddComponent(std::move(component1));
        m_scene->Add(std::move(weapon1));

        kiko::Transform transform2{m_transform.position, (m_transform.rotation - kiko::DegreesToRadians(10.0f)), m_transform.scale};
        std::unique_ptr<Weapon> weapon2 = std::make_unique<Weapon>(400.0f, transform2, m_model);
        weapon2->m_tag = "PlayerBullet";
        std::unique_ptr<kiko::SpriteComponent> component2 = std::make_unique<kiko::SpriteComponent>();
        component2->m_texture = GET_RESOURCE(kiko::Texture,"Ship_1_A_Large.png", kiko::g_renderer);
        weapon2->AddComponent(std::move(component2));
        m_scene->Add(std::move(weapon2));

        kiko::EmitterData data;
        data.burst = true;
        data.burstCount = 200;
        data.spawnRate = 0;
        data.angle = 0;
        data.angleRange = kiko::Pi;
        data.lifetimeMin = 0.5f;
        data.lifetimeMin = 0.5f;
        data.speedMin = 150;
        data.speedMax = 150;
        data.damping = 0.5f;
        data.color = kiko::Color{ 1, 1, 1, 1 };
        kiko::Transform transform{ { m_transform.position.x, m_transform.position.y }, 0, 1 };
        auto emitter = std::make_unique<kiko::Emitter>(transform, data);
        emitter->m_lifespan = 1.0f;
        m_scene->Add(std::move(emitter));*/
        
    }
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
    else kiko::g_time.SetTimeScale(1.0f);
    // healt check
    if (m_health <= 0.0f) {
        destroyed = true;
        if (destroyed = true) dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
    }
    
}

void Player::OnCollision(Actor* other)
{
    if (other->tag == "EnemyBullet") {
        destroyed = true;
        kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);

        //m_game->SetLIves(m_game->GetLives() - 1);
        //m_destroyed = true
        // dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDead);
    }

}
