/*
Copyright © 2012 Justin Jacobs

This file is part of FLARE.

FLARE is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

FLARE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
FLARE.  If not, see http://www.gnu.org/licenses/
*/

/**
 * class EffectManager
 *
 * Holds the collection of hazards (active attacks, spells, etc) and handles group operations
 */

#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "CommonIncludes.h"
#include "Hazard.h"
#include "SharedResources.h"
#include "Stats.h"
#include "Utils.h"

class Animation;
class Hazard;

#define EFFECT_COUNT 18

enum EFFECT_TYPE {
	EFFECT_NONE = 0,
	EFFECT_DAMAGE = 1,
	EFFECT_HPOT = 2,
	EFFECT_MPOT = 3,
	EFFECT_SPEED = 4,
	EFFECT_IMMUNITY = 5,
	EFFECT_STUN = 6,
	EFFECT_REVIVE = 7,
	EFFECT_CONVERT = 8,
	EFFECT_FEAR = 9,
	EFFECT_OFFENSE = 10,
	EFFECT_DEFENSE = 11,
	EFFECT_PHYSICAL = 12,
	EFFECT_MENTAL = 13,
	EFFECT_DEATH_SENTENCE = 14,
	EFFECT_SHIELD = 15,
	EFFECT_HEAL = 16,
};

class Effect {
public:
	std::string name;
	int icon;
	int ticks;
	int duration;
	int type;
	int magnitude;
	int magnitude_max;
	std::string animation_name;
	Animation* animation;
	bool item;
	int trigger;
	bool render_above;
	int passive_id;
	int source_type;

	Effect()
		: name("")
		, icon(-1)
		, ticks(0)
		, duration(-1)
		, type(EFFECT_NONE)
		, magnitude(0)
		, magnitude_max(0)
		, animation_name("")
		, animation(NULL)
		, item(false)
		, trigger(-1)
		, render_above(false)
		, passive_id(0)
		, source_type(SOURCE_TYPE_HERO) {
	}

	~Effect() {
	}

};

class EffectManager {
private:
	Animation* loadAnimation(std::string &s);
	void removeEffect(int id);
	void removeAnimation(int id);

public:
	EffectManager();
	~EffectManager();
	EffectManager& operator= (const EffectManager &emSource);
	void clearStatus();
	void logic();
	void addEffect(EffectDef &effect, int duration, int magnitude, bool item, int trigger, int passive_id, int source_type);
	void removeEffectType(const int &type);
	void removeEffectPassive(int id);
	void clearEffects();
	void clearNegativeEffects();
	void clearItemEffects();
	void clearTriggerEffects(int trigger);
	int damageShields(int dmg);
	int getType(const std::string type);

	std::vector<Effect> effect_list;

	int damage;
	int hpot;
	int mpot;
	float speed;
	bool immunity;
	bool stun;
	bool revive;
	bool convert;
	bool death_sentence;
	bool fear;

	int bonus_offense;
	int bonus_defense;
	int bonus_physical;
	int bonus_mental;
	std::vector<int> bonus;
	std::vector<int> bonus_resist;

	bool triggered_others;
	bool triggered_block;
	bool triggered_hit;
	bool triggered_halfdeath;
	bool triggered_joincombat;
	bool triggered_death;
};

#endif
