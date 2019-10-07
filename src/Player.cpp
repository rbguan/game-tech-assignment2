#include "Player.h"
#include "GameStateManager.h"

using namespace godot;

void Player::_register_methods() {
	register_method("_process", &Player::_process);
	register_method("_physics_process", &Player::_physics_process);
	register_method("_ready", &Player::_ready);
	register_method("_collected_coin", &Player::_collected_coin);
	register_method("_collected_powerup", &Player::_collected_powerup);
	register_property<Player, float>("gravityForce", &Player::set_gravityForce,&Player::get_gravityForce , 4.0);
	register_property<Player, float>("dashForce", &Player::dashForce, 50.0);
	register_property<Player, float>("airResistanceForce", &Player::airResistanceForce, 1.0);
	register_property<Player, float>("frictionForce", &Player::frictionForce, 50.0);
	register_property<Player, float>("moveSpeed", &Player::moveSpeed, 10.0);
	register_property<Player, float>("jumpForce", &Player::jumpForce, 50.0);
	register_property<Player, real_t>("walkableAngle", &Player::walkableAngle, 0.785398);
	register_property<Player, real_t>("rotationSpeed", &Player::rotationSpeed, 10);
	register_property<Player, float>("airControlLevel", &Player::airControlLevel, 1);
	register_property<Player, bool>("movementMode", &Player::movementMode, true);
	register_property<Player, Vector3>("myForward", &Player::myForward, Vector3(0,0,-1));
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
	gravity = Vector3(0,-gravityForce,0);
	movementMode = true;
	rotationSpeed = 10;
	myForward = Vector3(0,0,-1);
}

void Player::_ready(){
	
	
}

void Player::_collected_coin() {
	godot::Godot::print("Coin collected!");
	GameStateManager* temp = cast_to<GameStateManager>(get_node("/root/Spatial/MarginContainer"));
	if (temp != nullptr) {
		temp->_add_coin();
	}
}

void Player::_collected_powerup() {
	Godot::print("Powerup collected");
	powerupTimer = 30;
	hasPowerup = true;
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
}

void Player::_process(float delta) {
	if (powerupTimer > 0) {
		powerupTimer -= delta;
		if (powerupTimer <= 0) {
			hasPowerup = false;
		}
	}
}

void Player::_physics_process(float delta) {

	Vector3 forceVector = Vector3(0,0,0);
	Vector3 gravityVector = gravity;

	if (hasPowerup) {
		gravityVector = gravity * 0.5;
	}


	friction = Vector3(frictionForce,0,frictionForce);

	airResistance = Vector3(airResistanceForce,airResistanceForce,airResistanceForce);
	me = Object::cast_to<KinematicBody>(get_node("KinematicBody-player"));
	bool left = input->is_key_pressed(65);
	bool right = input->is_key_pressed(68);
	bool forward = input->is_key_pressed(87);
	bool back = input->is_key_pressed(83);
	bool jump = input->is_key_pressed(32); 		//SPACE
    bool dash = input->is_key_pressed(69); 		//E
	bool glide = input->is_key_pressed(81); 	//Q

	if (!me->is_on_floor() && !isGliding && !hasPowerup) {
		isGliding = glide;
	}

	bool enable_movement = !isOnLedge && !isGliding;
	bool enable_gravity = !isOnLedge;
	
	if (enable_movement) {
		if(movementMode){
			handle_movement(forceVector, left, right, forward, back);
			handle_dash(forceVector, dash, left, right, forward, back);
		} else{
			handle_rotate_movement(forceVector, left, right, forward, back);
			handle_rotate_dash(forceVector, dash, left, right, forward, back);
		}
	}

	handle_jump(forceVector, jump);

	if (enable_gravity) {
		Basis b = Basis(me->get_rotation());
		if (isGliding && velocity.y < 0) {
			Vector3 reduced_gravity = gravityVector * .1;
			//forceVector = forceVector.rotated(Vector3(0,1,0), forceVector.angle_to(myForward));
			handle_gravity(forceVector, reduced_gravity);
		} else {
			//forceVector = forceVector.rotated(Vector3(0,1,0), forceVector.angle_to(myForward));
			handle_gravity(forceVector, gravityVector);
		}
    }

	velocity += forceVector;
	
	if(me->is_on_floor()){
		std::cout << "onfloor\n";
		if(!jump){
			velocity.y = -1;
		}
	}

	me->move_and_slide(velocity, Vector3(0,1,0), true, 4, walkableAngle);
	
}

void Player::handle_movement(Vector3& force, bool left, bool right, bool forward, bool back) {
	if(left && velocity.z < moveSpeed){
		force.z += moveSpeed;
	}
	if(right && velocity.z > -moveSpeed){
		force.z += -moveSpeed;
	}
	
	if(forward && velocity.x > -moveSpeed){
		force.x += -moveSpeed;
	} 
	if(back && velocity.x < moveSpeed){
		force.x += moveSpeed;
	}
}

void Player::handle_rotate_movement(Vector3& force, bool left, bool right, bool forward, bool back) {
	Basis b = Basis(me->get_rotation());
	if(left){
		myForward.rotate(Vector3(0,1,0), rotationSpeed);
		me->rotate_y(rotationSpeed);
	}
	if(right){
		myForward.rotate(Vector3(0,1,0), -rotationSpeed);
		me->rotate_y(-rotationSpeed);
	}
	if(forward){
		force += -b.z;
	} 
	if(back){
		force += b.z;
	}
}

void Player::handle_jump(Vector3& force, bool jump) {
	if(jump && !isJumping){
		isJumping = true;
		force.y += jumpForce;
	}
}

void Player::handle_rotate_dash(Vector3& force, bool dash, bool right, bool left, bool forward, bool back) {
	if (dash && !isDashing && isJumping && !isGliding) {
		Basis b = Basis(me->get_rotation());
		isDashing = true;
		if(forward){
			force += -b.z * 2;
		}
		if(back){
			force += b.z * 2;
		}
	}
}

void Player::handle_dash(Vector3& force, bool dash, bool right, bool left, bool forward, bool back) {
	if (dash && !isDashing && isJumping && !isGliding) {
		isDashing = true;
		if(right && velocity.z > -dashForce){
			force.z += -dashForce;
		}
		if(left && velocity.z < dashForce){
			force.z += dashForce;
		}
		if(forward && velocity.x > -dashForce){
			force.x += -dashForce;
		}
		if(back && velocity.x < dashForce){
			force.x += dashForce;
		}
	}
}
void Player::handle_gravity(Vector3& force, Vector3& curr_gravity) {
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
		isGliding = false;

		// Friction
		velocity += friction * Vector3(-xDelta,-yDelta, -zDelta);
	} else {
		std::cout << "notonfloor\n";
		// Gravity
		velocity += curr_gravity;

		// Air ResistanceS
		if(isJumping && !me->is_on_floor()){
			velocity += airResistance * Vector3(-xDelta ,-yDelta, -zDelta);
		}
	}
}



void Player::set_gravityForce(float p_gravityForce){
	gravityForce = p_gravityForce;
}

float Player::get_gravityForce(){
	return gravityForce;
}

