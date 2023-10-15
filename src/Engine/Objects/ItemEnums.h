#pragma once

#include <cstdint>
#include <cassert>
#include <utility>

#include "Engine/Objects/CharacterEnums.h"
#include "Engine/Spells/SpellEnums.h"

#include "Utility/Workaround/ToUnderlying.h"
#include "Utility/Flags.h"
#include "Utility/Segment.h"
#include "Utility/IndexedArray.h"

enum class DamageType : unsigned int {
    DAMAGE_FIRE = 0,
    DAMAGE_AIR = 1,
    DAMAGE_WATER = 2,
    DAMAGE_EARTH = 3,
    DAMAGE_PHYSICAL = 4,
    DAMAGE_MAGIC = 5,
    DAMAGE_SPIRIT = 6,
    DAMAGE_MIND = 7,
    DAMAGE_BODY = 8,
    DAMAGE_LIGHT = 9,
    DAMAGE_DARK = 10,

    DAMAGE_FIRST = DAMAGE_FIRE,
    DAMAGE_LAST = DAMAGE_DARK
};
using enum DamageType;

/*  338 */
enum class ItemFlag : uint32_t {
    ITEM_IDENTIFIED = 0x1,
    ITEM_BROKEN = 0x2,
    ITEM_TEMP_BONUS = 0x8,
    ITEM_AURA_EFFECT_RED = 0x10,
    ITEM_AURA_EFFECT_BLUE = 0x20,
    ITEM_AURA_EFFECT_GREEN = 0x40,
    ITEM_AURA_EFFECT_PURPLE = 0x80,
    ITEM_ENCHANT_ANIMATION_MASK = 0xF0,
    ITEM_STOLEN = 0x100,
    ITEM_HARDENED = 0x200,
};
using enum ItemFlag;
MM_DECLARE_FLAGS(ItemFlags, ItemFlag)
MM_DECLARE_OPERATORS_FOR_FLAGS(ItemFlags)

enum class ItemEnchantment : unsigned int {
    ITEM_ENCHANTMENT_NULL = 0,

    ITEM_ENCHANTMENT_OF_PROTECTION = 1,    // Adds +10 to all Resistances
    ITEM_ENCHANTMENT_OF_GODS = 2,          // Adds +10 to all Seven Statistics
    ITEM_ENCHANTMENT_OF_CARNAGE = 3,       // Projectile explodes like fireball
    ITEM_ENCHANTMENT_OF_COLD = 4,          // Adds 3-4 points of cold damage
    ITEM_ENCHANTMENT_OF_FROST = 5,         // Adds 6-8 points of cold damage
    ITEM_ENCHANTMENT_OF_ICE = 6,           // Adds 9-12 points of cold damage
    ITEM_ENCHANTMENT_OF_SPARKS = 7,        // Adds 2-5 points of electrical damage
    ITEM_ENCHANTMENT_OF_LIGHTNING = 8,     // Adds 4-10 points of electrical damage
    ITEM_ENCHANTMENT_OF_THUNDERBOLTS = 9,  // Adds 6-15 points of electrical damage
    ITEM_ENCHANTMENT_OF_FIRE = 10,         // Adds 1-6 points of fire damage
    ITEM_ENCHANTMENT_OF_FLAME = 11,        // Adds 2-12 points of fire damage
    ITEM_ENCHANTMENT_OF_INFERNOS = 12,     // Adds 3-18 points of fire damage
    ITEM_ENCHANTMENT_OF_POISON = 13,       // Adds 5 points of body damage
    ITEM_ENCHANTMENT_OF_VENOM = 14,        // Adds 8 points of body damage
    ITEM_ENCHANTMENT_OF_ACID = 15,         // Adds 12 points of body damage
    ITEM_ENCHANTMENT_VAMPIRIC = 16,        // 20% of damage dealt given to wielder
    ITEM_ENCHANTMENT_OF_RECOVERY = 17,     // Increases rate of Recovery
    ITEM_ENCHANTMENT_OF_IMMUNITY = 18,     // Wearer immune to Diseases
    ITEM_ENCHANTMENT_OF_SANITY = 19,       // Wearer immune to Insanity
    ITEM_ENCHANTMENT_OF_FREEDOM = 20,      // Wearer immune to Paralysis
    ITEM_ENCHANTMENT_OF_ANTIDOTES = 21,    // Wearer immune to Poison
    ITEM_ENCHANTMENT_OF_ALARMS = 22,       // Wearer immune to Sleep
    ITEM_ENCHANTMENT_OF_MEDUSA = 23,       // Wearer immune to Stone
    ITEM_ENCHANTMENT_OF_FORCE = 24,        // Increased Knockback
    ITEM_ENCHANTMENT_OF_POWER = 25,        // Add +5 Levels
    ITEM_ENCHANTMENT_OF_AIR_MAGIC = 26,    // Increases effect of all Air spells
    ITEM_ENCHANTMENT_OF_BODY_MAGIC = 27,   // Increases effect of all Body spells
    ITEM_ENCHANTMENT_OF_DARK_MAGIC = 28,   // Increases effect of all Dark spells
    ITEM_ENCHANTMENT_OF_EARTH_MAGIC = 29,  // Increases effect of all Earth spells
    ITEM_ENCHANTMENT_OF_FIRE_MAGIC = 30,   // Increases effect of all Fire spells
    ITEM_ENCHANTMENT_OF_LIGHT_MAGIC = 31,  // Increases effect of all Light spells
    ITEM_ENCHANTMENT_OF_MIND_MAGIC = 32,   // Increases effect of all Mind spells
    ITEM_ENCHANTMENT_OF_SPIRIT_MAGIC = 33, // Increases effect of all Spirit spells
    ITEM_ENCHANTMENT_OF_WATER_MAGIC = 34,  // Increases effect of all Water spells
    ITEM_ENCHANTMENT_OF_THIEVERY = 35,     // Increases chance of Disarming (double)
    ITEM_ENCHANTMENT_OF_SHIELDING = 36,    // Half damage from all missile attacks (not cumulative)
    ITEM_ENCHANTMENT_OF_REGENERATION = 37, // Regenerate HP over time
    ITEM_ENCHANTMENT_OF_MANA = 38,         // Regenerate SP over time
    ITEM_ENCHANTMENT_DEMON_SLAYING = 39,   // Double damage vs Demons.
    ITEM_ENCHANTMENT_DRAGON_SLAYING = 40,  // Double damage vs Dragons
    ITEM_ENCHANTMENT_OF_DARKNESS = 41,     // Vampiric and Swift
    ITEM_ENCHANTMENT_OF_DOOM = 42,         // +1 to Seven Stats, HP, SP, Armor, Resistances
    ITEM_ENCHANTMENT_OF_EARTH = 43,        // +10 to Endurance, Armor, HP
    ITEM_ENCHANTMENT_OF_LIFE = 44,         // +10 HP and Regenerate HP over time
    ITEM_ENCHANTMENT_ROGUES = 45,          // Adds +5 Speed and Accuracy.
    ITEM_ENCHANTMENT_OF_DRAGON = 46,       // Adds 10-20 points of fire damage and +25 Might
    ITEM_ENCHANTMENT_OF_ECLIPSE = 47,      // +10 SP and Regenerate SP over time
    ITEM_ENCHANTMENT_OF_GOLEM = 48,        // +15 Endurance and +5 Armor
    ITEM_ENCHANTMENT_OF_MOON = 49,         // +10 Intellect and Luck
    ITEM_ENCHANTMENT_OF_PHOENIX = 50,      // +30 Fire Resistance and Regenerate HP over time
    ITEM_ENCHANTMENT_OF_SKY = 51,          // +10 Spell points, Speed, Intellect
    ITEM_ENCHANTMENT_OF_STARS = 52,        // +10 Endurance and Accuracy
    ITEM_ENCHANTMENT_OF_SUN = 53,          // +10 Might and Personality
    ITEM_ENCHANTMENT_OF_TROLL = 54,        // +15 Endurance and Regenerate HP over time
    ITEM_ENCHANTMENT_OF_UNICORN = 55,      // +15 Luck and Regenerate SP over time
    ITEM_ENCHANTMENT_WARRIORS = 56,        // Adds +5 Might and Endurance
    ITEM_ENCHANTMENT_WIZARDS = 57,         // Adds +5 Intellect and Personality
    ITEM_ENCHANTMENT_ANTIQUE = 58,         // Increased value
    ITEM_ENCHANTMENT_SWIFT = 59,           // Swift, increased Weapon speed
    ITEM_ENCHANTMENT_MONKS = 60,           // Adds +3 Unarmed and Dodging skills
    ITEM_ENCHANTMENT_THIEVES = 61,         // Adds +3 Stealing and Disarm skills
    ITEM_ENCHANTMENT_OF_IDENTIFYING = 62,  // Adds +3 ID Item and ID Monster skills
    ITEM_ENCHANTMENT_ELF_SLAYING = 63,     // Double Damage vs Elves
    ITEM_ENCHANTMENT_UNDEAD_SLAYING = 64,  // Double Damage vs Undead
    ITEM_ENCHANTMENT_TITAN_SLAYING = 65,   // Double Damage vs Titans
    ITEM_ENCHANTMENT_OF_PLENTY = 66,       // Regenerate SP and HP over time
    ITEM_ENCHANTMENT_ASSASINS = 67,        // Adds 5 points of Body damage and +2 Disarm skill
    ITEM_ENCHANTMENT_BARBARIANS = 68,      // Adds 6-8 points of Cold damage and +5 Armor Class
    ITEM_ENCHANTMENT_OF_STORM = 69,        // +20 Air Resistance and Shielding
    ITEM_ENCHANTMENT_OF_OCEAN = 70,        // +10 Water Resistance and +2 Alchemy skill
    ITEM_ENCHANTMENT_OF_WATER_WALKING = 71, // Prevents damage from drowning
    ITEM_ENCHANTMENT_OF_FEATHER_FALLING = 72, // Prevents damage from falling

