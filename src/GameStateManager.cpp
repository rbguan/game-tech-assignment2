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
	// input = Input::get_singleton();
	
}

void GameStateManager::_ready() {
	// input = Input::get_singleton();

	timeCount = cast_to<Label>(get_node("VBoxContainer/HBoxContainer/TimeCount"));
	coinCount = cast_to<Label>(get_node("VBoxContainer/HBoxContainer2/CoinCount"));
	volumeCount = cast_to<Label>(get_node("VBoxContainer/HBoxContainer3/VolumeCount"));

	backgroundMusic = cast_to<AudioStreamPlayer>(get_node("BackgroundMusic"));
	coinSFX = cast_to<AudioStreamPlayer>(get_node("VBoxContainer/HBoxContainer2/CoinSFX"));
	
	backgroundMusic->play();
}

void GameStateManager::_add_coin() {
	coinsCollected += 1;
	std::string tmp = std::to_string(coinsCollected);
	coinCount->set_text(tmp.c_str());
	coinSFX->play();
}

void GameStateManager::_set_volume(float update) {
	backgroundMusic->set_volume_db(backgroundMusic->get_volume_db() + update);

	std::string tmp = std::to_string(backgroundMusic->get_volume_db());
	volumeCount->set_text(tmp.c_str());	
}

void GameStateManager::_process(float delta) {
	timeRemaining -= delta;
	std::string tmp = std::to_string(int(floor(timeRemaining)));
	timeCount->set_text(tmp.c_str());

	// bool comma = input->is_key_pressed(44);
	// bool period = input->is_key_pressed(46);
	
	// if (comma) {
	// 	backgroundMusic->set_volume_db(backgroundMusic->get_volume_db() - 10.0 * delta);
	// }
	// if (period) {
	// 	backgroundMusic->set_volume_db(backgroundMusic->get_volume_db() + 10.0 * delta);
	// }

	// tmp = std::to_string(backgroundMusic->get_volume_db());
	// volumeCount->set_text(tmp.c_str());

	//godot::Godot::print(timeCount->get_text());
	//std::cout << floor(timeRemaining) << "\n";
	//if (timeRemaining <= 0.0) {
		//printf("OUT OF TIME");
		//Game is now over
	//}
}