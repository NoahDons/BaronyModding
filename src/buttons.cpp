/*-------------------------------------------------------------------------------

	BARONY
	File: buttons.cpp
	Desc: contains code for all buttons in the editor

	Copyright 2013-2016 (c) Turning Wheel LLC, all rights reserved.
	See LICENSE for details.

-------------------------------------------------------------------------------*/

#include "main.hpp"
#include "editor.hpp"
#include "entity.hpp"
#include "files.hpp"
#include "player.hpp"

button_t* butX;
button_t* but_;
button_t* butTilePalette;
button_t* butSprite;
button_t* butPencil;
button_t* butPoint;
button_t* butBrush;
button_t* butSelect;
button_t* butFill;
button_t* butFile;
button_t* butNew;
button_t* butOpen;
button_t* butDir;
button_t* butSave;
button_t* butSaveAs;
button_t* butExit;
button_t* butEdit;
button_t* butCut;
button_t* butCopy;
button_t* butPaste;
button_t* butDelete;
button_t* butSelectAll;
button_t* butUndo;
button_t* butRedo;
button_t* butView;
button_t* butToolbox;
button_t* butStatusBar;
button_t* butAllLayers;
button_t* butHoverText;
button_t* butViewSprites;
button_t* butGrid;
button_t* but3DMode;
button_t* butMap;
button_t* butAttributes;
button_t* butClearMap;
button_t* butHelp;
button_t* butAbout;
button_t* butEditorControls;
button_t* butMonsterHelm;
button_t* butMonsterWeapon;
button_t* butMonsterShield;
button_t* butMonsterArmor;
button_t* butMonsterRing;
button_t* butMonsterAmulet;
button_t* butMonsterBoots;
button_t* butMonsterGloves;
button_t* butMonsterItem1;
button_t* butMonsterItem2;
button_t* butMonsterItem3;
button_t* butMonsterItem4;
button_t* butMonsterItem5;
button_t* butMonsterItem6;
button_t* butMonsterCloak;
button_t* butMonsterMask;
button_t* butMonsterOK;
button_t* butMonsterX;
button_t* butMonsterCancel;
button_t* butMonsterItemOK;
button_t* butMonsterItemX;
button_t* butMonsterItemCancel;
button_t* butItemOK;
button_t* butItemCancel;
button_t* butItemX;

bool exitFromItemWindow = false;

static void updateMapNames()
{
	DIR* dir;
	struct dirent* ent;
	mapNames.clear();
	// file list
	std::string path;
	if ( savewindow > 0 )
	{
		path = physfs_saveDirectory + "/maps/";
	}
	else
	{
		path = physfs_openDirectory + "/maps/";
	}
	if ( (dir = openDataDir(path.c_str())) != NULL )
	{
		while ( (ent = readdir(dir)) != NULL )
		{
			if ( strstr(ent->d_name, ".lmp") != NULL || (!strcmp(ent->d_name, "..") || !strcmp(ent->d_name, ".")) )
			{
				mapNames.push_back(ent->d_name);
			}
		}
		closedir(dir);
	}
	else
	{
		// could not open directory
		printlog("failed to open map directory for viewing!\n");
		return;
	}
	std::sort(mapNames.begin(), mapNames.end());
}

static void updateModFolderNames()
{
	modFolderNames.clear();
	std::string path = outputdir;
	path.append(PHYSFS_getDirSeparator()).append("mods/");
	modFolderNames = directoryContents(path.c_str(), true, false);
	if ( !modFolderNames.empty() )
	{
		std::list<std::string>::iterator it = std::find(modFolderNames.begin(), modFolderNames.end(), "..");
		if ( it != modFolderNames.end() )
		{
			modFolderNames.erase(it);
		}
		std::sort(mapNames.begin(), mapNames.end());
	}
}

void writeLevelsTxt(std::string modFolder)
{
	std::string path = outputdir;
	path.append(PHYSFS_getDirSeparator()).append("mods/").append(modFolder);
	if ( access(path.c_str(), F_OK) == 0 )
	{
		std::string writeFile = modFolder + "/maps/levels.txt";
		PHYSFS_File *physfp = PHYSFS_openWrite(writeFile.c_str());
		if ( physfp != NULL )
		{
			PHYSFS_writeBytes(physfp, "map: start\n", 11);
			PHYSFS_writeBytes(physfp, "gen: mine\n", 10);
			PHYSFS_writeBytes(physfp, "gen: mine\n", 10);
			PHYSFS_writeBytes(physfp, "gen: mine\n", 10);
			PHYSFS_writeBytes(physfp, "gen: mine\n", 10);
			PHYSFS_writeBytes(physfp, "map: minetoswamp\n", 17);
			PHYSFS_writeBytes(physfp, "gen: swamp\n", 11);			
			PHYSFS_writeBytes(physfp, "gen: swamp\n", 11);			
			PHYSFS_writeBytes(physfp, "gen: swamp\n", 11);
			PHYSFS_writeBytes(physfp, "gen: swamp\n", 11);
			PHYSFS_writeBytes(physfp, "map: swamptolabyrinth\n", 22);			
			PHYSFS_writeBytes(physfp, "gen: labyrinth\n", 15);
			PHYSFS_writeBytes(physfp, "gen: labyrinth\n", 15);			
			PHYSFS_writeBytes(physfp, "gen: labyrinth\n", 15);			
			PHYSFS_writeBytes(physfp, "gen: labyrinth\n", 15);			
			PHYSFS_writeBytes(physfp, "map: labyrinthtoruins\n", 22);			
			PHYSFS_writeBytes(physfp, "gen: ruins\n", 11);			
			PHYSFS_writeBytes(physfp, "gen: ruins\n", 11);			
			PHYSFS_writeBytes(physfp, "gen: ruins\n", 11);			
			PHYSFS_writeBytes(physfp, "gen: ruins\n", 11);			
			PHYSFS_writeBytes(physfp, "map: boss\n", 10);			
			PHYSFS_writeBytes(physfp, "gen: hell\n", 10);			
			PHYSFS_writeBytes(physfp, "gen: hell\n", 10);			
			PHYSFS_writeBytes(physfp, "gen: hell\n", 10);			
			PHYSFS_writeBytes(physfp, "map: hellboss\n", 14);			
			PHYSFS_writeBytes(physfp, "map: hamlet\n", 12);			
			PHYSFS_writeBytes(physfp, "gen: caves\n", 11);			
			PHYSFS_writeBytes(physfp, "gen: caves\n", 11);			
			PHYSFS_writeBytes(physfp, "gen: caves\n", 11);			
			PHYSFS_writeBytes(physfp, "gen: caves\n", 11);			
			PHYSFS_writeBytes(physfp, "map: cavestocitadel\n", 20);			
			PHYSFS_writeBytes(physfp, "gen: citadel\n", 13);			
			PHYSFS_writeBytes(physfp, "gen: citadel\n", 13);			
			PHYSFS_writeBytes(physfp, "gen: citadel\n", 13);			
			PHYSFS_writeBytes(physfp, "gen: citadel\n", 13);			
			PHYSFS_writeBytes(physfp, "map: sanctum", 12);
			PHYSFS_close(physfp);
		}
		else
		{
			printlog("[PhysFS]: Failed to open %s/maps/levels.txt for writing.", path.c_str());
		}
	}
	else
	{
		printlog("[PhysFS]: Failed to write levels.txt in %s", path.c_str());
	}
}

// Corner buttons

void buttonExit(button_t* my)
{
	button_t* button;

	// this shouldn't work if a window is already open
	if ( subwindow )
	{
		return;
	}

	menuVisible = 0;
	subwindow = 1;
	subx1 = xres / 2 - 128;
	subx2 = xres / 2 + 128;
	suby1 = yres / 2 - 32;
	suby2 = yres / 2 + 32;
	strcpy(subtext, "Are you sure you want to quit?\nAny unsaved work will be lost.");

	button = newButton();
	strcpy(button->label, "Yes");
	button->x = subx1 + 32;
	button->y = suby2 - 24;
	button->sizex = 32;
	button->sizey = 16;
	button->action = &buttonExitConfirm;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "No");
	button->x = subx2 - 56;
	button->y = suby2 - 24;
	button->sizex = 24;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;
}

void buttonExitConfirm(button_t* my)
{
	mainloop = 0; // gracefully stops the game/editor
}

void buttonIconify(button_t* my)
{
	// aka minimize
	SDL_MinimizeWindow(screen);
}

// Toolbox buttons

void buttonTilePalette(button_t* my)
{
	tilepalette = 1;
}

void buttonSprite(button_t* my)
{
	makeUndo();
	spritepalette = 1;
}

void buttonPencil(button_t* my)
{
	selectedTool = 0;
	selectedarea = false;
}

void buttonPoint(button_t* my)
{
	selectedTool = 1;
	selectedarea = false;
}

void buttonBrush(button_t* my)
{
	selectedTool = 2;
	selectedarea = false;
}

void buttonSelect(button_t* my)
{
	selectedTool = 3;
	selectedarea = false;
}

void buttonFill(button_t* my)
{
	selectedTool = 4;
	selectedarea = false;
}

// File menu

void buttonFile(button_t* my)
{
	if ( menuVisible != 1 )
	{
		menuVisible = 1;
	}
	else
	{
		menuVisible = 0;
	}
}

void buttonNew(button_t* my)
{
	button_t* button;

	editproperty = 0;
	inputstr = map.name;
	snprintf(widthtext, 4, "%d", map.width);
	snprintf(heighttext, 4, "%d", map.height);
	strcpy(nametext, map.name);
	strcpy(authortext, map.author);
	snprintf(skyboxtext, 4, "%d", map.skybox);
	for ( int z = 0; z < MAPFLAGS; ++z )
	{
		if ( z < MAP_FLAG_GENBYTES1 || z > MAP_FLAG_GENBYTES6 )
		{
			snprintf(mapflagtext[z], 4, "%d", map.flags[z]);
		}
	}
	snprintf(mapflagtext[MAP_FLAG_GENTOTALMIN], 4, "%d", (map.flags[MAP_FLAG_GENBYTES1] >> 24) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENTOTALMAX], 4, "%d", (map.flags[MAP_FLAG_GENBYTES1] >> 16) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENMONSTERMIN], 4, "%d", (map.flags[MAP_FLAG_GENBYTES1] >> 8) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENMONSTERMAX], 4, "%d", (map.flags[MAP_FLAG_GENBYTES1] >> 0) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENLOOTMIN], 4, "%d", (map.flags[MAP_FLAG_GENBYTES2] >> 24) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENLOOTMAX], 4, "%d", (map.flags[MAP_FLAG_GENBYTES2] >> 16) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENDECORATIONMIN], 4, "%d", (map.flags[MAP_FLAG_GENBYTES2] >> 8) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENDECORATIONMAX], 4, "%d", (map.flags[MAP_FLAG_GENBYTES2] >> 0) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_PERIMETER_GAP], 4, "%d", (map.flags[MAP_FLAG_GENBYTES4] >> 0) & static_cast<int>(0xFF));
	if ( (map.flags[MAP_FLAG_GENBYTES3] >> 24) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEDIGGING], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEDIGGING], "[ ]");
	}

	if ( (map.flags[MAP_FLAG_GENBYTES3] >> 16) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLETELEPORT], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLETELEPORT], "[ ]");
	}

	if ( (map.flags[MAP_FLAG_GENBYTES3] >> 8) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLELEVITATION], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLELEVITATION], "[ ]");
	}

	if ( (map.flags[MAP_FLAG_GENBYTES3] >> 0) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_GENADJACENTROOMS], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_GENADJACENTROOMS], "[ ]");
	}
	if ( (map.flags[MAP_FLAG_GENBYTES4] >> 24) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEOPENING], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEOPENING], "[ ]");
	}
	if ( (map.flags[MAP_FLAG_GENBYTES4] >> 16) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEMESSAGES], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEMESSAGES], "[ ]");
	}
	if ( (map.flags[MAP_FLAG_GENBYTES4] >> 8) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEHUNGER], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEHUNGER], "[ ]");
	}

	if ( map.flags[MAP_FLAG_DISABLETRAPS] > 0 )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLETRAPS], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLETRAPS], "[ ]");
	}
	if ( map.flags[MAP_FLAG_DISABLEMONSTERS] > 0 )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEMONSTERS], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEMONSTERS], "[ ]");
	}
	if ( map.flags[MAP_FLAG_DISABLELOOT] > 0 )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLELOOT], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLELOOT], "[ ]");
	}
	cursorflash = ticks;
	menuVisible = 0;
	subwindow = 1;
	newwindow = 1;
	subx1 = xres / 2 - 200;
	subx2 = xres / 2 + 200;
	suby1 = yres / 2 - 200;
	suby2 = yres / 2 + 200;
	strcpy(subtext, "New map:");

	button = newButton();
	strcpy(button->label, "Create");
	button->x = subx2 - 64;
	button->y = suby2 - 48;
	button->sizex = 56;
	button->sizey = 16;
	button->action = &buttonNewConfirm;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "Cancel");
	button->x = subx2 - 64;
	button->y = suby2 - 24;
	button->sizex = 56;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "X");
	button->x = subx2 - 16;
	button->y = suby1;
	button->sizex = 16;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;
}

