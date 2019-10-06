#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <Godot.hpp>
#include <Label.hpp>
#include <string>
#include <math.h>
#include <Area.hpp>
#include <RandomNumberGenerator.hpp>
#include <CollisionShape.hpp>
#include <MeshInstance.hpp>
#include <core/Array.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <vector>
#include <KinematicBody.hpp>
#include <typeinfo>

namespace godot {

	class GameStateManager : public Spatial{
		GODOT_CLASS(GameStateManager, Spatial)

	private:

		//Input* input;
		int coinsCollected;
		float timeRemaining;
		Label* timeCount;
		Label* coinCount;

	public:
		//float maxTimeLimit;

		static void _register_methods();

		GameStateManager();
		~GameStateManager();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void _ready();

	};

}

#endif
