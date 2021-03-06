//-------------------------------------------------------------------------------------
// Util.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef UTIL_H
#define UTIL_H

// Game states.
enum class GAME_STATE {
	MAIN_MENU,
	PLAYING,
	GAME_OVER
};

// Player classes.
enum class PLAYER_CLASS {
    WARRIOR,
    MAGE,
    ARCHER,
    THIEF,
    COUNT
};

// Player traits.
enum class PLAYER_TRAIT {
    ATTACK,
    DEFENSE,
    STRENGTH,
    DEXTERITY,
    STAMINA,
    ACCURACY,
    COUNT
};

// Spawnable items.
enum class ITEM {
	GEM,
	GOLD,
	HEART,
	POTION,
    POISON_HEART,
	KEY,            // Keep key as the last item!!
	COUNT
};

// Potions.
enum class POTION {
    ATTACK,
    DEFENSE,
    STRENGTH,
    DEXTERITY,
    STAMINA,
    ACCURACY,
    COUNT
};

// Enemy types.
enum class ENEMY {
	SLIME,
	HUMANOID,
	COUNT
};

// Humanoid enemy types
enum class ENEMY_HUMANOIDS {
    GOBLIN,
    SKELETON,
    COUNT
};

// Colours predefined in SFML
enum class COLOR {
    BLACK,
    WHITE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA,
    CYAN,
    TRANSPARENT,
    COUNT
};

// Animation states.
// The walk and idle states must be kept apart by 4 or the anim code will require updating
enum class ANIMATION_STATE {
	WALK_UP,
	WALK_DOWN,
	WALK_RIGHT,
	WALK_LEFT,
	IDLE_UP,
	IDLE_DOWN,
	IDLE_RIGHT,
	IDLE_LEFT,
	COUNT
};

// Tiles.
enum class TILE {
	WALL_SINGLE,
	WALL_TOP_END,
	WALL_SIDE_RIGHT_END,
	WALL_BOTTOM_LEFT,
	WALL_BOTTOM_END,
	WALL_SIDE,
	WALL_TOP_LEFT,
	WALL_SIDE_LEFT_T,
	WALL_SIDE_LEFT_END,
	WALL_BOTTOM_RIGHT,
	WALL_TOP,
	WALL_BOTTOM_T,
	WALL_TOP_RIGHT,
	WALL_SIDE_RIGHT_T,
	WALL_TOP_T,
	WALL_INTERSECTION,
	WALL_DOOR_LOCKED,
    WALL_DOOR_UNLOCKED,
    WALL_DOOR_LOCKED_RIGHT,
    WALL_DOOR_UNLOCKED_RIGHT,
	WALL_ENTRANCE,
    WALL_ENTRANCE_LEFT,
	FLOOR,
	FLOOR_ALT,
    FLOOR_SPIKES,
	EMPTY,
	COUNT
};

// Game views.
enum class VIEW {
	MAIN,
	UI,
	COUNT
};

// Music tracks.
enum class MUSIC_TRACK {
    ALT_1,
    ALT_2,
    ALT_3,
    ALT_4,
    COUNT
};

enum class LEVEL_GENERATOR {
    BACKTRACKER,
    OPEN_ROOM,
    COUNT
};
#endif
