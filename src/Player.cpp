#include "Player.h"

using namespace godot;

void Player::_register_methods() {
	register_method("_process", &Player::_process);
	register_method("_ready", &Player::_ready);
	register_method("_physics_process", &Player::_physics_process);
	register_method("_collected_coin", &Player::_collected_coin);
	register_property<Player, float>("gravity", &Player::gravity, -500.00);
	register_property<Player, float>("jumpForce", &Player::jumpForce, 150.00);
}

Player::Player() {
}

Player::~Player() {
	// add your cleanup here
}


void Player::_init() {
	input = Input::get_singleton();
	currentGravity = gravity;
	velocity = Vector3(0,0,0);
}

void Player::_ready() {
	//add_user_signal("collected_coin");
	//connect("collected_coin", this, "_collected_coin");
}

void Player::_process(float delta) {

}

void Player::_collected_coin() {
	godot::Godot::print("Coin collected!");
}

void Player::_physics_process(float delta) {
	//printf("%f\n", velocity.y);
	velocity = Vector3(0,0,0);
	me = Object::cast_to<KinematicBody>(get_node("KinematicBody-player"));
	bool left = input->is_key_pressed(65);
	bool right = input->is_key_pressed(68);
	bool forward = input->is_key_pressed(87);
	bool back = input->is_key_pressed(83);
	bool jump = input->is_key_pressed(32);
    bool dash = input->is_key_pressed(69);
	
	if(left){
		//Godot::print("A pressed");
		//me = Object::cast_to<KinematicBody>(get_node("KinematicBody-player"));
		velocity.z += 10;
		//me->rotate_x(10);
	}
	if(right){
		velocity.z -= 10;
	}
	if(forward){
		velocity.x -= 10;
		//me->move_and_slide(Vector3(-10,0,0), Vector3(0,1,0));
	}
	if(back){
		velocity.x += 10;
		//me->move_and_slide(Vector3(10,0,0), Vector3(0,1,0));
	}
	if(jump && !isJumping){
		isJumping = true;
		velocity.y += jumpForce;
		currentGravity = gravity;
	}
    if (dash && !isDashing && isJumping) {
        isDashing = true;
        velocity.x -= 200;
    }
	if(!me->is_on_floor()){
		velocity.y += currentGravity;
		currentGravity *= 1 + delta;
	} else{
		currentGravity = gravity;
	}
	if(me->is_on_floor()) {
		isJumping = false;
        isDashing = false;
		//currentGravity = 0;
		}
	me->move_and_slide(velocity, Vector3(0,1,0));
	
}
