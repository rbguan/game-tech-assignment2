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
#include <AudioStreamPlayer.hpp>
#include <typeinfo>

namespace godot {

	class GameStateManager : public Spatial{
		GODOT_CLASS(GameStateManager, Spatial)

	private:

		// Input* input;
		int coinsCollected = 0;
		float timeRemaining = 120.0;
		Label* timeCount;
		Label* coinCount;
		Label* volumeCount;
		AudioStreamPlayer* backgroundMusic;
		AudioStreamPlayer* coinSFX;


	public:
		//float maxTimeLimit;

		// Input* _get_input() {return input;} 

		void _set_volume(float update);

		static void _register_methods();

		GameStateManager();
		~GameStateManager();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void _ready();
		void _add_coin();
		bool _get_is_key_pressed(int scancode);
		void _input(InputEvent ev);

	};

}

#endif
