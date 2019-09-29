#ifndef GAME_H
#define GAME_H

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
    float time_passed;
    float amplitude;
    float speed;
    MeshInstance* ball1;
    Vector3 ball1Vel;
    Vector3 ball2Vel;
    Vector3 ball3Vel;
    std::vector<MeshInstance*> balls;
    std::vector<MeshInstance*> walls;
    std::vector<Vector3> velocities;
    MeshInstance* ball2;
    MeshInstance* ball3;
    MeshInstance* wall1;
    MeshInstance* wall2;
    MeshInstance* wall3;
    MeshInstance* wall4;
    MeshInstance* wall5;
    MeshInstance* wall6;

public:
    static void _register_methods();

    Game();
    ~Game();

    void _init(); // our initializer called by Godot

    void _process(float delta);
    void set_speed(float p_speed);
    float get_speed();
    
};

}

#endif