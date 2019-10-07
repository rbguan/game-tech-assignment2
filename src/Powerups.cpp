#include "Powerups.h"
#include "Player.h"

using namespace godot;

void Powerups::_register_methods() {
	register_method("_process", &Powerups::_process);
	register_method("_body_entered", &Powerups::_body_entered);
	register_method("_ready", &Powerups::_ready);
}

Powerups::Powerups() {

}

Powerups::~Powerups() {
	// add your cleanup here
}


void Powerups::_init() {
}

void Powerups::_ready() {
	
	this->get_node("PowerupArea")->connect("body_entered", this, "_body_entered");
	
}

void Powerups::_process(float delta) {

}


void Powerups::_body_entered(Node *other) {
	
	
	//godot::Godot::print(other->get_parent()->get_name());
	Player* pl = cast_to<Player>(other->get_parent());
	//other->get_parent()->connect("collected_coin", pl, "_collected_coin");
	pl->_collected_powerup();
	queue_free();

}