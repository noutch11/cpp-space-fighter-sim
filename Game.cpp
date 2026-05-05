/**
 * File: Game.cpp
 * Author: Brian Noutchang
 * Desc: Definition of the Game class. This class manages the entire game
*/

#include "Game.h"

// Name: Game(string itemFile, string planetFile) - Overloaded Constructor
// Description: Creates a new Game by setting m_fileItems and m_filePlanets
// Preconditions: None
// Postconditions: Sets two file names in Game
Game::Game(string itemFile, string planetFile) {
    m_fileItems = itemFile;
    m_filePlanets = planetFile;
}
  
// Name: ~Game
// Description: Destructor
// Preconditions: None
// Postconditions: Deallocates anything dynamically allocated
//                 in Game (ship, items, and planets)
Game::~Game() {
    //deallocate each item in m_items starting from last element
    for (int i = (int)m_items.size() - 1; i >= 0; i--) {
        Item *currItem = m_items.at (i); //current airport in iteration
        delete currItem;
        currItem = nullptr;
    }

    //deallocate each planet in m_planets starting from last element
    for (int i = (int)m_planets.size() - 1; i >= 0; i--) {
        Planet *currPlanet = m_planets.at (i); //current airport in iteration
        delete currPlanet;
        currPlanet = nullptr;
    }

    //deallocate m_ship
    delete m_ship;
    m_ship = nullptr;

    //clear vectors
    m_items.clear();
    m_planets.clear();
}

// Name: LoadItems()
// Description: Dynamically allocates items and inserts them into
//              the m_items vector
// Note: the number of items is NOT known - you should not use constants
// Hint: Use getline(file,variable,delimiter) - may also use stoi
// Precondition: m_itemFile is populated
// Postcondition: m_items is populated
void Game::LoadItems() {
    ifstream infile; //used to read from the file
    infile.open (m_fileItems);

    //while there is still content to be read
    while (infile.peek() > 0) {
        //vars to be read in
        string name; // item's name
        string type; // item's type
        int value; // item's value
        string valueStr; // to read item's value as a string

        if (infile.peek() == '\n')
            infile.ignore();

        /* data file in format: name,type,value
            read 3 times per iteration, using ',' as delimiter
        */
        getline (infile, name, DELIMITER);
        getline (infile, type, DELIMITER);
        getline (infile, valueStr);
        // convert from string to int for value
        value = stoi(valueStr);

        // create a new item based on corresponding type and add to m_items
        if (type == "armor") {
            Item *newArmor = new Armor (name, type, value);
            m_items.push_back(newArmor);

        } else if (type == "engine") {
            Item *newEngine = new Engine (name, type, value);
            m_items.push_back (newEngine);

        } else if (type == "weapon") {
            Item *newWeapon = new Weapon (name, type, value);
            m_items.push_back (newWeapon);
        }

        

    }
    infile.close();
    cout << m_items.size() << " items loaded.\n";
}

// Name: LoadPlanets()
// Description: Dynamically allocates items and inserts them into
//              the m_planets vector
// Note: the number of planets is NOT known - you should NOT use constants
// Hint: Use getline(file,variable,delimiter) - may also use stoi
// Precondition: m_planetFile is populated
// Postcondition: m_planets is populated
void Game::LoadPlanets() {
    ifstream infile; //used to read from the file
    infile.open (m_filePlanets);

    //while there is still content to be read
    while (infile.peek() > 0) {
        //vars to be read in
        string name; // planet's name
        string type; // planet's type
        int challenge; // planet's challenge
        string challengeStr; // to read planet's challenge as a string
        
        /* data file in format: name,type,challenge
            read 3 times per iteration, using ',' as delimiter
        */
        getline (infile, name, DELIMITER);
        getline (infile, type, DELIMITER);
        getline (infile, challengeStr);//cout << challengeStr << endl;
        // convert from string to int for challenge
        challenge = stoi(challengeStr);

        // create a new planet based on corresponding type and add to m_planets
        if (type == "enemy") {
            Planet *newEnemy = new Enemy (name, challenge);
            m_planets.push_back(newEnemy);

        } else if (type == "gas") {
            Planet *newGas = new Gas (name, challenge);
            m_planets.push_back(newGas);

        } else if (type == "mining") {
            Planet *newMining = new Mining (name, challenge);
            m_planets.push_back(newMining);
        }

    }
    infile.close();
    cout << m_planets.size() << " planets loaded.\n";
}