    ITEM_ENCHANTMENT_FIRST_VALID = 1,
    ITEM_ENCHANTMENT_LAST_VALID = 72
};
using enum ItemEnchantment;

enum class ItemRarity : uint8_t {
    RARITY_COMMON = 0,
    RARITY_ARTIFACT = 1, // Artifacts always give positive bonuses.
    RARITY_RELIC = 2,    // Relics can be more powerful than artifacts but carry a penalty (have a negative bonus).
    RARITY_SPECIAL = 3,  // Pretty much just weak artifacts, and often quest items. Not in the loot table, so can
                         // only be found where the level designers have put them.
};
using enum ItemRarity;

enum class ItemTreasureLevel : int8_t {
    ITEM_TREASURE_LEVEL_INVALID = 0,
    ITEM_TREASURE_LEVEL_1 = 1,
    ITEM_TREASURE_LEVEL_2 = 2,
    ITEM_TREASURE_LEVEL_3 = 3,
    ITEM_TREASURE_LEVEL_4 = 4,
    ITEM_TREASURE_LEVEL_5 = 5,
    ITEM_TREASURE_LEVEL_6 = 6, // 5% chance for an artifact.
    ITEM_TREASURE_LEVEL_7 = 7, // Guaranteed artifact.

    ITEM_TREASURE_LEVEL_FIRST_RANDOM = ITEM_TREASURE_LEVEL_1,
    ITEM_TREASURE_LEVEL_LAST_RANDOM = ITEM_TREASURE_LEVEL_6,
};
using enum ItemTreasureLevel;

inline bool isRandomTreasureLevel(ItemTreasureLevel level) {
    return level >= ITEM_TREASURE_LEVEL_FIRST_RANDOM && level <= ITEM_TREASURE_LEVEL_LAST_RANDOM;
}

/**
 * Enum of all item types in the game.
 *
 * DON'T EDIT, THIS IS AUTOGENERATED CODE.
 *
 * @see runItemIdCodeGen
 */