void buttonNewConfirm(button_t* my)
{
	int x, y, z, c;
	clearUndos();
	free(map.tiles);
	free(camera.vismap);
	list_FreeAll(map.entities);
	strcpy(map.name, nametext);
	strcpy(map.author, authortext);
	map.skybox = atoi(skyboxtext);
	for ( z = 0; z < MAPFLAGS; ++z )
	{
		if ( z == MAP_FLAG_DISABLETRAPS )
		{
			if ( !strncmp(mapflagtext[MAP_FLAG_DISABLETRAPS], "[x]", 3) )
			{
				map.flags[MAP_FLAG_DISABLETRAPS] = 1;
			}
			else
			{
				map.flags[MAP_FLAG_DISABLETRAPS] = 0;
			}
		}
		else if ( z == MAP_FLAG_DISABLEMONSTERS )
		{
			if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEMONSTERS], "[x]", 3) )
			{
				map.flags[MAP_FLAG_DISABLEMONSTERS] = 1;
			}
			else
			{
				map.flags[MAP_FLAG_DISABLEMONSTERS] = 0;
			}
		}
		else if ( z == MAP_FLAG_DISABLELOOT )
		{
			if ( !strncmp(mapflagtext[MAP_FLAG_DISABLELOOT], "[x]", 3) )
			{
				map.flags[MAP_FLAG_DISABLELOOT] = 1;
			}
			else
			{
				map.flags[MAP_FLAG_DISABLELOOT] = 0;
			}
		}
		else if ( z == MAP_FLAG_GENBYTES1 )
		{
			map.flags[z] = 0;
			map.flags[z] |= (atoi(mapflagtext[MAP_FLAG_GENTOTALMIN]) & 0xFF) << 24;
			map.flags[z] |= (atoi(mapflagtext[MAP_FLAG_GENTOTALMAX]) & 0xFF) << 16;
			map.flags[z] |= (atoi(mapflagtext[MAP_FLAG_GENMONSTERMIN]) & 0xFF) << 8;
			map.flags[z] |= (atoi(mapflagtext[MAP_FLAG_GENMONSTERMAX]) & 0xFF) << 0;
		}
		else if ( z == MAP_FLAG_GENBYTES2 )
		{
			map.flags[z] = 0;
			map.flags[z] |= (atoi(mapflagtext[MAP_FLAG_GENLOOTMIN]) & 0xFF) << 24;
			map.flags[z] |= (atoi(mapflagtext[MAP_FLAG_GENLOOTMAX]) & 0xFF) << 16;
			map.flags[z] |= (atoi(mapflagtext[MAP_FLAG_GENDECORATIONMIN]) & 0xFF) << 8;
			map.flags[z] |= (atoi(mapflagtext[MAP_FLAG_GENDECORATIONMAX]) & 0xFF) << 0;
		}
		else if ( z == MAP_FLAG_GENBYTES3 )
		{
			map.flags[z] = 0;
			if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEDIGGING], "[x]", 3) )
			{
				map.flags[z] |= (1 << 24);
			}
			if ( !strncmp(mapflagtext[MAP_FLAG_DISABLETELEPORT], "[x]", 3) )
			{
				map.flags[z] |= (1 << 16);
			}
			if ( !strncmp(mapflagtext[MAP_FLAG_DISABLELEVITATION], "[x]", 3) )
			{
				map.flags[z] |= (1 << 8);
			}
			if ( !strncmp(mapflagtext[MAP_FLAG_GENADJACENTROOMS], "[x]", 3) )
			{
				map.flags[z] |= (1 << 0);
			}
		}
		else if ( z == MAP_FLAG_GENBYTES4 )
		{
			map.flags[z] = 0;
			if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEOPENING], "[x]", 3) )
			{
				map.flags[z] |= (1 << 24);
			}
			if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEMESSAGES], "[x]", 3) )
			{
				map.flags[z] |= (1 << 16);
			}
			if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEHUNGER], "[x]", 3) )
			{
				map.flags[z] |= (1 << 8);
			}
			map.flags[z] |= atoi(mapflagtext[MAP_FLAG_PERIMETER_GAP]) & 0xFF;
		}
		else
		{
			map.flags[z] = atoi(mapflagtext[z]);
		}
	}
	map.width = atoi(widthtext);
	map.height = atoi(heighttext);
	map.width = std::min(std::max(MINWIDTH, map.width), MAXWIDTH);
	map.height = std::min(std::max(MINHEIGHT, map.height), MAXHEIGHT);
	map.tiles = (int*) malloc(sizeof(int) * MAPLAYERS * map.height * map.width);
	camera.vismap = (bool*) malloc(sizeof(bool) * map.height * map.width);
    memset(camera.vismap, 0, sizeof(bool) * map.height * map.width);
	for ( z = 0; z < MAPLAYERS; z++ )
	{
		for ( y = 0; y < map.height; y++ )
		{
			for ( x = 0; x < map.width; x++ )
			{
				if ( z == OBSTACLELAYER )
				{
					if (x == 0 || y == 0 || x == map.width - 1 || y == map.height - 1)
					{
						map.tiles[z + y * MAPLAYERS + x * MAPLAYERS * map.height] = 2;
					}
					else
					{
						map.tiles[z + y * MAPLAYERS + x * MAPLAYERS * map.height] = 0;
					}
				}
				else
				{
					map.tiles[z + y * MAPLAYERS + x * MAPLAYERS * map.height] = 1;
				}
			}
		}
	}
    for (int c = 0; c < MAXPLAYERS + 1; ++c) {
        lightmaps[c].clear();
        lightmaps[c].resize(map.width * map.height);
        lightmapsSmoothed[c].clear();
        lightmapsSmoothed[c].resize((map.width + 2) * (map.height + 2));
    }
	strcpy(message, "                             Created a new map.");
	filename[0] = 0;
	oldfilename[0] = 0;
	messagetime = 60;
	buttonCloseSubwindow(my);
}

void buttonOpen(button_t* my)
{
	button_t* button;
	DIR* dir = NULL;
	struct dirent* ent = NULL;
	unsigned long c = 0;

	inputstr = filename;
	cursorflash = ticks;
	menuVisible = 0;
	subwindow = 1;
	openwindow = 1;
	slidery = 0;
	selectedFile = 0;
	subx1 = xres / 2 - 160;
	subx2 = xres / 2 + 160;
	suby1 = yres / 2 - 120;
	suby2 = yres / 2 + 120;
	strcpy(subtext, "Open file:");

	button = newButton();
	strcpy(button->label, " Open ");
	button->x = subx2 - 64;
	button->y = suby2 - 48;
	button->sizex = 56;
	button->sizey = 16;
	button->action = &buttonOpenConfirm;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "Cancel");
	button->x = subx2 - 64;
	button->y = suby2 - 24;
	button->sizex = 56;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "X");
	button->x = subx2 - 16;
	button->y = suby1;
	button->sizex = 16;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	updateMapNames();
}

void buttonSetSaveDirectoryFolder(button_t* my)
{
	std::string filepath = outputdir;
	bool inModFolder = false;
	if ( strcmp(foldername, ".") == 0 || strcmp(foldername, "") == 0 )
	{
		physfs_saveDirectory = BASE_DATA_DIR;
	}
	else if ( strcmp(foldername, BASE_DATA_DIR) )
	{
		filepath.append(PHYSFS_getDirSeparator()).append("mods/").append(foldername);
		physfs_saveDirectory = filepath + PHYSFS_getDirSeparator();
		inModFolder = true;
	}
	else
	{
		physfs_saveDirectory = BASE_DATA_DIR;
	}
	if ( access(physfs_saveDirectory.c_str(), F_OK) == 0 )
	{
		printlog("[PhysFS]: Changed save directory folder to %s", physfs_saveDirectory.c_str());
	}
	else if ( inModFolder )
	{
		printlog("[PhysFS]: Directory %s does not exist. Creating new mod folder...", physfs_saveDirectory.c_str());
		
		if ( PHYSFS_mkdir(foldername) )
		{
			std::string dir = foldername;
			std::string folder = "/books";
			PHYSFS_mkdir((dir + folder).c_str());
			folder = "/editor";
			PHYSFS_mkdir((dir + folder).c_str());

			folder = "/images";
			PHYSFS_mkdir((dir + folder).c_str());
			std::string subfolder = "/sprites";
			PHYSFS_mkdir((dir + folder + subfolder).c_str());
			subfolder = "/system";
			PHYSFS_mkdir((dir + folder + subfolder).c_str());
			subfolder = "/tiles";
			PHYSFS_mkdir((dir + folder + subfolder).c_str());

			folder = "/items";
			PHYSFS_mkdir((dir + folder).c_str());
			subfolder = "/images";
			PHYSFS_mkdir((dir + folder + subfolder).c_str());

			folder = "/lang";
			PHYSFS_mkdir((dir + folder).c_str());
			folder = "/maps";
			PHYSFS_mkdir((dir + folder).c_str());
			writeLevelsTxt(foldername);

			folder = "/models";
			PHYSFS_mkdir((dir + folder).c_str());
			subfolder = "/creatures";
			PHYSFS_mkdir((dir + folder + subfolder).c_str());
			subfolder = "/decorations";
			PHYSFS_mkdir((dir + folder + subfolder).c_str());
			subfolder = "/doors";
			PHYSFS_mkdir((dir + folder + subfolder).c_str());
			subfolder = "/items";
			PHYSFS_mkdir((dir + folder + subfolder).c_str());
			subfolder = "/particles";
			PHYSFS_mkdir((dir + folder + subfolder).c_str());

			folder = "/music";
			PHYSFS_mkdir((dir + folder).c_str());
			folder = "/sound";
			PHYSFS_mkdir((dir + folder).c_str());
			printlog("[PhysFS]: New folder %s created.", physfs_saveDirectory.c_str());
			strcpy(message, "                      Created a new mod folder.");
			messagetime = 60;
		}
		else
		{
			physfs_saveDirectory = BASE_DATA_DIR;
			printlog("[PhysFS]: Unable to create mods/ folder %s.", physfs_saveDirectory.c_str());
		}
	}
	updateModFolderNames();
}

void buttonSetOpenDirectoryFolder(button_t* my)
{
	if ( PHYSFS_unmount(physfs_openDirectory.c_str()) )
	{
		std::string filepath = outputdir;
		if ( strcmp(foldername, ".") == 0 || strcmp(foldername, "") == 0 )
		{
			physfs_openDirectory = BASE_DATA_DIR;
		}
		else if ( strcmp(foldername, BASE_DATA_DIR) )
		{
			filepath.append(PHYSFS_getDirSeparator()).append("mods/").append(foldername);
			physfs_openDirectory = filepath + PHYSFS_getDirSeparator();
		}
		else
		{
			physfs_openDirectory = BASE_DATA_DIR;
		}
		if ( PHYSFS_mount(physfs_openDirectory.c_str(), NULL, 1) )
		{
			printlog("[PhysFS]: Changed open directory folder to %s", physfs_openDirectory.c_str());
		}
		else
		{
			printlog("[PhysFS]: Failed to change open directory folder to %s", physfs_openDirectory.c_str());
			physfs_openDirectory = BASE_DATA_DIR;
			PHYSFS_mount(BASE_DATA_DIR, NULL, 1);
		}
	}
	else
	{
		printlog("[PhysFS]: Failed to change open directory folder.");
	}
	updateModFolderNames();
}

void buttonPHYSFSDirDefault(button_t* my)
{
	strcpy(foldername, BASE_DATA_DIR);
	buttonSetSaveDirectoryFolder(nullptr);
	buttonSetOpenDirectoryFolder(nullptr);
}

void buttonOpenDirectory(button_t* my)
{
	button_t* button;

	inputstr = foldername;
	cursorflash = ticks;
	menuVisible = 0;
	subwindow = 1;
	openwindow = 2;
	slidery = 0;
	selectedFile = 0;
	subx1 = xres / 2 - 160;
	subx2 = xres / 2 + 160;
	suby1 = yres / 2 - 150;
	suby2 = yres / 2 + 150;
	strcpy(subtext, "Choose mod folders to read/write maps:");

	button = newButton();
	strcpy(button->label, "Set as save directory");
	button->x = subx2 - 16 - strlen(button->label) * TTF12_WIDTH;
	button->y = suby2 - 90;
	button->sizex = strlen(button->label) * TTF12_WIDTH + 8;
	button->sizey = 16;
	button->action = &buttonSetSaveDirectoryFolder;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "Reset to default");
	button->x = subx2 - 16 - strlen(button->label) * TTF12_WIDTH;
	button->y = suby2 - 54;
	button->sizex = strlen(button->label) * TTF12_WIDTH + 8;
	button->sizey = 16;
	button->action = &buttonPHYSFSDirDefault;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "Set as load directory");
	button->x = subx2 - 16 - strlen(button->label) * TTF12_WIDTH;
	button->y = suby2 - 72;
	button->sizex = strlen(button->label) * TTF12_WIDTH + 8;
	button->sizey = 16;
	button->action = &buttonSetOpenDirectoryFolder;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "X");
	button->x = subx2 - 16;
	button->y = suby1;
	button->sizex = 16;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	updateModFolderNames();
}

void buttonOpenConfirm(button_t* my)
{
	int c, c2;
	clearUndos();
	strcpy(oldfilename, filename);
	strcpy(message, "");
	for ( c = 0; c < 32; c++ )
	{
		if (filename[c] == 0)
		{
			break;
		}
	}
	/*for ( c2 = 0; c2 < 32 - c; c2++ )
	{
		strcat(message, " ");
	}*/
	std::string fullMapName = physfsFormatMapName(filename);
	printlog("opening map file '%s'...\n", fullMapName.c_str());
	if (loadMap(fullMapName.c_str(), &map, map.entities, map.creatures) == -1)
	{
		strcat(message, "Failed to open ");
		strcat(message, filename);
	}
	else
	{
		strcat(message, "Opened '");
		strcat(message, filename);
		strcat(message, "'");
	}
	messagetime = 60; // 60*50 ms = 3000 ms (3 seconds)
	buttonCloseSubwindow(my);
}

void buttonSave(button_t* my)
{
	int c, c2;
	menuVisible = 0;
	strcpy(oldfilename, filename);
	inputstr = filename;
	if (filename[0] == 0)
	{
		buttonSaveAs(my);
	}
	else
	{
		strcpy(message, "");
		for ( c = 0; c < 32; c++ )
		{
			if (filename[c] == 0)
			{
				break;
			}
		}
		/*for ( c2 = 0; c2 < 32 - c; c2++ )
		{
			strcat(message, " ");
		}*/
		printlog("saving map file '%s'...\n", filename);

		std::string path = physfs_saveDirectory;
		path.append("/maps/").append(filename);
		if (saveMap(path.c_str()))
		{
			strcat(message, "Failed to save ");
			strcat(message, path.c_str());
		}
		else
		{
			strcat(message, "Saved '");
			strcat(message, path.c_str());
			strcat(message, "'");
		}
		messagetime = 60; // 60*50 ms = 3000 ms (3 seconds)
		buttonCloseSubwindow(my);
	}
}

void buttonSaveAs(button_t* my)
{
	button_t* button;

	cursorflash = ticks;
	menuVisible = 0;
	subwindow = 1;
	savewindow = 1;
	slidery = 0;
	selectedFile = 0;
	subx1 = xres / 2 - 160;
	subx2 = xres / 2 + 160;
	suby1 = yres / 2 - 120;
	suby2 = yres / 2 + 120;
	strcpy(subtext, "Save file:");

	button = newButton();
	strcpy(button->label, " Save ");
	button->x = subx2 - 64;
	button->y = suby2 - 48;
	button->sizex = 56;
	button->sizey = 16;
	button->action = &buttonSave;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "Cancel");
	button->x = subx2 - 64;
	button->y = suby2 - 24;
	button->sizex = 56;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "X");
	button->x = subx2 - 16;
	button->y = suby1;
	button->sizex = 16;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	updateMapNames();
}

// Edit menu

void buttonEdit(button_t* my)
{
	if ( menuVisible != 2 )
	{
		menuVisible = 2;
	}
	else
	{
		menuVisible = 0;
	}
}

void buttonCut(button_t* my)
{
	menuVisible = 0;
	if ( !selectedarea )
	{
		return;
	}
	buttonCopy(my);
	selectedarea = true;
	buttonDelete(my);
}

void buttonCopy(button_t* my)
{
	menuVisible = 0;
	int x, y;

	// copy the selected tiles
	if (selectedarea && !pasting)
	{
		copymap.width = selectedarea_x2 - selectedarea_x1 + 1;
		copymap.height = selectedarea_y2 - selectedarea_y1 + 1;
		if ( copymap.tiles != NULL )
		{
			free(copymap.tiles);
		}
		copymap.tiles = (Sint32*) malloc(sizeof(Sint32) * copymap.width * copymap.height * MAPLAYERS);
		memset(copymap.tiles, 0, sizeof(Sint32)*copymap.width * copymap.height * MAPLAYERS);
		for ( x = 0; x < copymap.width; x++ )
		{
			for ( y = 0; y < copymap.height; y++ )
			{
				copymap.tiles[drawlayer + y * MAPLAYERS + x * MAPLAYERS * copymap.height] = map.tiles[drawlayer + (y + selectedarea_y1) * MAPLAYERS + (x + selectedarea_x1) * MAPLAYERS * map.height];
			}
		}
		copymap.name[0] = drawlayer;
	}
	selectedarea = false;
}

void buttonPaste(button_t* my)
{
	menuVisible = 0;

	// paste the selected tiles
	if ( copymap.tiles != NULL )
	{
		pasting = true;
		selectedarea = false;
	}
}

void buttonDelete(button_t* my)
{
	menuVisible = 0;
	makeUndo();

	// delete the selected entity, if there is one
	if ( selectedEntity[0] != NULL)
	{
		list_RemoveNode(selectedEntity[0]->mynode);
		selectedEntity[0] = NULL;
		lastSelectedEntity[0] = NULL;
	}
	if (selectedarea)
	{
		// delete all selected tiles
		int x, y;
		for ( x = selectedarea_x1; x <= selectedarea_x2; x++ )
		{
			for ( y = selectedarea_y1; y <= selectedarea_y2; y++ )
			{
				map.tiles[drawlayer + y * MAPLAYERS + x * MAPLAYERS * map.height] = 0;
			}
		}
		selectedarea = false;
	}
}

