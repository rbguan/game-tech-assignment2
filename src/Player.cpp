#include "Player.h"

using namespace godot;

void Player::_register_methods() {
	register_method("_process", &Player::_process);
	register_method("_physics_process", &Player::_physics_process);
}

Player::Player() {
}

Player::~Player() {
	// add your cleanup here
}


void Player::_init() {
	input = Input::get_singleton();

	gravityForce = 10;
	dashForce = 50;
	airResistanceForce = 5;
	frictionForce = 5;
	moveSpeed = 10;
	jumpForce = 50;

	velocity = Vector3(0,0,0);
	friction = Vector3(frictionForce,0,frictionForce);
	gravity = Vector3(0,-gravityForce,0);
	airResistance = Vector3(airResistanceForce,airResistanceForce,airResistanceForce);
}

void Player::_ready(){
	
}

void Player::_process(float delta) {

}

void Player::_physics_process(float delta) {

	//Handle Friction Here
	Vector3 forceVector = Vector3(0,0,0);
	
	me = Object::cast_to<KinematicBody>(get_node("KinematicBody-player"));
	bool left = input->is_key_pressed(65);
	bool right = input->is_key_pressed(68);
	bool forward = input->is_key_pressed(87);
	bool back = input->is_key_pressed(83);
	bool jump = input->is_key_pressed(32);
    bool dash = input->is_key_pressed(69);
	
	if(left && velocity.z < moveSpeed){
		forceVector.z = moveSpeed;
	}
	if(right && velocity.z > -moveSpeed){
		forceVector.z = -moveSpeed;
	}
	
	if(forward && velocity.x > -moveSpeed){
		forceVector.x = -moveSpeed;
	} 
	if(back && velocity.x < moveSpeed){
		forceVector.x = moveSpeed;
	}

	if(jump && !isJumping){
		isJumping = true;
		forceVector.y = jumpForce;
	}
    if (dash && !isDashing && isJumping) {
        isDashing = true;
        forceVector.x = -dashForce;
    }

	int xDelta, yDelta, zDelta;
	if (velocity.x == 0) {
		xDelta = 0;
	} else {
		xDelta = (velocity.x) / abs(velocity.x);
	}
	if (velocity.y == 0) {
		yDelta = 0;
	} else {
		yDelta = (velocity.y) / abs(velocity.y);
	}
	if (velocity.z == 0) {
		zDelta = 0;
	} else {
		zDelta = (velocity.z) / abs(velocity.z);
	}
	

	if(me->is_on_floor()) {
		isJumping = false;
        isDashing = false;
		
		// Friction
		forceVector += airResistance * Vector3(-xDelta,-yDelta, -zDelta);

	} else {

		// Gravity
		forceVector += gravity;

		// Air Resistance
		forceVector += airResistance * Vector3(-xDelta,-yDelta, -zDelta);
	}

	velocity += forceVector;
	//Max Velocities
	// if (abs(velocity.x) > moveSpeed) {velocity.x = moveSpeed;}
	// if (abs(velocity.z) > moveSpeed) {velocity.z = moveSpeed;}
	if (velocity.y < -gravityForce) {velocity.y = -gravityForce;}

	std::cout << "Velocity Y" << velocity.y;
	me->move_and_slide(velocity, Vector3(0,1,0));
	
}

