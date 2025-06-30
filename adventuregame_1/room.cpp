#include <format>
#include <string_view>
#include "room.h"
#include <iostream>
#include <array>

namespace game {
	// initialize the static variable
	int Room::nextRoomId = 0;
	Room nullRoom("nullroom");

	Room::Room()
		: south(&nullRoom), east(&nullRoom), west(&nullRoom), north(&nullRoom)
	{
		this->roomId = ++nextRoomId;
		this->roomName = std::format("default_{}", roomId);
	}
	Room::Room(Room& nuller)
		: south(&nuller), east(&nuller), west(&nuller), north(&nuller)
	{
		this->roomId = ++nextRoomId;
		this->roomName = std::format("default_{}", roomId);
	}
	Room::Room(const std::string& name)
		: south(&nullRoom), east(&nullRoom), west(&nullRoom), north(&nullRoom)
	{
		this->roomId = ++nextRoomId;
		this->roomName = name;
	}
	Room::Room(const std::string& name, Room& nuller)
		: south(&nuller), east(&nuller), west(&nuller), north(&nuller)
	{
		this->roomId = ++nextRoomId;
		this->roomName = name;
	}

	void Room::setExit(Room& room, game::Directions direction) {
		switch (direction) {
		case game::Directions::south:
			this->south = &room;
			room.north = this;
			return;
		case game::Directions::east:
			this->east = &room;
			room.west = this;
			return;
		case game::Directions::west:
			this->west = &room;
			room.east = this;
			return;
		case game::Directions::north:
			this->north = &room;
			room.south = this;
			return;
		}
	}

	Room& Room::getExit(game::Directions direction) {
		switch (direction) {
		case game::Directions::south:
			return *this->south;
		case game::Directions::east:
			return *this->east;
		case game::Directions::west:
			return *this->west;
		case game::Directions::north:
			return *this->north;
		default:
			return nullRoom;
		}
	}

	const int Room::getId() {
		return this->roomId;
	}
	std::string_view Room::getName() {
		return this->roomName;
	}

	std::array<int, 4> Room::getAllExits() {
		//std::cout << this->getExit(Directions::south).getId();
		 std::array<int, 4> exitIds {
			this->getExit(Directions::south).getId(),
			this->getExit(Directions::east).getId(),
			this->getExit(Directions::west).getId(),
			this->getExit(Directions::north).getId(),
		};

		return exitIds;

	}
}