enum class ItemId : int32_t {
    ITEM_NULL = 0,
    ITEM_CRUDE_LONGSWORD = 1,
    ITEM_ELVEN_SABER = 2,
    ITEM_KEEN_LONGSWORD = 3,
    ITEM_GRACEFUL_SWORD = 4,
    ITEM_DUELIST_BLADE = 5,
    ITEM_TWO_HANDED_SWORD = 6,
    ITEM_GREAT_SWORD = 7,
    ITEM_HEROIC_SWORD = 8,
    ITEM_BROADSWORD = 9,
    ITEM_STEEL_BROADSWORD = 10,
    ITEM_CHAMPION_SWORD = 11,
    ITEM_CUTLASS = 12,
    ITEM_GOBLIN_CUTLASS = 13,
    ITEM_REGNAN_CUTLASS = 14,
    ITEM_DAGGER = 15,
    ITEM_DWARVEN_DAGGER = 16,
    ITEM_SHARKTOOTH_DAGGER = 17,
    ITEM_ASSASSINS_DAGGER = 18,
    ITEM_MAGE_DAGGER = 19,
    ITEM_LONG_DAGGER = 20,
    ITEM_ERATHIAN_LONG_DAGGER = 21,
    ITEM_EXQUISITE_LONG_DAGGER = 22,
    ITEM_CRUDE_AXE = 23,
    ITEM_BATTLE_AXE = 24,
    ITEM_DWARVEN_AXE = 25,
    ITEM_STEEL_AXE = 26,
    ITEM_MINOTAUR_AXE = 27,
    ITEM_POLEAXE = 28,
    ITEM_WARRIORS_POLEAXE = 29,
    ITEM_HEADSMANS_POLEAXE = 30,
    ITEM_CRUDE_SPEAR = 31,
    ITEM_SOLDIERS_SPEAR = 32,
    ITEM_ELVEN_SPEAR = 33,
    ITEM_CRUEL_SPEAR = 34,
    ITEM_SUBLIME_SPEAR = 35,
    ITEM_HALBERD = 36,
    ITEM_WEIGHTED_HALBERD = 37,
    ITEM_MIGHTY_HALBERD = 38,
    ITEM_TRIDENT = 39,
    ITEM_BARBED_TRIDENT = 40,
    ITEM_WAR_TRIDENT = 41,
    ITEM_CRUDE_BOW = 42,
    ITEM_LONGBOW = 43,
    ITEM_ELVEN_LONGBOW = 44,
    ITEM_COMPOSITE_BOW = 45,
    ITEM_GRIFFIN_BOW = 46,
    ITEM_CROSSBOW = 47,
    ITEM_HEAVY_CROSSBOW = 48,
    ITEM_IDEAL_CROSSBOW = 49,
    ITEM_MACE = 50,
    ITEM_SPIKED_MACE = 51,
    ITEM_ZEALOT_MACE = 52,
    ITEM_DWARVEN_MORNINGSTAR = 53,
    ITEM_SUPREME_FLAIL = 54,
    ITEM_HAMMER = 55,
    ITEM_WAR_HAMMER = 56,
    ITEM_DWARVEN_HAMMER = 57,
    ITEM_CLUB = 58,
    ITEM_SPIKED_CLUB = 59,
    ITEM_STEEL_CLUB = 60,
    ITEM_STAFF = 61,
    ITEM_IRON_CORE_STAFF = 62,
    ITEM_WIZARD_STAFF = 63,
    ITEM_BLASTER = 64,
    ITEM_BLASTER_RIFLE = 65,
    ITEM_LEATHER_ARMOR = 66,
    ITEM_STUDDED_LEATHER = 67,
    ITEM_OFFICERS_LEATHER = 68,
    ITEM_REGNAN_LEATHER = 69,
    ITEM_ROYAL_LEATHER = 70,
    ITEM_CHAIN_MAIL = 71,
    ITEM_STEEL_CHAIN_MAIL = 72,
    ITEM_FINE_CHAIN_MAIL = 73,
    ITEM_RESPLENDENT_CHAIN_MAIL = 74,
    ITEM_GOLDEN_CHAIN_MAIL = 75,
    ITEM_PLATE_ARMOR = 76,
    ITEM_SPLENDID_PLATE_ARMOR = 77,
    ITEM_NOBLE_PLATE_ARMOR = 78,
    ITEM_GOBLIN_SHIELD = 79,
    ITEM_WOODEN_SHIELD = 80,
    ITEM_HORSEMANS_SHIELD = 81,
    ITEM_STERLING_SHIELD = 82,
    ITEM_PHYNAXIAN_SHIELD = 83,
    ITEM_WOODEN_BUCKLER = 84,
    ITEM_BRONZE_SHIELD = 85,
    ITEM_METAL_SHIELD = 86,
    ITEM_ALLOYED_SHIELD = 87,
    ITEM_MAJESTIC_SHIELD = 88,
    ITEM_HORNED_HELM = 89,
    ITEM_CONSCRIPTS_HELM = 90,
    ITEM_FULL_HELM = 91,
    ITEM_PHYNAXIAN_HELM = 92,
    ITEM_MOGRED_HELM = 93,
    ITEM_PEASANT_HAT = 94,
    ITEM_TRAVELLERS_HAT = 95,
    ITEM_FANCY_HAT = 96,
    ITEM_CROWN = 97,
    ITEM_NOBLE_CROWN = 98,
    ITEM_REGAL_CROWN = 99,
    ITEM_LEATHER_BELT = 100,
    ITEM_FINE_BELT = 101,
    ITEM_STRONG_BELT = 102,
    ITEM_SILVER_BELT = 103,
    ITEM_GILDED_BELT = 104,
    ITEM_LEATHER_CLOAK = 105,
    ITEM_HUNTSMANS_CLOAK = 106,
    ITEM_RANGERS_CLOAK = 107,
    ITEM_ELEGANT_CLOAK = 108,
    ITEM_GLORIOUS_CLOAK = 109,
    ITEM_GAUNTLETS = 110,
    ITEM_STEEL_GAUNTLETS = 111,
    ITEM_SILVER_MESH_GAUNTLETS = 112,
    ITEM_DRAGON_HIDE_GAUNTLETS = 113,
    ITEM_MOGRED_GAUNTLETS = 114,
    ITEM_LEATHER_BOOTS = 115,
    ITEM_STEEL_PLATED_BOOTS = 116,
    ITEM_RANGER_BOOTS = 117,
    ITEM_KNIGHTS_BOOTS = 118,
    ITEM_PALADIN_BOOTS = 119,
    ITEM_BRASS_RING = 120,
    ITEM_PEARL_RING = 121,
    ITEM_PLATINUM_RING = 122,
    ITEM_EMERALD_RING = 123,
    ITEM_SAPPHIRE_RING = 124,
    ITEM_WARLOCKS_RING = 125,
    ITEM_ENCHANTED_RING = 126,
    ITEM_DAZZLING_RING = 127,
    ITEM_WIZARD_RING = 128,
    ITEM_ANGELS_RING = 129,
    ITEM_EYEBALL_AMULET = 130,
    ITEM_BRONZE_AMULET = 131,
    ITEM_WITCHS_AMULET = 132,
    ITEM_DEATHS_HEAD_PENDANT = 133,
    ITEM_SUN_AMULET = 134,
    ITEM_WAND_OF_FIRE = 135,
    ITEM_WAND_OF_SPARKS = 136,
    ITEM_WAND_OF_POISON = 137,
    ITEM_WAND_OF_STUNNING = 138,
    ITEM_WAND_OF_HARM = 139,
    ITEM_FAIRY_WAND_OF_LIGHT = 140,
    ITEM_FAIRY_WAND_OF_ICE = 141,
    ITEM_FAIRY_WAND_OF_LASHING = 142,
    ITEM_FAIRY_WAND_OF_MIND = 143,
    ITEM_FAIRY_WAND_OF_SWARMS = 144,
    ITEM_ALACORN_WAND_OF_FIREBALLS = 145,
    ITEM_ALACORN_WAND_OF_ACID = 146,
    ITEM_ALACORN_WAND_OF_LIGHTNING = 147,
    ITEM_ALACORN_WAND_OF_BLADES = 148,
    ITEM_ALACORN_WAND_OF_CHARMS = 149,
    ITEM_ARCANE_WAND_OF_BLASTING = 150,
    ITEM_ARCANE_WAND_OF_THE_FIST = 151,
    ITEM_ARCANE_WAND_OF_ROCKS = 152,
    ITEM_ARCANE_WAND_OF_PARALYZING = 153,
    ITEM_ARCANE_WAND_OF_CLOUDS = 154,
    ITEM_MYSTIC_WAND_OF_IMPLOSION = 155,
    ITEM_MYSTIC_WAND_OF_DISTORTION = 156,
    ITEM_MYSTIC_WAND_OF_SHRAPMETAL = 157,
    ITEM_MYSTIC_WAND_OF_SHRINKING = 158,
    ITEM_MYSTIC_WAND_OF_INCINERATION = 159,
    ITEM_160 = 160,                                  // Unused.
    ITEM_161 = 161,                                  // Unused.
    ITEM_162 = 162,                                  // Unused.
    ITEM_163 = 163,                                  // Unused.
    ITEM_164 = 164,                                  // Unused.
    ITEM_165 = 165,                                  // Unused.
    ITEM_166 = 166,                                  // Unused.
    ITEM_167 = 167,                                  // Unused.
    ITEM_168 = 168,                                  // Unused.
    ITEM_169 = 169,                                  // Unused.
    ITEM_170 = 170,                                  // Unused.
    ITEM_171 = 171,                                  // Unused.
    ITEM_172 = 172,                                  // Unused.
    ITEM_173 = 173,                                  // Unused.
    ITEM_174 = 174,                                  // Unused.
    ITEM_175 = 175,                                  // Unused.
    ITEM_176 = 176,                                  // Unused.
    ITEM_177 = 177,                                  // Unused.
    ITEM_178 = 178,                                  // Unused.
    ITEM_179 = 179,                                  // Unused.
    ITEM_180 = 180,                                  // Unused.
    ITEM_181 = 181,                                  // Unused.
    ITEM_182 = 182,                                  // Unused.
    ITEM_183 = 183,                                  // Unused.
    ITEM_184 = 184,                                  // Unused.
    ITEM_185 = 185,                                  // Unused.
    ITEM_GEM_BLUE_QUARTZ = 186,
    ITEM_GEM_TOPAZ = 187,
    ITEM_GEM_EMERALD = 188,
    ITEM_GEM_SAPPHIRE = 189,
    ITEM_GEM_GREEN_GARNET = 190,
    ITEM_GEM_ROSE_CRYSTAL = 191,
    ITEM_GEM_DIAMOND_1 = 192,
    ITEM_GEM_AMYTHEST = 193,
    ITEM_GEM_YELLOW_TOPAZ = 194,
    ITEM_GEM_DIAMOND_2 = 195,
    ITEM_GEM_RUBY = 196,
    ITEM_GOLD_SMALL = 197,
    ITEM_GOLD_MEDIUM = 198,
    ITEM_GOLD_LARGE = 199,
    ITEM_REAGENT_WIDOWSWEEP_BERRIES = 200,
    ITEM_REAGENT_CRUSHED_ROSE_PETALS = 201,
    ITEM_REAGENT_VIAL_OF_TROLL_BLOOD = 202,
    ITEM_REAGENT_RUBY = 203,
    ITEM_REAGENT_DRAGONS_EYE = 204,
    ITEM_REAGENT_PHIRNA_ROOT = 205,
    ITEM_REAGENT_METEORITE_FRAGMENT = 206,
    ITEM_REAGENT_HARPY_FEATHER = 207,
    ITEM_REAGENT_MOONSTONE = 208,
    ITEM_REAGENT_ELVISH_TOADSTOOL = 209,
    ITEM_REAGENT_POPPYSNAPS = 210,
    ITEM_REAGENT_FAE_DUST = 211,
    ITEM_REAGENT_SULFUR = 212,
    ITEM_REAGENT_GARNET = 213,
    ITEM_REAGENT_VIAL_OF_DEVIL_ICHOR = 214,
    ITEM_REAGENT_MUSHROOM = 215,
    ITEM_REAGENT_OBSIDIAN = 216,
    ITEM_REAGENT_VIAL_OF_OOZE_ENDOPLASM = 217,
    ITEM_REAGENT_MERCURY = 218,
    ITEM_REAGENT_PHILOSOPHERS_STONE = 219,
    ITEM_POTION_BOTTLE = 220,
    ITEM_POTION_CATALYST = 221,
    ITEM_POTION_CURE_WOUNDS = 222,
    ITEM_POTION_MAGIC = 223,
    ITEM_POTION_CURE_WEAKNESS = 224,
    ITEM_POTION_CURE_DISEASE = 225,
    ITEM_POTION_CURE_POISON = 226,
    ITEM_POTION_AWAKEN = 227,
    ITEM_POTION_HASTE = 228,
    ITEM_POTION_HEROISM = 229,
    ITEM_POTION_BLESS = 230,
    ITEM_POTION_PRESERVATION = 231,
    ITEM_POTION_SHIELD = 232,
    ITEM_POTION_RECHARGE_ITEM = 233,
    ITEM_POTION_STONESKIN = 234,
    ITEM_POTION_WATER_BREATHING = 235,
    ITEM_POTION_HARDEN_ITEM = 236,
    ITEM_POTION_REMOVE_FEAR = 237,
    ITEM_POTION_REMOVE_CURSE = 238,
    ITEM_POTION_CURE_INSANITY = 239,
    ITEM_POTION_MIGHT_BOOST = 240,
    ITEM_POTION_INTELLECT_BOOST = 241,
    ITEM_POTION_PERSONALITY_BOOST = 242,
    ITEM_POTION_ENDURANCE_BOOST = 243,
    ITEM_POTION_SPEED_BOOST = 244,
    ITEM_POTION_ACCURACY_BOOST = 245,
    ITEM_POTION_FLAMING = 246,
    ITEM_POTION_FREEZING = 247,
    ITEM_POTION_NOXIOUS = 248,
    ITEM_POTION_SHOCKING = 249,
    ITEM_POTION_SWIFT = 250,
    ITEM_POTION_CURE_PARALYSIS = 251,
    ITEM_POTION_DIVINE_RESTORATION = 252,
    ITEM_POTION_DIVINE_CURE = 253,
    ITEM_POTION_DIVINE_POWER = 254,
    ITEM_POTION_LUCK_BOOST = 255,
    ITEM_POTION_FIRE_RESISTANCE = 256,
    ITEM_POTION_AIR_RESISTANCE = 257,
    ITEM_POTION_WATER_RESISTANCE = 258,
    ITEM_POTION_EARTH_RESISTANCE = 259,
    ITEM_POTION_MIND_RESISTANCE = 260,
    ITEM_POTION_BODY_RESISTANCE = 261,
    ITEM_POTION_STONE_TO_FLESH = 262,
    ITEM_POTION_SLAYING = 263,
    ITEM_POTION_PURE_LUCK = 264,
    ITEM_POTION_PURE_SPEED = 265,
    ITEM_POTION_PURE_INTELLECT = 266,
    ITEM_POTION_PURE_ENDURANCE = 267,
    ITEM_POTION_PURE_PERSONALITY = 268,
    ITEM_POTION_PURE_ACCURACY = 269,
    ITEM_POTION_PURE_MIGHT = 270,
    ITEM_POTION_REJUVENATION = 271,
    ITEM_272 = 272,                                  // Unused.
    ITEM_273 = 273,                                  // Unused.
    ITEM_274 = 274,                                  // Unused.
    ITEM_275 = 275,                                  // Unused.
    ITEM_276 = 276,                                  // Unused.
    ITEM_277 = 277,                                  // Unused.
    ITEM_278 = 278,                                  // Unused.
    ITEM_279 = 279,                                  // Unused.
    ITEM_280 = 280,                                  // Unused.
    ITEM_281 = 281,                                  // Unused.
    ITEM_282 = 282,                                  // Unused.
    ITEM_283 = 283,                                  // Unused.
    ITEM_284 = 284,                                  // Unused.
    ITEM_285 = 285,                                  // Unused.
    ITEM_286 = 286,                                  // Unused.
    ITEM_287 = 287,                                  // Unused.
    ITEM_288 = 288,                                  // Unused.
    ITEM_289 = 289,                                  // Unused.
    ITEM_290 = 290,                                  // Unused.
    ITEM_291 = 291,                                  // Unused.
    ITEM_292 = 292,                                  // Unused.
    ITEM_293 = 293,                                  // Unused.
    ITEM_294 = 294,                                  // Unused.
    ITEM_295 = 295,                                  // Unused.
    ITEM_296 = 296,                                  // Unused.
    ITEM_297 = 297,                                  // Unused.
    ITEM_298 = 298,                                  // Unused.
    ITEM_299 = 299,                                  // Unused.
    ITEM_SCROLL_TORCH_LIGHT = 300,
    ITEM_SCROLL_FIRE_BOLT = 301,
    ITEM_SCROLL_FIRE_RESISTANCE = 302,
    ITEM_SCROLL_FIRE_AURA = 303,
    ITEM_SCROLL_HASTE = 304,
    ITEM_SCROLL_FIREBALL = 305,
    ITEM_SCROLL_FIRE_SPIKE = 306,
    ITEM_SCROLL_IMMOLATION = 307,
    ITEM_SCROLL_METEOR_SHOWER = 308,
    ITEM_SCROLL_INFERNO = 309,
    ITEM_SCROLL_INCINERATE = 310,
    ITEM_SCROLL_WIZARD_EYE = 311,
    ITEM_SCROLL_FEATHER_FALL = 312,
    ITEM_SCROLL_AIR_RESISTANCE = 313,
    ITEM_SCROLL_SPARKS = 314,
    ITEM_SCROLL_JUMP = 315,
    ITEM_SCROLL_SHIELD = 316,
    ITEM_SCROLL_LIGHTNING_BOLT = 317,
    ITEM_SCROLL_INVISIBILITY = 318,
    ITEM_SCROLL_IMPLOSION = 319,
    ITEM_SCROLL_FLY = 320,
    ITEM_SCROLL_STARBURST = 321,
    ITEM_SCROLL_AWAKEN = 322,
    ITEM_SCROLL_POISON_SPRAY = 323,
    ITEM_SCROLL_WATER_RESISTANCE = 324,
    ITEM_SCROLL_ICE_BOLT = 325,
    ITEM_SCROLL_WATER_WALK = 326,
    ITEM_SCROLL_RECHARGE_ITEM = 327,
    ITEM_SCROLL_ACID_BURST = 328,
    ITEM_SCROLL_ENCHANT_ITEM = 329,
    ITEM_SCROLL_TOWN_PORTAL = 330,
    ITEM_SCROLL_ICE_BLAST = 331,
    ITEM_SCROLL_LLOYDS_BEACON = 332,
    ITEM_SCROLL_STUN = 333,
    ITEM_SCROLL_SLOW = 334,
    ITEM_SCROLL_EARTH_RESISTANCE = 335,
    ITEM_SCROLL_DEADLY_SWARM = 336,
    ITEM_SCROLL_STONE_SKIN = 337,
    ITEM_SCROLL_BLADES = 338,
    ITEM_SCROLL_STONE_TO_FLESH = 339,
    ITEM_SCROLL_ROCK_BLAST = 340,
    ITEM_SCROLL_TELEKINESIS = 341,
    ITEM_SCROLL_DEATH_BLOSSOM = 342,
    ITEM_SCROLL_MASS_DISTORTION = 343,
    ITEM_SCROLL_DETECT_LIFE = 344,
    ITEM_SCROLL_BLESS = 345,
    ITEM_SCROLL_FATE = 346,
    ITEM_SCROLL_TURN_UNDEAD = 347,
    ITEM_SCROLL_REMOVE_CURSE = 348,
    ITEM_SCROLL_PRESERVATION = 349,
    ITEM_SCROLL_HEROISM = 350,
    ITEM_SCROLL_SPIRIT_LASH = 351,
    ITEM_SCROLL_RAISE_DEAD = 352,
    ITEM_SCROLL_SHARED_LIFE = 353,
    ITEM_SCROLL_RESURRECTION = 354,
    ITEM_SCROLL_REMOVE_FEAR = 355,
    ITEM_SCROLL_MIND_BLAST = 356,
    ITEM_SCROLL_MIND_RESISTANCE = 357,
    ITEM_SCROLL_TELEPATHY = 358,
    ITEM_SCROLL_CHARM = 359,
    ITEM_SCROLL_CURE_PARALYSIS = 360,
    ITEM_SCROLL_BERSERK = 361,
    ITEM_SCROLL_MASS_FEAR = 362,
    ITEM_SCROLL_CURE_INSANITY = 363,
    ITEM_SCROLL_PSYCHIC_SHOCK = 364,
    ITEM_SCROLL_ENSLAVE = 365,
    ITEM_SCROLL_CURE_WEAKNESS = 366,
    ITEM_SCROLL_HEAL = 367,
    ITEM_SCROLL_BODY_RESISTANCE = 368,
    ITEM_SCROLL_HARM = 369,
    ITEM_SCROLL_REGENERATION = 370,
    ITEM_SCROLL_CURE_POISON = 371,
    ITEM_SCROLL_HAMMERHANDS = 372,
    ITEM_SCROLL_CURE_DISEASE = 373,
    ITEM_SCROLL_PROTECTION_FROM_MAGIC = 374,
    ITEM_SCROLL_FLYING_FIST = 375,
    ITEM_SCROLL_POWER_CURE = 376,
    ITEM_SCROLL_LIGHT_BOLT = 377,
    ITEM_SCROLL_DESTROY_UNDEAD = 378,
    ITEM_SCROLL_DISPEL_MAGIC = 379,
    ITEM_SCROLL_PARALYZE = 380,
    ITEM_SCROLL_SUMMON_ELEMENTAL = 381,
    ITEM_SCROLL_DAY_OF_THE_GODS = 382,
    ITEM_SCROLL_PRISMATIC_LIGHT = 383,
    ITEM_SCROLL_DAY_OF_PROTECTION = 384,
    ITEM_SCROLL_HOUR_OF_POWER = 385,
    ITEM_SCROLL_SUNRAY = 386,
    ITEM_SCROLL_DIVINE_INTERVENTION = 387,
    ITEM_SCROLL_REANIMATE = 388,
    ITEM_SCROLL_TOXIC_CLOUD = 389,
    ITEM_SCROLL_VAMPIRIC_WEAPON = 390,
    ITEM_SCROLL_SHRINKING_RAY = 391,
    ITEM_SCROLL_SHRAPMETAL = 392,
    ITEM_SCROLL_CONTROL_UNDEAD = 393,
    ITEM_SCROLL_PAIN_REFLECTION = 394,
    ITEM_SCROLL_SACRIFICE = 395,
    ITEM_SCROLL_DRAGON_BREATH = 396,
    ITEM_SCROLL_ARMAGEDDON = 397,
    ITEM_SCROLL_SOULDRINKER = 398,
    ITEM_399 = 399,                                  // Unused.
    ITEM_SPELLBOOK_TORCH_LIGHT = 400,
    ITEM_SPELLBOOK_FIRE_BOLT = 401,
    ITEM_SPELLBOOK_FIRE_RESISTANCE = 402,
    ITEM_SPELLBOOK_FIRE_AURA = 403,
    ITEM_SPELLBOOK_HASTE = 404,
    ITEM_SPELLBOOK_FIREBALL = 405,
    ITEM_SPELLBOOK_FIRE_SPIKE = 406,
    ITEM_SPELLBOOK_IMMOLATION = 407,
    ITEM_SPELLBOOK_METEOR_SHOWER = 408,
    ITEM_SPELLBOOK_INFERNO = 409,
    ITEM_SPELLBOOK_INCINERATE = 410,
    ITEM_SPELLBOOK_WIZARD_EYE = 411,
    ITEM_SPELLBOOK_FEATHER_FALL = 412,
    ITEM_SPELLBOOK_AIR_RESISTANCE = 413,
    ITEM_SPELLBOOK_SPARKS = 414,
    ITEM_SPELLBOOK_JUMP = 415,
    ITEM_SPELLBOOK_SHIELD = 416,
    ITEM_SPELLBOOK_LIGHTNING_BOLT = 417,
    ITEM_SPELLBOOK_INVISIBILITY = 418,
    ITEM_SPELLBOOK_IMPLOSION = 419,
    ITEM_SPELLBOOK_FLY = 420,
    ITEM_SPELLBOOK_STARBURST = 421,
    ITEM_SPELLBOOK_AWAKEN = 422,
    ITEM_SPELLBOOK_POISON_SPRAY = 423,
    ITEM_SPELLBOOK_WATER_RESISTANCE = 424,
    ITEM_SPELLBOOK_ICE_BOLT = 425,
    ITEM_SPELLBOOK_WATER_WALK = 426,
    ITEM_SPELLBOOK_RECHARGE_ITEM = 427,
    ITEM_SPELLBOOK_ACID_BURST = 428,
    ITEM_SPELLBOOK_ENCHANT_ITEM = 429,
    ITEM_SPELLBOOK_TOWN_PORTAL = 430,
    ITEM_SPELLBOOK_ICE_BLAST = 431,
    ITEM_SPELLBOOK_LLOYDS_BEACON = 432,
    ITEM_SPELLBOOK_STUN = 433,
    ITEM_SPELLBOOK_SLOW = 434,
    ITEM_SPELLBOOK_EARTH_RESISTANCE = 435,
    ITEM_SPELLBOOK_DEADLY_SWARM = 436,
    ITEM_SPELLBOOK_STONE_SKIN = 437,
    ITEM_SPELLBOOK_BLADES = 438,
    ITEM_SPELLBOOK_STONE_TO_FLESH = 439,
    ITEM_SPELLBOOK_ROCK_BLAST = 440,
    ITEM_SPELLBOOK_TELEKINESIS = 441,
    ITEM_SPELLBOOK_DEATH_BLOSSOM = 442,
    ITEM_SPELLBOOK_MASS_DISTORTION = 443,
    ITEM_SPELLBOOK_DETECT_LIFE = 444,
    ITEM_SPELLBOOK_BLESS = 445,
    ITEM_SPELLBOOK_FATE = 446,
    ITEM_SPELLBOOK_TURN_UNDEAD = 447,
    ITEM_SPELLBOOK_REMOVE_CURSE = 448,
    ITEM_SPELLBOOK_PRESERVATION = 449,
    ITEM_SPELLBOOK_HEROISM = 450,
    ITEM_SPELLBOOK_SPIRIT_LASH = 451,
    ITEM_SPELLBOOK_RAISE_DEAD = 452,
    ITEM_SPELLBOOK_SHARED_LIFE = 453,
    ITEM_SPELLBOOK_RESURRECTION = 454,
    ITEM_SPELLBOOK_REMOVE_FEAR = 455,
    ITEM_SPELLBOOK_MIND_BLAST = 456,
    ITEM_SPELLBOOK_MIND_RESISTANCE = 457,
    ITEM_SPELLBOOK_TELEPATHY = 458,
    ITEM_SPELLBOOK_CHARM = 459,
    ITEM_SPELLBOOK_CURE_PARALYSIS = 460,
    ITEM_SPELLBOOK_BERSERK = 461,
    ITEM_SPELLBOOK_MASS_FEAR = 462,
    ITEM_SPELLBOOK_CURE_INSANITY = 463,
    ITEM_SPELLBOOK_PSYCHIC_SHOCK = 464,
    ITEM_SPELLBOOK_ENSLAVE = 465,
    ITEM_SPELLBOOK_CURE_WEAKNESS = 466,
    ITEM_SPELLBOOK_HEAL = 467,
    ITEM_SPELLBOOK_BODY_RESISTANCE = 468,
    ITEM_SPELLBOOK_HARM = 469,
    ITEM_SPELLBOOK_REGENERATION = 470,
    ITEM_SPELLBOOK_CURE_POISON = 471,
    ITEM_SPELLBOOK_HAMMERHANDS = 472,
    ITEM_SPELLBOOK_CURE_DISEASE = 473,
    ITEM_SPELLBOOK_PROTECTION_FROM_MAGIC = 474,
    ITEM_SPELLBOOK_FLYING_FIST = 475,
    ITEM_SPELLBOOK_POWER_CURE = 476,
    ITEM_SPELLBOOK_LIGHT_BOLT = 477,
    ITEM_SPELLBOOK_DESTROY_UNDEAD = 478,
    ITEM_SPELLBOOK_DISPEL_MAGIC = 479,
    ITEM_SPELLBOOK_PARALYZE = 480,
    ITEM_SPELLBOOK_SUMMON_ELEMENTAL = 481,
    ITEM_SPELLBOOK_DAY_OF_THE_GODS = 482,
    ITEM_SPELLBOOK_PRISMATIC_LIGHT = 483,
    ITEM_SPELLBOOK_DAY_OF_PROTECTION = 484,
    ITEM_SPELLBOOK_HOUR_OF_POWER = 485,
    ITEM_SPELLBOOK_SUNRAY = 486,
    ITEM_SPELLBOOK_DIVINE_INTERVENTION = 487,
    ITEM_SPELLBOOK_REANIMATE = 488,
    ITEM_SPELLBOOK_TOXIC_CLOUD = 489,
    ITEM_SPELLBOOK_VAMPIRIC_WEAPON = 490,
    ITEM_SPELLBOOK_SHRINKING_RAY = 491,
    ITEM_SPELLBOOK_SHRAPMETAL = 492,
    ITEM_SPELLBOOK_CONTROL_UNDEAD = 493,
    ITEM_SPELLBOOK_PAIN_REFLECTION = 494,
    ITEM_SPELLBOOK_SACRIFICE = 495,
    ITEM_SPELLBOOK_DRAGON_BREATH = 496,
    ITEM_SPELLBOOK_ARMAGEDDON = 497,
    ITEM_SPELLBOOK_SOULDRINKER = 498,
    ITEM_499 = 499,                                  // Unused.
    ITEM_ARTIFACT_PUCK = 500,
    ITEM_ARTIFACT_IRON_FEATHER = 501,
    ITEM_ARTIFACT_WALLACE = 502,
    ITEM_ARTIFACT_CORSAIR = 503,
    ITEM_ARTIFACT_GOVERNORS_ARMOR = 504,
    ITEM_ARTIFACT_YORUBA = 505,
    ITEM_ARTIFACT_SPLITTER = 506,
    ITEM_ARTIFACT_GHOULSBANE = 507,
    ITEM_ARTIFACT_GIBBET = 508,
    ITEM_ARTIFACT_CHARELE = 509,
    ITEM_ARTIFACT_ULLYSES = 510,
    ITEM_ARTIFACT_HANDS_OF_THE_MASTER = 511,
    ITEM_ARTIFACT_SEVEN_LEAGUE_BOOTS = 512,
    ITEM_ARTIFACT_RULERS_RING = 513,
    ITEM_RELIC_MASH = 514,
    ITEM_RELIC_ETHRICS_STAFF = 515,
    ITEM_RELIC_HARECKS_LEATHER = 516,
    ITEM_RELIC_OLD_NICK = 517,
    ITEM_RELIC_AMUCK = 518,
    ITEM_RELIC_GLORY_SHIELD = 519,
    ITEM_RELIC_KELEBRIM = 520,
    ITEM_RELIC_TALEDONS_HELM = 521,
    ITEM_RELIC_SCHOLARS_CAP = 522,
    ITEM_RELIC_PHYNAXIAN_CROWN = 523,
    ITEM_RELIC_TITANS_BELT = 524,
    ITEM_RELIC_TWILIGHT = 525,
    ITEM_RELIC_ANIA_SELVING = 526,
    ITEM_RELIC_JUSTICE = 527,
    ITEM_RELIC_MEKORIGS_HAMMER = 528,
    ITEM_ARTIFACT_HERMES_SANDALS = 529,
    ITEM_ARTIFACT_CLOAK_OF_THE_SHEEP = 530,
    ITEM_ARTIFACT_ELFBANE = 531,
    ITEM_ARTIFACT_MINDS_EYE = 532,
    ITEM_ARTIFACT_ELVEN_CHAINMAIL = 533,
    ITEM_ARTIFACT_FORGE_GAUNTLETS = 534,
    ITEM_ARTIFACT_HEROS_BELT = 535,
    ITEM_ARTIFACT_LADYS_ESCORT = 536,
    ITEM_SPECIAL_CLANKERS_AMULET = 537,
    ITEM_SPECIAL_LIEUTENANTS_CUTLASS = 538,
    ITEM_SPECIAL_MEDUSAS_MIRROR = 539,
    ITEM_SPECIAL_LADY_CARMINES_DAGGER = 540,
    ITEM_SPECIAL_VILLAINS_BLADE = 541,
    ITEM_SPECIAL_THE_PERFECT_BOW = 542,
    ITEM_SPECIAL_THE_PERFECT_BOW_FIXED = 543,
    ITEM_SPECIAL_SHADOWS_MASK = 544,
    ITEM_SPECIAL_GHOST_RING = 545,
    ITEM_SPECIAL_FAERIE_RING = 546,
    ITEM_SPECIAL_SUN_CLOAK = 547,
    ITEM_SPECIAL_MOON_CLOAK = 548,
    ITEM_SPECIAL_ZOKARRS_AXE = 549,
    ITEM_SPECIAL_VAMPIRES_CAPE = 550,
    ITEM_SPECIAL_MINOTAURS_AXE = 551,
    ITEM_SPECIAL_GROGNARDS_CUTLASS = 552,
    ITEM_553 = 553,                                  // Unused.
    ITEM_554 = 554,                                  // Unused.
    ITEM_555 = 555,                                  // Unused.
    ITEM_556 = 556,                                  // Unused.
    ITEM_557 = 557,                                  // Unused.
    ITEM_558 = 558,                                  // Unused.
    ITEM_559 = 559,                                  // Unused.
    ITEM_560 = 560,                                  // Unused.
    ITEM_561 = 561,                                  // Unused.
    ITEM_562 = 562,                                  // Unused.
    ITEM_563 = 563,                                  // Unused.
    ITEM_564 = 564,                                  // Unused.
    ITEM_565 = 565,                                  // Unused.
    ITEM_566 = 566,                                  // Unused.
    ITEM_567 = 567,                                  // Unused.
    ITEM_568 = 568,                                  // Unused.
    ITEM_569 = 569,                                  // Unused.
    ITEM_SPECIAL_THE_DEATHBLADE = 570,
    ITEM_571 = 571,                                  // Unused.
    ITEM_572 = 572,                                  // Unused.
    ITEM_573 = 573,                                  // Unused.
    ITEM_574 = 574,                                  // Unused.
    ITEM_575 = 575,                                  // Unused.
    ITEM_576 = 576,                                  // Unused.
    ITEM_577 = 577,                                  // Unused.
    ITEM_578 = 578,                                  // Unused.
    ITEM_579 = 579,                                  // Unused.
    ITEM_580 = 580,                                  // Unused.
    ITEM_581 = 581,                                  // Unused.
    ITEM_582 = 582,                                  // Unused.
    ITEM_583 = 583,                                  // Unused.
    ITEM_584 = 584,                                  // Unused.
    ITEM_585 = 585,                                  // Unused.
    ITEM_586 = 586,                                  // Unused.
    ITEM_587 = 587,                                  // Unused.
    ITEM_588 = 588,                                  // Unused.
    ITEM_589 = 589,                                  // Unused.
    ITEM_590 = 590,                                  // Unused.
    ITEM_591 = 591,                                  // Unused.
    ITEM_592 = 592,                                  // Unused.
    ITEM_593 = 593,                                  // Unused.
    ITEM_594 = 594,                                  // Unused.
    ITEM_595 = 595,                                  // Unused.
    ITEM_596 = 596,                                  // Unused.
    ITEM_597 = 597,                                  // Unused.
    ITEM_598 = 598,                                  // Unused.
    ITEM_599 = 599,                                  // Unused.
    ITEM_QUEST_HEART_OF_THE_WOOD = 600,
    ITEM_QUEST_LICH_JAR_FULL = 601,
    ITEM_QUEST_CASE_OF_SOUL_JARS = 602,
    ITEM_QUEST_PARSONS_QUILL = 603,
    ITEM_QUEST_WETSUIT = 604,
    ITEM_QUEST_OSCILLATION_OVERTHRUSTER = 605,
    ITEM_QUEST_SIGNET_RING = 606,
    ITEM_QUEST_LETTER_FROM_JOHANN_KERRID = 607,
    ITEM_608 = 608,                                  // Sealed Letter 2, unused.
    ITEM_609 = 609,                                  // Sealed Letter 3, unused.
    ITEM_610 = 610,                                  // Sealed Letter 4, unused.
    ITEM_611 = 611,                                  // Sealed Letter 5, unused.
    ITEM_612 = 612,                                  // Sealed Letter 6, unused.
    ITEM_613 = 613,                                  // Sealed Letter 7, unused.
    ITEM_QUEST_LETTER_FROM_NORBERT_THRUSH = 614,
    ITEM_QUEST_LICH_JAR_EMPTY = 615,
    ITEM_GENIE_LAMP = 616,
    ITEM_QUEST_KNIGHT_STATUETTE = 617,
    ITEM_QUEST_EAGLE_STATUETTE = 618,
    ITEM_QUEST_ANGEL_STATUETTE = 619,
    ITEM_BIG_TAPESTRY = 620,
    ITEM_QUEST_ANGEL_STATUE_PAINTING = 621,
    ITEM_QUEST_ARCHIBALD_IRONFIST_PAINTING = 622,
    ITEM_QUEST_ROLAND_IRONFIST_PAINTING = 623,
    ITEM_QUEST_VASE = 624,
    ITEM_FLOWER_ROSE = 625,
    ITEM_QUEST_ZOKARR_IVS_SKULL = 626,
    ITEM_THIGH_BONE = 627,
    ITEM_QUEST_HALDARS_REMAINS = 628,
    ITEM_QUEST_ELIXIR = 629,
    ITEM_RED_APPLE = 630,
    ITEM_QUEST_WEALTHY_HAT = 631,
    ITEM_QUEST_LUTE = 632,
    ITEM_QUEST_FAERIE_PIPES = 633,
    ITEM_QUEST_GRYPHONHEARTS_TRUMPET = 634,
    ITEM_QUEST_SEASHELL = 635,
    ITEM_QUEST_FLOOR_TILE_W_MOON_INSIGNIA = 636,
    ITEM_WINGED_SANDALS = 637,
    ITEM_QUEST_SEASONS_STOLE = 638,
    ITEM_QUEST_GOLEM_CHEST = 639,
    ITEM_QUEST_ABBEY_NORMAL_GOLEM_HEAD = 640,
    ITEM_QUEST_GOLEM_HEAD = 641,
    ITEM_QUEST_GOLEM_LEFT_LEG = 642,
    ITEM_QUEST_GOLEM_RIGHT_LEG = 643,
    ITEM_QUEST_GOLEM_RIGHT_ARM = 644,
    ITEM_QUEST_GOLEM_LEFT_ARM = 645,
    ITEM_HORSESHOE = 646,
    ITEM_QUEST_DRAGON_EGG = 647,
    ITEM_QUEST_LANTERN_OF_LIGHT = 648,
    ITEM_QUEST_WORN_BELT = 649,
    ITEM_TEMPLE_IN_A_BOTTLE = 650,
    ITEM_QUEST_ARCOMAGE_DECK = 651,
    ITEM_WEST_PILLAR_KEY = 652,
    ITEM_CENTRAL_PILLAR_KEY = 653,
    ITEM_EAST_PILLAR_KEY = 654,
    ITEM_BARROW_KEY_1 = 655,
    ITEM_BARROW_KEY_2 = 656,
    ITEM_BARROW_KEY_3 = 657,
    ITEM_QUEST_CONTESTANTS_SHIELD = 658,
    ITEM_WILLIAMS_TOWER_KEY = 659,
    ITEM_CATHERINES_KEY = 660,
    ITEM_COLONY_ZOD_KEY = 661,
    ITEM_FAERIE_KEY = 662,
    ITEM_SEWER_KEY = 663,
    ITEM_664 = 664,                                  // Key placeholder, unused.
    ITEM_665 = 665,                                  // Key placeholder, unused.
    ITEM_666 = 666,                                  // Key placeholder, unused.
    ITEM_667 = 667,                                  // Key placeholder, unused.
    ITEM_668 = 668,                                  // Key placeholder, unused.
    ITEM_669 = 669,                                  // Key placeholder, unused.
    ITEM_670 = 670,                                  // Key placeholder, unused.
    ITEM_QUEST_SNERGLES_AXE = 671,
    ITEM_QUEST_LORD_KILBURNS_SHIELD = 672,
    ITEM_673 = 673,                                  // Lich Jar Placeholder, unused.
    ITEM_674 = 674,                                  // Elixir Placeholder, unused.
    ITEM_QUEST_CONTROL_CUBE = 675,
    ITEM_QUEST_ALTAR_PIECE_1 = 676,
    ITEM_QUEST_ALTAR_PIECE_2 = 677,
    ITEM_678 = 678,                                  // Final Part Placeholder, unused.
    ITEM_679 = 679,                                  // Level Design Placeholder, unused.
    ITEM_680 = 680,                                  // Artifact Placeholder (Elf vs. Human), unused.
    ITEM_681 = 681,                                  // Riverstride Plans Placeholder, unused.
    ITEM_682 = 682,                                  // False Plans Placeholder, unused.
    ITEM_MESSAGE_MAP_TO_EVENMORN_ISLAND = 683,
    ITEM_684 = 684,                                  // Neutral Bow Placeholder, unused.
    ITEM_685 = 685,                                  // Elf/Human Artifact Placeholder, unused.
    ITEM_IRON_LACED_ORE = 686,
    ITEM_SIERTAL_LACED_ORE = 687,
    ITEM_PHYLT_LACED_ORE = 688,
    ITEM_KERGAR_LACED_ORE = 689,
    ITEM_ERUDINE_LACED_ORE = 690,
    ITEM_STALT_LACED_ORE = 691,
    ITEM_CRATE_OF_ARROWHEADS = 692,
    ITEM_CRATE_OF_GRIFFIN_FEATHERS = 693,
    ITEM_CRATE_OF_TULAREAN_WOOD = 694,
    ITEM_CRATE_OF_SAND = 695,
    ITEM_CRATE_OF_GLASS_BOTTLES = 696,
    ITEM_CRATE_OF_ENROTHIAN_WINE = 697,
    ITEM_698 = 698,                                  // Orders from Snergle, unused remnant from MM6.
    ITEM_699 = 699,                                  // Empty scroll placeholder, unused.
    ITEM_MESSAGE_FROM_ERATHIA = 700,
    ITEM_MESSAGE_CIPHER = 701,
    ITEM_MESSAGE_SCROLL_OF_WAVES = 702,
    ITEM_MESSAGE_BASIC_CRYPTOGRAPHY = 703,
    ITEM_MESSAGE_FROM_MR_STANTLEY = 704,
    ITEM_MESSAGE_RIVERSTRIDE_PLANS = 705,
    ITEM_MESSAGE_FALSE_RIVERSTRIDE_PLANS = 706,
    ITEM_MESSAGE_FRAGMENT_OF_SOLDIERS_DIARY = 707,
    ITEM_MESSAGE_LETTER_FROM_MR_STANTLEY_1 = 708,
    ITEM_MESSAGE_TORN_PAGE = 709,
    ITEM_MESSAGE_REMAINS_OF_A_JOURNAL = 710,
    ITEM_MESSAGE_JOURNAL_EXCERPT = 711,
    ITEM_MESSAGE_LETTER_FROM_ARCHIBALD = 712,
    ITEM_MESSAGE_LETTER_FROM_MALWICK = 713,
    ITEM_MESSAGE_LETTER_FROM_GAVIN_MAGNUS = 714,
    ITEM_MESSAGE_JOURNAL_FRAGMENT = 715,
    ITEM_MESSAGE_LETTER_TO_HAIRBAUGH = 716,
    ITEM_MESSAGE_LETTER_FROM_MR_STANTLEY_2 = 717,
    ITEM_MESSAGE_JOURNAL_ENTRY_23RD_APRIL = 718,
    ITEM_MESSAGE_JOURNAL_ENTRY_30TH_JUNE = 719,
    ITEM_MESSAGE_EXCERPT_FROM_A_DIARY = 720,
    ITEM_MESSAGE_LETTER = 721,
    ITEM_MESSAGE_JOURNAL_ENTRY_11TH_DECEMBER = 722,
    ITEM_MESSAGE_ORDERS_FROM_STEADWICK = 723,
    ITEM_MESSAGE_JOURNAL_ENTRY_2ND_JANUARY = 724,
    ITEM_MESSAGE_JOURNAL_ENTRY_19TH_SEPTEMBER = 725,
    ITEM_MESSAGE_JOURNAL_ENTRY = 726,
    ITEM_727 = 727,                                  // Empty scroll placeholder, unused.
    ITEM_MESSAGE_BILL_OF_SALE = 728,
    ITEM_729 = 729,                                  // Empty scroll placeholder, unused.
    ITEM_730 = 730,                                  // Empty scroll placeholder, unused.
    ITEM_731 = 731,                                  // Empty scroll placeholder, unused.
    ITEM_732 = 732,                                  // Empty scroll placeholder, unused.
    ITEM_733 = 733,                                  // Empty scroll placeholder, unused.
    ITEM_MESSAGE_LETTER_FROM_XENOFEX = 734,
    ITEM_735 = 735,                                  // Empty scroll placeholder, unused.
    ITEM_736 = 736,                                  // Empty scroll placeholder, unused.
    ITEM_737 = 737,                                  // Empty scroll placeholder, unused.
    ITEM_738 = 738,                                  // Empty scroll placeholder, unused.
    ITEM_739 = 739,                                  // Empty scroll placeholder, unused.
    ITEM_RECIPE_REJUVENATION = 740,
    ITEM_RECIPE_PURE_MIGHT = 741,
    ITEM_RECIPE_PURE_ACCURACY = 742,
    ITEM_RECIPE_PURE_PERSONALITY = 743,
    ITEM_RECIPE_PURE_ENDURANCE = 744,
    ITEM_RECIPE_PURE_INTELLECT = 745,
    ITEM_RECIPE_PURE_SPEED = 746,
    ITEM_RECIPE_PURE_LUCK = 747,
    ITEM_RECIPE_SLAYING_POTION = 748,
    ITEM_RECIPE_STONE_TO_FLESH = 749,
    ITEM_RECIPE_MIGHT_BOOST = 750,
    ITEM_RECIPE_INTELLECT_BOOST = 751,
    ITEM_RECIPE_PERSONALITY_BOOST = 752,
    ITEM_RECIPE_ENDURANCE_BOOST = 753,
    ITEM_RECIPE_SPEED_BOOST = 754,
    ITEM_RECIPE_ACCURACY_BOOST = 755,
    ITEM_RECIPE_FLAMING_POTION = 756,
    ITEM_RECIPE_FREEZING_POTION = 757,
    ITEM_RECIPE_NOXIOUS_POTION = 758,
    ITEM_RECIPE_SHOCKING_POTION = 759,
    ITEM_RECIPE_SWIFT_POTION = 760,
    ITEM_RECIPE_CURE_PARALYSIS = 761,
    ITEM_RECIPE_DIVINE_RESTORATION = 762,
    ITEM_RECIPE_DIVINE_CURE = 763,
    ITEM_RECIPE_DIVINE_POWER = 764,
    ITEM_RECIPE_LUCK_BOOST = 765,
    ITEM_RECIPE_FIRE_RESISTANCE = 766,
    ITEM_RECIPE_AIR_RESISTANCE = 767,
    ITEM_RECIPE_WATER_RESISTANCE = 768,
    ITEM_RECIPE_EARTH_RESISTANCE = 769,
    ITEM_RECIPE_MIND_RESISTANCE = 770,
    ITEM_RECIPE_BODY_RESISTANCE = 771,
    ITEM_772 = 772,                                  // Empty scroll placeholder, unused.
    ITEM_773 = 773,                                  // Empty scroll placeholder, unused.
    ITEM_774 = 774,                                  // Empty scroll placeholder, unused.
    ITEM_775 = 775,                                  // Empty scroll placeholder, unused.
    ITEM_776 = 776,                                  // Empty scroll placeholder, unused.
    ITEM_777 = 777,                                  // Empty scroll placeholder, unused.
    ITEM_778 = 778,                                  // Empty scroll placeholder, unused.
    ITEM_779 = 779,                                  // Empty scroll placeholder, unused.
    ITEM_780 = 780,                                  // Empty scroll placeholder, unused.
    ITEM_781 = 781,                                  // Unused.
    ITEM_782 = 782,                                  // Unused.
    ITEM_783 = 783,                                  // Unused.
    ITEM_784 = 784,                                  // Unused.
    ITEM_785 = 785,                                  // Unused.
    ITEM_786 = 786,                                  // Unused.
    ITEM_787 = 787,                                  // Unused.
    ITEM_788 = 788,                                  // Unused.
    ITEM_789 = 789,                                  // Unused.
    ITEM_790 = 790,                                  // Unused.
    ITEM_791 = 791,                                  // Unused.
    ITEM_792 = 792,                                  // Unused.
    ITEM_793 = 793,                                  // Unused.
    ITEM_794 = 794,                                  // Unused.
    ITEM_795 = 795,                                  // Unused.
    ITEM_796 = 796,                                  // Unused.
    ITEM_797 = 797,                                  // Unused.
    ITEM_798 = 798,                                  // Unused.
    ITEM_799 = 799,                                  // Unused.