// Name: ShipCreation()
// Description: Populates m_ship and asks name (sets name of ship)
//              Also adds items (START_ENGINE, START_ARMOR, START_WEAPON)
// Preconditions: None
// Postconditions: m_ship is populated
void Game::ShipCreation() {
    cout << "Enter ship name: ";
    string shipName; //ship to get from user input
    getline (cin, shipName);

    //create a new ship
    m_ship = new Ship (shipName);

    //declare starter items
    Item *starterEngine = m_items.at(START_ENGINE);
    Item *starterArmor = m_items.at(START_ARMOR);
    Item *starterWeapon = m_items.at (START_WEAPON);

    //add start items
    m_ship->AddItem(starterEngine);
    m_ship->AddItem (starterArmor);
    m_ship->AddItem(starterWeapon);
}

// Name: StartGame()
// Description: Welcomes the player to the game. "Super Space Exploration"
//              Calls LoadPlanets, LoadItems, ShipCreation, sets the m_curPlanet (0)
//              randomizes m_winEngine based on UTOPIA_MAX and UTOPIA_MIN
//              Finally, calls Action (which is the main menu)
// Preconditions: Input files must exist
// Postconditions: All game components loaded to play game
void Game::StartGame() {
    cout << "Welcome to Super Space Exploration!\n";
    LoadPlanets();
    LoadItems();
    ShipCreation();

    //set current planet to starter planet and display it
    m_curPlanet = m_planets.at(START_PLANET);
    cout << *m_curPlanet << endl;
    //randomize m_winEngine based on UTOPIA_MAX and UTOPIA_MIN
    m_winEngine = (rand() % (UTOPIA_MAX+1 - UTOPIA_MIN)) + UTOPIA_MIN;

    //call main menu
    Action();
}
  
// Name: Action()
// Description: Menu for game. Displays menu.
//              Player can examine the ship's items, move, attack planet,
//              Try to travel to Utopia, check stats, or quit
//              Player dies in one of two ways: 1. <= 0 fuel or
//                   2. Tries to go to Utopia but doesn't have high enough engine
// Preconditions: Everything in start has been completed
// Postconditions: Game continues until quit or player dies
void Game::Action() {
    int choice; //menu choice entered by user
    //do while loop for input validation in main menu
    do {
        //end game for empty fuel
        if (m_ship->GetFuel() <= 0) {
            cout << "\nUnfortunately you ran out of fuel and died. Game over.\n";
            cout << "Please play again!\n";
            cout << "Goodbye!\n\n";
            return;
        }

        cout << "\nWhat would you like to do?\n";
        cout << "1. Examine Items\n";
        cout << "2. Move\n";
        cout << "3. Attack Planet\n";
        cout << "4. Travel to Utopia\n";
        cout << "5. Check Stats\n";
        cout << "6. Quit\n";
        cin >> choice;

        //different actions based on choice
        switch (choice) {
            case 1: DisplayShipItems();
            break;
            case 2: Move();
            break;
            case 3: AttackPlanet();
            break;

            case 4: {//utopia case
            int utopia = TravelUtopia();
            // engine total < UTOPIA_MIN, just give a warning
            if (utopia == 0) {
                cout << "You are not prepared to try to travel to Utopia yet.\n";
                cout << "Perhaps develop your engines more?\n";
            }
            // engine total <= m_winEngine, lost game
            else if (utopia == -1) {
                cout << "Your ship attempts to make it to Utopia.\n";
                cout << "The engines just weren't powerful enough.\n";
                cout << "You eventually ran out of food and fuel and died.\n";
                cout << "Please play again!\n";
                cout << "Goodbye!\n\n";
                return;
            }
            // engine total > m_winEngine, win game
            else if (utopia == 1) {
                cout << "Your ship attempts to make it to Utopia.\n";
                cout << "You successfully made it there.\n";
                cout << "You win!\n";
                cout << "Goodbye!\n\n";
                return;
            }
            break;
            }

            case 5: Stats();
            break;

            case 6: //exit case
            cout << "Goodbye!\n\n";
            return;
            break;

            default: cout << "Invalid entry";
        }

    } while (choice != 6);
}