void buttonCycleSprites(button_t* my)
{
	SDL_Rect pos;
	char tmp[4];
	Entity* entity = nullptr;
	Entity* lastEntity = nullptr;
	bool entityWasSelected = false;
	for ( node_t* node = map.entities->first; node != nullptr; node = node->next )
	{
		entity = (Entity*)node->element;
		pos.x = entity->x * (TEXTURESIZE / 16) - camx;
		pos.y = entity->y * (TEXTURESIZE / 16) - camy;
		if ( (omousex / TEXTURESIZE) * 32 == pos.x && (omousey / TEXTURESIZE) * 32 == pos.y )
		{
			// set lastEntity to each entity on the tile.
			lastEntity = entity;
		}
	}

	if ( lastEntity != nullptr )
	{
		if ( selectedEntity[0] )
		{
			entityWasSelected = true;
		}

		selectedEntity[0] = nullptr;
		lastSelectedEntity[0] = nullptr;

		// create new entity on the list, copying and removing the previous last one.
		entity = newEntity(lastEntity->sprite, 0, map.entities, nullptr);
		setSpriteAttributes(entity, lastEntity, lastEntity);
		list_RemoveNode(lastEntity->mynode);

		if ( entityWasSelected )
		{
			selectedEntity[0] = entity;
			lastSelectedEntity[0] = selectedEntity[0];
		}
	}
}

void buttonSelectAll(button_t* my)
{
	menuVisible = 0;
	selectedTool = 3;
	selectedarea = true;
	selectingspace = false;
	selectedarea_x1 = 0;
	selectedarea_x2 = map.width - 1;
	selectedarea_y1 = 0;
	selectedarea_y2 = map.height - 1;
}

void buttonUndo(button_t* my)
{
	menuVisible = 0;
	undo();
}

void buttonRedo(button_t* my)
{
	menuVisible = 0;
	redo();
}

// View menu

void buttonView(button_t* my)
{
	if ( menuVisible != 3 )
	{
		menuVisible = 3;
	}
	else
	{
		menuVisible = 0;
	}
}

void buttonToolbox(button_t* my)
{
	toolbox = (toolbox == 0);
	butTilePalette->visible = (butTilePalette->visible == 0);
	butPencil->visible = (butPencil->visible == 0);
	butSprite->visible = (butSprite->visible == 0);
	butPoint->visible = (butPoint->visible == 0);
	butBrush->visible = (butBrush->visible == 0);
	butSelect->visible = (butSelect->visible == 0);
	butFill->visible = (butFill->visible == 0);
}

void buttonStatusBar(button_t* my)
{
	statusbar = (statusbar == 0);
}

void buttonAllLayers(button_t* my)
{
	alllayers = (alllayers == 0);
}

void buttonViewSprites(button_t* my)
{
	viewsprites = (viewsprites == 0);
}

void buttonGrid(button_t* my)
{
	showgrid = (showgrid == 0);
}

void button3DMode(button_t* my)
{
	mode3d = (mode3d == false);
}

void buttonHoverText(button_t* my)
{
	hovertext = (hovertext == false);
}

// Map menu

void buttonMap(button_t* my)
{
	if ( menuVisible != 4 )
	{
		menuVisible = 4;
	}
	else
	{
		menuVisible = 0;
	}
}

void buttonAttributes(button_t* my)
{
	button_t* button;

	editproperty = 0;
	inputstr = map.name;
	snprintf(widthtext, 4, "%d", map.width);
	snprintf(heighttext, 4, "%d", map.height);
	strcpy(nametext, map.name);
	strcpy(authortext, map.author);
	snprintf(skyboxtext, 4, "%d", map.skybox);
	for ( int z = 0; z < MAPFLAGS; ++z )
	{
		if ( z < MAP_FLAG_GENBYTES1 || z > MAP_FLAG_GENBYTES6 )
		{
			snprintf(mapflagtext[z], 4, "%d", map.flags[z]);
		}
	}

	snprintf(mapflagtext[MAP_FLAG_GENTOTALMIN], 4, "%d", (map.flags[MAP_FLAG_GENBYTES1] >> 24) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENTOTALMAX], 4, "%d", (map.flags[MAP_FLAG_GENBYTES1] >> 16) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENMONSTERMIN], 4, "%d", (map.flags[MAP_FLAG_GENBYTES1] >> 8) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENMONSTERMAX], 4, "%d", (map.flags[MAP_FLAG_GENBYTES1] >> 0) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENLOOTMIN], 4, "%d", (map.flags[MAP_FLAG_GENBYTES2] >> 24) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENLOOTMAX], 4, "%d", (map.flags[MAP_FLAG_GENBYTES2] >> 16) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENDECORATIONMIN], 4, "%d", (map.flags[MAP_FLAG_GENBYTES2] >> 8) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_GENDECORATIONMAX], 4, "%d", (map.flags[MAP_FLAG_GENBYTES2] >> 0) & static_cast<int>(0xFF));
	snprintf(mapflagtext[MAP_FLAG_PERIMETER_GAP], 4, "%d", (map.flags[MAP_FLAG_GENBYTES4] >> 0) & static_cast<int>(0xFF));
	if ( (map.flags[MAP_FLAG_GENBYTES3] >> 24) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEDIGGING], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEDIGGING], "[ ]");
	}

	if ( (map.flags[MAP_FLAG_GENBYTES3] >> 16) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLETELEPORT], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLETELEPORT], "[ ]");
	}

	if ( (map.flags[MAP_FLAG_GENBYTES3] >> 8) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLELEVITATION], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLELEVITATION], "[ ]");
	}

	if ( (map.flags[MAP_FLAG_GENBYTES3] >> 0) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_GENADJACENTROOMS], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_GENADJACENTROOMS], "[ ]");
	}
	if ( (map.flags[MAP_FLAG_GENBYTES4] >> 24) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEOPENING], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEOPENING], "[ ]");
	}
	if ( (map.flags[MAP_FLAG_GENBYTES4] >> 16) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEMESSAGES], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEMESSAGES], "[ ]");
	}
	if ( (map.flags[MAP_FLAG_GENBYTES4] >> 8) & static_cast<int>(0xFF) )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEHUNGER], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEHUNGER], "[ ]");
	}

	if ( map.flags[MAP_FLAG_DISABLETRAPS] > 0 )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLETRAPS], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLETRAPS], "[ ]");
	}
	if ( map.flags[MAP_FLAG_DISABLEMONSTERS] > 0 )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEMONSTERS], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLEMONSTERS], "[ ]");
	}
	if ( map.flags[MAP_FLAG_DISABLELOOT] > 0 )
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLELOOT], "[x]");
	}
	else
	{
		strcpy(mapflagtext[MAP_FLAG_DISABLELOOT], "[ ]");
	}
	
	cursorflash = ticks;
	menuVisible = 0;
	subwindow = 1;
	newwindow = 1;
	subx1 = xres / 2 - 200;
	subx2 = xres / 2 + 200;
	suby1 = yres / 2 - 200;
	suby2 = yres / 2 + 200;
	strcpy(subtext, "Map properties:");

	button = newButton();
	strcpy(button->label, "  OK  ");
	button->x = subx2 - 64;
	button->y = suby2 - 48;
	button->sizex = 56;
	button->sizey = 16;
	button->action = &buttonAttributesConfirm;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "Cancel");
	button->x = subx2 - 64;
	button->y = suby2 - 24;
	button->sizex = 56;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "X");
	button->x = subx2 - 16;
	button->y = suby1;
	button->sizex = 16;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;
}

void buttonAttributesConfirm(button_t* my)
{
	int x, y, z, c;
	map_t mapcopy;
	makeUndo();

	// make a copy of the current map
	mapcopy.width = map.width;
	mapcopy.height = map.height;
	mapcopy.tiles = (int*) malloc(sizeof(int) * MAPLAYERS * mapcopy.width * mapcopy.height);
	for ( z = 0; z < MAPLAYERS; z++ )
	{
		for ( y = 0; y < map.height; y++ )
		{
			for ( x = 0; x < map.width; x++ )
			{
				mapcopy.tiles[z + y * MAPLAYERS + x * MAPLAYERS * map.height] = map.tiles[z + y * MAPLAYERS + x * MAPLAYERS * mapcopy.height];
			}
		}
	}

	// allocate memory for a new map
	free(map.tiles);
	free(camera.vismap);
	map.width = atoi(widthtext);
	map.height = atoi(heighttext);
	map.width = std::min(std::max(MINWIDTH, map.width), MAXWIDTH);
	map.height = std::min(std::max(MINHEIGHT, map.height), MAXHEIGHT);
	map.skybox = atoi(skyboxtext);
	if ( map.skybox > numtiles )
	{
		map.skybox = 0;
	}
	map.flags[MAP_FLAG_CEILINGTILE] = atoi(mapflagtext[MAP_FLAG_CEILINGTILE]);
	if ( map.flags[MAP_FLAG_CEILINGTILE] >= numtiles )
	{
		map.flags[MAP_FLAG_CEILINGTILE] = 0;
	}

	// start storing some misc bytes within the Sint32 flags to save space:
	map.flags[MAP_FLAG_GENBYTES1] = 0; // clear the flag 1 slot.
	if ( atoi(mapflagtext[MAP_FLAG_GENTOTALMIN]) >= 0 )
	{
		map.flags[MAP_FLAG_GENBYTES1] |= atoi(mapflagtext[MAP_FLAG_GENTOTALMIN]) << 24; // store in first leftmost byte.
	}
	if ( atoi(mapflagtext[MAP_FLAG_GENTOTALMAX]) >= 0 )
	{
		map.flags[MAP_FLAG_GENBYTES1] |= atoi(mapflagtext[MAP_FLAG_GENTOTALMAX]) << 16; // store in second leftmost byte.
	}
	if ( atoi(mapflagtext[MAP_FLAG_GENMONSTERMIN]) >= 0 )
	{
		map.flags[MAP_FLAG_GENBYTES1] |= atoi(mapflagtext[MAP_FLAG_GENMONSTERMIN]) << 8; // store in third leftmost byte.
	}
	if ( atoi(mapflagtext[MAP_FLAG_GENMONSTERMAX]) >= 0 )
	{
		map.flags[MAP_FLAG_GENBYTES1] |= atoi(mapflagtext[MAP_FLAG_GENMONSTERMAX]) << 0; // store in fourth leftmost byte.
	}

	map.flags[MAP_FLAG_GENBYTES2] = 0; // clear the flag 2 slot.
	if ( atoi(mapflagtext[MAP_FLAG_GENMONSTERMIN]) >= 0 )
	{
		map.flags[MAP_FLAG_GENBYTES2] |= atoi(mapflagtext[MAP_FLAG_GENLOOTMIN]) << 24; // store in first leftmost byte.
	}
	if ( atoi(mapflagtext[MAP_FLAG_GENMONSTERMAX]) >= 0 )
	{
		map.flags[MAP_FLAG_GENBYTES2] |= atoi(mapflagtext[MAP_FLAG_GENLOOTMAX]) << 16; // store in second leftmost byte.
	}
	if ( atoi(mapflagtext[MAP_FLAG_GENDECORATIONMIN]) >= 0 )
	{
		map.flags[MAP_FLAG_GENBYTES2] |= atoi(mapflagtext[MAP_FLAG_GENDECORATIONMIN]) << 8; // store in third leftmost byte.
	}
	if ( atoi(mapflagtext[MAP_FLAG_GENDECORATIONMAX]) >= 0 )
	{
		map.flags[MAP_FLAG_GENBYTES2] |= atoi(mapflagtext[MAP_FLAG_GENDECORATIONMAX]) << 0; // store in fourth leftmost byte.
	}

	map.flags[MAP_FLAG_GENBYTES3] = 0; // clear the flag 3 slot.
	if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEDIGGING], "[x]", 3) )
	{
		map.flags[MAP_FLAG_GENBYTES3] |= (1 << 24); // store in first leftmost byte.
	}
	if ( !strncmp(mapflagtext[MAP_FLAG_DISABLETELEPORT], "[x]", 3) )
	{
		map.flags[MAP_FLAG_GENBYTES3] |= (1 << 16); // store in second leftmost byte.
	}
	if ( !strncmp(mapflagtext[MAP_FLAG_DISABLELEVITATION], "[x]", 3) )
	{
		map.flags[MAP_FLAG_GENBYTES3] |= (1 << 8); // store in third leftmost byte.
	}
	if ( !strncmp(mapflagtext[MAP_FLAG_GENADJACENTROOMS], "[x]", 3) )
	{
		map.flags[MAP_FLAG_GENBYTES3] |= (1 << 0); // store in fourth leftmost byte.
	}
	map.flags[MAP_FLAG_GENBYTES4] = 0; // clear the flag 4 slot.
	if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEOPENING], "[x]", 3) )
	{
		map.flags[MAP_FLAG_GENBYTES4] |= (1 << 24); // store in first leftmost byte.
	}
	if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEMESSAGES], "[x]", 3) )
	{
		map.flags[MAP_FLAG_GENBYTES4] |= (1 << 16); // store in second leftmost byte.
	}
	if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEHUNGER], "[x]", 3) )
	{
		map.flags[MAP_FLAG_GENBYTES4] |= (1 << 8); // store in third leftmost byte.
	}
	if ( atoi(mapflagtext[MAP_FLAG_PERIMETER_GAP]) >= 0 )
	{
		map.flags[MAP_FLAG_GENBYTES4] |= 0xFF & (atoi(mapflagtext[MAP_FLAG_PERIMETER_GAP]) << 0); // store in fourth leftmost byte.
	}

	if ( !strncmp(mapflagtext[MAP_FLAG_DISABLETRAPS], "[x]", 3) )
	{
		map.flags[MAP_FLAG_DISABLETRAPS] = 1;
	}
	else
	{
		map.flags[MAP_FLAG_DISABLETRAPS] = 0;
	}
	if ( !strncmp(mapflagtext[MAP_FLAG_DISABLEMONSTERS], "[x]", 3) )
	{
		map.flags[MAP_FLAG_DISABLEMONSTERS] = 1;
	}
	else
	{
		map.flags[MAP_FLAG_DISABLEMONSTERS] = 0;
	}
	if ( !strncmp(mapflagtext[MAP_FLAG_DISABLELOOT], "[x]", 3) )
	{
		map.flags[MAP_FLAG_DISABLELOOT] = 1;
	}
	else
	{
		map.flags[MAP_FLAG_DISABLELOOT] = 0;
	}

	map.tiles = (int*) malloc(sizeof(int) * MAPLAYERS * map.height * map.width);
	camera.vismap = (bool*) malloc(sizeof(bool) * map.height * map.width);
    memset(camera.vismap, 0, sizeof(bool) * map.height * map.width);
	strcpy(map.name, nametext);
	strcpy(map.author, authortext);
    for (int c = 0; c < MAXPLAYERS + 1; ++c) {
        lightmaps[c].clear();
        lightmaps[c].resize(map.width * map.height);
        lightmapsSmoothed[c].clear();
        lightmapsSmoothed[c].resize((map.width + 2) * (map.height + 2));
    }

	// transfer data from the new map to the old map and fill extra space with empty data
	for ( z = 0; z < MAPLAYERS; z++ )
	{
		for ( y = 0; y < map.height; y++ )
		{
			for ( x = 0; x < map.width; x++ )
			{
				if ( x >= mapcopy.width || y >= mapcopy.height )
				{
					map.tiles[z + y * MAPLAYERS + x * MAPLAYERS * map.height] = 0;
				}
				else
				{
					map.tiles[z + y * MAPLAYERS + x * MAPLAYERS * map.height] = mapcopy.tiles[z + y * MAPLAYERS + x * MAPLAYERS * mapcopy.height];
				}
			}
		}
	}
	free(mapcopy.tiles);
	strcpy(message, "                       Modified map attributes.");
	messagetime = 60;
	buttonCloseSubwindow(my);
}

void buttonClearMap(button_t* my)
{
	button_t* button;

	menuVisible = 0;
	subwindow = 1;
	subx1 = xres / 2 - 160;
	subx2 = xres / 2 + 160;
	suby1 = yres / 2 - 56;
	suby2 = yres / 2 + 56;
	strcpy(subtext, "Warning:\n\nThis option will completely erase your\nentire map.\n\nAre you sure you want to continue?\n");

	button = newButton();
	strcpy(button->label, "OK");
	button->x = subx1 + 64;
	button->y = suby2 - 24;
	button->sizex = 24;
	button->sizey = 16;
	button->action = &buttonClearMapConfirm;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "Cancel");
	button->x = subx2 - 112;
	button->y = suby2 - 24;
	button->sizex = 56;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "X");
	button->x = subx2 - 16;
	button->y = suby1;
	button->sizex = 16;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;
}

