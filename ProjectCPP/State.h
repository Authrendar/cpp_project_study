#ifndef STATE_H
#define STATE_H



#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <map>
class State
{
public:
	State(sf::RenderWindow* window);
	virtual ~State();

	virtual void endState() = 0;

	virtual void checkForQuit();

	const bool& getQuit() const;
	virtual sf::View getView()=0;

	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;

private:

protected:
	std::vector<sf::Texture> texture;
	sf::RenderWindow* window;

	bool quit;
};

#endif // !STATE_H