#include "ResourceManager.h"
#include "ShaderBank.h"
#include "gamestates/StateStack.h"
#include "gamestates/IState.h"
#include "gamestates/StateMenu.h"
#include <memory>
#include <stack>
#include <optional>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "entities/Player.h"

int main(int argc, char* argv[])
{
    (void)argc;

    // ResourceManager must be instantiated here -- DO NOT CHANGE
    ResourceManager::init(argv[0]);

    sf::RenderWindow window(sf::VideoMode({1024, 1024}), "Runner");
	ShaderBank::init(window);
    window.setKeyRepeatEnabled(true);

    StateStack gamestates;
    if (!gamestates.push<StateMenu>())
        return -1;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();

        IState* pState = gamestates.getCurrentState();
        if (!pState) return -1;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                return 0;
            }
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
					Player::jumpInput = true;
				if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
					Player::deflectInput = true;
			}
			if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
					Player::jumpInput = false;
				if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
					Player::deflectInput = false;
			}
        }

        pState->update(elapsedTime.asSeconds());
        window.clear(sf::Color::Blue);
        pState->render(window);
        window.display();

        gamestates.performDeferredPops();
    }
    
    return 0;
}