void buttonClearMapConfirm(button_t* my)
{
	long x, y, z;
	makeUndo();
	for ( z = 0; z < MAPLAYERS; z++ )
	{
		for ( y = 0; y < map.height; y++ )
		{
			for ( x = 0; x < map.width; x++ )
			{
				map.tiles[z + y * MAPLAYERS + x * MAPLAYERS * map.height] = 0;
			}
		}
	}
	list_FreeAll(map.entities);
	buttonCloseSubwindow(my);
}

// Help menu

void buttonHelp(button_t* my)
{
	if ( menuVisible != 5 )
	{
		menuVisible = 5;
	}
	else
	{
		menuVisible = 0;
	}
	strcpy(subtext, "");
}

void buttonAbout(button_t* my)
{
	button_t* button;

	menuVisible = 0;
	subwindow = 1;
	subx1 = xres / 2 - 160;
	subx2 = xres / 2 + 160;
	suby1 = yres / 2 - 56;
	suby2 = yres / 2 + 56;
	strcpy(subtext, "Barony: Map Editor v2.4"
		"\n\nSee EDITING for full documentation."
		"\n\nThis software is copyright 2018 (c)"
		"\nSheridan Rathbun, all rights reserved."
		"\n\nSee LICENSE for details.\n");

	button = newButton();
	strcpy(button->label, "OK");
	button->x = xres / 2 - 12;
	button->y = suby2 - 24;
	button->sizex = 24;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "X");
	button->x = subx2 - 16;
	button->y = suby1;
	button->sizex = 16;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;
}

void buttonEditorToolsHelp(button_t* my)
{
	node_t* node;
	node_t* nextnode;
	button_t* button;
	for ( node = button_l.first; node != NULL; node = nextnode )
	{
		nextnode = node->next;
		button = (button_t*)node->element;
		if ( button->focused )
		{
			list_RemoveNode(button->node);
			continue;
		}
	}
	subwindow = 1;
	if ( newwindow == 16 )
	{
		newwindow = 17;
		subx1 = xres / 2 - 280;
		subx2 = xres / 2 + 280;
		suby1 = yres / 2 - 190;
		suby2 = yres / 2 + 190;

		button = newButton();
		strcpy(button->label, "OK");
		button->sizex = 9 * 12 + 8;
		button->x = xres / 2 - button->sizex - 4;
		button->y = suby2 - 24;
		button->sizey = 16;
		button->action = &buttonCloseSubwindow;
		button->visible = 1;
		button->focused = 1;

		button = newButton();
		strcpy(button->label, "Next Page");
		button->x = xres / 2 + 4;
		button->y = suby2 - 24;
		button->sizex = strlen(button->label) * 12 + 8;
		button->sizey = 16;
		button->action = &buttonEditorToolsHelp;
		button->visible = 1;
		button->focused = 1;

		button = newButton();
		strcpy(button->label, "X");
		button->x = subx2 - 16;
		button->y = suby1;
		button->sizex = 16;
		button->sizey = 16;
		button->action = &buttonCloseSubwindow;
		button->visible = 1;
		button->focused = 1;
	}
	else
	{
		buttonEditorControls(nullptr);
	}
}

void buttonEditorControls(button_t* my)
{
	button_t* button;

	menuVisible = 0;
	subwindow = 1;
	newwindow = 16;
	subx1 = xres / 2 - 250;
	subx2 = xres / 2 + 250;
	suby1 = yres / 2 - 210;
	suby2 = yres / 2 + 210;

	button = newButton();
	strcpy(button->label, "OK");
	button->sizex = 9 * 12 + 8;
	button->x = xres / 2 - button->sizex - 4;
	button->y = suby2 - 24;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "Next Page");
	button->x = xres / 2 + 4;
	button->y = suby2 - 24;
	button->sizex = strlen(button->label) * 12 + 8;
	button->sizey = 16;
	button->action = &buttonEditorToolsHelp;
	button->visible = 1;
	button->focused = 1;

	button = newButton();
	strcpy(button->label, "X");
	button->x = subx2 - 16;
	button->y = suby1;
	button->sizex = 16;
	button->sizey = 16;
	button->action = &buttonCloseSubwindow;
	button->visible = 1;
	button->focused = 1;
}

// Subwindows
void buttonCloseSubwindow(button_t* my)
{
	int c;

	// close window
	selectedEntity[0] = NULL;
	subwindow = 0;
	newwindow = 0;
	openwindow = 0;
	savewindow = 0;
	editproperty = 0;
	strcpy(filename, oldfilename);
}

