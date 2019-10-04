#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <Godot.hpp>
#include <Area.hpp>
#include <RandomNumberGenerator.hpp>
#include <CollisionShape.hpp>
#include <MeshInstance.hpp>
#include <core/Array.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <vector>
#include <KinematicBody.hpp>

namespace godot {

	class GameStateManager : public Spatial{
		GODOT_CLASS(GameStateManager, Spatial)

	private:

		//Input* input;
		int coinsCollected;
		float timeRemaining;

	public:
		float maxTimeLimit;

		static void _register_methods();

		GameStateManager();
		~GameStateManager();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void _ready();

	};

}

#endif
