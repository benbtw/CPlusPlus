#include "GameManagement.h"
#include "World.h"

using namespace sf;

/*

TO-DO LIST
 - collision + gravity
 - jumping
 - scrolling camera
 - enemies, goomba stomp type
 - level like change
 - start menu
 - potential pause menu
 - lives
*/

int init()
{
	RenderWindow window(VideoMode(640, 480), "Platformer");
	window.setFramerateLimit(60);
	Player player;
	World world;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		world.draw(window);
		player.update(window);
		window.display();
	}

	return EXIT_SUCCESS;
}