#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

//void playMap(sf::RenderWindow &win);

class Character {

private:
    sf::RectangleShape player = sf::RectangleShape(sf::Vector2f(40.0f, 40.0f));
    sf::Vector2f playerPos = player.getPosition(); 
    bool collided = false;
    
    
public:
    void playerMovement() {

        sf::Vector2f pos = player.getPosition();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && playerPos.x > 0 && !collided) {
            player.move(-0.1f, 0.0f);
            playerPos.x += -0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && playerPos.x < 472){
            player.move(0.1f, 0.0f);
            playerPos.x += 0.1f;
            collided = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && playerPos.y > 0) {
            player.move(0.0f, -0.1f);
            playerPos.y += -0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && playerPos.y < 472) {
            player.move(0.0f, 0.1f);
            playerPos.y += 0.1f;
        }
    }

    void playMap(sf::RenderWindow& win) {
        //make collision first then finish the rest of the map
        std::vector<sf::RectangleShape> tiles;
        sf::Vector2f pos;
        tiles.push_back(sf::RectangleShape(sf::Vector2f(472, 40)));
        tiles.push_back(sf::RectangleShape(sf::Vector2f(422, 40)));
        tiles.push_back(sf::RectangleShape(sf::Vector2f(40, 472)));
        tiles.push_back(sf::RectangleShape(sf::Vector2f(40, 472)));
        tiles[0].setPosition(80, 0);
        tiles[1].setPosition(0, 472);
        tiles[2].setPosition(0, 40);
        tiles[3].setPosition(472, 0);
        for (int i = 0; i < tiles.size(); i++) {
            float tileSide = tiles[i].getPosition().x;
            float leftSide = player.getPosition().x;
            win.draw(tiles[i]);
            if (player.getPosition.x)
                collided = true;
            else
                collided = false;
        }
    }

    void drawWindow(sf::RenderWindow& win) {
        win.draw(player);
    }

    void setColor(sf::Color color) {
        player.setFillColor(color);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "Game", sf::Style::Close | sf::Style::Titlebar);
    sf::Event evnt;
    Character charac;
    charac.setColor(sf::Color::Green);

    while (window.isOpen()) {
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
            case sf::Event::Closed:
                window.close();
                break;
           }
        }

        charac.playerMovement();

        window.clear();
        charac.drawWindow(window);
        charac.playMap(window);
        window.display();
        
    }

    return EXIT_SUCCESS;
}