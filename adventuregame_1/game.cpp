#include "game_map.h"
#include <vector>
//
namespace game {
	Map::Map(){}

	int Map::addRoom() {
		Room room;
		Room* pRoom = &room;
		this->rooms.push_back(&room);
		this->idMap.insert(std::make_pair(room.getId(), pRoom));
		return room.getId();
	}

	/*Room* getRoom(int id) {
		return 
	}*/
}