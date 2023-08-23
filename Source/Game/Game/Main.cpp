 //Charles Xavier Grant 
 //6/26/2023

#include "Core/Core.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Framework/ResourceManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Physics/PhysicsSystem.h"

#include "Framework/Factory.h"

#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <thread>
#include <map>
#include <array>
#include <list>
#include <functional>




using namespace std;

using vec2 = kiko::Vector2;

class Star
{
public:
    Star(const kiko::Vector2& pos, const kiko::Vector2& vel) :
        m_pos{ pos },
        m_vel{ vel }
    {}

    void Update(int width, int height)
    {
        m_pos += m_vel * kiko::g_time.getDeltaTime();
        if (m_pos.x >= width) m_pos.x = 0;
        if (m_pos.y >= height) m_pos.y = 0;
    }

    void Draw(kiko::Renderer& renderer)
    {
        renderer.DrawPoint(m_pos.x, m_pos.y);
    }

public:
    kiko::Vector2 m_pos;
    kiko::Vector2 m_vel;
};

void print(int i)
{
    cout << i << endl;
}


int main(int argc, char* argv[])
{
 
    //kiko::Factory::Instance().Register<kiko::SpriteComponent>("SpriteComponent");



    INFO_LOG("Initialize Engine...");

    cout << "Initialize...\n";
    kiko::MemoryTracker::Initialize();

    kiko::seedRandom((unsigned int)time(nullptr));
    kiko::setFilePath("Assets");

   
    
    kiko::g_renderer.Initialize();
    kiko::g_audioSystem.Initialize();
    kiko::PhysicsSystem::Instance().Initialize();

    kiko::g_renderer.CreateWindow("CSC196", 800, 600);

    //Added Audio
    kiko::setFilePath("Assets");
    
    // Comment out from here down

    
    kiko::g_inputSystem.Initialize();
    unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
    game->Initialize();


    // std::vector<kiko::vec2> points{{-10, 5}, { 10, 5 }, { 0, -5 }, { -10, 5 }};
    

    kiko::vec2 v{5, 5};
    v.Normalize();

    vector<Star> stars;
    for (int i = 0; i < 1000; i++) {
        vec2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
        vec2 vel(kiko::randomf(1, 4), 0.0f);

        stars.push_back(Star(pos, vel));
    }
    //kiko::vec2 position{400, 300};
    //kiko::Transform transform({ 400, 300 }, 0, 3);
    float speed = 50;
    constexpr float turnRate = kiko::DegreesToRadians(180.0f); 

    kiko::g_audioSystem.PlayOneShot("Music", true);

    
    // Main Game Loop
    bool quit = false;
    while (!quit)
    {
        //update engine
        kiko::g_time.Tick();
        kiko::g_inputSystem.Update();
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
        {
            quit = true;
        }
        //update game
        game->Update(kiko::g_time.getDeltaTime());
        
        


        /*kiko::vec2 direction;
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) kiko::g_audioSystem.PlayOneShot("hit");*/
        

        //position += (direction * speed * kiko::g_time.getDeltaTime());
        

        
        /*if (kiko::g_inputSystem.GetMouseButtonDown(0))
        {
            cout << "Curent MB State: 0" << endl;
        }
        else if (kiko::g_inputSystem.GetMouseButtonDown(1))
        {
            cout << "Curent MB State: 1" << endl;
        }
        else if (kiko::g_inputSystem.GetMouseButtonDown(2))
        {
            cout << "Curent MB State: 2" << endl;
        }
        else {
            cout << "Mouse X = " << kiko::g_inputSystem.GetMousePosition().x << endl;
            cout << "Mouse Y = " << kiko::g_inputSystem.GetMousePosition().y << endl;
        }*/

        kiko::g_particleSystem.Update(kiko::g_time.getDeltaTime());

        kiko::g_renderer.SetColor(0, 0, 0, 255);
        kiko::g_renderer.BeginFrame();
        // draw
        vec2 vel(1.0f, 0.3f);

        game->Draw(kiko::g_renderer);
        for (auto& star : stars)
        {
            star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());

            kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
            star.Draw(kiko::g_renderer);
        }
        //kiko::g_renderer.DrawTexture(texture.get(), 50.0f, 50.0f);
                
        


        //for (int i = 0; i < 1000; i++) {
        //    kiko::Vector2 pos(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
        //
        //    renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
        //    renderer.DrawPoint(pos.x, pos.y);
        //}


        kiko::g_renderer.EndFrame();

        //this_thread::sleep_for(chrono::milliseconds(100));
}
    

    return 0;
}