#include "Coins.h"
#include "Player.h"

using namespace godot;

void Coins::_register_methods() {
	register_method("_process", &Coins::_process);
	register_method("_body_entered", &Coins::_body_entered);
	register_method("_body_exited", &Coins::_body_exited);
	register_method("_ready", &Coins::_ready);
}

Coins::Coins() {

}

Coins::~Coins() {
	// add your cleanup here
}


void Coins::_init() {
}

void Coins::_ready() {
	
	this->get_node("CoinArea")->connect("body_entered", this, "_body_entered");
	this->get_node("CoinArea")->connect("body_exited", this, "_body_exited");
	
}

void Coins::_process(float delta) {

}


void Coins::_body_entered(Node *other) {
	
	
	//godot::Godot::print(other->get_parent()->get_name());
	Player* pl = cast_to<Player>(other->get_parent());
	//other->get_parent()->connect("collected_coin", pl, "_collected_coin");
	pl->_collected_coin(this, true);

}

void Coins::_body_exited(Node *other) {

	Player* pl = cast_to<Player>(other->get_parent());
	pl->_collected_coin(this, false);
}