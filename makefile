CXX = g++
CXXFLAGS = -Wall

proj4: Item.o Armor.o Engine.o Weapon.o Ship.o Planet.o Enemy.o Gas.o Mining.o Game.o proj4.cpp
	$(CXX) $(CXXFLAGS) Item.o Armor.o Engine.o Weapon.o Ship.o Planet.o Enemy.o Gas.o Mining.o Game.o proj4.cpp -o proj4

Game.o: Ship.o Planet.o Enemy.o Gas.o Mining.o Item.o Armor.o Engine.o Weapon.o Game.h Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

Ship.o: Item.o Ship.h Ship.cpp
	$(CXX) $(CXXFLAGS) -c Ship.cpp

Mining.o: Planet.o Mining.h Mining.cpp
	$(CXX) $(CXXFLAGS) -c Mining.cpp

Gas.o: Planet.o Gas.h Gas.cpp
	$(CXX) $(CXXFLAGS) -c Gas.cpp

Enemy.o: Planet.o Enemy.h Enemy.cpp
	$(CXX) $(CXXFLAGS) -c Enemy.cpp

Planet.o: Ship.o Planet.h Planet.cpp
	$(CXX) $(CXXFLAGS) -c Planet.cpp

Weapon.o: Item.o Weapon.h Weapon.cpp
	$(CXX) $(CXXFLAGS) -c Weapon.cpp

Engine.o: Item.o Engine.h Engine.cpp
	$(CXX) $(CXXFLAGS) -c Engine.cpp

Armor.o: Item.o Armor.h Armor.cpp
	$(CXX) $(CXXFLAGS) -c Armor.cpp

Item.o: Item.h Item.cpp
	$(CXX) $(CXXFLAGS) -c Item.cpp

run:
	./proj4 proj4_items.txt proj4_planets.txt

clean:
	rm *.o

val:
	valgrind ./proj4 proj4_items.txt proj4_planets.txt