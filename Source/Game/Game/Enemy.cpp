#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Weapon.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Core/MathUtils.h"
bool Enemy::Initialize()
{
    Actor::Initialize();

    // cache off
    
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
void Enemy::Update(float dt)
{
    Actor::Update(dt);

    kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(transform.rotation);
    Player* player = m_scene->GetActor<Player>();
    if (player)
    {
        kiko::Vector2 direction = player->transform.position - transform.position;

        float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());

        transform.rotation += turnAngle * dt;

        float angle = kiko::vec2::Angle(forward, direction.Normalized());
        if (angle < kiko::DegreesToRadians(30.0f)) {
            //make enemy NOT shoot
        }
    }

    transform.position += forward * m_speed * kiko::g_time.getDeltaTime();
    transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
    transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

    //fire weapon
    if (m_fireTimer <= 0)
    {
        // create weapon
        /*kiko::Transform transform{m_transform.position, m_transform.rotation, m_transform.scale};
        std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
        weapon->m_tag = "EnemyBullet";
        m_scene->Add(std::move(weapon));

        m_fireTimer = m_fireRate;*/
    }
    else m_fireTimer -= dt;

    // check health
    if (m_health <= 0.0f) {
        destroyed = true;
    }
}

void Enemy::OnCollision(Actor* other)
{
    //Player* p = dynamic_cast<Player*>(other);
    

    if (other->tag == "PlayerBullet") {
        m_health -= 5.0f;
        //dynamic_cast<SpaceGame*>(m_game)->AddPoints(100);
        kiko::EventManager::Instance().DispatchEvent("AddPoints", 100);
    }
}
