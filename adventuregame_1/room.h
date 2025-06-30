#pragma once
#include <string>
#include <string_view>
#include <array>

namespace game {
	enum class Directions {
		south,
		east,
		west,
		north
	};
	class Room {
	private:
		static int nextRoomId; // static class-level counter
		int roomId;
		std::string roomName;
		std::string roomDescription;
		Room* south;
		Room* east;
		Room* west;
		Room* north;
	public:
		Room();
		Room(Room& nuller);
		Room(const std::string& name);
		Room(const std::string& name, Room& nuller);
		void setExit(Room& room, game::Directions direction);
		Room& getExit(game::Directions direction);
		const int getId();
		std::string_view getName();
		std::array<int, 4> getAllExits();
	};
	extern Room nullRoom;
}
#pragma once
