#include "Ledge.h"
#include "Player.h"

using namespace godot;

void Ledge::_register_methods() {
	register_method("_body_entered", &Ledge::_body_entered);
    register_method("_body_exited", &Ledge::_body_exited);
	register_method("_ready", &Ledge::_ready);
}

Ledge::Ledge() {
}

Ledge::~Ledge() {
}

void Ledge::_init() {
}

void Ledge::_ready(){
		this->get_node("LedgeMesh/LedgeArea")->connect("body_entered", this, "_body_entered");
        this->get_node("LedgeMesh/LedgeArea")->connect("body_exited", this, "_body_exited");
}

void Ledge::_body_entered(Node *other) {
	
	Player* pl = cast_to<Player>(other->get_parent());
	pl->_hit_ledge();

}

void Ledge::_body_exited(Node* other) {
    Player* pl = cast_to<Player>(other->get_parent());
	pl->_exit_ledge();
}
