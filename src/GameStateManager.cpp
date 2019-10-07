#include "GameStateManager.h"

using namespace godot;

void GameStateManager::_register_methods() {
	register_method("_process", &GameStateManager::_process);
	register_method("_ready", &GameStateManager::_ready);
	register_method("_add_coin", &GameStateManager::_add_coin);
	//register_property<GameStateManager, float>("maxTimeLimit", &GameStateManager::maxTimeLimit, 120.0);
}

GameStateManager::GameStateManager() {
}

GameStateManager::~GameStateManager() {
	// add your cleanup here
}


void GameStateManager::_init() {
	//input = Input::get_singleton();
	
}

void GameStateManager::_ready() {
	timeRemaining = 120.0;
	coinsCollected = 0;
	timeCount = cast_to<Label>(get_node("VBoxContainer/HBoxContainer/TimeCount"));
	coinCount = cast_to<Label>(get_node("VBoxContainer/HBoxContainer2/CoinCount"));
	//godot::Godot::print(timeCount->get_name());
	
}

void GameStateManager::_add_coin() {
	coinsCollected += 1;
	std::string tmp = std::to_string(coinsCollected);
	coinCount->set_text(tmp.c_str());
}

void GameStateManager::_process(float delta) {
	timeRemaining -= delta;
	// int(floor(timeRemaining))
	//String tmp = String(std::to_string(int(floor(timeRemaining)).std::c_str()));
	std::string tmp = std::to_string(int(floor(timeRemaining)));
	timeCount->set_text(tmp.c_str());

	//godot::Godot::print(timeCount->get_text());
	//std::cout << floor(timeRemaining) << "\n";
	//if (timeRemaining <= 0.0) {
		//printf("OUT OF TIME");
		//Game is now over
	//}
}