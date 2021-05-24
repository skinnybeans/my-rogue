//
//  SoundList.hpp
//  my-rogue
//
//  Created by Henrik Axelsson on 14/7/17.
//  Copyright © 2017 Henrik Axelsson. All rights reserved.
//

#ifndef SoundList_hpp
#define SoundList_hpp

#include <string>

enum class SOUND_ID
{
    // Enemy
    ENEMY_DEAD,
    
    // Environmental
    FIRE,
    
    // Item
    GEM_PICKUP,
    KEY_PICKUP,
    COIN_PICKUP,
    
    // Player
    PLAYER_HIT,
    
    // Done
    COUNT
};

const std::string SoundStrings [] = {
    // Enemy
    "/resources/sounds/snd_enemy_dead.wav",
    
    // Environmental
    "/resources/sounds/snd_fire.wav",
    
    // Item
    "/resources/sounds/snd_gem_pickup.wav",
    "/resources/sounds/snd_key_pickup.wav",
    "/resources/sounds/snd_coin_pickup.wav",
    
    // Player
    "/resources/sounds/snd_player_hit.wav",
};

enum class MUSIC_ID
{
    // General music
    GENERAL_1,
    GENERAL_2,
    GENERAL_3,
    GENERAL_4,
    
    // Done
    COUNT
};

const std::string MusicStrings [] = {
  // General music
    "/resources/music/msc_main_track_1.wav",
    "/resources/music/msc_main_track_2.wav",
    "/resources/music/msc_main_track_3.wav",
    "/resources/music/msc_main_track_4.wav"
};

#endif /* SoundList_hpp */
