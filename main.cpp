#include "Game.cpp"
#include "State.cpp"
#include "GameState.cpp"
#include "Tile.cpp"
#include "Entity.cpp"
#include "Player.cpp"
#include "MainMenuState.cpp"
#include "SettingsState.cpp"
#include "gui.cpp"
#include "MovementComponent.cpp"
#include "AnimationComponent.cpp"
#include "HitboxComponent.cpp"
#include "EditorState.cpp"
#include "PauseMenu.cpp"

int main()
{
	Game game;

	game.run();
	return 0;
d