void buttonSpriteProperties(button_t* my)
{
	button_t* button;
	int c = 0;
	Stat* tmpSpriteStats = NULL;
	int spriteType = 0;
	int spacing = 20;
	int pad_y2;
	int pad_x3;
	int pad_x4;
	char tmpStr[32] = "";
	int itemIndex = 0;

	if ( selectedEntity[0] == NULL && lastSelectedEntity[0] != NULL )
	{
		if ( checkSpriteType(lastSelectedEntity[0]->sprite) != 0 )
		{
			selectedEntity[0] = lastSelectedEntity[0];
		}
		else
		{
			strcpy(message, "No properties available for previous sprite.");
			messagetime = 60;
		}
	}

	if ( selectedEntity[0] != NULL )
	{
		editproperty = 0;
		for ( int i = 0; i < (sizeof(spriteProperties) / sizeof(spriteProperties[0])); i++ )
		{
			strcpy(spriteProperties[i], "");
		}

		spriteType = checkSpriteType(selectedEntity[0]->sprite);
		switch ( spriteType )
		{
			case 1: //monsters
				tmpSpriteStats = selectedEntity[0]->getStats();
				if ( tmpSpriteStats != nullptr )
				{
					if ( exitFromItemWindow == true )
					{
						exitFromItemWindow = false;
						// retreives any modified monster stats, to be restored when window is closed.

						for ( int i = 0; i < sizeof(spriteProperties) / sizeof(spriteProperties[0]); i++ )
						{
							strcpy(spriteProperties[i], tmpSpriteProperties[i]);
						}
					}
					else
					{
						copyMonsterStatToPropertyStrings(tmpSpriteStats);
					}
					inputstr = spriteProperties[0];
					initMonsterPropertiesWindow();
				}
				tmpSpriteStats = NULL;
				break;
			case 2: //chests
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->yaw));
				snprintf(spriteProperties[1], 4, "%d", selectedEntity[0]->skill[9]);
				snprintf(spriteProperties[2], 4, "%d", selectedEntity[0]->chestLocked);
				snprintf(spriteProperties[3], 4, "%d", selectedEntity[0]->chestMimicChance);
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 3;
				subx1 = xres / 2 - 160;
				subx2 = xres / 2 + 160;
				suby1 = yres / 2 - 125;
				suby2 = yres / 2 + 125;
				strcpy(subtext, "Chest Properties:");
				break;
			case 3: //items
				itemSelect = 1;
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->skill[10])); //ID
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->skill[11])); //status
				if ( (int)selectedEntity[0]->skill[12] == 10 )
				{
					strcpy(spriteProperties[2], "00"); //bless random
				}
				else
				{
					snprintf(spriteProperties[2], 4, "%d", static_cast<int>(selectedEntity[0]->skill[12])); //bless
				}
				snprintf(spriteProperties[3], 4, "%d", static_cast<int>(selectedEntity[0]->skill[13])); //count
				snprintf(spriteProperties[4], 4, "%d", static_cast<int>(selectedEntity[0]->skill[15])); //identified
				snprintf(spriteProperties[5], 4, "%d", static_cast<int>(selectedEntity[0]->skill[16])); //category if random
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 4;
				slidery = 0;
				subx1 = xres / 2 - 200;
				subx2 = xres / 2 + 200;
				suby1 = yres / 2 - 140;
				suby2 = yres / 2 + 140;
				strcpy(subtext, "Item Properties:");
				break;
			case 4:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->skill[0])); //Monster to Spawn
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->skill[1])); //Qty
				snprintf(spriteProperties[2], 4, "%d", static_cast<int>(selectedEntity[0]->skill[2])); //Time Between Spawns
				snprintf(spriteProperties[3], 4, "%d", static_cast<int>(selectedEntity[0]->skill[3])); //Amount of Spawns 
				snprintf(spriteProperties[4], 4, "%d", static_cast<int>(selectedEntity[0]->skill[4])); //Requires Power
				snprintf(spriteProperties[5], 4, "%d", static_cast<int>(selectedEntity[0]->skill[5])); //Chance to Stop Working
				snprintf(spriteProperties[6], 4, "%d", static_cast<int>(selectedEntity[0]->skill[9])); //Autospawn
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 6;
				subx1 = xres / 2 - 220;
				subx2 = xres / 2 + 220;
				suby1 = yres / 2 - 140;
				suby2 = yres / 2 + 140;
				strcpy(subtext, "Summoning Trap Properties:");
				break;
			case 5:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->yaw)); //Orientation
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->crystalNumElectricityNodes)); //Powered Distance
				snprintf(spriteProperties[2], 4, "%d", static_cast<int>(selectedEntity[0]->crystalTurnReverse)); //Rotation direction
				snprintf(spriteProperties[3], 4, "%d", static_cast<int>(selectedEntity[0]->crystalSpellToActivate)); //Spell to activate
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 7;
				subx1 = xres / 2 - 210;
				subx2 = xres / 2 + 210;
				suby1 = yres / 2 - 120;
				suby2 = yres / 2 + 120;
				strcpy(subtext, "Power Crystal Properties:");
				break;
			case 6:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->leverTimerTicks));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 8;
				subx1 = xres / 2 - 120;
				subx2 = xres / 2 + 120;
				suby1 = yres / 2 - 60;
				suby2 = yres / 2 + 60;
				strcpy(subtext, "Lever Timer Properties:");
				break;
			case 7:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->boulderTrapRefireAmount));
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->boulderTrapRefireDelay));
				snprintf(spriteProperties[2], 4, "%d", static_cast<int>(selectedEntity[0]->boulderTrapPreDelay));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 9;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 100;
				suby2 = yres / 2 + 100;
				strcpy(subtext, "Boulder Trap Properties:");
				break;
			case 8:
				snprintf(spriteProperties[0], 2, "%d", static_cast<int>(selectedEntity[0]->pedestalOrbType));
				snprintf(spriteProperties[1], 2, "%d", static_cast<int>(selectedEntity[0]->pedestalHasOrb));
				snprintf(spriteProperties[2], 2, "%d", static_cast<int>(selectedEntity[0]->pedestalInvertedPower));
				snprintf(spriteProperties[3], 2, "%d", static_cast<int>(selectedEntity[0]->pedestalInGround));
				snprintf(spriteProperties[4], 2, "%d", static_cast<int>(selectedEntity[0]->pedestalLockOrb));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 10;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 110;
				suby2 = yres / 2 + 110;
				strcpy(subtext, "Pedestal Properties:");
				break;
			case 9:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->teleporterX));
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->teleporterY));
				snprintf(spriteProperties[2], 2, "%d", static_cast<int>(selectedEntity[0]->teleporterType));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 11;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 100;
				suby2 = yres / 2 + 100;
				strcpy(subtext, "Teleporter Properties:");
				break;
			case 10:
				snprintf(spriteProperties[0], 5, "%d", static_cast<int>(selectedEntity[0]->ceilingTileModel));
				snprintf(spriteProperties[1], 5, "%d", static_cast<int>(selectedEntity[0]->ceilingTileDir));
				snprintf(spriteProperties[2], 5, "%d", static_cast<int>(selectedEntity[0]->ceilingTileAllowTrap));
				snprintf(spriteProperties[3], 5, "%d", static_cast<int>(selectedEntity[0]->ceilingTileBreakable));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 12;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 100;
				suby2 = yres / 2 + 100;
				strcpy(subtext, "Ceiling Tile Properties:");
				break;
			case 11:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->spellTrapType));
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->spellTrapRefire));
				snprintf(spriteProperties[2], 4, "%d", static_cast<int>(selectedEntity[0]->spellTrapLatchPower));
				snprintf(spriteProperties[3], 5, "%d", static_cast<int>(selectedEntity[0]->spellTrapFloorTile));
				snprintf(spriteProperties[4], 4, "%d", static_cast<int>(selectedEntity[0]->spellTrapRefireRate));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 13;
				subx1 = xres / 2 - 200;
				subx2 = xres / 2 + 200;
				suby1 = yres / 2 - 110;
				suby2 = yres / 2 + 110;
				strcpy(subtext, "Spell Trap Properties:");
				break;
			case 12:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->furnitureDir));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 14;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 60;
				suby2 = yres / 2 + 60;
				strcpy(subtext, "Furniture Properties:");
				break;
			case 13:
			{
				snprintf(spriteProperties[0], 5, "%d", static_cast<int>(selectedEntity[0]->floorDecorationModel));
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->floorDecorationRotation));
				snprintf(spriteProperties[2], 5, "%d", static_cast<int>(selectedEntity[0]->floorDecorationHeightOffset));
				snprintf(spriteProperties[3], 5, "%d", static_cast<int>(selectedEntity[0]->floorDecorationXOffset));
				snprintf(spriteProperties[4], 5, "%d", static_cast<int>(selectedEntity[0]->floorDecorationYOffset));
				char buf[256] = "";
				int totalChars = 0;
				for ( int i = 8; i < 60; ++i )
				{
					if ( selectedEntity[0]->skill[i] != 0 && i != 28 ) // skill[28] is circuit status.
					{
						for ( int c = 0; c < 4; ++c )
						{
							if ( static_cast<char>((selectedEntity[0]->skill[i] >> (c * 8)) & 0xFF) == '\0'
								&& i != 59 && selectedEntity[0]->skill[i + 1] != 0 )
							{
								// don't add '\0' termination unless the next skill slot is empty as we have more data to read.
							}
							else
							{
								buf[totalChars] = static_cast<char>((selectedEntity[0]->skill[i] >> (c * 8)) & 0xFF);
								++totalChars;
							}
						}
					}
				}
				if ( buf[totalChars] != '\0' )
				{
					buf[totalChars] = '\0';
				}
				strncpy(spriteProperties[5], buf, 48);
				strncpy(spriteProperties[6], buf + 48, 48);
				strncpy(spriteProperties[7], buf + 96, 48);
				strncpy(spriteProperties[8], buf + 144, 48);
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 15;
				subx1 = xres / 2 - 200;
				subx2 = xres / 2 + 200;
				suby1 = yres / 2 - 180;
				suby2 = yres / 2 + 180;
				strcpy(subtext, "Decoration Model Properties:");
				break;
			}
			case 14:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->soundSourceToPlay));
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->soundSourceVolume));
				snprintf(spriteProperties[2], 2, "%d", static_cast<int>(selectedEntity[0]->soundSourceLatchOn));
				snprintf(spriteProperties[3], 5, "%d", static_cast<int>(selectedEntity[0]->soundSourceDelay));
				snprintf(spriteProperties[4], 2, "%d", static_cast<int>(selectedEntity[0]->soundSourceOrigin));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 18;
				subx1 = xres / 2 - 230;
				subx2 = xres / 2 + 230;
				suby1 = yres / 2 - 112;
				suby2 = yres / 2 + 112;
				strcpy(subtext, "Sound Source Properties:");
				break;
			case 15:
				snprintf(spriteProperties[0], 2, "%d", static_cast<int>(selectedEntity[0]->lightSourceAlwaysOn));
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->lightSourceBrightness));
				snprintf(spriteProperties[2], 2, "%d", static_cast<int>(selectedEntity[0]->lightSourceInvertPower));
				snprintf(spriteProperties[3], 2, "%d", static_cast<int>(selectedEntity[0]->lightSourceLatchOn));
				snprintf(spriteProperties[4], 3, "%d", static_cast<int>(selectedEntity[0]->lightSourceRadius));
				snprintf(spriteProperties[5], 2, "%d", static_cast<int>(selectedEntity[0]->lightSourceFlicker));
				snprintf(spriteProperties[6], 5, "%d", static_cast<int>(selectedEntity[0]->lightSourceDelay));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 19;
				subx1 = xres / 2 - 200;
				subx2 = xres / 2 + 200;
				suby1 = yres / 2 - 160;
				suby2 = yres / 2 + 160;
				strcpy(subtext, "Light Source Properties:");
				break;
			case 16:
			{
				Uint32 r = (Uint32)(selectedEntity[0]->textSourceColorRGB >> 16) & 0xFF;
				Uint32 g = (Uint32)(selectedEntity[0]->textSourceColorRGB >> 8) & 0xFF;
				Uint32 b = (Uint32)(selectedEntity[0]->textSourceColorRGB >> 0) & 0xFF;
				snprintf(spriteProperties[0], 4, "%d", r);
				snprintf(spriteProperties[1], 4, "%d", g);
				snprintf(spriteProperties[2], 4, "%d", b);
				char buf[256] = "";
				int totalChars = 0;
				for ( int i = 4; i < 60; ++i )
				{
					if ( selectedEntity[0]->skill[i] != 0 && i != 28 ) // skill[28] is circuit status.
					{
						for ( int c = 0; c < 4; ++c )
						{
							if ( static_cast<char>((selectedEntity[0]->skill[i] >> (c * 8)) & 0xFF) == '\0'
								&& i != 59 && selectedEntity[0]->skill[i + 1] != 0 )
							{
								// don't add '\0' termination unless the next skill slot is empty as we have more data to read.
							}
							else
							{
								buf[totalChars] = static_cast<char>((selectedEntity[0]->skill[i] >> (c * 8)) & 0xFF);
								++totalChars;
							}
						}
					}
				}
				if ( buf[totalChars] != '\0' )
				{
					buf[totalChars] = '\0';
				}
				strncpy(spriteProperties[3], buf, 48);
				strncpy(spriteProperties[4], buf + 48, 48);
				strncpy(spriteProperties[5], buf + 96, 48);
				strncpy(spriteProperties[6], buf + 144, 48);
				strncpy(spriteProperties[7], buf + 192, 48);
				snprintf(spriteProperties[8], 5, "%d", static_cast<int>(selectedEntity[0]->textSourceDelay));
				snprintf(spriteProperties[9], 2, "%d", static_cast<int>((selectedEntity[0]->textSourceVariables4W >> 8) & 0xFF));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 20;
				subx1 = xres / 2 - 200;
				subx2 = xres / 2 + 200;
				suby1 = yres / 2 - 140;
				suby2 = yres / 2 + 140;
				strcpy(subtext, "Text Source Properties:");
				break;
			}
			case 17:
				snprintf(spriteProperties[0], 2, "%d", static_cast<int>(selectedEntity[0]->signalInputDirection));
				snprintf(spriteProperties[1], 5, "%d", static_cast<int>(selectedEntity[0]->signalActivateDelay));
				snprintf(spriteProperties[2], 5, "%d", static_cast<int>(selectedEntity[0]->signalTimerInterval));
				snprintf(spriteProperties[3], 5, "%d", static_cast<int>(selectedEntity[0]->signalTimerRepeatCount));
				snprintf(spriteProperties[4], 2, "%d", static_cast<int>(selectedEntity[0]->signalTimerLatchInput));
				snprintf(spriteProperties[5], 2, "%d", static_cast<int>(selectedEntity[0]->signalInvertOutput));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 21;
				subx1 = xres / 2 - 220;
				subx2 = xres / 2 + 220;
				suby1 = yres / 2 - 120;
				suby2 = yres / 2 + 120;
				strcpy(subtext, "Signal Timer Properties:");
				break;
			case 18: // custom portal
			{
				snprintf(spriteProperties[0], 5, "%d", static_cast<int>(selectedEntity[0]->portalCustomSprite));
				snprintf(spriteProperties[1], 2, "%d", static_cast<int>(selectedEntity[0]->portalCustomSpriteAnimationFrames));
				snprintf(spriteProperties[2], 5, "%d", static_cast<int>(selectedEntity[0]->portalCustomZOffset));
				snprintf(spriteProperties[3], 3, "%d", static_cast<int>(selectedEntity[0]->portalCustomLevelsToJump));
				snprintf(spriteProperties[5], 2, "%d", static_cast<int>(selectedEntity[0]->portalCustomRequiresPower));
				snprintf(spriteProperties[6], 2, "%d", static_cast<int>((selectedEntity[0]->portalNotSecret ? 0 : 1)));

				char buf[64] = "";
				int totalChars = 0;
				for ( int i = 11; i <= 18; ++i )
				{
					if ( selectedEntity[0]->skill[i] != 0 && i != 28 ) // skill[28] is circuit status.
					{
						for ( int c = 0; c < 4; ++c )
						{
							if ( static_cast<char>((selectedEntity[0]->skill[i] >> (c * 8)) & 0xFF) == '\0'
								&& i != 18 && selectedEntity[0]->skill[i + 1] != 0 )
							{
								// don't add '\0' termination unless the next skill slot is empty as we have more data to read.
							}
							else
							{
								buf[totalChars] = static_cast<char>((selectedEntity[0]->skill[i] >> (c * 8)) & 0xFF);
								++totalChars;
							}
						}
					}
				}
				if ( buf[totalChars] != '\0' )
				{
					buf[totalChars] = '\0';
				}
				strncpy(spriteProperties[4], buf, 32);

				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 22;
				subx1 = xres / 2 - 220;
				subx2 = xres / 2 + 220;
				suby1 = yres / 2 - 140;
				suby2 = yres / 2 + 140;
				strcpy(subtext, "Custom Exit Properties:");
				break;
			}
			case 19: // tables
				snprintf(spriteProperties[0], 3, "%d", static_cast<int>(selectedEntity[0]->furnitureDir));
				snprintf(spriteProperties[1], 3, "%d", static_cast<int>(selectedEntity[0]->furnitureTableSpawnChairs));
				snprintf(spriteProperties[2], 4, "%d", static_cast<int>(selectedEntity[0]->furnitureTableRandomItemChance));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 23;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 100;
				suby2 = yres / 2 + 100;
				strcpy(subtext, "Table Properties:");
				break;
			case 20: // readablebook
			{
				snprintf(spriteProperties[0], 3, "%d", static_cast<int>(selectedEntity[0]->skill[11])); // status
				if ( (int)selectedEntity[0]->skill[12] == 10 )
				{
					strcpy(spriteProperties[1], "00"); //bless random
				}
				else
				{
					snprintf(spriteProperties[1], 3, "%d", static_cast<int>(selectedEntity[0]->skill[12])); //bless
				}
				snprintf(spriteProperties[2], 3, "%d", static_cast<int>(selectedEntity[0]->skill[15])); // identified
				char buf[64] = "";
				int totalChars = 0;
				for ( int i = 40; i <= 52; ++i )
				{
					if ( selectedEntity[0]->skill[i] != 0 && i != 28 ) // skill[28] is circuit status.
					{
						for ( int c = 0; c < 4; ++c )
						{
							if ( static_cast<char>((selectedEntity[0]->skill[i] >> (c * 8)) & 0xFF) == '\0'
								&& i != 52 && selectedEntity[0]->skill[i + 1] != 0 )
							{
								// don't add '\0' termination unless the next skill slot is empty as we have more data to read.
							}
							else
							{
								buf[totalChars] = static_cast<char>((selectedEntity[0]->skill[i] >> (c * 8)) & 0xFF);
								++totalChars;
							}
						}
					}
				}
				if ( buf[totalChars] != '\0' )
				{
					buf[totalChars] = '\0';
				}
				strncpy(spriteProperties[3], buf, 32);

				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 24;
				subx1 = xres / 2 - 220;
				subx2 = xres / 2 + 220;
				suby1 = yres / 2 - 110;
				suby2 = yres / 2 + 110;
				strcpy(subtext, "Readable Book Properties:");
			}
				break;
			case 21:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->doorForceLockedUnlocked));
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->doorDisableLockpicks));
				snprintf(spriteProperties[2], 4, "%d", static_cast<int>(selectedEntity[0]->doorDisableOpening));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 26;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 100;
				suby2 = yres / 2 + 100;
				strcpy(subtext, "Door Properties:");
				break;
			case 22:
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->gateDisableOpening));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 27;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 60;
				suby2 = yres / 2 + 60;
				strcpy(subtext, "Gate Properties:");
				break;
			case 23: // player spawn
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->playerStartDir));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 28;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 60;
				suby2 = yres / 2 + 60;
				strcpy(subtext, "Player Spawn Properties:");
				break;
			case 24: // statue
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->statueDir));
				snprintf(spriteProperties[1], 32, "%d", static_cast<int>(selectedEntity[0]->statueId));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 29;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 60;
				suby2 = yres / 2 + 60;
				strcpy(subtext, "Statue Properties:");
				break;
			case 25: // teleport shrine
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->shrineDir));
				snprintf(spriteProperties[1], 5, "%d", static_cast<int>(selectedEntity[0]->shrineZ));
				snprintf(spriteProperties[2], 5, "%d", static_cast<int>(selectedEntity[0]->shrineDestXOffset));
				snprintf(spriteProperties[3], 5, "%d", static_cast<int>(selectedEntity[0]->shrineDestYOffset));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 30;
				subx1 = xres / 2 - 220;
				subx2 = xres / 2 + 220;
				suby1 = yres / 2 - 90;
				suby2 = yres / 2 + 90;
				strcpy(subtext, "Teleport Shrine Properties:");
				break;
			case 26: // spell shrine
				snprintf(spriteProperties[0], 4, "%d", static_cast<int>(selectedEntity[0]->shrineDir));
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->shrineZ));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 30;
				subx1 = xres / 2 - 220;
				subx2 = xres / 2 + 220;
				suby1 = yres / 2 - 60;
				suby2 = yres / 2 + 60;
				strcpy(subtext, "Spell Shrine Properties:");
				break;
			case 27:
			{
				snprintf(spriteProperties[0], 5, "%d", static_cast<int>(selectedEntity[0]->colliderDecorationModel));
				snprintf(spriteProperties[1], 4, "%d", static_cast<int>(selectedEntity[0]->colliderDecorationRotation));
				snprintf(spriteProperties[2], 5, "%d", static_cast<int>(selectedEntity[0]->colliderDecorationHeightOffset));
				snprintf(spriteProperties[3], 5, "%d", static_cast<int>(selectedEntity[0]->colliderDecorationXOffset));
				snprintf(spriteProperties[4], 5, "%d", static_cast<int>(selectedEntity[0]->colliderDecorationYOffset));
				snprintf(spriteProperties[5], 5, "%d", static_cast<int>(selectedEntity[0]->colliderHasCollision));
				snprintf(spriteProperties[6], 4, "%d", static_cast<int>(selectedEntity[0]->colliderSizeX));
				snprintf(spriteProperties[7], 4, "%d", static_cast<int>(selectedEntity[0]->colliderSizeY));
				snprintf(spriteProperties[8], 5, "%d", static_cast<int>(selectedEntity[0]->colliderMaxHP));
				snprintf(spriteProperties[9], 4, "%d", static_cast<int>(selectedEntity[0]->colliderDiggable));
				snprintf(spriteProperties[10], 4, "%d", static_cast<int>(selectedEntity[0]->colliderDamageTypes));

				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 31;
				subx1 = xres / 2 - 200;
				subx2 = xres / 2 + 200;
				suby1 = yres / 2 - 220;
				suby2 = yres / 2 + 220;
				strcpy(subtext, "Collider Model Properties:");
				break;
			}
			case 28:
				snprintf(spriteProperties[0], 2, "%d", static_cast<int>(selectedEntity[0]->signalInputDirection));
				snprintf(spriteProperties[1], 5, "%d", static_cast<int>(selectedEntity[0]->signalActivateDelay));
				snprintf(spriteProperties[2], 5, "%d", static_cast<int>(selectedEntity[0]->signalTimerInterval));
				snprintf(spriteProperties[3], 5, "%d", static_cast<int>(selectedEntity[0]->signalTimerRepeatCount));
				snprintf(spriteProperties[4], 2, "%d", static_cast<int>(selectedEntity[0]->signalTimerLatchInput));
				snprintf(spriteProperties[5], 2, "%d", static_cast<int>(selectedEntity[0]->signalInvertOutput));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 32;
				subx1 = xres / 2 - 220;
				subx2 = xres / 2 + 220;
				suby1 = yres / 2 - 120;
				suby2 = yres / 2 + 120;
				strcpy(subtext, "AND Gate Properties:");
				break;
			case 29:
				snprintf(spriteProperties[0], 2, "%d", static_cast<int>(selectedEntity[0]->pressurePlateTriggerType));
				inputstr = spriteProperties[0];
				cursorflash = ticks;
				menuVisible = 0;
				subwindow = 1;
				newwindow = 33;
				subx1 = xres / 2 - 170;
				subx2 = xres / 2 + 170;
				suby1 = yres / 2 - 60;
				suby2 = yres / 2 + 60;
				strcpy(subtext, "Pressure Plate Properties:");
				break;
			default:
				strcpy(message, "No properties available for current sprite.");
				messagetime = 60;
			break;
		}

		//remaining buttons
		switch ( spriteType )
		{
			case 1: //monsters
				tmpSpriteStats = selectedEntity[0]->getStats();
				if ( tmpSpriteStats != nullptr )
				{

					butMonsterOK = newButton();
					strcpy(butMonsterOK->label, "  OK  ");
					butMonsterOK->x = subx2 - 64;
					butMonsterOK->y = suby2 - 48;
					butMonsterOK->sizex = 56;
					butMonsterOK->sizey = 16;
					butMonsterOK->action = &buttonSpritePropertiesConfirm;
					butMonsterOK->visible = 1;
					butMonsterOK->focused = 1;

					butMonsterCancel = newButton();
					strcpy(butMonsterCancel->label, "Cancel");
					butMonsterCancel->x = subx2 - 64;
					butMonsterCancel->y = suby2 - 24;
					butMonsterCancel->sizex = 56;
					butMonsterCancel->sizey = 16;
					butMonsterCancel->action = &buttonCloseSpriteSubwindow;
					butMonsterCancel->visible = 1;
					butMonsterCancel->focused = 1;

					butMonsterX = newButton();
					strcpy(butMonsterX->label, "X");
					butMonsterX->x = subx2 - 16;
					butMonsterX->y = suby1;
					butMonsterX->sizex = 16;
					butMonsterX->sizey = 16;
					butMonsterX->action = &buttonCloseSpriteSubwindow;
					butMonsterX->visible = 1;
					butMonsterX->focused = 1;

					pad_y2 = suby1 + 28 + 2 * spacing;
					pad_x3 = 40;
					pad_x4 = subx2 - 112;
					itemIndex = 0;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}

					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterHelm = newButton();
						strcpy(butMonsterHelm->label, tmpStr);
						butMonsterHelm->x = pad_x4 - 10;
						butMonsterHelm->y = pad_y2 + spacing - 4;
						butMonsterHelm->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterHelm->sizey = 16;
						butMonsterHelm->action = &buttonMonsterItems;
						butMonsterHelm->visible = 1;
						butMonsterHelm->focused = 1;
					}

					pad_y2 += spacing * 2;
					itemIndex = 6;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterAmulet = newButton();
						strcpy(butMonsterAmulet->label, tmpStr);
						butMonsterAmulet->x = pad_x4 - 10;
						butMonsterAmulet->y = pad_y2 + spacing - 4;
						butMonsterAmulet->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterAmulet->sizey = 16;
						butMonsterAmulet->action = &buttonMonsterItems;
						butMonsterAmulet->visible = 1;
						butMonsterAmulet->focused = 1;
					}

					pad_y2 += spacing * 2;
					itemIndex = 3;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterArmor = newButton();
						strcpy(butMonsterArmor->label, tmpStr);
						butMonsterArmor->x = pad_x4 - 10;
						butMonsterArmor->y = pad_y2 + spacing - 4;
						butMonsterArmor->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterArmor->sizey = 16;
						butMonsterArmor->action = &buttonMonsterItems;
						butMonsterArmor->visible = 1;
						butMonsterArmor->focused = 1;
					}

					pad_y2 += spacing * 2;
					itemIndex = 4;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterBoots = newButton();
						strcpy(butMonsterBoots->label, tmpStr);
						butMonsterBoots->x = pad_x4 - 10;
						butMonsterBoots->y = pad_y2 + spacing - 4;
						butMonsterBoots->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterBoots->sizey = 16;
						butMonsterBoots->action = &buttonMonsterItems;
						butMonsterBoots->visible = 1;
						butMonsterBoots->focused = 1;
					}

					pad_y2 = suby1 + 28 + 2 * spacing; //reset y coord
					pad_y2 += 16;
					pad_x4 -= 64;
					itemIndex = 7;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}

					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterCloak = newButton();
						strcpy(butMonsterCloak->label, tmpStr);
						butMonsterCloak->x = pad_x4 - 10;
						butMonsterCloak->y = pad_y2 + spacing - 4;
						butMonsterCloak->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterCloak->sizey = 16;
						butMonsterCloak->action = &buttonMonsterItems;
						butMonsterCloak->visible = 1;
						butMonsterCloak->focused = 1;
					}
					
					pad_x4 += 64 * 2;
					itemIndex = 8;

					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}

					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterMask = newButton();
						strcpy(butMonsterMask->label, tmpStr);
						butMonsterMask->x = pad_x4 - 10;
						butMonsterMask->y = pad_y2 + spacing - 4;
						butMonsterMask->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterMask->sizey = 16;
						butMonsterMask->action = &buttonMonsterItems;
						butMonsterMask->visible = 1;
						butMonsterMask->focused = 1;
					}

					pad_y2 += spacing * 2;
					itemIndex = 2;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterShield = newButton();
						strcpy(butMonsterShield->label, tmpStr);
						butMonsterShield->x = pad_x4 - 10;
						butMonsterShield->y = pad_y2 + spacing - 4;
						butMonsterShield->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterShield->sizey = 16;
						butMonsterShield->action = &buttonMonsterItems;
						butMonsterShield->visible = 1;
						butMonsterShield->focused = 1;
					}

					pad_x4 -= 64 * 2;
					itemIndex = 1;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterWeapon = newButton();
						strcpy(butMonsterWeapon->label, tmpStr);
						butMonsterWeapon->x = pad_x4 - 10;
						butMonsterWeapon->y = pad_y2 + spacing - 4;
						butMonsterWeapon->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterWeapon->sizey = 16;
						butMonsterWeapon->action = &buttonMonsterItems;
						butMonsterWeapon->visible = 1;
						butMonsterWeapon->focused = 1;
					}

					pad_y2 += spacing * 2;
					itemIndex = 5;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}

					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterRing = newButton();
						strcpy(butMonsterRing->label, tmpStr);
						butMonsterRing->x = pad_x4 - 10;
						butMonsterRing->y = pad_y2 + spacing - 4;
						butMonsterRing->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterRing->sizey = 16;
						butMonsterRing->action = &buttonMonsterItems;
						butMonsterRing->visible = 1;
						butMonsterRing->focused = 1;
					}
					pad_x4 += 64 * 2;
					itemIndex = 9;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					if ( canWearEquip(selectedEntity[0], itemIndex) )
					{
						butMonsterGloves = newButton();
						strcpy(butMonsterGloves->label, tmpStr);
						butMonsterGloves->x = pad_x4 - 10;
						butMonsterGloves->y = pad_y2 + spacing - 4;
						butMonsterGloves->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
						butMonsterGloves->sizey = 16;
						butMonsterGloves->action = &buttonMonsterItems;
						butMonsterGloves->visible = 1;
						butMonsterGloves->focused = 1;
					}
					
					pad_y2 += 32 + spacing * 2;
					itemIndex = 12;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					butMonsterItem3 = newButton();
					strcpy(butMonsterItem3->label, tmpStr);
					butMonsterItem3->x = pad_x4 - 10;
					butMonsterItem3->y = pad_y2 + spacing - 4;
					butMonsterItem3->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
					butMonsterItem3->sizey = 16;
					butMonsterItem3->action = &buttonMonsterItems;
					butMonsterItem3->visible = 1;
					butMonsterItem3->focused = 1;

					itemIndex = 15;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					butMonsterItem6 = newButton();
					strcpy(butMonsterItem6->label, tmpStr);
					butMonsterItem6->x = pad_x4 - 10;
					butMonsterItem6->y = pad_y2 + 2 * spacing - 4;
					butMonsterItem6->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
					butMonsterItem6->sizey = 16;
					butMonsterItem6->action = &buttonMonsterItems;
					butMonsterItem6->visible = 1;
					butMonsterItem6->focused = 1;

					pad_x4 -= 64;
					itemIndex = 11;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					butMonsterItem2 = newButton();
					strcpy(butMonsterItem2->label, tmpStr);
					butMonsterItem2->x = pad_x4 - 10;
					butMonsterItem2->y = pad_y2 + spacing - 4;
					butMonsterItem2->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
					butMonsterItem2->sizey = 16;
					butMonsterItem2->action = &buttonMonsterItems;
					butMonsterItem2->visible = 1;
					butMonsterItem2->focused = 1;

					itemIndex = 14;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					butMonsterItem5 = newButton();
					strcpy(butMonsterItem5->label, tmpStr);
					butMonsterItem5->x = pad_x4 - 10;
					butMonsterItem5->y = pad_y2 + 2 * spacing - 4;
					butMonsterItem5->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
					butMonsterItem5->sizey = 16;
					butMonsterItem5->action = &buttonMonsterItems;
					butMonsterItem5->visible = 1;
					butMonsterItem5->focused = 1;

					pad_x4 -= 64;
					itemIndex = 10;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					}
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					butMonsterItem1 = newButton();
					strcpy(butMonsterItem1->label, tmpStr);
					butMonsterItem1->x = pad_x4 - 10;
					butMonsterItem1->y = pad_y2 + spacing - 4;
					butMonsterItem1->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
					butMonsterItem1->sizey = 16;
					butMonsterItem1->action = &buttonMonsterItems;
					butMonsterItem1->visible = 1;
					butMonsterItem1->focused = 1;

					itemIndex = 13;
					if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 0 )
					{
						strcpy(tmpStr, "NULL");
					} 
					else if ( tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES] == 1 )
					{
						strcpy(tmpStr, "RAND");
					}
					else
					{
						snprintf(tmpStr, 4, "%d", tmpSpriteStats->EDITOR_ITEMS[itemIndex * ITEM_SLOT_NUMPROPERTIES]);
					}
					butMonsterItem4 = newButton();
					strcpy(butMonsterItem4->label, tmpStr);
					butMonsterItem4->x = pad_x4 - 10;
					butMonsterItem4->y = pad_y2 + 2 * spacing - 4;
					butMonsterItem4->sizex = pad_x4 + pad_x3 - (pad_x4 - 10);
					butMonsterItem4->sizey = 16;
					butMonsterItem4->action = &buttonMonsterItems;
					butMonsterItem4->visible = 1;
					butMonsterItem4->focused = 1;
				}
				break;
			case 3: //items
				butItemOK = newButton();
				strcpy(butItemOK->label, "  OK  ");
				butItemOK->x = subx2 - 128;
				butItemOK->y = suby2 - 24;
				butItemOK->sizex = 56;
				butItemOK->sizey = 16;
				butItemOK->action = &buttonSpritePropertiesConfirm;
				butItemOK->visible = 1;
				butItemOK->focused = 1;

				butItemCancel = newButton();
				strcpy(butItemCancel->label, "Cancel");
				butItemCancel->x = subx2 - 64;
				butItemCancel->y = suby2 - 24;
				butItemCancel->sizex = 56;
				butItemCancel->sizey = 16;
				butItemCancel->action = &buttonCloseSpriteSubwindow;
				butItemCancel->visible = 1;
				butItemCancel->focused = 1;

				butItemX = newButton();
				strcpy(butItemX->label, "X");
				butItemX->x = subx2 - 16;
				butItemX->y = suby1;
				butItemX->sizex = 16;
				butItemX->sizey = 16;
				butItemX->action = &buttonCloseSpriteSubwindow;
				butItemX->visible = 1;
				butItemX->focused = 1;
				break;
			default:
				button = newButton();
				strcpy(button->label, "  OK  ");
				button->x = subx2 - 64;
				button->y = suby2 - 48;
				button->sizex = 56;
				button->sizey = 16;
				button->action = &buttonSpritePropertiesConfirm;
				button->visible = 1;
				button->focused = 1;
				break;
		}

		if ( spriteType != 1 && spriteType != 3 )
		{
			button = newButton();
			strcpy(button->label, "Cancel");
			button->x = subx2 - 64;
			button->y = suby2 - 24;
			button->sizex = 56;
			button->sizey = 16;
			button->action = &buttonCloseSpriteSubwindow;
			button->visible = 1;
			button->focused = 1;

			button = newButton();
			strcpy(button->label, "X");
			button->x = subx2 - 16;
			button->y = suby1;
			button->sizex = 16;
			button->sizey = 16;
			button->action = &buttonCloseSpriteSubwindow;
			button->visible = 1;
			button->focused = 1;
		}
	}
}

