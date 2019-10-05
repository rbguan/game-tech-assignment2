#include "Player.h"

using namespace godot;

void Player::_register_methods() {
	register_method("_process", &Player::_process);
	register_method("_physics_process", &Player::_physics_process);
	register_property<Player, float>("gravityForce", &Player::gravityForce, -10);
	register_property<Player, float>("jumpForce", &Player::jumpForce, -10);
	register_property<Player, float>("frictionForce", &Player::frictionForce, 10);
}

Player::Player() {
}

Player::~Player() {
	// add your cleanup here
}


void Player::_init() {
	input = Input::get_singleton();
	velocity = Vector3(0,0,0);
	gravity = Vector3(0,-20,0);
	airResistance = 2;
}

void Player::_ready(){
	
}

void Player::_process(float delta) {

}

void Player::_physics_process(float delta) {

	//Handle Friction Here
	velocity = Vector3(0,0,0);
	
	me = Object::cast_to<KinematicBody>(get_node("KinematicBody-player"));
	bool left = input->is_key_pressed(65);
	bool right = input->is_key_pressed(68);
	bool forward = input->is_key_pressed(87);
	bool back = input->is_key_pressed(83);
	bool jump = input->is_key_pressed(32);
    bool dash = input->is_key_pressed(69);
	
	if(left){
		velocity.z = 10;
	}
	if(right){
		velocity.z = -10;
	}
	
	if(forward){
		velocity.x = -10;
	} 
	if(back){
		velocity.x = 10;
	}

	if(jump && !isJumping){
		isJumping = true;
		velocity.y = 200;
	}
    if (dash && !isDashing && isJumping) {
        isDashing = true;
        //velocity.x = 20;
    }
	if (isDashing) {
		velocity.x = -20;
	}
	if(me->is_on_floor()) {
		isJumping = false;
        isDashing = false;
	} else {

		// Air Resistance
		if (abs(velocity.x) > airResistance) {
			velocity.x -= velocity.x / abs(velocity.x) * airResistance;
		} else {
			velocity.x = 0;
		}
		if (abs(velocity.y) > airResistance) {
			velocity.y -= velocity.x / abs(velocity.y) * airResistance;
		} else {
			velocity.y = 0;
		}
		
	}

	//Gravity
	velocity = (velocity + gravity);
	if (velocity.y < -10) {
		velocity.y = -10;
	}
	std::cout << "Velocity Y" << velocity.y;
	me->move_and_slide(velocity, Vector3(0,1,0));
	
}