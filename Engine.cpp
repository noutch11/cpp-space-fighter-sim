/**
 * File: Engine.cpp
 * Author: Brian Noutchang
 * Desc: Definition of the Engine class. The Engine is a type of item used by your ship. It affects engine.
*/

#include "Engine.h"

// Name: Engine(string name, string type, int value)
// Description: Creates a new Engine item
// Preconditions: None
// Postconditions: Can create a Engine
Engine::Engine(string name, string type, int value):Item(name, type, value) {}

// Name: Display
// Description: Displays ENGINE, name, and value of engine item
// Preconditions: None
// Postconditions: Displays information about the engine
void Engine::Display() {
    cout << ENGINE << GetName() << "(" << GetValue() << ")";
}