void buttonSpritePropertiesConfirm(button_t* my)
{
	Stat* tmpSpriteStats = NULL;
	button_t* button = NULL;
	if ( selectedEntity[0] != NULL )
	{
		int spriteType = checkSpriteType(selectedEntity[0]->sprite);
		switch ( spriteType )
		{
			case 1: //monsters
				tmpSpriteStats = selectedEntity[0]->getStats();
				if ( tmpSpriteStats != nullptr )
				{
					if ( my == butMonsterItemOK )
					{
						if ( strcmp(spriteProperties[0], "0") < 0 )
						{
							strcpy(spriteProperties[0], "1");
						}
						tmpSpriteStats->EDITOR_ITEMS[(itemSlotSelected)* ITEM_SLOT_NUMPROPERTIES] = (Sint32)atoi(spriteProperties[0]);
						tmpSpriteStats->EDITOR_ITEMS[(itemSlotSelected)* ITEM_SLOT_NUMPROPERTIES + 1] = (Sint32)atoi(spriteProperties[1]);
						if ( strcmp(spriteProperties[2], "00") == 0 )
						{
							selectedEntity[0]->skill[12] = 10; //bless random
						}
						else
						{
							tmpSpriteStats->EDITOR_ITEMS[(itemSlotSelected)* ITEM_SLOT_NUMPROPERTIES + 2] = (Sint32)atoi(spriteProperties[2]); //bless
						}
						if ( strcmp(spriteProperties[3], "0") == 0 )
						{
							tmpSpriteStats->EDITOR_ITEMS[(itemSlotSelected)* ITEM_SLOT_NUMPROPERTIES + 2] = 1; //reset quantity to 1
						}
						if ( strcmp(spriteProperties[3], "0") == 0 )
						{
							tmpSpriteStats->EDITOR_ITEMS[(itemSlotSelected)* ITEM_SLOT_NUMPROPERTIES + 3] = 1; //reset quantity to 1
						}
						else
						{
							tmpSpriteStats->EDITOR_ITEMS[(itemSlotSelected)* ITEM_SLOT_NUMPROPERTIES + 3] = (Sint32)atoi(spriteProperties[3]); //quantity
						}
						tmpSpriteStats->EDITOR_ITEMS[(itemSlotSelected)* ITEM_SLOT_NUMPROPERTIES + 4] = (Sint32)atoi(spriteProperties[4]);
						tmpSpriteStats->EDITOR_ITEMS[(itemSlotSelected)* ITEM_SLOT_NUMPROPERTIES + 5] = (Sint32)atoi(spriteProperties[5]);
						tmpSpriteStats->EDITOR_ITEMS[(itemSlotSelected)* ITEM_SLOT_NUMPROPERTIES + 6] = (Sint32)atoi(spriteProperties[6]);
						newwindow = 2;

						/*button = newButton();
						strcpy(button->label, "Cancel");
						button->x = subx2 - 64;
						button->y = suby2 - 24;
						button->sizex = 56;
						button->sizey = 16;
						button->action = &buttonCloseSpriteSubwindow;
						button->visible = 1;
						button->focused = 1;

						button = newButton();
						strcpy(button->label, "X");
						button->x = subx2 - 16;
						button->y = suby1;
						button->sizex = 16;
						button->sizey = 16;
						button->action = &buttonCloseSpriteSubwindow;
						button->visible = 1;
						button->focused = 1;

						button = newButton();
						strcpy(button->label, "  OK  ");
						button->x = subx2 - 64;
						button->y = suby2 - 48;
						button->sizex = 56;
						button->sizey = 16;
						button->action = &buttonSpritePropertiesConfirm;
						button->visible = 1;
						button->focused = 1;*/

						//butItemOK->visible = 0;
						//butItemCancel->visible = 0;
						//butItemX->visible = 0;
						if ( butMonsterItemOK != NULL )
						{
							butMonsterItemOK->visible = 0;
						}
						if ( butMonsterItemX != NULL )
						{
							butMonsterItemX->visible = 0;
						}
						if ( butMonsterItemCancel != NULL )
						{
							butMonsterItemCancel->visible = 0;
						}

						// retrieves any modified monster stats, restored when window is closed.

						for ( int i = 0; i < sizeof(spriteProperties) / sizeof(spriteProperties[0]); i++ )
						{
							strcpy(spriteProperties[i], tmpSpriteProperties[i]);
						}
					}
					else
					{
						strcpy(tmpSpriteStats->name, spriteProperties[0]);
						tmpSpriteStats->MAXHP = (Sint32)atoi(spriteProperties[1]);
						tmpSpriteStats->HP = (Sint32)atoi(spriteProperties[2]);
						tmpSpriteStats->MAXMP = (Sint32)atoi(spriteProperties[3]);
						tmpSpriteStats->MP = (Sint32)atoi(spriteProperties[4]);
						tmpSpriteStats->LVL = (Sint32)atoi(spriteProperties[5]);
						tmpSpriteStats->GOLD = (Sint32)atoi(spriteProperties[6]);
						tmpSpriteStats->STR = (Sint32)atoi(spriteProperties[7]);
						tmpSpriteStats->DEX = (Sint32)atoi(spriteProperties[8]);
						tmpSpriteStats->CON = (Sint32)atoi(spriteProperties[9]);
						tmpSpriteStats->INT = (Sint32)atoi(spriteProperties[10]);
						tmpSpriteStats->PER = (Sint32)atoi(spriteProperties[11]);
						tmpSpriteStats->CHR = (Sint32)atoi(spriteProperties[12]);

						tmpSpriteStats->RANDOM_MAXHP = (Sint32)atoi(spriteProperties[13]) - tmpSpriteStats->MAXHP;
						if ( tmpSpriteStats->RANDOM_MAXHP < 0 )
						{
							tmpSpriteStats->RANDOM_MAXHP = 0;
						}
						tmpSpriteStats->RANDOM_HP = (Sint32)atoi(spriteProperties[14]) - tmpSpriteStats->HP;
						if ( tmpSpriteStats->RANDOM_HP < 0 )
						{
							tmpSpriteStats->RANDOM_HP = 0;
						}
						tmpSpriteStats->RANDOM_MAXMP = (Sint32)atoi(spriteProperties[15]) - tmpSpriteStats->MAXMP;
						if ( tmpSpriteStats->RANDOM_MAXMP < 0 )
						{
							tmpSpriteStats->RANDOM_MAXMP = 0;
						}
						tmpSpriteStats->RANDOM_MP = (Sint32)atoi(spriteProperties[16]) - tmpSpriteStats->MP;
						if ( tmpSpriteStats->RANDOM_MP < 0 )
						{
							tmpSpriteStats->RANDOM_MP = 0;
						}
						tmpSpriteStats->RANDOM_LVL = (Sint32)atoi(spriteProperties[17]) - tmpSpriteStats->LVL;
						if ( tmpSpriteStats->RANDOM_LVL < 0 )
						{
							tmpSpriteStats->RANDOM_LVL = 0;
						}
						tmpSpriteStats->RANDOM_GOLD = (Sint32)atoi(spriteProperties[18]) - tmpSpriteStats->GOLD;
						if ( tmpSpriteStats->RANDOM_GOLD < 0 )
						{
							tmpSpriteStats->RANDOM_GOLD = 0;
						}
						tmpSpriteStats->RANDOM_STR = (Sint32)atoi(spriteProperties[19]) - tmpSpriteStats->STR;
						if ( tmpSpriteStats->RANDOM_STR < 0 )
						{
							tmpSpriteStats->RANDOM_STR = 0;
						}
						tmpSpriteStats->RANDOM_DEX = (Sint32)atoi(spriteProperties[20]) - tmpSpriteStats->DEX;
						if ( tmpSpriteStats->RANDOM_DEX < 0 )
						{
							tmpSpriteStats->RANDOM_DEX = 0;
						}
						tmpSpriteStats->RANDOM_CON = (Sint32)atoi(spriteProperties[21]) - tmpSpriteStats->CON;
						if ( tmpSpriteStats->RANDOM_CON < 0 )
						{
							tmpSpriteStats->RANDOM_CON = 0;
						}
						tmpSpriteStats->RANDOM_INT = (Sint32)atoi(spriteProperties[22]) - tmpSpriteStats->INT;
						if ( tmpSpriteStats->RANDOM_INT < 0 )
						{
							tmpSpriteStats->RANDOM_INT = 0;
						}
						tmpSpriteStats->RANDOM_PER = (Sint32)atoi(spriteProperties[23]) - tmpSpriteStats->PER;
						if ( tmpSpriteStats->RANDOM_PER < 0 )
						{
							tmpSpriteStats->RANDOM_PER = 0;
						}
						tmpSpriteStats->RANDOM_CHR = (Sint32)atoi(spriteProperties[24]) - tmpSpriteStats->CHR;
						if ( tmpSpriteStats->RANDOM_CHR < 0 )
						{
							tmpSpriteStats->RANDOM_CHR = 0;
						}
						tmpSpriteStats->MISC_FLAGS[STAT_FLAG_NPC] = (Sint32)atoi(spriteProperties[25]);
						if ( !strcmp(spriteProperties[31], "disable") )
						{
							tmpSpriteStats->MISC_FLAGS[STAT_FLAG_DISABLE_MINIBOSS] = 1;
						}
						else
						{
							tmpSpriteStats->MISC_FLAGS[STAT_FLAG_DISABLE_MINIBOSS] = 0;
						}
					}
				}
				break;
			case 2: //chest
				selectedEntity[0]->yaw = (real_t)atoi(spriteProperties[0]);
				selectedEntity[0]->skill[9] = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->chestLocked = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->chestMimicChance = (Sint32)atoi(spriteProperties[3]);
				break;
			case 3: //items
				if ( strcmp(spriteProperties[0], "0") == 0 )
				{
					strcpy(spriteProperties[0], "1");
				}
				selectedEntity[0]->skill[10] = (Sint32)atoi(spriteProperties[0]); //id
				selectedEntity[0]->skill[11] = (Sint32)atoi(spriteProperties[1]); //status
				if ( strcmp(spriteProperties[2], "00") == 0 )
				{
					selectedEntity[0]->skill[12] = 10; //bless random
				}
				else
				{
					selectedEntity[0]->skill[12] = (Sint32)atoi(spriteProperties[2]); //bless
				}
				if ( strcmp(spriteProperties[3], "0") == 0 )
				{
					selectedEntity[0]->skill[13] = 1; //reset quantity to 1
				}
				else
				{
					selectedEntity[0]->skill[13] = (Sint32)atoi(spriteProperties[3]); //quantity
				}
				selectedEntity[0]->skill[15] = (Sint32)atoi(spriteProperties[4]); //identified
				selectedEntity[0]->skill[16] = (Sint32)atoi(spriteProperties[5]); //cateogry if random
				break;
			case 4: //summoning traps
				if ( (Sint32)atoi(spriteProperties[0]) < -1 || (Sint32)atoi(spriteProperties[0]) == 6
					|| (Sint32)atoi(spriteProperties[0]) == 12 )
				{
					selectedEntity[0]->skill[0] = 0;
				}
				else
				{
					selectedEntity[0]->skill[0] = (Sint32)atoi(spriteProperties[0]); //Monster to Spawn
				}

				if ( (Sint32)atoi(spriteProperties[1]) == 0 )
				{
					selectedEntity[0]->skill[1] = 1;
				}
				else
				{
					selectedEntity[0]->skill[1] = (Sint32)atoi(spriteProperties[1]); //Qty
				}

				if ( (Sint32)atoi(spriteProperties[2]) == 0 )
				{
					selectedEntity[0]->skill[2] = 1;
				}
				else
				{
					selectedEntity[0]->skill[2] = (Sint32)atoi(spriteProperties[2]); //Time Between Spawns
				}

				if ( (Sint32)atoi(spriteProperties[3]) == 0 )
				{
					selectedEntity[0]->skill[3] = 1;
				}
				else
				{
					selectedEntity[0]->skill[3] = (Sint32)atoi(spriteProperties[3]); //Amount of Spawns 
				}
				selectedEntity[0]->skill[4] = (Sint32)atoi(spriteProperties[4]); //Requires Power
				selectedEntity[0]->skill[5] = (Sint32)atoi(spriteProperties[5]); //Chance to Stop Working
				selectedEntity[0]->skill[9] = (Sint32)atoi(spriteProperties[6]); //Autospawn
				break;
			case 5: //power crystal
				selectedEntity[0]->yaw = (real_t)atoi(spriteProperties[0]);
				selectedEntity[0]->crystalNumElectricityNodes = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->crystalTurnReverse = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->crystalSpellToActivate = (Sint32)atoi(spriteProperties[3]);
				break;
			case 6: //lever timer
				if ( (Sint32)atoi(spriteProperties[0]) == 0 )
				{
					selectedEntity[0]->leverTimerTicks = 1;
				}
				else
				{
					selectedEntity[0]->leverTimerTicks = (Sint32)atoi(spriteProperties[0]);
				}
				break;
			case 7: //boulder trap
				selectedEntity[0]->boulderTrapRefireAmount = (Sint32)atoi(spriteProperties[0]);
				if ( (Sint32)atoi(spriteProperties[1]) < 2 )
				{
					selectedEntity[0]->boulderTrapRefireDelay = 2;
				}
				else
				{
					selectedEntity[0]->boulderTrapRefireDelay = (Sint32)atoi(spriteProperties[1]);
				}
				if ( (Sint32)atoi(spriteProperties[2]) < 0 )
				{
					selectedEntity[0]->boulderTrapPreDelay = 0;
				}
				else
				{
					selectedEntity[0]->boulderTrapPreDelay = (Sint32)atoi(spriteProperties[2]);
				}
				break;
			case 8: //pedestal
				selectedEntity[0]->pedestalOrbType = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->pedestalHasOrb = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->pedestalInvertedPower = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->pedestalInGround = (Sint32)atoi(spriteProperties[3]);
				selectedEntity[0]->pedestalLockOrb = (Sint32)atoi(spriteProperties[4]);
				break;
			case 9: //teleporter
				selectedEntity[0]->teleporterX = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->teleporterY = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->teleporterType = (Sint32)atoi(spriteProperties[2]);
				break;
			case 10: //ceiling tile model
				selectedEntity[0]->ceilingTileModel = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->ceilingTileDir = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->ceilingTileAllowTrap = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->ceilingTileBreakable = (Sint32)atoi(spriteProperties[3]);
				break;
			case 11: //spell trap ceiling
				selectedEntity[0]->spellTrapType = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->spellTrapRefire = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->spellTrapLatchPower = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->spellTrapFloorTile = (Sint32)atoi(spriteProperties[3]);
				selectedEntity[0]->spellTrapRefireRate = (Sint32)atoi(spriteProperties[4]);
				break;
			case 12: //furniture
				selectedEntity[0]->furnitureDir = (Sint32)atoi(spriteProperties[0]);
				break;
			case 13: //floor decoration
			{
				selectedEntity[0]->floorDecorationModel = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->floorDecorationRotation = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->floorDecorationHeightOffset = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->floorDecorationXOffset = (Sint32)atoi(spriteProperties[3]);
				selectedEntity[0]->floorDecorationYOffset = (Sint32)atoi(spriteProperties[4]);

				int totalChars = 0;
				char checkChr = 'a';
				const int kMaxCharacters = 192; // 4x48 char fields.
				for ( int i = 8; i < 60 && totalChars < kMaxCharacters; ++i )
				{
					selectedEntity[0]->skill[i] = 0;
				}
				for ( int i = 8; i < 60 && totalChars < kMaxCharacters; ++i )
				{
					if ( i == 28 ) // circuit_status
					{
						continue;
					}
					for ( int c = 0; c < 4; ++c )
					{
						if ( totalChars >= 144 )
						{
							selectedEntity[0]->skill[i] |= (spriteProperties[8][totalChars - 144]) << (c * 8);
							checkChr = spriteProperties[8][totalChars - 144];
						}
						else if ( totalChars >= 96 )
						{
							selectedEntity[0]->skill[i] |= (spriteProperties[7][totalChars - 96]) << (c * 8);
							checkChr = spriteProperties[7][totalChars - 96];
						}
						else if ( totalChars >= 48 )
						{
							selectedEntity[0]->skill[i] |= (spriteProperties[6][totalChars - 48]) << (c * 8);
							checkChr = spriteProperties[6][totalChars - 48];
						}
						else
						{
							selectedEntity[0]->skill[i] |= (spriteProperties[5][totalChars]) << (c * 8);
							checkChr = spriteProperties[5][totalChars];
						}
						if ( checkChr == '\0' )
						{
							totalChars += (48 - (totalChars % 48));
						}
						else
						{
							++totalChars;
						}
					}
				}
			}
				break;
			case 14: //sound source
				selectedEntity[0]->soundSourceToPlay = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->soundSourceVolume = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->soundSourceLatchOn = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->soundSourceDelay = (Sint32)atoi(spriteProperties[3]);
				selectedEntity[0]->soundSourceOrigin = (Sint32)atoi(spriteProperties[4]);
				break;
			case 15: //light source
				selectedEntity[0]->lightSourceAlwaysOn = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->lightSourceBrightness = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->lightSourceInvertPower = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->lightSourceLatchOn = (Sint32)atoi(spriteProperties[3]);
				selectedEntity[0]->lightSourceRadius = (Sint32)atoi(spriteProperties[4]);
				selectedEntity[0]->lightSourceFlicker = (Sint32)atoi(spriteProperties[5]);
				selectedEntity[0]->lightSourceDelay = (Sint32)atoi(spriteProperties[6]);
				break;
			case 16: // text source
			{
				Uint32 r = (Uint32)atoi(spriteProperties[0]);
				Uint32 g = (Uint32)atoi(spriteProperties[1]);
				Uint32 b = (Uint32)atoi(spriteProperties[2]);
				selectedEntity[0]->textSourceColorRGB = 0;
				selectedEntity[0]->textSourceColorRGB |= (r << 16);
				selectedEntity[0]->textSourceColorRGB |= (g << 8);
				selectedEntity[0]->textSourceColorRGB |= (b << 0);
				selectedEntity[0]->textSourceDelay = (Sint32)atoi(spriteProperties[8]);
				selectedEntity[0]->textSourceVariables4W = 0;
				selectedEntity[0]->textSourceVariables4W |= ((Sint32)atoi(spriteProperties[9]) & 0xFF) << 8;
				int totalChars = 0;
				char checkChr = 'a';
				const int kMaxCharacters = 220; //55 skills, starting at 4 ending at 59, skipping 28. storing 4 chars each.
				for ( int i = 4; i < 60 && totalChars < kMaxCharacters; ++i )
				{
					selectedEntity[0]->skill[i] = 0;
				}
				for ( int i = 4; i < 60 && totalChars < kMaxCharacters; ++i )
				{
					if ( i == 28 ) // circuit_status
					{
						continue;
					}
					for ( int c = 0; c < 4; ++c )
					{
						if ( totalChars >= 192 )
						{
							selectedEntity[0]->skill[i] |= (spriteProperties[7][totalChars - 192]) << (c * 8);
							checkChr = spriteProperties[7][totalChars - 192];
						}
						else if ( totalChars >= 144 )
						{
							selectedEntity[0]->skill[i] |= (spriteProperties[6][totalChars - 144]) << (c * 8);
							checkChr = spriteProperties[6][totalChars - 144];
						}
						else if ( totalChars >= 96 )
						{
							selectedEntity[0]->skill[i] |= (spriteProperties[5][totalChars - 96]) << (c * 8);
							checkChr = spriteProperties[5][totalChars - 96];
						}
						else if ( totalChars >= 48 )
						{
							selectedEntity[0]->skill[i] |= (spriteProperties[4][totalChars - 48]) << (c * 8);
							checkChr = spriteProperties[4][totalChars - 48];
						}
						else
						{
							selectedEntity[0]->skill[i] |= (spriteProperties[3][totalChars]) << (c * 8);
							checkChr = spriteProperties[3][totalChars];
						}
						if ( checkChr == '\0' )
						{
							totalChars += (48 - (totalChars % 48));
						}
						else
						{
							++totalChars;
						}
					}
				}
				break;
			}
			case 17:
				selectedEntity[0]->signalInputDirection = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->signalActivateDelay = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->signalTimerInterval = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->signalTimerRepeatCount = (Sint32)atoi(spriteProperties[3]);
				selectedEntity[0]->signalTimerLatchInput = (Sint32)atoi(spriteProperties[4]);
				selectedEntity[0]->signalInvertOutput = (Sint32)atoi(spriteProperties[5]);
				break;
			case 18: // custom portal
			{
				selectedEntity[0]->portalCustomSprite = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->portalCustomSpriteAnimationFrames = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->portalCustomZOffset = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->portalCustomLevelsToJump = (Sint32)atoi(spriteProperties[3]);
				selectedEntity[0]->portalCustomRequiresPower = (Sint32)atoi(spriteProperties[5]);
				int isSecret = (Sint32)atoi(spriteProperties[6]);
				selectedEntity[0]->portalNotSecret = isSecret ? 0 : 1;

				int totalChars = 0;
				char checkChr = 'a';
				const int kMaxCharacters = 32;
				for ( int i = 11; i <= 18 && totalChars < kMaxCharacters; ++i )
				{
					selectedEntity[0]->skill[i] = 0;
				}
				for ( int i = 11; i <= 18 && totalChars < kMaxCharacters; ++i )
				{
					if ( i == 28 ) // circuit_status
					{
						continue;
					}
					for ( int c = 0; c < 4; ++c )
					{
						selectedEntity[0]->skill[i] |= (spriteProperties[4][totalChars]) << (c * 8);
						checkChr = spriteProperties[4][totalChars];
						++totalChars;
					}
				}
			}
				break;
			case 19: // tables
				selectedEntity[0]->furnitureDir = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->furnitureTableSpawnChairs = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->furnitureTableRandomItemChance = (Sint32)atoi(spriteProperties[2]);
				break;
			case 20: // readablebook
			{
				selectedEntity[0]->skill[11] = (Sint32)atoi(spriteProperties[0]); // status
				if ( strcmp(spriteProperties[1], "00") == 0 )
				{
					selectedEntity[0]->skill[12] = 10; //bless random
				}
				else
				{
					selectedEntity[0]->skill[12] = (Sint32)atoi(spriteProperties[1]); //bless
				}
				selectedEntity[0]->skill[15] = (Sint32)atoi(spriteProperties[2]); // identified
				int totalChars = 0;
				char checkChr = 'a';
				const int kMaxCharacters = 48;
				for ( int i = 40; i <= 52 && totalChars < kMaxCharacters; ++i )
				{
					selectedEntity[0]->skill[i] = 0;
				}
				for ( int i = 40; i <= 52 && totalChars < kMaxCharacters; ++i )
				{
					if ( i == 28 ) // circuit_status
					{
						continue;
					}
					for ( int c = 0; c < 4; ++c )
					{
						selectedEntity[0]->skill[i] |= (spriteProperties[3][totalChars]) << (c * 8);
						checkChr = spriteProperties[3][totalChars];
						++totalChars;
					}
				}
			}
				break;
			case 21: // doors
				selectedEntity[0]->doorForceLockedUnlocked = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->doorDisableLockpicks = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->doorDisableOpening = (Sint32)atoi(spriteProperties[2]);
				break;
			case 22: // gates
				selectedEntity[0]->gateDisableOpening = (Sint32)atoi(spriteProperties[0]);
				break;
			case 23: // player spawn
				selectedEntity[0]->playerStartDir = (Sint32)atoi(spriteProperties[0]);
				break;
			case 24: // statue
				selectedEntity[0]->statueDir = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->statueId = (Sint32)atoi(spriteProperties[1]);
				break;
			case 25: // teleport shrine
				selectedEntity[0]->shrineDir = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->shrineZ = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->shrineDestXOffset = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->shrineDestYOffset = (Sint32)atoi(spriteProperties[3]);
				break;
			case 26: // spell shrine
				selectedEntity[0]->shrineDir = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->shrineZ = (Sint32)atoi(spriteProperties[1]);
				break;
			case 27:
				selectedEntity[0]->colliderDecorationModel = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->colliderDecorationRotation = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->colliderDecorationHeightOffset = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->colliderDecorationXOffset = (Sint32)atoi(spriteProperties[3]);
				selectedEntity[0]->colliderDecorationYOffset = (Sint32)atoi(spriteProperties[4]);
				selectedEntity[0]->colliderHasCollision = (Sint32)atoi(spriteProperties[5]);
				selectedEntity[0]->colliderSizeX = (Sint32)atoi(spriteProperties[6]);
				selectedEntity[0]->colliderSizeY = (Sint32)atoi(spriteProperties[7]);
				selectedEntity[0]->colliderMaxHP = (Sint32)atoi(spriteProperties[8]);
				selectedEntity[0]->colliderDiggable = (Sint32)atoi(spriteProperties[9]);
				selectedEntity[0]->colliderDamageTypes = (Sint32)atoi(spriteProperties[10]);
				break;
			case 28:
				selectedEntity[0]->signalInputDirection = (Sint32)atoi(spriteProperties[0]);
				selectedEntity[0]->signalActivateDelay = (Sint32)atoi(spriteProperties[1]);
				selectedEntity[0]->signalTimerInterval = (Sint32)atoi(spriteProperties[2]);
				selectedEntity[0]->signalTimerRepeatCount = (Sint32)atoi(spriteProperties[3]);
				selectedEntity[0]->signalTimerLatchInput = (Sint32)atoi(spriteProperties[4]);
				selectedEntity[0]->signalInvertOutput = (Sint32)atoi(spriteProperties[5]);
				break;
			case 29: // pressure plate
				selectedEntity[0]->pressurePlateTriggerType = (Sint32)atoi(spriteProperties[0]);
				break;
			default:
				break;
		}

		strcpy(message, "                 Modified sprite properties.");
		messagetime = 60;
	}

	if ( my == butMonsterItemOK && tmpSpriteStats != NULL )
	{
		//copyMonsterStatToPropertyStrings(tmpSpriteStats);
		exitFromItemWindow = true;
		inputstr = spriteProperties[0];
		initMonsterPropertiesWindow();

		buttonSpriteProperties(my);
		itemSlotSelected = -1;
	}
	else
	{
		if ( my == butMonsterOK )
		{
			makeUndo();
		}
		buttonCloseSpriteSubwindow(my);
	}
}