    // These are used in chests and are replaced with normal random-generated items in GenerateItemsInChest().
    ITEM_RANDOM_LEVEL_1 = -1,
    ITEM_RANDOM_LEVEL_2 = -2,
    ITEM_RANDOM_LEVEL_3 = -3,
    ITEM_RANDOM_LEVEL_4 = -4,
    ITEM_RANDOM_LEVEL_5 = -5,
    ITEM_RANDOM_LEVEL_6 = -6,
    ITEM_RANDOM_LEVEL_7 = -7,

    ITEM_FIRST_RANDOM = ITEM_RANDOM_LEVEL_7,
    ITEM_LAST_RANDOM = ITEM_RANDOM_LEVEL_1,

    ITEM_FIRST_VALID = ITEM_CRUDE_LONGSWORD,
    ITEM_LAST_VALID = ITEM_799,

    ITEM_FIRST_REGULAR = ITEM_CRUDE_LONGSWORD,
    ITEM_LAST_REGULAR = ITEM_SUN_AMULET,

    ITEM_FIRST_ARTIFACT = ITEM_ARTIFACT_PUCK,
    ITEM_LAST_ARTIFACT = ITEM_SPECIAL_GROGNARDS_CUTLASS,

    ITEM_FIRST_SPAWNABLE_ARTIFACT = ITEM_ARTIFACT_PUCK,
    ITEM_LAST_SPAWNABLE_ARTIFACT = ITEM_RELIC_MEKORIGS_HAMMER,