// Name: Move
// Description: Moves ship to new random location
//              Charges MOVE_FUEL as cost to move to new planet
//              Displays information about new planet
// Preconditions: Must be valid move (may go to same planet more than once)
// Postconditions: Displays planet information and reduces fuel
void Game::Move() {
    int randPlanet;
    do {
        //choose a random planet until chosen planet is not the current one
        randPlanet = rand() % (int)m_planets.size();
    } while (m_planets.at(randPlanet) == m_curPlanet);
    m_curPlanet = m_planets.at(randPlanet);
    
    cout << "You travel to the next planet.\n";
    cout << *m_curPlanet << endl;

    //update ship fuel
    m_ship->ModifyFuel(MOVE_FUEL);
}

// Name: AttackPlanet
// Description: Allows ship to attack a planet
//              1. Checks if planet already defeated (displays message if already won)
//              2. Calls Planet's battle with ship (if not already defeated)
//              3. Displays if win or not. Can attack again if not defeated.
//              4. If winner, Identifies an item load on ship
// Preconditions: None
// Postconditions: Fuel may be below zero. May get new item.
void Game::AttackPlanet() {
    //notify if planet already defeated
    if (m_curPlanet->GetIsExplored()) {
        cout << "This planet has already been defeated.\n";
        cout << "You should move to a new planet.\n";
        return;
    }

    //if we win identify a new item
    if (m_curPlanet->Battle(m_ship))
        IdentifyItem(m_curPlanet->GetChallenge());
}

// Name: IdentifyItem(int challenge)
// Description: Randomly identifies an item of the challenge's level
//              Calls AddItem in ship and tries to add the item
// Preconditions: None
// Postconditions: Will try to add an item to the ship of a random type
void Game::IdentifyItem(int challenge) {
    Item *randItem = m_items.at(0);

    //look for random item while the value doesn't correspond to the challenge
    do {
        int random = rand() % m_items.size();
        randItem = m_items.at(random); //choose random item from random generated index
    } while (randItem->GetValue() != challenge);

    cout << "You have found: " << randItem->GetName();
    cout << "(" << randItem->GetType() << ") " << randItem->GetValue() << endl;
    //add the new item to the ship
    m_ship->AddItem(randItem);
}

// Name: Stats()
// Description: Calls the ship's display function
// Preconditions: None
// Postconditions: None
void Game::Stats() {
    m_ship->DisplayShip();
}

// Name: TravelUtopia()
// Description: Attempts to win game if total engine value > m_engineValue
//              if total engine value is below UTOPIA_MIN, returns 0
//              If total engine value above m_engineValue, returns 1
//              If total engine value below m_engineValue, returns -1
// Preconditions: None
// Postconditions: -1 = lose; 0 = continue, 1 = win
int Game::TravelUtopia() {
    int engineTotal = m_ship->GetTotal ("engine"); //the ship's engine total
    int retVal = 0; //return value

    // return correct int value based on engine total
    if (engineTotal < UTOPIA_MIN)
        retVal = 0;
    else if (engineTotal <= m_winEngine)
        retVal = -1;
    else if (engineTotal > m_winEngine)
        retVal= 1;

    return retVal;
}

// Name: DisplayShipItems
// Description: Displays a numbered list of all items on ship
// Preconditions: m_items has items in it otherwise says No Items Found
// Postconditions: None
void Game::DisplayShipItems() {
    //notify if no items in the ship
    if (m_ship->GetItemCount() == 0)
        cout << "No items found.\n";
    else
        m_ship->DisplayItems();
}