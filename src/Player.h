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

namespace godot {

	class Player : public Area {
		GODOT_CLASS(Player, Area)

	private:
		
		Input* input;
		KinematicBody* me;
		Vector3 velocity;

	public:
		bool isGliding = false;
		bool movementMode;
		bool isJumping = false;
		bool isFalling = false;
        bool isDashing = false;
		float maxWalkAngle;
		float moveSpeed;

		float jumpForce;
		float gravityForce;
		float frictionForce;
		float airResistanceForce;
		float dashForce;

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

	};

}

#endif