    ITEM_FIRST_MESSAGE_SCROLL = ITEM_MESSAGE_FROM_ERATHIA,
    ITEM_LAST_MESSAGE_SCROLL = ITEM_781,

    ITEM_FIRST_RECIPE = ITEM_RECIPE_REJUVENATION,
    ITEM_LAST_RECIPE = ITEM_RECIPE_BODY_RESISTANCE,

    ITEM_FIRST_QUEST = ITEM_QUEST_HEART_OF_THE_WOOD,
    ITEM_LAST_QUEST = ITEM_699,

    ITEM_FIRST_REAGENT = ITEM_REAGENT_WIDOWSWEEP_BERRIES,
    ITEM_LAST_REAGENT = ITEM_REAGENT_PHILOSOPHERS_STONE,

    ITEM_FIRST_REAL_POTION = ITEM_POTION_CURE_WOUNDS,
    ITEM_LAST_REAL_POTION = ITEM_POTION_REJUVENATION,

    // TODO(captainurist): ITEM_POTION_BOTTLE equip type is ITEM_TYPE_POTION, but we don't have an empty bottle in the range below. Not good.
    ITEM_FIRST_POTION = ITEM_POTION_CATALYST,
    ITEM_LAST_POTION = ITEM_POTION_REJUVENATION,

