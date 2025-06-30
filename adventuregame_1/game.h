#pragma once
#include <vector>
#include <map>
#include "room.h"
namespace game {
	class Map {
	private:
		std::vector<Room*> rooms;
		std::map<int, Room*> idMap;
	public:
		Map();
		int addRoom();
		Room* getRoom(int id);
		void addRoomFromExisting(Room& room); 
		Room getEastern();
		/*
			Getting the longest path in any direction requires searching
			through all the map and subtracting each jump in one direction
			from the opposite direction.
			e.g. to get the longest path to the east, we go through each single path
			and in each path, we count every time we go east and every time we go west.
			after a path is complete (i.e. we found a room leading to a dead end OR we found a loop),
			we subtract the number of `west` walks from the number of `east` walks (number_east - number_west)
			which will give us a distance we can compare to other rooms, of which there may be more than
			a single room applicable (i.e. 2 rooms with the same result), however this doesn't matter and we can
			return any of the results.

			to detect a loop, we must save the room we started in,
			and each intersection between 3 or more rooms (the direction
			we came from, and at least 2 other directions).
			if we go through an intersection more than once in a single path, or if
			the starting room was walked more than a single time, we can
			say we are at a loop.
			in this loop, we can take any of the x-most rooms which can be found by
			going through the loop, counting the walks in the directions, and then finding
			a room which to get to, the number of walks is equal to the number we found earlier.
		*/
	};
}