# C++ Space Fighter Simulator

A modular, systems-driven simulation engine built to demonstrate advanced **Inheritance**, **Polymorphism**, and **Dynamic Memory Management** in C++.

## Key Engineering Features
* **Polymorphic Item Architecture:** Implemented an abstract `Item` base class with derived `Weapon`, `Armor`, and `Engine` classes. This allows the Ship to manage a diverse inventory through a single `vector<Item*>` while maintaining type-specific behaviors.
* **Data-Driven Engine:** Engineered a robust file-parsing system that dynamically loads and initializes 100+ unique planets and items from external CSV-style data files.
* **Procedural Battle Logic:** Developed a planetary bombardment system that calculates combat outcomes by comparing ship-wide attack and defense totals against randomized planet challenges.
* **Strategic Resource Management:** Built a fuel-based movement and reward system, requiring players to balance exploration costs against the acquisition of high-tier ship upgrades.

## Technical Engineering Highlights
* **Abstract Class Implementation:** Utilized pure virtual functions to enforce a consistent interface across the entire item hierarchy.
* **Manual Memory Management:** Demonstrated expertise in the C++ object lifecycle by implementing deep deallocation of dynamically allocated pointers within complex containers.
* **Calculated Progression:** Integrated a "Utopia" win condition that evaluates the ship's aggregated engine power against a procedurally generated target value.
* **Modular Codebase:** Strictly adhered to professional standards by separating core engine logic, entity definitions, and game-state management into distinct header and implementation files.

## Project Structure
* **`Ship.h / .cpp`**: Manages player attributes, fuel mechanics, and polymorphic inventory.
* **`Item.h / Weapon.h / Armor.h / Engine.h`**: The polymorphic hierarchy defining ship upgrades.
* **`Planet.h / Enemy.h / Gas.h / Mining.h`**: A derived system for diverse planetary encounters and resource nodes.
* **`Game.h / .cpp`**: The primary engine handling the main simulation loop, file I/O, and win/loss state logic.
* **`makefile`**: Automated build script with dedicated targets for compilation, execution, and memory leak testing via Valgrind.
  
***

**Note:** This project was developed as part of the **CMSC 202: Computer Science II** curriculum at **UMBC**. While the core engine and data structures were independently developed, the initial project architecture and data files were provided as part of the coursework.
