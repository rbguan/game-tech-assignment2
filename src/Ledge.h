#ifndef LEDGE_H
#define LEDGE_H

#include <Godot.hpp>
#include <Spatial.hpp>

namespace godot {

class Ledge : public Spatial {
	GODOT_CLASS(Ledge, Spatial)
        
public:
	static void _register_methods();

	Ledge();
	~Ledge();

	void _init(); // our initializer called by Godot

};

}

#endif
