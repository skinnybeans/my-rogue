//
//  TextureList.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 18/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef TextureList_hpp
#define TextureList_hpp

#include <string>

enum class TEXTURE_ID {
    
    // ---------------
    // PLAYER TEXTURES
    // ---------------
    
    // Player warrior textures
    PLAYER_WARRIOR_WALK_UP,
    PLAYER_WARRIOR_WALK_DOWN,
    PLAYER_WARRIOR_WALK_RIGHT,
    PLAYER_WARRIOR_WALK_LEFT,
    PLAYER_WARRIOR_IDLE_UP,
    PLAYER_WARRIOR_IDLE_DOWN,
    PLAYER_WARRIOR_IDLE_RIGHT,
    PLAYER_WARRIOR_IDLE_LEFT,
    
    // Player thief textures
    PLAYER_THIEF_WALK_UP,
    PLAYER_THIEF_WALK_DOWN,
    PLAYER_THIEF_WALK_RIGHT,
    PLAYER_THIEF_WALK_LEFT,
    PLAYER_THIEF_IDLE_UP,
    PLAYER_THIEF_IDLE_DOWN,
    PLAYER_THIEF_IDLE_RIGHT,
    PLAYER_THIEF_IDLE_LEFT,
    
    // Player mage textures
    PLAYER_MAGE_WALK_UP,
    PLAYER_MAGE_WALK_DOWN,
    PLAYER_MAGE_WALK_RIGHT,
    PLAYER_MAGE_WALK_LEFT,
    PLAYER_MAGE_IDLE_UP,
    PLAYER_MAGE_IDLE_DOWN,
    PLAYER_MAGE_IDLE_RIGHT,
    PLAYER_MAGE_IDLE_LEFT,
    
    // Player archer
    PLAYER_ARCHER_WALK_UP,
    PLAYER_ARCHER_WALK_DOWN,
    PLAYER_ARCHER_WALK_RIGHT,
    PLAYER_ARCHER_WALK_LEFT,
    PLAYER_ARCHER_IDLE_UP,
    PLAYER_ARCHER_IDLE_DOWN,
    PLAYER_ARCHER_IDLE_RIGHT,
    PLAYER_ARCHER_IDLE_LEFT,

    // ---------------
    // ENEMY TEXTURES
    // ---------------
    
    // Slime
    ENEMY_SLIME_WALK_UP,
    ENEMY_SLIME_WALK_DOWN,
    ENEMY_SLIME_WALK_RIGHT,
    ENEMY_SLIME_WALK_LEFT,
    ENEMY_SLIME_IDLE_UP,
    ENEMY_SLIME_IDLE_DOWN,
    ENEMY_SLIME_IDLE_RIGHT,
    ENEMY_SLIME_IDLE_LEFT,
    
    // Skeleton
    ENEMY_SKELETON_WALK_UP,
    ENEMY_SKELETON_WALK_DOWN,
    ENEMY_SKELETON_WALK_RIGHT,
    ENEMY_SKELETON_WALK_LEFT,
    ENEMY_SKELETON_IDLE_UP,
    ENEMY_SKELETON_IDLE_DOWN,
    ENEMY_SKELETON_IDLE_RIGHT,
    ENEMY_SKELETON_IDLE_LEFT,
    
    // Goblin
    ENEMY_GOBLIN_WALK_UP,
    ENEMY_GOBLIN_WALK_DOWN,
    ENEMY_GOBLIN_WALK_RIGHT,
    ENEMY_GOBLIN_WALK_LEFT,
    ENEMY_GOBLIN_IDLE_UP,
    ENEMY_GOBLIN_IDLE_DOWN,
    ENEMY_GOBLIN_IDLE_RIGHT,
    ENEMY_GOBLIN_IDLE_LEFT,
    
    // Enemy armour
    ARMOR_HELMET_WALK_FRONT,
    ARMOR_HELMET_WALK_SIDE,
    ARMOR_HELMET_IDLE_FRONT,
    ARMOR_HELMET_IDLE_SIDE,
    
    ARMOR_TORSO_WALK_FRONT,
    ARMOR_TORSO_WALK_SIDE,
    ARMOR_TORSO_IDLE_FRONT,
    ARMOR_TORSO_IDLE_SIDE,
    
    ARMOR_LEGS_WALK_FRONT,
    ARMOR_LEGS_WALK_SIDE,
    ARMOR_LEGS_IDLE_FRONT,
    ARMOR_LEGS_IDLE_SIDE,
    
    COUNT
};

struct TextureInfo {
    TextureInfo() {};
    TextureInfo(std::string texturePath, int animationFrames)
    {
        this->texturePath = texturePath;
        this->animationFrames = animationFrames;
    }
    std::string texturePath;
    int animationFrames;
};