void buttonCloseSpriteSubwindow(button_t* my)
{
	Stat* tmpSpriteStats = NULL;
	// close window
	if ( my == butMonsterItemCancel || my == butMonsterItemX )
	{
		if ( selectedEntity[0] != NULL )
		{
			tmpSpriteStats = selectedEntity[0]->getStats();
		}
		if ( tmpSpriteStats != NULL )
		{
			//copyMonsterStatToPropertyStrings(tmpSpriteStats);
			exitFromItemWindow = true;
			inputstr = spriteProperties[0];
			initMonsterPropertiesWindow();

			buttonSpriteProperties(my);
			itemSlotSelected = -1;
			if ( butMonsterItemOK != NULL )
			{
				butMonsterItemOK->visible = 0;
			}
			if ( butMonsterItemX != NULL )
			{
				butMonsterItemX->visible = 0;
			}
			if ( butMonsterItemCancel != NULL )
			{
				butMonsterItemCancel->visible = 0;
			}
		}
	}
	else {
		selectedEntity[0] = NULL;
		newwindow = 0;
		subwindow = 0;
		editproperty = 0;
		spritepalette = 0;
	}
}

void buttonMonsterItems(button_t* my)
{
	int spacing = 20;
	int pad_y2 = suby1 + 28 + 2 * spacing;
	int pad_x3 = 40;
	int pad_x4 = subx2 - 112;
	char tmpStr[32] = "";
	button_t* button = NULL;

	itemSelect = 0;

	inputstr = spriteProperties[0];
	cursorflash = ticks;
	menuVisible = 0;
	subwindow = 1;
	slidery = 0;
	subx1 = xres / 2 - 200;
	subx2 = xres / 2 + 200;
	suby1 = yres / 2 - 158;
	suby2 = yres / 2 + 158;
	strcpy(subtext, "Monster Item Properties:");

	Stat* tmpSpriteStats = selectedEntity[0]->getStats();

	// stores any modified monster stats, to be restored when window is closed.

	for ( int i = 0; i < sizeof(spriteProperties) / sizeof(spriteProperties[0]); i++ )
	{
		strcpy(tmpSpriteProperties[i], spriteProperties[i]);
	}

	if ( my == butMonsterHelm )
	{
		itemSlotSelected = 0;
	}
	else if ( my == butMonsterWeapon )
	{
		itemSlotSelected = 1;
	}
	else if ( my == butMonsterShield )
	{
		itemSlotSelected = 2;
	}
	else if ( my == butMonsterArmor )
	{
		itemSlotSelected = 3;
	}
	else if ( my == butMonsterBoots )
	{
		itemSlotSelected = 4;
	}
	else if ( my == butMonsterRing )
	{
		itemSlotSelected = 5;
	}
	else if ( my == butMonsterAmulet )
	{
		itemSlotSelected = 6;
	}
	else if ( my == butMonsterCloak )
	{
		itemSlotSelected = 7;
	}
	else if ( my == butMonsterMask )
	{
		itemSlotSelected = 8;
	}
	else if ( my == butMonsterGloves )
	{
		itemSlotSelected = 9;
	}
	else if ( my == butMonsterItem1 )
	{
		itemSlotSelected = 10;
	}
	else if ( my == butMonsterItem2 )
	{
		itemSlotSelected = 11;
	}
	else if ( my == butMonsterItem3 )
	{
		itemSlotSelected = 12;
	}
	else if ( my == butMonsterItem4 )
	{
		itemSlotSelected = 13;
	}
	else if ( my == butMonsterItem5 )
	{
		itemSlotSelected = 14;
	}
	else if ( my == butMonsterItem6 )
	{
		itemSlotSelected = 15;
	}
	else
	{
		itemSlotSelected = -1;
	}

	newwindow = 5;


	if ( butMonsterHelm != NULL )
	{
		butMonsterHelm->visible = 0;
	}
	if ( butMonsterWeapon != NULL )
	{
		butMonsterWeapon->visible = 0;
	}
	if ( butMonsterShield != NULL )
	{
		butMonsterShield->visible = 0;
	}
	if ( butMonsterArmor != NULL )
	{
		butMonsterArmor->visible = 0;
	}
	if ( butMonsterRing != NULL )
	{
		butMonsterRing->visible = 0;
	}
	if ( butMonsterAmulet != NULL )
	{
		butMonsterAmulet->visible = 0;
	}
	if ( butMonsterBoots != NULL )
	{
		butMonsterBoots->visible = 0;
	}
	if ( butMonsterCloak != NULL )
	{
		butMonsterCloak->visible = 0;
	}
	if ( butMonsterMask != NULL )
	{
		butMonsterMask->visible = 0;
	}
	if ( butMonsterGloves != NULL )
	{
		butMonsterGloves->visible = 0;
	}
	if ( butMonsterItem1 != NULL )
	{
		butMonsterItem1->visible = 0;
	}
	if ( butMonsterItem2 != NULL )
	{
		butMonsterItem2->visible = 0;
	}
	if ( butMonsterItem3 != NULL )
	{
		butMonsterItem3->visible = 0;
	}
	if ( butMonsterItem4 != NULL )
	{
		butMonsterItem4->visible = 0;
	}
	if ( butMonsterItem5 != NULL )
	{
		butMonsterItem5->visible = 0;
	}
	if ( butMonsterItem6 != NULL )
	{
		butMonsterItem6->visible = 0;
	}
	if ( butMonsterOK != NULL )
	{
		butMonsterOK->visible = 0;
	}
	if ( butMonsterCancel != NULL )
	{
		butMonsterCancel->visible = 0;
	}
	if ( butMonsterX != NULL )
	{
		butMonsterX->visible = 0;
	}
	snprintf(spriteProperties[0], 5, "%d", tmpSpriteStats->EDITOR_ITEMS[itemSlotSelected * ITEM_SLOT_NUMPROPERTIES + 0]);
	snprintf(spriteProperties[1], 5, "%d", tmpSpriteStats->EDITOR_ITEMS[itemSlotSelected * ITEM_SLOT_NUMPROPERTIES + 1]);
	if ( (int)tmpSpriteStats->EDITOR_ITEMS[itemSlotSelected * ITEM_SLOT_NUMPROPERTIES + 2] == 10 )
	{
		strcpy(spriteProperties[2], "00"); //bless random
	}
	else
	{
		snprintf(spriteProperties[2], 4, "%d", (int)tmpSpriteStats->EDITOR_ITEMS[itemSlotSelected * ITEM_SLOT_NUMPROPERTIES + 2]); //bless
	}
	snprintf(spriteProperties[3], 5, "%d", tmpSpriteStats->EDITOR_ITEMS[itemSlotSelected * ITEM_SLOT_NUMPROPERTIES + 3]);
	snprintf(spriteProperties[4], 5, "%d", tmpSpriteStats->EDITOR_ITEMS[itemSlotSelected * ITEM_SLOT_NUMPROPERTIES + 4]);
	snprintf(spriteProperties[5], 5, "%d", tmpSpriteStats->EDITOR_ITEMS[itemSlotSelected * ITEM_SLOT_NUMPROPERTIES + 5]);
	snprintf(spriteProperties[6], 5, "%d", tmpSpriteStats->EDITOR_ITEMS[itemSlotSelected * ITEM_SLOT_NUMPROPERTIES + 6]);

	butMonsterItemOK = newButton();
	strcpy(butMonsterItemOK->label, "  OK  ");
	butMonsterItemOK->x = subx2 - 128;
	butMonsterItemOK->y = suby2 - 24;
	butMonsterItemOK->sizex = 56;
	butMonsterItemOK->sizey = 16;
	butMonsterItemOK->action = &buttonSpritePropertiesConfirm;
	butMonsterItemOK->visible = 1;
	butMonsterItemOK->focused = 1;

	butMonsterItemCancel = newButton();
	strcpy(butMonsterItemCancel->label, "Cancel");
	butMonsterItemCancel->x = subx2 - 64;
	butMonsterItemCancel->y = suby2 - 24;
	butMonsterItemCancel->sizex = 56;
	butMonsterItemCancel->sizey = 16;
	butMonsterItemCancel->action = &buttonCloseSpriteSubwindow;
	butMonsterItemCancel->visible = 1;
	butMonsterItemCancel->focused = 1;

	butMonsterItemX = newButton();
	strcpy(butMonsterItemX->label, "X");
	butMonsterItemX->x = subx2 - 16;
	butMonsterItemX->y = suby1;
	butMonsterItemX->sizex = 16;
	butMonsterItemX->sizey = 16;
	butMonsterItemX->action = &buttonCloseSpriteSubwindow;
	butMonsterItemX->visible = 1;
	butMonsterItemX->focused = 1;
}

