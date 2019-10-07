#ifndef COINS_H
#define COINS_H

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

	class Coins : public Area {
		GODOT_CLASS(Coins, Area)

	private:


	public:
		static void _register_methods();

		Coins();
		~Coins();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void _ready();
		void _body_entered(Node *other);
		void _body_exited(Node *other);
	};

}

#endif