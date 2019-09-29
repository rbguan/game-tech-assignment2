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
	input = Input::get_singleton();
	gravity = -200;
}

void Player::_process(float delta) {

}

void Player::_physics_process(float delta) {
	me = Object::cast_to<KinematicBody>(get_node("KinematicBody-player"));
	bool left = input->is_key_pressed(65);
	bool right = input->is_key_pressed(68);
	bool forward = input->is_key_pressed(87);
	bool back = input->is_key_pressed(83);
	
	if(left){
		//Godot::print("A pressed");
		//me = Object::cast_to<KinematicBody>(get_node("KinematicBody-player"));
		me->move_and_slide(Vector3(0,0,10), Vector3(0,1,0));
		//me->rotate_x(10);
	}
	if(right){
		me->move_and_slide(Vector3(0,0,-10), Vector3(0,1,0));
	}
	if(forward){
		me->move_and_slide(Vector3(-10,0,0), Vector3(0,1,0));
	}
	if(back){
		me->move_and_slide(Vector3(10,0,0), Vector3(0,1,0));
	}
	me->move_and_slide(Vector3(0,gravity*delta,0), Vector3(0,1,0));
	if(!me->is_on_floor()){
		gravity += gravity* delta;
	}
	
}