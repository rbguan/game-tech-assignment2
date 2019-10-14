## Build Instructions

# building bindings

cd assignment2
godot --gdnative-generate-json-api api.json
cd godot-cpp
scons platform=<PLATFORM> generate_bindings=yes use_custom_api_file=yes custom_api_file=../api.json
cd ..

# building scripts

cd assignment2
scons platform=<PLATFORM>