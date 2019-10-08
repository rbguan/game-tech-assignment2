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

		//Input* input;
		int coinsCollected;
		float timeRemaining;
		float powerupTimeRemaining = 10;
		Label* timeCount;
		Label* coinCount;
		Label* volumeValue;
		Label* powerupLabel;
		Label* powerupTimer;
		Label* muted;

	public:
		//float maxTimeLimit;
		bool powerup = false;

		static void _register_methods();

		GameStateManager();
		~GameStateManager();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void _ready();
		void _add_coin();

		void _update_volume(float val);
		void _activate_powerup();
		void _toggle_sfx(bool muted);

	};

}

#endif
