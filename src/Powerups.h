#ifndef POWERUPS_H
#define  POWERUPS_H

#include <Godot.hpp>
#include <Area.hpp>
#include <Node.hpp>
#include <CollisionShape.hpp>
#include <MeshInstance.hpp>
#include <core/Array.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <vector>
#include <KinematicBody.hpp>
#include <iostream>
#include <string>

namespace godot {

	class Powerups : public Area {
		GODOT_CLASS(Powerups, Area)

	private:


	public:
		static void _register_methods();

		Powerups();
		~Powerups();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void _ready();
		void _body_entered(Node *other);
	};

}

#endif