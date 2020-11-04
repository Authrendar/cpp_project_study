#pragma once
#include "State.h"
#include "GameState.h"	

//Glowna klasa gry
class Game
{
public:
	Game();
	virtual ~Game();

	/* ^^^ Konstruktor, destruktor*/


	void run();	/*Funkcja uruchamiaj¹ca ca³y stan gry */
	void update(float& deltaTime); /*Aktualizowanie stanu gry*/
	void updateDt(); /*Obliczanie deltaTime -> zmienna potrzebna do stalego dzialania gry. Bez tego - im lepszy komputer, tym gra bedzie dzialac szybciej w doslownym tego slowa znaczeniu.*/
	/*30fps = gra dziala normalnie, 60fps = gra dziala 2 razy szybciej. Z t¹ zmienna pozbywamy sie tego problemu.*/
	void render();  /*Rysowanie obiektow itp*/

private:
	sf::RenderWindow* window; /*Zmienna okna gry*/
	sf::Event event; /*Zmienna zdarzen gry*/
	sf::Clock dtClock; /*Zmienna zegarowa - wykorzystana do obliczania deltaTime*/
	float dt; /*Delta time*/

	int W_WIDTH; int W_HEIGHT; /*Wymiary okna - dlugosc, wysokosc*/
	std::string TITLE; /*Nazwa aplikacji - wyswietla sie na gornym pasku*/

	std::stack<State*> states; /*stos stanów gry - Menu, Poziom_1, Poziom_2 itp. Dosyc trudny system, ale bardzo wydajny  */

	void initWindow(); /*Inicjacja okna aplikacji - przypisanie wymiarow itp*/
	void initStates(); /*Inicjacja stanow gry - dodajemy wszystkie stany, ktore potem zostana wykorzystane w grze */
	void endApp(); /*Funkcja oznajmiajaca o zakonczeniu aplikacji - mozliwosc zapisu jakichs danych do pliku.*/
};

