// adventuregame.cpp : Defines the entry point for the application.
//
#include "room.h"
#include "gamemap.h"
#include <iostream>
#include <format>


//using namespace std;
using namespace game;
int main()
{

	game::Map gameMap;

	//int room2id = gameMap.addRoom("room2");
	//Room& room1 = gameMap.getRoom(gameMap.addRoom("room1"));
	//Room& room2 = gameMap.getRoom(room2id);
	//Room& room3 = gameMap.getRoom(gameMap.addRoom("room3"));
	//Room& room4 = gameMap.getRoom(gameMap.addRoom("room4"));
	//Room& room5 = gameMap.getRoom(gameMap.addRoom("room5"));
	//Room& room6 = gameMap.getRoom(gameMap.addRoom("room6"));
	//Room& room7 = gameMap.getRoom(gameMap.addRoom("room7"));
	//Room& room8 = gameMap.getRoom(gameMap.addRoom("room8"));
	//Room& room9 = gameMap.getRoom(gameMap.addRoom("room9"));

	Room& startRoom = gameMap.getRoom(gameMap.addRoom());
	// TODO buildCorridor should return either the last room id
	// or all the corridor rooms' ids
	gameMap.buildCorridor(Directions::north, 5, startRoom);
	std::vector<Room*> rooms = gameMap.getRooms();


	//room1.setExit(room5, Directions::west);
	//room1.setExit(room6, Directions::south);
	//room1.setExit(room3, Directions::east);
	//room3.setExit(room4, Directions::north);
	//room3.setExit(room2, Directions::east);
	//
	//room2.setExit(room7, Directions::east);
	//room7.setExit(room8, Directions::east);
	//room8.setExit(room9, Directions::east);
	 
	/*gameMap.setStart();
	std::cout << "distance to north is " << gameMap.getEdge(Directions::north) << " rooms.\n";
	std::cout << "distance to south is " << gameMap.getEdge(Directions::south) << " rooms.\n";
	std::cout << "distance to east is " << gameMap.getEdge(Directions::east) << " rooms.\n";
	std::cout << "distance to west is " << gameMap.getEdge(Directions::west) << " rooms.\n";*/

}
