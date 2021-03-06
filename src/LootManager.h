/*
Copyright © 2011-2012 Clint Bellanger
Copyright © 2012 Stefan Beller
Copyright © 2013 Henrik Andersson

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
 * class LootManager
 *
 * Handles floor loot
 */

#ifndef LOOT_MANAGER_H
#define LOOT_MANAGER_H

#include "CommonIncludes.h"
#include "FileParser.h"
#include "ItemManager.h"
#include "Loot.h"
#include "Settings.h"

class Animation;

class EnemyManager;
class MenuInventory;
class WidgetTooltip;

// this means that normal items are 10x more common than epic items
// these numbers have to be balanced by various factors
const int RARITY_LOW = 7;
const int RARITY_NORMAL = 10;
const int RARITY_HIGH = 3;
const int RARITY_EPIC = 1;

class LootManager {
private:

	WidgetTooltip *tip;

	// functions
	void loadGraphics();
	void checkEnemiesForLoot();
	void checkMapForLoot();
	void loadLootTables();
	void getLootTable(const std::string &filename, std::vector<Event_Component> *ec_list);

	SoundManager::SoundID sfx_loot;

	int drop_max;
	int drop_radius;

	// loot refers to ItemManager indices
	std::vector<Loot> loot;

	// enemies which should drop loot, but didnt yet.
	std::vector<class Enemy*> enemiesDroppingLoot;

	// loot tables defined in files under "loot/"
	std::map<std::string, std::vector<Event_Component> > loot_tables;

	// to prevent dropping multiple loot stacks on the same tile,
	// we block tiles that have loot dropped on them
	std::vector<Point> tiles_to_unblock;

public:
	LootManager();
	LootManager(const LootManager &copy); // not implemented
	~LootManager();

	void handleNewMap();
	void logic();
	void renderTooltips(FPoint cam);

	// called by enemy, who definitly wants to drop loot.
	void addEnemyLoot(Enemy *e);
	void addLoot(ItemStack stack, FPoint pos, bool dropped_by_hero = false);
	void checkLoot(std::vector<Event_Component> &loot_table, FPoint *pos = NULL);
	ItemStack checkPickup(Point mouse, FPoint cam, FPoint hero_pos, MenuInventory *inv);
	ItemStack checkAutoPickup(FPoint hero_pos, MenuInventory *inv);
	ItemStack checkNearestPickup(FPoint hero_pos, MenuInventory *inv);

	void addRenders(std::vector<Renderable> &ren, std::vector<Renderable> &ren_dead);

	void parseLoot(FileParser &infile, Event_Component *e, std::vector<Event_Component> *ec_list);

	StatBlock *hero;
	int tooltip_margin; // pixels between loot drop center and label
	bool full_msg;
};

#endif