void initMonsterPropertiesWindow() {
	cursorflash = ticks;
	menuVisible = 0;
	subwindow = 1;
	newwindow = 2;
	subx1 = xres / 2 - 200;
	subx2 = xres / 2 + 200;
	suby1 = yres / 2 - 190;
	suby2 = yres / 2 + 190;
	strcpy(subtext, "Sprite properties: ");
	strcat(subtext, spriteEditorNameStrings[selectedEntity[0]->sprite]);
}

void copyMonsterStatToPropertyStrings(Stat* tmpSpriteStats)
{
	if ( tmpSpriteStats != NULL )
	{
		strcpy(spriteProperties[0], tmpSpriteStats->name);
		snprintf(spriteProperties[1], 5, "%d", tmpSpriteStats->MAXHP);
		snprintf(spriteProperties[2], 5, "%d", tmpSpriteStats->HP);
		snprintf(spriteProperties[3], 5, "%d", tmpSpriteStats->MAXMP);
		snprintf(spriteProperties[4], 5, "%d", tmpSpriteStats->MP);
		snprintf(spriteProperties[5], 4, "%d", tmpSpriteStats->LVL);
		snprintf(spriteProperties[6], 4, "%d", tmpSpriteStats->GOLD);
		snprintf(spriteProperties[7], 4, "%d", tmpSpriteStats->STR);
		snprintf(spriteProperties[8], 4, "%d", tmpSpriteStats->DEX);
		snprintf(spriteProperties[9], 4, "%d", tmpSpriteStats->CON);
		snprintf(spriteProperties[10], 4, "%d", tmpSpriteStats->INT);
		snprintf(spriteProperties[11], 4, "%d", tmpSpriteStats->PER);
		snprintf(spriteProperties[12], 4, "%d", tmpSpriteStats->CHR);
		snprintf(spriteProperties[13], 5, "%d", tmpSpriteStats->RANDOM_MAXHP + tmpSpriteStats->MAXHP);
		snprintf(spriteProperties[14], 5, "%d", tmpSpriteStats->RANDOM_HP + tmpSpriteStats->HP);
		snprintf(spriteProperties[15], 5, "%d", tmpSpriteStats->RANDOM_MAXMP + tmpSpriteStats->MAXMP);
		snprintf(spriteProperties[16], 5, "%d", tmpSpriteStats->RANDOM_MP + tmpSpriteStats->MP);
		snprintf(spriteProperties[17], 4, "%d", tmpSpriteStats->RANDOM_LVL + tmpSpriteStats->LVL);
		snprintf(spriteProperties[18], 4, "%d", tmpSpriteStats->RANDOM_GOLD + tmpSpriteStats->GOLD);
		snprintf(spriteProperties[19], 4, "%d", tmpSpriteStats->RANDOM_STR + tmpSpriteStats->STR);
		snprintf(spriteProperties[20], 4, "%d", tmpSpriteStats->RANDOM_DEX + tmpSpriteStats->DEX);
		snprintf(spriteProperties[21], 4, "%d", tmpSpriteStats->RANDOM_CON + tmpSpriteStats->CON);
		snprintf(spriteProperties[22], 4, "%d", tmpSpriteStats->RANDOM_INT + tmpSpriteStats->INT);
		snprintf(spriteProperties[23], 4, "%d", tmpSpriteStats->RANDOM_PER + tmpSpriteStats->PER);
		snprintf(spriteProperties[24], 4, "%d", tmpSpriteStats->RANDOM_CHR + tmpSpriteStats->CHR);
		snprintf(spriteProperties[25], 4, "%d", tmpSpriteStats->MISC_FLAGS[STAT_FLAG_NPC]);
		if ( tmpSpriteStats->MISC_FLAGS[STAT_FLAG_DISABLE_MINIBOSS] == 0 )
		{
			strcpy(spriteProperties[31], "");
		}
		else
		{
			strcpy(spriteProperties[31], "disable");
		}
	}
	return;
}
