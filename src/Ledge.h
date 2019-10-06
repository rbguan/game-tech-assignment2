#ifndef LEDGE_H
#define LEDGE_H

#include <Godot.hpp>
#include <Area.hpp>


namespace godot {

class Ledge : public Area {
	GODOT_CLASS(Ledge, Area)
        
public:
		static void _register_methods();

		Ledge();
		~Ledge();

		void _init(); // our initializer called by Godot

		void _ready();
		void _body_entered(Node *other);
		void _body_exited(Node *other);
	};

}

#endif
