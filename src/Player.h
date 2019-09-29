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

namespace godot {

	class Player : public Area {
		GODOT_CLASS(Player, Area)

	private:
		bool isGliding;
		bool movementMode;
		bool isJumping;
		bool isFalling;
		float maxWalkAngle;
		float moveSpeed;
		float jumpForce;
		float gravity;
		float airResistance;
		float airControlLevel;
		float turnSpeed;

	public:
		static void _register_methods();

		Player();
		~Player();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void _physics_process(float delta);

	};

}

#endif