    ITEM_FIRST_WAND = ITEM_WAND_OF_FIRE,
    ITEM_LAST_WAND = ITEM_MYSTIC_WAND_OF_INCINERATION,

    ITEM_FIRST_SPELL_SCROLL = ITEM_SCROLL_TORCH_LIGHT,
    ITEM_LAST_SPELL_SCROLL = ITEM_SCROLL_SOULDRINKER,

    ITEM_FIRST_SPELLBOOK = ITEM_SPELLBOOK_TORCH_LIGHT,
    ITEM_LAST_SPELLBOOK = ITEM_SPELLBOOK_SOULDRINKER,

    ITEM_FIRST_SPAWNABLE = ITEM_CRUDE_LONGSWORD,
    ITEM_LAST_SPAWNABLE = ITEM_499,

    ITEM_FIRST_GOLD = ITEM_GOLD_SMALL,
    ITEM_LAST_GOLD = ITEM_GOLD_LARGE,
};
using enum ItemId;

namespace detail {
extern const IndexedArray<SpellId, ITEM_FIRST_WAND, ITEM_LAST_WAND> spellForWand;
extern const IndexedArray<SpellId, ITEM_FIRST_SPELL_SCROLL, ITEM_LAST_SPELL_SCROLL> spellForScroll;
extern const IndexedArray<SpellId, ITEM_FIRST_SPELLBOOK, ITEM_LAST_SPELLBOOK> spellForSpellbook;
} // namespace detail

