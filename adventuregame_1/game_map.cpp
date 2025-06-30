#include "gamemap.h"
//#include "room.h"
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
//
namespace game {
	Map::Map()
		: idMap()
	{
		createNullRoom();
	}

	int Map::addRoom()
	{
		// creating the room with unique_ptr changes
		// the way its lifetime is managed
		// instead of being created locally and dying
		// when the function exits, the lifetime management
		// is granted to the idMap map, thus the room object
		// only dies when idMap dies.
		std::unique_ptr<Room> room = std::make_unique<Room>(*this->idMap[this->nullRoomId]);
		int roomId = room->getId();
		this->idMap[roomId] = std::move(room);
		return roomId;
	}

	int Map::addRoom(const std::string& name) {
		std::unique_ptr<Room> room = std::make_unique<Room>(name, *this->idMap[this->nullRoomId]);
		int roomId = room->getId();
		this->idMap[roomId] = std::move(room);
		return roomId;
	}

	int Map::addRoom(Room& room) {
		std::unique_ptr<Room> unique = std::make_unique<Room>(room);
		int roomId = unique->getId();
		this->idMap[roomId] = std::move(unique);
		return roomId;
	}
	
	//int Map::addRoom(Room& room, Room& nuller) {
	//	//std::unique_ptr<Room> unique = std::make_unique<Room>(room, nuller);
	//	int roomId = room.getId();
	//	this->idMap[roomId] = std::move(room);
	//	return roomId;
	//}

	void walkDirection(Directions direction, Room* room) {
		std::vector<Directions> dirArr = {
			Directions::east,
			Directions::west,
			Directions::south,
			Directions::north
		};

	}

	void Map::findIntersections() {

	}

	void Map::createNullRoom() {
		std::unique_ptr<Room> room = std::make_unique<Room>();
		int roomId = room->getId();
		this->idMap[roomId] = std::move(room);
		this->nullRoomId = roomId;
	}

	Room& Map::getRoom(int id) {
		return *idMap.at(id); // does not return a local variable which gets destroyed
							  // returns a reference to the object stored by the map
							  // with the id
	}

	int Map::getNullRoomId() {
		return this->nullRoomId;
	}

	void Map::setStart(Room& room) {
		this->startRoomId = room.getId();
	}

	int Map::getEdge(Directions direction) {
		int nullRoomId = this->getNullRoomId();
		Room& nullRoom = this->getRoom(nullRoomId);
		Room& startRoom = this->getRoom(this->startRoomId);
		std::vector<Directions> dirArr = {
			Directions::east,
			Directions::west,
			Directions::south,
			Directions::north
		};
		std::vector<int> distanceArr{};
		for (Directions inDir: dirArr) {
			int roomId = startRoom.getExit(inDir).getId();
			if (roomId == nullRoomId) {
				continue;
			}
			else {
				int distance = 0;
				if (inDir == direction) { ++distance; }
				distance = this->getEdge(roomId ,this->startRoomId, direction, getOppositeDirection(inDir), distance);
				distanceArr.push_back(distance);
			}
		}
		int distance = *std::max_element(distanceArr.begin(), distanceArr.end());

		return distance;
	}

	int Map::getEdge(int current_room_id, int prev_room_id, Directions direction, Directions prev_direction, int distance) {
		if (Directions::east != prev_direction) {
			int room_id = checkNullExit(current_room_id, Directions::east);
			if(room_id != 0) {
				if (Directions::east == direction) { ++distance; }
				distance = this->getEdge(room_id, current_room_id, direction, Directions::west, distance);
			}
		}
		
		if (Directions::west != prev_direction) {
			int room_id = checkNullExit(current_room_id, Directions::west);
			if (room_id != 0) {
				if (Directions::west == direction) { ++distance; }
				distance = this->getEdge(room_id, current_room_id, direction, Directions::east, distance);
			}
		}
		
		if (Directions::north != prev_direction) {
			int room_id = checkNullExit(current_room_id, Directions::north);
			if (room_id != 0) {
				if (Directions::north == direction) { ++distance; }
				distance = this->getEdge(room_id, current_room_id, direction, Directions::south, distance);
			}
		}
		
		if (Directions::south != prev_direction) {
			int room_id = checkNullExit(current_room_id, Directions::south);
			if (room_id != 0) {
				if (Directions::south == direction) { ++distance; }
				distance = this->getEdge(room_id, current_room_id, direction, Directions::north, distance);
			}
		}
		return distance;
	}

	int Map::checkNullExit(int room_id, Directions direction) {
		int nullRoomId = this->getNullRoomId();
		int roomId = this->getRoom(room_id).getExit(direction).getId();
		if (roomId == nullRoomId) {
			return 0;
		}
		return roomId;
	}

	std::vector<Room*> Map::getRooms() {
		std::vector<Room*> rooms;
		int nullRoomId = this->getNullRoomId();
		for (auto& [key, ptr] : this->idMap) {
			if(key != nullRoomId && ptr) {
				rooms.push_back(ptr.get());
			}
		}
		return rooms;
	}

	Directions Map::getOppositeDirection(Directions direction) {
		switch (direction)
		{
		case game::Directions::south:
			return Directions::north;
		case game::Directions::east:
			return Directions::west;
		case game::Directions::west:
			return Directions::east;
		case game::Directions::north:
			return Directions::south;
		}
	}

	std::string_view Map::directionToString(Directions direction) {
		switch (direction)
		{
		case game::Directions::south:
			return "south";
		case game::Directions::east:
			return "east";
		case game::Directions::west:
			return "west";
		case game::Directions::north:
			return "north";
		default:
			break;
		}
	}
}