const TextureInfo TextureStrings [] = {
    
    // ---------------
    // PLAYER TEXTURES
    // ---------------
    
    // Player warrior textures
    TextureInfo("resources/players/warrior/spr_warrior_walk_up.png", 8),
    TextureInfo("resources/players/warrior/spr_warrior_walk_down.png", 8),
    TextureInfo("resources/players/warrior/spr_warrior_walk_right.png", 8),
    TextureInfo("resources/players/warrior/spr_warrior_walk_left.png", 8),
    TextureInfo("resources/players/warrior/spr_warrior_idle_up.png", 1),
    TextureInfo("resources/players/warrior/spr_warrior_idle_down.png", 1),
    TextureInfo("resources/players/warrior/spr_warrior_idle_right.png", 1),
    TextureInfo("resources/players/warrior/spr_warrior_idle_left.png", 1),
    
    // Player thief textures
    TextureInfo("resources/players/thief/spr_thief_walk_up.png", 8),
    TextureInfo("resources/players/thief/spr_thief_walk_down.png", 8),
    TextureInfo("resources/players/thief/spr_thief_walk_right.png", 8),
    TextureInfo("resources/players/thief/spr_thief_walk_left.png", 8),
    TextureInfo("resources/players/thief/spr_thief_idle_up.png", 1),
    TextureInfo("resources/players/thief/spr_thief_idle_down.png", 1),
    TextureInfo("resources/players/thief/spr_thief_idle_right.png", 1),
    TextureInfo("resources/players/thief/spr_thief_idle_left.png", 1),
    
    // Player mage textures
    TextureInfo("resources/players/mage/spr_mage_walk_up.png", 8),
    TextureInfo("resources/players/mage/spr_mage_walk_down.png", 8),
    TextureInfo("resources/players/mage/spr_mage_walk_right.png", 8),
    TextureInfo("resources/players/mage/spr_mage_walk_left.png", 8),
    TextureInfo("resources/players/mage/spr_mage_idle_up.png", 1),
    TextureInfo("resources/players/mage/spr_mage_idle_down.png", 1),
    TextureInfo("resources/players/mage/spr_mage_idle_right.png", 1),
    TextureInfo("resources/players/mage/spr_mage_idle_left.png", 1),
    
    // Player archer textures
    TextureInfo("resources/players/archer/spr_archer_walk_up.png", 8),
    TextureInfo("resources/players/archer/spr_archer_walk_down.png", 8),
    TextureInfo("resources/players/archer/spr_archer_walk_right.png", 8),
    TextureInfo("resources/players/archer/spr_archer_walk_left.png", 8),
    TextureInfo("resources/players/archer/spr_archer_idle_up.png", 1),
    TextureInfo("resources/players/archer/spr_archer_idle_down.png", 1),
    TextureInfo("resources/players/archer/spr_archer_idle_right.png", 1),
    TextureInfo("resources/players/archer/spr_archer_idle_left.png", 1),
    
    // ---------------
    // ENEMY TEXTURES
    // ---------------
    
    // Slime
    TextureInfo("resources/enemies/slime/spr_slime_walk_up.png", 8),
    TextureInfo("resources/enemies/slime/spr_slime_walk_down.png", 8),
    TextureInfo("resources/enemies/slime/spr_slime_walk_right.png", 8),
    TextureInfo("resources/enemies/slime/spr_slime_walk_left.png", 8),
    TextureInfo("resources/enemies/slime/spr_slime_idle_up.png", 1),
    TextureInfo("resources/enemies/slime/spr_slime_idle_down.png", 1),
    TextureInfo("resources/enemies/slime/spr_slime_idle_right.png", 1),
    TextureInfo("resources/enemies/slime/spr_slime_idle_left.png", 1),
    
    // Skeleton
    TextureInfo("resources/enemies/skeleton/spr_skeleton_walk_up.png", 8),
    TextureInfo("resources/enemies/skeleton/spr_skeleton_walk_down.png", 8),
    TextureInfo("resources/enemies/skeleton/spr_skeleton_walk_right.png", 8),
    TextureInfo("resources/enemies/skeleton/spr_skeleton_walk_left.png", 8),
    TextureInfo("resources/enemies/skeleton/spr_skeleton_idle_up.png", 1),
    TextureInfo("resources/enemies/skeleton/spr_skeleton_idle_down.png", 1),
    TextureInfo("resources/enemies/skeleton/spr_skeleton_idle_right.png", 1),
    TextureInfo("resources/enemies/skeleton/spr_skeleton_idle_left.png", 1),
    
    // Goblin
    TextureInfo("resources/enemies/goblin/spr_goblin_walk_up.png", 8),
    TextureInfo("resources/enemies/goblin/spr_goblin_walk_down.png", 8),
    TextureInfo("resources/enemies/goblin/spr_goblin_walk_right.png", 8),
    TextureInfo("resources/enemies/goblin/spr_goblin_walk_left.png", 8),
    TextureInfo("resources/enemies/goblin/spr_goblin_idle_up.png", 1),
    TextureInfo("resources/enemies/goblin/spr_goblin_idle_down.png", 1),
    TextureInfo("resources/enemies/goblin/spr_goblin_idle_right.png", 1),
    TextureInfo("resources/enemies/goblin/spr_goblin_idle_left.png", 1),
    
    // Armor
    TextureInfo("resources/armor/helmet/spr_helmet_walk_front.png", 8),
    TextureInfo("resources/armor/helmet/spr_helmet_walk_side.png", 8),
    TextureInfo("resources/armor/helmet/spr_helmet_idle_front.png", 8),
    TextureInfo("resources/armor/helmet/spr_helmet_idle_side.png", 8),
    
    TextureInfo("resources/armor/torso/spr_torso_walk_front.png", 8),
    TextureInfo("resources/armor/torso/spr_torso_walk_side.png", 8),
    TextureInfo("resources/armor/torso/spr_torso_idle_front.png", 8),
    TextureInfo("resources/armor/torso/spr_torso_idle_side.png", 8),
    
    TextureInfo("resources/armor/legs/spr_legs_walk_front.png", 8),
    TextureInfo("resources/armor/legs/spr_legs_walk_side.png", 8),
    TextureInfo("resources/armor/legs/spr_legs_idle_front.png", 8),
    TextureInfo("resources/armor/legs/spr_legs_idle_side.png", 8),
};
#endif /* TextureList_hpp */