/**
 * Checks if item is a regular item - a weapon or equipment that's not a quest item or an artifact.
 *
 * Regular items can be enchanted, unlike other types of items.
 *
 * @param type                          Item type to check.
 * @return                              Whether the provided item is a regular item.
 */
inline bool isRegular(ItemId type) {
    return type >= ITEM_FIRST_REGULAR && type <= ITEM_LAST_REGULAR;
}

inline bool isRecipe(ItemId type) {
    return type >= ITEM_FIRST_RECIPE && type <= ITEM_LAST_RECIPE;
}

inline bool isWand(ItemId type) {
    return type >= ITEM_FIRST_WAND && type <= ITEM_LAST_WAND;
}

inline bool isPotion(ItemId type) {
    return type >= ITEM_FIRST_POTION && type <= ITEM_LAST_POTION;
}

inline bool isReagent(ItemId type) {
    return type >= ITEM_FIRST_REAGENT && type <= ITEM_LAST_REAGENT;
}

inline bool isEnchantingPotion(ItemId type) {
    return type >= ITEM_POTION_FLAMING && type <= ITEM_POTION_SWIFT || type == ITEM_POTION_SLAYING;
}

inline bool isMessageScroll(ItemId type) {
    return type >= ITEM_FIRST_MESSAGE_SCROLL && type <= ITEM_LAST_MESSAGE_SCROLL;
}

inline bool isArtifact(ItemId type) {
    return type >= ITEM_FIRST_ARTIFACT && type <= ITEM_LAST_ARTIFACT;
}

inline bool isSpawnableArtifact(ItemId type) {
    return type >= ITEM_FIRST_SPAWNABLE_ARTIFACT && type <= ITEM_LAST_SPAWNABLE_ARTIFACT;
}

inline bool isGold(ItemId type) {
    return type >= ITEM_FIRST_GOLD && type <= ITEM_LAST_GOLD;
}

inline bool isRandomItem(ItemId type) {
    return type >= ITEM_FIRST_RANDOM && type <= ITEM_LAST_RANDOM;
}

inline bool isSpellbook(ItemId item) {
    return item >= ITEM_FIRST_SPELLBOOK && item <= ITEM_LAST_SPELLBOOK;
}

inline bool isQuestItem(ItemId item) {
    return item >= ITEM_FIRST_QUEST && item <= ITEM_LAST_QUEST;
}

inline ItemTreasureLevel randomItemTreasureLevel(ItemId type) {
    assert(isRandomItem(type));
    return ItemTreasureLevel(-std::to_underlying(type));
}

inline int spellCountForMastery(CharacterSkillMastery maxMastery) {
    switch(maxMastery) {
      case CHARACTER_SKILL_MASTERY_NOVICE:
        return 4;
      case CHARACTER_SKILL_MASTERY_EXPERT:
        return 7;
      case CHARACTER_SKILL_MASTERY_MASTER:
        return 10;
      case CHARACTER_SKILL_MASTERY_GRANDMASTER:
        return 11;
      default:
        assert(false);
        return 0;
    }
}

inline Segment<ItemId> spellbooksForSchool(MagicSchool school, CharacterSkillMastery maxMastery = CHARACTER_SKILL_MASTERY_GRANDMASTER) {
    int spellSchoolSequential = std::to_underlying(school);
    int firstSpell = std::to_underlying(ITEM_FIRST_SPELLBOOK);
    int numSpells = spellCountForMastery(maxMastery);
    int firstSpellInSchool = firstSpell + 11 * spellSchoolSequential;
    int lastSpellInSchool = firstSpellInSchool + numSpells - 1;
    return {static_cast<ItemId>(firstSpellInSchool), static_cast<ItemId>(lastSpellInSchool)};
}

