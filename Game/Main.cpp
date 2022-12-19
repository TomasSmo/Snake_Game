#include <SFML/Graphics.hpp>
#include <time.h>
#include <format>
#include "Objects.h"
#include "Values.h"

using namespace sf;
using namespace std;

void ConnectBody(Snake snk[])
{
	for (int i = snake_body; i > 0; --i)
	{
		snk[i].x = snk[i - 1].x; snk[i].y = snk[i - 1].y;
	}
}

void SpawnAndAddBodyPart(Snake snk[], BodyPart& bdy)
{
	if ((snk[0].x == bdy.x) && (snk[0].y == bdy.y)) {

		snake_body++;
		bdy.x = rand() % N_WIDTH; bdy.y = rand() % M_HEIGHT;
	}
}

void Movement(Snake snk[])
{
	if (direction == 0) snk[0].y += 1;
	if (direction == 1) snk[0].x -= 1;
	if (direction == 2) snk[0].x += 1;
	if (direction == 3) snk[0].y -= 1;
}

void CheckBorders(Snake snk[])
{
	if (snk[0].x > N_WIDTH - 1) {

		snake_body = 2;
		snk[0].x = 10;
		snk[0].y = 10;
	}
	if (snk[0].x < 0) {

		snake_body = 2;
		snk[0].x = 10;
		snk[0].y = 10;
	}
	if (snk[0].y > M_HEIGHT - 1) {

		snake_body = 2;
		snk[0].x = 10;
		snk[0].y = 10;
	}
	if (snk[0].y < 0) {

		snake_body = 2;
		snk[0].x = 10;
		snk[0].y = 10;
	}
}

void CheckIfCollidesWithBody(Snake snk[])
{
	for (int i = 1; i < snake_body; i++) {

		if (snk[0].x == snk[i].x && snk[0].y == snk[i].y) {

			snake_body = 2;
			snk[0].x = 10;
			snk[0].y = 10;
		}
	}
}

void GetKeyboarInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {

		direction = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {

		direction = 2;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {

		direction = 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {

		direction = 0;
	}
}

void Run()
{
	//Kuno sujungimas
	ConnectBody(snk);

	//Judejimas
	Movement(snk);

	//Pailgina kuna ir atspawnina nauja kuno dali
	SpawnAndAddBodyPart(snk, bdy);

	//Borders
	CheckBorders(snk);

	//Susilietimas su kunu
	CheckIfCollidesWithBody(snk);
}

int main()
{
	srand((unsigned)time(nullptr));
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
	app.setFramerateLimit(60);

	//Background, Snake body
	Texture tBackground, tSnake;
	tBackground.loadFromFile("Resources/background.png");
	tSnake.loadFromFile("Resources/body.png");

	Sprite sprBackground(tBackground);
	Sprite sprSnake(tSnake);

	Clock clock;
	float timer = 0, delay = 0.1;

	bdy.x = 10;
	bdy.y = 10;

	while (app.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		GetKeyboarInput();

		if (timer > delay) {

			timer = 0; Run();
		}

		app.clear();

		app.draw(sprBackground);

		for (int i = 0; i < snake_body; i++) {

			sprSnake.setPosition(snk[i].x * moving_area, snk[i].y * moving_area); app.draw(sprSnake);
		}

		sprSnake.setPosition(bdy.x * moving_area, bdy.y * moving_area); app.draw(sprSnake);

		app.display();
	}

	return 0;
}