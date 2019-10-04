#include "GameStateManager.h"

using namespace godot;

void GameStateManager::_register_methods() {
	register_method("_process", &GameStateManager::_process);
	register_property<GameStateManager, float>("maxTimeLimit", &GameStateManager::maxTimeLimit, 120.0);
}

GameStateManager::GameStateManager() {
}

GameStateManager::~GameStateManager() {
	// add your cleanup here
}


void GameStateManager::_init() {
	//input = Input::get_singleton();
	timeRemaining = maxTimeLimit;
}

void GameStateManager::_ready() {

}

void GameStateManager::_process(float delta) {
	timeRemaining -= delta;
	//if (timeRemaining <= 0.0) {
		//printf("OUT OF TIME");
		//Game is now over
	//}
}