/**
 * File: Ship.cpp
 * Author: Brian Noutchang
 * Desc: Definition of the ship class. The ship is the object that the player controls
*/

#include "Ship.h"

// Name: Ship(string) - Overloaded ship 
// Description: Creates a new ship that can hold items (MAX_ITEMS)
//              and Fuel (STARTING_FUEL). Populates m_name
// Preconditions: None
// Postconditions: A new ship
Ship::Ship(string name) {
    m_name = name;
    m_fuel = STARTING_FUEL;
}

// Name: GetName()
// Description: Returns m_name
// Preconditions: None
// Postconditions: Returns ship's m_name
string Ship::GetName() {
    return m_name;
}

// Name: GetTotal(string type)
// Description: Passed an item type (armor, weapon, or engine)
//     Iterates over all items on ship and totals type passed in
// Preconditions: None
// Postconditions: Returns total value for armor, weapon, or engine
int Ship::GetTotal(string type) {
    int total = 0; //counter for the total value

    for (int i = 0; i < (int)m_shipItems.size(); i++) {
        //if current item in iteration matches the type passed it, add its value to total
        if (m_shipItems.at(i)->GetType() == type)
            total += m_shipItems.at(i)->GetValue();
    }

    return total;
}

// Name: AddItem
// Description: Adds a new item into m_items up to MAX_ITEMS.
//    If at max, calls ReplaceItem
// Preconditions: None
// Postconditions: m_items is populated
void Ship::AddItem(Item* item) {
    //if item inventory is full, replace an item
    if ((int)m_shipItems.size() == MAX_ITEMS)
        ReplaceItem(item);
    else
        m_shipItems.push_back (item);
}

// Name: ReplaceItem(Item*)
// Description: Used when m_shipItem is at capacity.
//   Lists all ship items and replaces with updated pointer
//   Does NOT make a new object - just updates pointer
// Preconditions: None
// Postconditions: Used to replace an item in inventory (m_shipItems)
void Ship::ReplaceItem(Item* item) {
    int choice; //the item to replace

    //display each item in inventory and get input from user
    do {
        cout << "Which item would you like to replace?\n";
        DisplayItems();

        cin >> choice;
        if (choice >= 1 && choice <= (int) m_shipItems.size())
            m_shipItems.at(choice-1) = item;

    } while (choice < 1 || choice > (int)m_shipItems.size());
}

// Name: GetFuel
// Description: Returns fuel
// Preconditions: None
// Postconditions: Returns m_fuel
int Ship::GetFuel() {
    return m_fuel;
}

// Name: ModifyFuel(int)
// Description: Used to increase (positive int) or
//              decrease (negative int) m_fuel
// Preconditions: None
// Postconditions: Used to update fuel.
void Ship::ModifyFuel(int fuel) {
    m_fuel += fuel;
    cout << "Your fuel has been modified by " << fuel << " fuel\n";
}

// Name: DisplayItems
// Description: Displays a numbered list of all items on ship.
// Preconditions: None
// Postconditions: m_items is populated
void Ship::DisplayItems() {
    for (int i = 0; i < GetItemCount(); i++) {
        cout << i+1 << ". ";
        //each type of item has its own display behavior
        m_shipItems.at(i)->Display();
        cout << endl;
    }
}

// Name: GetItemCount();
// Description: Returns number of items in m_shipItems
// Preconditions: None
// Postconditions: Returns items in m_shipItems
int Ship::GetItemCount() {
    return m_shipItems.size();
}

// Name: DisplayShip;
// Description: Displays stats about the ship
// Displays name, fuel, attack(weapon), defense(armor), engine(engine) all all items
// Preconditions: None
// Postconditions: None
void Ship::DisplayShip() {
    cout << "********************\n";
    
    // Ship Name:
    cout << "Ship Name: " << m_name << endl;
    // Fuel:
    cout << "Fuel: " << m_fuel << endl;
    // Attack:
    cout << "Attack: " << GetTotal("weapon") << endl;
    // Defense:
    cout << "Defense: " << GetTotal("armor") << endl;
    // Engine:
    cout << "Engine: " << GetTotal("engine") << endl;

    cout << "********************\n";
    
    DisplayItems();
}