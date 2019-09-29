#include "game.h"

using namespace godot;

void Game::_register_methods() {
	register_method("_process", &Game::_process);
	//register_property<Game, float>("amplitude", &Game::amplitude, 10.0);
	
}

Game::Game() {
}

Game::~Game() {
	// add your cleanup here
}


void Game::_init() {
	// initialize any variables here
	time_passed = 0.0;
	amplitude = 1;
	speed = 0.1;
	ball1Vel = speed * Vector3((amplitude + rand() % 2), (amplitude + rand() % 2), (amplitude + rand() % 2));
	//ball1Vel = Vector3(0, 1, 0);
	//ball2Vel = Vector3(0, -1, 0);
	ball2Vel = Vector3((amplitude + rand() % 2), (amplitude + rand() % 2), (amplitude + rand() % 2));
	ball3Vel = Vector3((amplitude + rand() % 2), (amplitude + rand() % 2), (amplitude + rand() % 2));
	velocities.push_back(ball1Vel.normalized());
	velocities.push_back(ball2Vel.normalized());
	velocities.push_back(ball3Vel.normalized());
}

void Game::_process(float delta) {
	//ball1 = Object::cast_to<MeshInstance>(get_node("ball1"));
	

}

void Game::_physics_process() {

}