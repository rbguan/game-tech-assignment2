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
	volumeValue = cast_to<Label>(get_node("VBoxContainer/HBoxContainer3/VolumeValue"));
	powerupLabel = cast_to<Label>(get_node("VBoxContainer/HBoxContainer4/PowerupLabel"));
	powerupTimer = cast_to<Label>(get_node("VBoxContainer/HBoxContainer4/Powerup"));
	muted = cast_to<Label>(get_node("VBoxContainer/HBoxContainer5/Muted"));
	
}

void GameStateManager::_update_volume(float val) {
	std::string tmp = std::to_string(int(floor(val)));
	volumeValue->set_text(tmp.c_str());
}

void GameStateManager::_activate_powerup() {
	powerup = true;
	powerupTimeRemaining = 10;
	powerupLabel->set_text("POWER UP MODE!!!  ");
}

void GameStateManager::_add_coin() {
	coinsCollected += 1;
	std::string tmp = std::to_string(coinsCollected);
	coinCount->set_text(tmp.c_str());
}

void GameStateManager::_toggle_sfx(bool toggle) {
	if (toggle) 
		muted->set_text("SFX MUTED");
	else
		muted->set_text("");
}

void GameStateManager::_process(float delta) {
	timeRemaining -= delta;
	std::string tmp = std::to_string(int(floor(timeRemaining)));
	timeCount->set_text(tmp.c_str());

	if (powerup) {
		powerupTimeRemaining -= delta;
		if (powerupTimeRemaining < 0) {
			powerupLabel->set_text("");
			powerupTimer->set_text("");
			powerup = false;
		} else {
			tmp = std::to_string(int(floor(powerupTimeRemaining)));
			powerupTimer->set_text(tmp.c_str());
		}
	}

	//godot::Godot::print(timeCount->get_text());
	//std::cout << floor(timeRemaining) << "\n";
	//if (timeRemaining <= 0.0) {
		//printf("OUT OF TIME");
		//Game is now over
	//}
}