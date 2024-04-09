#include "bEngine.h"
#include <memory>

int main(int argc, char *argv[])
{
	std::unique_ptr<bWindow> window(new bWindow);

	window->createWindow(640, 480, "testing");
	window->createRenderer();
	window->setFPS(120);

	while (1)
	{
		window->startClock(); // regulates while loop to 120 fps
		window->pollEvents(); // polls window, keyboard, and mouse events

		window->startRender();
		window->setDrawColor(0, 0, 0, 1);
		window->stopRender();
	}
	return 0;
}