inline Segment<ItemId> allRecipeScrolls() {
    return {ITEM_FIRST_RECIPE, ITEM_LAST_RECIPE};
}

/**
 * @return                              Range of all items that can be randomly generated as loot. Note that not all
 *                                      of the entries might actually be valid.
 */
inline Segment<ItemId> allSpawnableItems() {
    return {ITEM_FIRST_SPAWNABLE, ITEM_LAST_SPAWNABLE};
}

/**
 * @return                              Range of all artifacts and relics that can be randomly generated as loot
 *                                      (e.g. picked up from a dragon corpse). Note that not all artifacts can be
 *                                      generated this way, e.g. Hermes' Sandals can only be picked up from a
 *                                      Mega Dragon's corpse.
 */
inline Segment<ItemId> allSpawnableArtifacts() {
    return {ITEM_FIRST_SPAWNABLE_ARTIFACT, ITEM_LAST_SPAWNABLE_ARTIFACT};
}

/**
 * @return                              List of lowest level (power=1) alchemical reagents.
 */
inline std::initializer_list<ItemId> allLevel1Reagents() {
    static constexpr std::initializer_list<ItemId> result = {
        ITEM_REAGENT_WIDOWSWEEP_BERRIES,
        ITEM_REAGENT_PHIRNA_ROOT,
        ITEM_REAGENT_POPPYSNAPS
    };
    return result;
}

inline ItemEnchantment potionEnchantment(ItemId enchantingPotion) {
    assert(isEnchantingPotion(enchantingPotion));

    switch (enchantingPotion) {
    case ITEM_POTION_SLAYING: return ITEM_ENCHANTMENT_DRAGON_SLAYING;
    case ITEM_POTION_FLAMING: return ITEM_ENCHANTMENT_OF_FLAME;
    case ITEM_POTION_FREEZING: return ITEM_ENCHANTMENT_OF_FROST;
    case ITEM_POTION_NOXIOUS: return ITEM_ENCHANTMENT_OF_POISON;
    case ITEM_POTION_SHOCKING: return ITEM_ENCHANTMENT_OF_SPARKS;
    case ITEM_POTION_SWIFT: return ITEM_ENCHANTMENT_SWIFT;
    default:
        assert(false);
        return ITEM_ENCHANTMENT_NULL;
    }
}

inline SpellId spellForSpellbook(ItemId spellbook) {
    return detail::spellForSpellbook[spellbook];
}

inline SpellId spellForScroll(ItemId scroll) {
    return detail::spellForScroll[scroll];
}

inline SpellId spellForWand(ItemId wand) {
    return detail::spellForWand[wand];
}

enum class ItemType : uint8_t {
    ITEM_TYPE_SINGLE_HANDED = 0,
    ITEM_TYPE_TWO_HANDED = 1,
    ITEM_TYPE_BOW = 2,
    ITEM_TYPE_ARMOUR = 3,
    ITEM_TYPE_SHIELD = 4,
    ITEM_TYPE_HELMET = 5,
    ITEM_TYPE_BELT = 6,
    ITEM_TYPE_CLOAK = 7,
    ITEM_TYPE_GAUNTLETS = 8,
    ITEM_TYPE_BOOTS = 9,
    ITEM_TYPE_RING = 10,
    ITEM_TYPE_AMULET = 11,
    ITEM_TYPE_WAND = 12,
    ITEM_TYPE_REAGENT = 13,
    ITEM_TYPE_POTION = 14,
    ITEM_TYPE_SPELL_SCROLL = 15,
    ITEM_TYPE_BOOK = 16,
    ITEM_TYPE_MESSAGE_SCROLL = 17,
    ITEM_TYPE_GOLD = 18,
    ITEM_TYPE_GEM = 19,
    ITEM_TYPE_NONE = 20, // Ores, quest items.

    ITEM_TYPE_FIRST = ITEM_TYPE_SINGLE_HANDED,
    ITEM_TYPE_LAST = ITEM_TYPE_NONE,

    ITEM_TYPE_FIRST_SPECIAL_ENCHANTABLE = ITEM_TYPE_SINGLE_HANDED,
    ITEM_TYPE_LAST_SPECIAL_ENCHANTABLE = ITEM_TYPE_AMULET,

    ITEM_TYPE_FIRST_NORMAL_ENCHANTABLE = ITEM_TYPE_ARMOUR,
    ITEM_TYPE_LAST_NORMAL_ENCHANTABLE = ITEM_TYPE_AMULET,
};
using enum ItemType;

/**
 * @param type                          Type to check.
 * @return                              Whether the provided type represents a `passive` equipment, e.g. shields,
 *                                      armor, rings, amulets, etc.
 */
inline bool isPassiveEquipment(ItemType type) {
    return type >= ITEM_TYPE_ARMOUR && type <= ITEM_TYPE_AMULET;
}

/**
 * @param type                          Type to check.
 * @return                              Whether the provided type represents wearable armor, e.g. any passive
 *                                      equipment except amulets and rings.
 */
inline bool isArmor(ItemType type) {
    return type >= ITEM_TYPE_ARMOUR && type <= ITEM_TYPE_BOOTS;
}

/**
 * @param type                          Type to check.
 * @return                              Whether the provided type represents a weapon. Note that wands are not
 *                                      considered weapons.
 */
inline bool isWeapon(ItemType type) {
    return type >= ITEM_TYPE_SINGLE_HANDED && type <= ITEM_TYPE_BOW;
}

/**
 * Slot on the paperdoll that the item can be equipped into.
 */
enum class ItemSlot : uint8_t {
    ITEM_SLOT_INVALID = 0,

    ITEM_SLOT_OFF_HAND = 1,
    ITEM_SLOT_MAIN_HAND = 2,
    ITEM_SLOT_BOW = 3,
    ITEM_SLOT_ARMOUR = 4,
    ITEM_SLOT_HELMET = 5,
    ITEM_SLOT_BELT = 6,
    ITEM_SLOT_CLOAK = 7,
    ITEM_SLOT_GAUTNLETS = 8,
    ITEM_SLOT_BOOTS = 9,
    ITEM_SLOT_AMULET = 10,
    ITEM_SLOT_RING1 = 11,
    ITEM_SLOT_RING2 = 12,
    ITEM_SLOT_RING3 = 13,
    ITEM_SLOT_RING4 = 14,
    ITEM_SLOT_RING5 = 15,
    ITEM_SLOT_RING6 = 16,

    ITEM_SLOT_ANY = 17,

    ITEM_SLOT_FIRST_VALID = ITEM_SLOT_OFF_HAND,
    ITEM_SLOT_LAST_VALID = ITEM_SLOT_RING6,
};
using enum ItemSlot;

inline Segment<ItemSlot> allRingSlots() {
    return {ITEM_SLOT_RING1, ITEM_SLOT_RING6};
}

inline ItemSlot ringSlot(int index) {
    assert(index >= 0 && index <= 5);
    return static_cast<ItemSlot>(std::to_underlying(ITEM_SLOT_RING1) + index);
}

inline Segment<ItemSlot> allItemSlots() {
    return {ITEM_SLOT_FIRST_VALID, ITEM_SLOT_LAST_VALID};
}

/**
 * Item types used in random item creation code.
 *
 * @see https://github.com/GrayFace/MMExtension/blob/4d6600f164315f38157591d7f0307a86594c22ef/Scripts/Core/ConstAndBits.lua#L592
 */
enum class RandomItemType {
    RANDOM_ITEM_ANY = 0,

    // TODO(captainurist): Values in 1-19 are ITEM_EQUIP_TYPE + 1, but those are not used in MM7?
    //                     See code in ItemTable::generateItem.

    RANDOM_ITEM_WEAPON = 20, // A single-handed weapon.
    RANDOM_ITEM_ARMOR = 21,
    RANDOM_ITEM_MICS = 22, // For items requiring CHARACTER_SKILL_MISC - magic shop items.
    RANDOM_ITEM_SWORD = 23,
    RANDOM_ITEM_DAGGER = 24,
    RANDOM_ITEM_AXE = 25,
    RANDOM_ITEM_SPEAR = 26,
    RANDOM_ITEM_BOW = 27,
    RANDOM_ITEM_MACE = 28,
    RANDOM_ITEM_CLUB = 29, // For items requiring CHARACTER_SKILL_CLUB, which is a hidden skill.
    RANDOM_ITEM_STAFF = 30,
    RANDOM_ITEM_LEATHER_ARMOR = 31,
    RANDOM_ITEM_CHAIN_ARMOR = 32,
    RANDOM_ITEM_PLATE_ARMOR = 33,
    RANDOM_ITEM_SHIELD = 34,
    RANDOM_ITEM_HELMET = 35,
    RANDOM_ITEM_BELT = 36,
    RANDOM_ITEM_CLOAK = 37,
    RANDOM_ITEM_GAUNTLETS = 38,
    RANDOM_ITEM_BOOTS = 39,
    RANDOM_ITEM_RING = 40,
    RANDOM_ITEM_AMULET = 41,
    RANDOM_ITEM_WAND = 42,
    RANDOM_ITEM_SPELL_SCROLL = 43,
    RANDOM_ITEM_POTION = 44,
    RANDOM_ITEM_REAGENT = 45,
    RANDOM_ITEM_GEM = 46,
    // MMExtension also has Gems2 = 47
    //                  and Gold_ = 50

    RANDOM_ITEM_FIRST_SPAWNABLE = RANDOM_ITEM_WEAPON,
    RANDOM_ITEM_LAST_SPAWNABLE = RANDOM_ITEM_GEM
};
using enum RandomItemType;

inline Segment<RandomItemType> allSpawnableRandomItemTypes() {
    return {RANDOM_ITEM_FIRST_SPAWNABLE, RANDOM_ITEM_LAST_SPAWNABLE};
}
