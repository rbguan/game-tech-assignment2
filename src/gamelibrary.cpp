#include "Player.h"
#include "Ledge.h"
#include "Coins.h"
#include "GameStateManager.h"
#include "Powerups.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::Player>();
    godot::register_class<godot::Ledge>();
	godot::register_class<godot::Coins>();
	godot::register_class<godot::GameStateManager>();
	godot::register_class<godot::Powerups>();
}