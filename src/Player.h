#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Area.hpp>
#include <RandomNumberGenerator.hpp>
#include <CollisionShape.hpp>
#include <MeshInstance.hpp>
#include <core/Array.hpp>
#include <vector>

namespace godot {

	class Game : public Area {
		GODOT_CLASS(Game, Area)

	private:
		

	public:
		static void _register_methods();

		Game();
		~Game();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void _physics_process();

	};

}

#endif