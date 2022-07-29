#include "Game.cpp"
#include "State.cpp"
#include "GameState.cpp"
#include "Entity.cpp"
#include "Player.cpp"
#include "MainMenuState.cpp"
#include "SettingsState.cpp"
#include "Button.cpp"
#include "MovementComponent.cpp"
#include "AnimationComponent.cpp"

int main()
{
	Game game;

	game.run();
	return 0;
}