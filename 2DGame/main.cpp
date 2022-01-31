#include "Ball.h"
#include "Paddle.h"

#include <imgui.h>
#include <imgui-SFML.h>

#include <rapidxml.hpp>

using namespace gp;

int main()
{
    //inital window
    sf::RenderWindow l_window(sf::VideoMode(1920, 1080), "Our Game", sf::Style::Default);
    l_window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(l_window);

    //initial game objects
    gp::Ball l_ball(&l_window, 1024.f);
    gp::Paddle l_paddle(&l_window, false, 512.f);
    gp::Paddle l_paddle2(&l_window, true, 512.f);

    //inital framerate clock
    sf::Clock l_clockFramerate;
    sf::Clock l_time; 

    //Our small engine / gameloop
    while (l_window.isOpen())
    {
        ImGui::SFML::Update(l_window, l_time.restart());

        //calculate deltatime (its important to decouple game logic from real frametime (because we have different framerates 144 and 60 etc.)
        float l_deltaTime = l_clockFramerate.getElapsedTime().asSeconds();
        l_clockFramerate.restart();
        //This line looks random but it is important to avoid problems like: your pc lacks one time hard and because that the deltaTime would be so high that everything looks wrong in the next frame.
        l_deltaTime = (l_deltaTime > 512) ? 512 : l_deltaTime;  

        //poolevents
        sf::Event event;
        while (l_window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(l_window, event);

            if (event.type == sf::Event::Closed)
                l_window.close();
        }

        ImGui::Begin("Engine Interface");
        if (ImGui::Button("Reset"))
        {
            l_paddle.reset();
            l_paddle2.reset();
            l_ball.reset();
        }
        ImGui::End();

        //handle
        l_paddle.handle(l_deltaTime);
        l_paddle2.handle(l_deltaTime);
        l_ball.handle(l_deltaTime);

        //update
        l_paddle.update(l_deltaTime, l_ball);
        l_paddle2.update(l_deltaTime, l_ball);
        l_ball.update(l_deltaTime);

        //render
        l_window.clear();
        // Draw the sprite

        l_paddle.render();
        l_paddle2.render();
        l_ball.render();
        ImGui::SFML::Render(l_window);
        // Update the window
        l_window.display();
    }

    ImGui::SFML::Shutdown();
}