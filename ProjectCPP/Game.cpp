#include "Game.h"

Game::Game()
{
	W_WIDTH = 800;
	W_HEIGHT = 600;
	TITLE = "PROJECT CPP 1.0v";
	/*Przypisanie ustawien okna gry*/
}

Game::~Game()
{

	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}

	/*Usuwanie z pamieci zmiennych, elementow stosu - (stany gry)*/
}

void Game::run()
{
	std::cout << "Game is running..." << std::endl;
	this->initWindow();
	this->initStates();

	while (this->window->isOpen()) { /*Glowna petla gry, dopoki okno jest otwarte, wszystko dziala*/
		while (this->window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->window->close(); /*Obsluga podstawowych zdarzen - wy³aczenie aplikacji poprzez krzyzyk na pasku*/
			}
		}


		this->update(this->dt); /*Glowna funkcja aktualizujaca logikê gry*/
		this->updateDt(); /*Obliczanie deltaTime*/
		this->render(); /*Rysowanie obiektow itp*/
	}


}

void Game::update(float& deltaTime)
{
	/*Dzialanie na stosie ze stanami gry. Sprawdzanie czy stos nie jest pusty, jezeli nie, to -> update(), jezeli obecnie obslugiwany stan wywola funkcje getQuit() -> Usuwanie stanu z gory stosu, uruchomienie kolejnego, jezeli taki istnieje */
	if (!this->states.empty()) {
		this->states.top()->update(deltaTime);

		if (this->states.top()->getQuit()) {

			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApp();
		this->window->close();
	}
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty()) {
		this->states.top()->render(this->window);

	}
	this->window->display();
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(W_WIDTH, W_HEIGHT), TITLE);
	this->window->setFramerateLimit(30);
}

void Game::initStates()
{
	this->states.push(new GameState(this->window));



	std::cout << "States inited\n";
	std::cout << states.size() << std::endl;
}

void Game::endApp()
{
	std::cout << "Ending app...\n";
}
