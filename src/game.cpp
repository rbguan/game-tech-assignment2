#include "game.h"

using namespace godot;

void Game::_register_methods() {
    register_method("_process", &Game::_process);
    register_property<Game, float>("amplitude", &Game::amplitude, 10.0);
    register_property<Game, float>("speed", &Game::set_speed, &Game::get_speed, 1.0);
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
    ball1 = Object::cast_to<MeshInstance>(get_node("ball1"));
    ball2 = Object::cast_to<MeshInstance>(get_node("ball2"));
    ball3 = Object::cast_to<MeshInstance>(get_node("ball3"));
    balls.push_back(ball1);
    balls.push_back(ball2);
    balls.push_back(ball3);
    wall1 = Object::cast_to<MeshInstance>(get_node("Wall1"));
    wall2 = Object::cast_to<MeshInstance>(get_node("Wall2"));
    wall3 = Object::cast_to<MeshInstance>(get_node("Wall3"));
    wall4 = Object::cast_to<MeshInstance>(get_node("Wall4"));
    wall5 = Object::cast_to<MeshInstance>(get_node("Wall5"));
    wall6 = Object::cast_to<MeshInstance>(get_node("Wall6"));
    walls.push_back(wall1);
    walls.push_back(wall2);
    walls.push_back(wall3);
    walls.push_back(wall4);
    walls.push_back(wall5);
    walls.push_back(wall6);

    for(int p = 0; p < 3; ++p){
        for(int j = 0; j < 3; ++j){
            if(j != p && p < j){
                Vector3 firstLocation = balls[p]->get_translation();
                Vector3 secondLocation = balls[j]->get_translation();   
                if(firstLocation.distance_to(secondLocation) < 2){
                    Vector3 normal = (firstLocation - secondLocation).normalized();
                    velocities[p] = (velocities[p] - (2*normal*(normal.dot(velocities[p])))).normalized();
                    velocities[j] = (velocities[j] - (2*(-normal)*((-normal).dot(velocities[j])))).normalized();
                    balls[p]->translate(((1 - ((firstLocation.distance_to(secondLocation))/2))) * normal);
                    balls[j]->translate(((1 - ((firstLocation.distance_to(secondLocation))/2))) * -normal);
                }
            }
        }
    }
    for(int i = 0; i < 3; ++i){
        
        
        Vector3 location = balls[i]->get_translation();
        Vector3 endForce = Vector3(0,0,0);
        bool bumped = false;
        if(location.z <= walls[0]->get_translation().z + 1){
            endForce += Vector3(0,0,1);
            bumped = true;
            //velocities[i] = velocities[i].bounce(Vector3(0,0,1)).normalized();
        }
        if(location.x <= walls[1]->get_translation().x + 1){
            endForce += Vector3(1,0,0);
            bumped = true;
            //velocities[i] = velocities[i].bounce(Vector3(1,0,0)).normalized();
        }
        if(location.x >= walls[2]->get_translation().x - 1){
            endForce += Vector3(-1,0,0);
            bumped = true;
            //velocities[i] = velocities[i].bounce(Vector3(-1,0,0)).normalized();
        }
        if(location.z >= walls[3]->get_translation().z - 1){
            endForce += Vector3(0,0,-1);
            bumped = true;
            //velocities[i] = velocities[i].bounce(Vector3(0,0,-1)).normalized();
        }
        if(location.y >= walls[4]->get_translation().y - 1){
            endForce += Vector3(0,-1,0);
            bumped = true;
            //velocities[i] = velocities[i].bounce(Vector3(0,-1,0)).normalized();
        }
        if(location.y <= walls[5]->get_translation().y + 1){
            endForce += Vector3(0,1,0);
            bumped = true;
            //velocities[i] = velocities[i].bounce(Vector3(0,1,0)).normalized();
        }
        endForce.normalize();
        if(bumped){
            velocities[i] = velocities[i] - 2*endForce*(endForce.dot(velocities[i]));
        }
        
        balls[i]->translate(velocities[i] * speed);
    }
    
    walls.clear();
    balls.clear();

}

void Game::set_speed(float p_speed) {
    speed = p_speed;
}

float Game::get_speed() {
    return speed;
}