#include "Player.h"

using namespace godot;

void Player::_register_methods() {
	register_method("_process", &Player::_process);
	register_method("_physics_process", &Player::_physics_process);
	register_method("_ready", &Player::_ready);
	register_method("_collected_coin", &Player::_collected_coin);
	register_property<Player, float>("gravityForce", &Player::set_gravityForce,&Player::get_gravityForce , 4.0);
	register_property<Player, float>("dashForce", &Player::dashForce, 50.0);
	register_property<Player, float>("airResistanceForce", &Player::airResistanceForce, 1.0);
	register_property<Player, float>("frictionForce", &Player::frictionForce, 50.0);
	register_property<Player, float>("moveSpeed", &Player::moveSpeed, 10.0);
	register_property<Player, float>("jumpForce", &Player::jumpForce, 50.0);
	register_property<Player, real_t>("walkableAngle", &Player::walkableAngle, 0.785398);
	register_property<Player, float>("airControlLevel", &Player::airControlLevel, 1);
}

Player::Player() {
}

Player::~Player() {
	// add your cleanup here
}


void Player::_init() {
	input = Input::get_singleton();
	airControlLevel= 1;
	gravityForce = 1;
	dashForce = 50;
	airResistanceForce = 1;
	frictionForce = 5;
	moveSpeed = 10;
	jumpForce = 25;
	velocity = Vector3(0,0,0);
	walkableAngle = 0.785398;
}

void Player::_ready(){
	
	
}

void Player::_collected_coin() {
	godot::Godot::print("Coin collected!");
<<<<<<< HEAD
=======
}

void Player::_hit_ledge() {
	godot::Godot::print("Hit Ledge!");
	velocity = Vector3(0,0,0);
	isJumping = false;
	isOnLedge = true;
}

void Player::_exit_ledge() {
	godot::Godot::print("Exited Ledge!");
	isOnLedge = false;
>>>>>>> 56ec708ec6ff3627acee9868a095851fb5a1eedc
}

void Player::_process(float delta) {

}

void Player::_physics_process(float delta) {

	bool enable_movement = !isOnLedge;
	bool enable_gravity = !isOnLedge;


	//Handle Friction Here
	Vector3 forceVector = Vector3(0,0,0);
	gravity = Vector3(0,-gravityForce,0);
	friction = Vector3(frictionForce,0,frictionForce);
	//velocity = velocity.linear_interpolate(Vector3(0, -1, 0), delta);
	airResistance = Vector3(airResistanceForce,airResistanceForce,airResistanceForce);
	me = Object::cast_to<KinematicBody>(get_node("KinematicBody-player"));
	bool left = input->is_key_pressed(65);
	bool right = input->is_key_pressed(68);
	bool forward = input->is_key_pressed(87);
	bool back = input->is_key_pressed(83);
	bool jump = input->is_key_pressed(32);
    bool dash = input->is_key_pressed(69);
	
<<<<<<< HEAD
	if(left && velocity.z < moveSpeed){
		if(!me->is_on_floor()){
			forceVector.z += moveSpeed * airControlLevel;
		} else{
			forceVector.z += moveSpeed;
		}
	}
	if(right && velocity.z > -moveSpeed){
		if(!me->is_on_floor()){
			forceVector.z += -moveSpeed * airControlLevel;
		} else{
			forceVector.z += -moveSpeed;
		}
		
	}
	
	if(forward && velocity.x > -moveSpeed){
		if(!me->is_on_floor()){
			forceVector.x += -moveSpeed * airControlLevel;
		} else{
			forceVector.x += -moveSpeed;
		}
	} 
	if(back && velocity.x < moveSpeed){
		if(!me->is_on_floor()){
			forceVector.x += moveSpeed * airControlLevel;
		} else{
			forceVector.x += moveSpeed;
		}
=======
	if (enable_movement) {
		if(left && velocity.z < moveSpeed){
			forceVector.z += moveSpeed;
		}
		if(right && velocity.z > -moveSpeed){
			forceVector.z += -moveSpeed;
		}
		
		if(forward && velocity.x > -moveSpeed){
			forceVector.x += -moveSpeed;
		} 
		if(back && velocity.x < moveSpeed){
			forceVector.x += moveSpeed;
		}

		if (dash && !isDashing && isJumping) {
			isDashing = true;
			if(right){
				forceVector.z += -dashForce;
			}
			if(left){
				forceVector.z += dashForce;
			}
			if(forward){
				forceVector.x += -dashForce;
			}
			if(back){
				forceVector.x += dashForce;
			}
		}

>>>>>>> 56ec708ec6ff3627acee9868a095851fb5a1eedc
	}

	if(jump && !isJumping){
		isJumping = true;
		forceVector.y += jumpForce;
	}

	if (enable_gravity) {

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
	
	velocity += forceVector;
	if(me->is_on_floor()) {
		isJumping = false;
        isDashing = false;
		
		// Friction
		velocity += friction * Vector3(-xDelta,-yDelta, -zDelta);
	} else {
		std::cout << "notonfloor\n";
		// Gravity
		velocity += gravity;

		// Air ResistanceS
		if(isJumping && !me->is_on_floor()){
			velocity += airResistance * Vector3(-xDelta ,-yDelta, -zDelta);
		}
	}

<<<<<<< HEAD
	
	//Max Velocities
	// if (abs(velocity.x) > moveSpeed) {velocity.x = moveSpeed;}
	// if (abs(velocity.z) > moveSpeed) {velocity.z = moveSpeed;}
	//if (velocity.y < -gravityForce) {velocity.y = -gravityForce;}

=======
	velocity += forceVector;
>>>>>>> 56ec708ec6ff3627acee9868a095851fb5a1eedc
	
	if(me->is_on_floor()){
		std::cout << "onfloor\n";
		if(!jump){
			velocity.y = -1;
		}
	}
	me->move_and_slide(velocity, Vector3(0,1,0), true, 4, walkableAngle);
	
}

void Player::set_gravityForce(float p_gravityForce){
	gravityForce = p_gravityForce;
}

float Player::get_gravityForce(){
	return gravityForce;
}

