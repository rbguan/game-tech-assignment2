#ifndef PLAYER_H
#define PLAYER_H

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
#include <Coins.h>
#include <Powerups.h>
#include <AudioStreamPlayer.hpp>
#include "GameStateManager.h"

namespace godot {

	class Player : public Area {
		GODOT_CLASS(Player, Area)

	private:
		
		Input* input;
		KinematicBody* me;
		Vector3 velocity;
		GameStateManager* gamestate;
		AudioStreamPlayer* backgroundMusic;
		AudioStreamPlayer* coinSFX;
		AudioStreamPlayer* powerupSFX;
		AudioStreamPlayer* errorSFX;

	public:
		bool isGliding = false;
		bool movementMode;
		bool isJumping = false;
		bool isFalling = false;
        bool isDashing = false;
		bool isOnLedge = false;
		bool touchingPowerup = false;
		bool touchingCoin = false;
		bool hasPowerup = false;
		bool sfxMuted = false;
		Powerups* lastPowerup;
		Coins* lastCoin;

		float maxWalkAngle;
		float moveSpeed;

		float jumpForce;
		float gravityForce;
		float frictionForce;
		float airResistanceForce;
		float dashForce;
		float powerupTimer = 0;
		real_t walkableAngle;

		Vector3 gravity;
		Vector3 friction;
		Vector3 airResistance;

		float airControlLevel;
		float turnSpeed;
		static void _register_methods();

		Player();
		~Player();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void _physics_process(float delta);
		void _ready();
		void set_gravityForce(float p_gravityForce);
		float get_gravityForce();
		void _collected_coin(Coins *coin, bool touching);
		void _collected_powerup(Powerups *powerup, bool touching);
		void _hit_ledge();
		void _exit_ledge();

	private:
		void handle_gravity(Vector3& force, Vector3& gravity);
		void handle_movement(Vector3& force, bool left, bool right, bool forward, bool backward);
		void handle_rotate_movement(Vector3& force, bool left, bool right, bool forward, bool backward);
		void handle_jump(Vector3& force, bool jump);
		void handle_dash(Vector3& force, bool dash, bool right, bool left, bool forward, bool back);

	};

}

#endif