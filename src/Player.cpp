#include "Player.h"

using namespace godot;

void Player::_register_methods() {
	register_method("_process", &Player::_process);
	register_method("_physics_process", &Player::_physics_process);
	//register_property<Game, float>("amplitude", &Game::amplitude, 10.0);
	
}

Player::Player() {
}

Player::~Player() {
	// add your cleanup here
}


void Player::_init() {

}

void Player::_process(float delta) {

}

void Player::_physics_process(float delta) {
	// bool left = Input::get_singleton().is_key_pressed(65);
	// if(Input::is_key_pressed(65)){
	// 	Godot::print("W pressed");
	// }
}