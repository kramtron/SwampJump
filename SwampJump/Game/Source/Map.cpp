#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>

Map::Map() : Module(), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// L06: TODO 7: Ask for the value of a custom property
int Properties::GetProperty(const char* value, int defaultValue) const
{
	//...

	ListItem<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == value)
			return item->data->value;
		item = item->next;
	}

	return defaultValue;
}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

// Draw the map (all requried layers)
/*void Map::Draw()
{
	if (mapLoaded == false) return;

	// L04: DONE 5: Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	// L06: TODO 4: Make sure we draw all the layers and not just the first one
	while (mapLayerItem != NULL) {

		//if (mapLayerItem->data->properties.GetProperty("Draw") == 1) {

			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					// L04: DONE 9: Complete the draw function
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
						//now we always use the firt tileset in the list
						//TileSet* tileset = mapData.tilesets.start->data;
						TileSet* tileset = GetTilesetFromTileId(gid);

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						app->render->DrawTexture(tileset->texture,
							pos.x,
							pos.y,
							&r);
					}

				}
			}
		}

		mapLayerItem = mapLayerItem->next;
//	}
}*/

void Map::Getcolision_coords(int player_x, int player_y) {
	int i = 0;
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;
	mapLayerItem = mapLayerItem->next;
	
	for (int j = 0; j < 50; j++) {
		colision_coords[j] = nullptr;
	}

	for (int x = (player_x / 32) - 1; x < (player_x / 32) + 3; x++) // 1 tile enrere i 3 endevant
	{
		for (int y = (player_y / 32) - 2; y < (player_y / 32) + 10; y++)
		{
			if (x >= 0 && x < 600 && y >= 0 && y < 32) {
				int gid = mapLayerItem->data->Get(x, y);

				if (gid > 0) {
					colision_coords[i] = new iPoint(MapToWorld(x, y));
					++i;
				}
			}
		}
	}
}

void Map::DrawColisions() {
	if (mapLoaded == false) return;

	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;
	mapLayerItem = mapLayerItem->next;

	for (int x = 0; x < mapLayerItem->data->width; x++)
	{
		for (int y = 0; y < mapLayerItem->data->height; y++)
		{
			int gid = mapLayerItem->data->Get(x, y);

			if (gid > 0) {
				iPoint pos = MapToWorld(x, y);
				SDL_Rect rectCollider = { pos.x, pos.y, 32, 32 };
				app->render->DrawRectangle(rectCollider, 255, 0, 0, 80);
			}

		}
	}
	
}

void Map::Draw()
{
	if (mapLoaded == false) return;

	// L04: DONE 5: Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	while (mapLayerItem != NULL) {

		//if (mapLayerItem->data->properties.GetProperty("name") != "colision") {

		for (int x = 0; x < mapLayerItem->data->width; x++)
		{
			for (int y = 0; y < mapLayerItem->data->height; y++)
			{
				// L04: DONE 9: Complete the draw function
				int gid = mapLayerItem->data->Get(x, y);

				if (gid > 0) {

					//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
					//now we always use the firt tileset in the list
					TileSet* tileset = mapData.tilesets.start->data;

					SDL_Rect r = tileset->GetTileRect(gid);
					iPoint pos = MapToWorld(x, y);

					app->render->DrawTexture(tileset->texture,
						pos.x,
						pos.y,
						&r);
				}

			}
		}

		mapLayerItem = mapLayerItem->next;
	}
}

// L04: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	// L05: DONE 1: Add isometric map to world coordinates
	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * mapData.tileWidth;
		ret.y = y * mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (mapData.tileWidth / 2);
		ret.y = (x + y) * (mapData.tileHeight / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

// L05: DON 2: Add orthographic world to map coordinates
iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// L05: DONE 3: Add the case for isometric maps to WorldToMap
	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / mapData.tileWidth;
		ret.y = y / mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{

		float half_width = mapData.tileWidth * 0.5f;
		float half_height = mapData.tileHeight * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2);
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

// L06: TODO 3: Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = mapData.tilesets.start;
	TileSet* set = item->data;

	while (item)
	{
		if (id < item->data->firstgid)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}

	return set;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// L04: DONE 7: Get relative Tile rectangle
	int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % columns));
	rect.y = margin + ((rect.h + spacing) * (relativeId / columns));
	
	return rect;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L03: DONE 2: Make sure you clean up any memory allocated from tilesets/map
    // Remove all tilesets
	ListItem<TileSet*>* item;
	item = mapData.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	mapData.tilesets.clear();

	// L04: DONE 2: clean up all layer data
	// Remove all layers
	ListItem<MapLayer*>* item2;
	item2 = mapData.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	mapData.layers.clear();

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

	pugi::xml_document mapFile; 
    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

	// Load general info
    if(ret == true)
    {
        // L03: DONE 3: Create and call a private function to load and fill all your map data
		ret = LoadMap(mapFile);
	}

    // L03: DONE 4: Create and call a private function to load a tileset
    // remember to support more any number of tilesets!
	if (ret == true)
	{
		ret = LoadTileSets(mapFile.child("map"));
	}

	// L04: DONE 4: Iterate all layers and load each of them
	// Load layer info
	if (ret == true)
	{
		ret = LoadAllLayers(mapFile.child("map"));
	}
    
    if(ret == true)
    {
        // L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything

		// L04: TODO 4: LOG the info for each loaded layer
    }

    mapLoaded = ret;

    return ret;
}

// L03: TODO: Load map general properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// L03: DONE 3: Load map general properties
		mapData.height = map.attribute("height").as_int();
		mapData.width = map.attribute("width").as_int();
		mapData.tileHeight = map.attribute("tileheight").as_int();
		mapData.tileWidth = map.attribute("tilewidth").as_int();

		// L05: DONE 1: Add formula to go from isometric map to world coordinates
		mapData.type = MAPTYPE_UNKNOWN;
		if (strcmp(map.attribute("orientation").as_string(), "isometric") == 0)
		{
			mapData.type = MAPTYPE_ISOMETRIC;
		}
		if (strcmp(map.attribute("orientation").as_string(), "orthogonal") == 0)
		{
			mapData.type = MAPTYPE_ORTHOGONAL;
		}
	}

	return ret;
}

// L03: DONE 4: Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSets(pugi::xml_node mapFile) {

	bool ret = true;

	pugi::xml_node tileset;
	for (tileset = mapFile.child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();
		if (ret == true) ret = LoadTilesetDetails(tileset, set);
		if (ret == true) ret = LoadTilesetImage(tileset, set);
		mapData.tilesets.add(set);
	}

	return ret;
}

// L03: DONE 4: Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	// L03: DONE 4: Load Tileset attributes
	set->name.Create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tileWidth = tileset_node.attribute("tilewidth").as_int();
	set->tileHeight = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->tilecount = tileset_node.attribute("tilecount").as_int();
	set->columns = tileset_node.attribute("columns").as_int();

	return ret;
}

// L03: DONE 4: Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// L03: DONE 4: Load Tileset image
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
	}

	return ret;
}

// L04: DONE 3: Implement a function that loads a single layer layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	//Load the attributes
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();

	//L06: TODO 6 Call Load Propoerties
	LoadProperties(node, layer->properties);

	//Reserve the memory for the tile array
	layer->data = new uint[layer->width * layer->height];
	memset(layer->data, 0, layer->width * layer->height);

	//Iterate over all the tiles and assign the values
	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"))
	{
		layer->data[i] = tile.attribute("gid").as_int();
		i++;
	}

	return ret;
}

// L04: DONE 4: Iterate all layers and load each of them
bool Map::LoadAllLayers(pugi::xml_node mapNode) {
	bool ret = true;
	for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		//Load the layer
		MapLayer* mapLayer = new MapLayer();
		ret = LoadLayer(layerNode, mapLayer);

		//add the layer to the map
		mapData.layers.add(mapLayer);
	}

	return ret;
}


// L06: TODO 6: Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	for (pugi::xml_node propertieNode = node.child("properties").child("property"); propertieNode; propertieNode = propertieNode.next_sibling("property"))
	{
		Properties::Property *p = new Properties::Property();
		p->name = propertieNode.attribute("name").as_string();
		p->value = propertieNode.attribute("value").as_int();

		if (p->name == ("Draw")) {
			LOG("OK");
		}
		else if (p->name == ("Navigation")) {
			LOG("NYA");
		}

		LOG("Propiedades del layer %s, %d", p->name, p->value);
		properties.list.add(p);
	}

	
	return ret;
}

//PATHFINDING
void Map::ResetPath(int x, int y)
{
	frontier.Clear();
	visited.clear();
	breadcrumbs.clear();
	path.Clear();

	frontier.Push(iPoint(x, y), 0);
	visited.add(iPoint(x, y));
	breadcrumbs.add(iPoint(x, y));
}

void Map::DrawPath()
{
	// Draw path
	for (uint i = 0; i < path.Count(); ++i)
	{
		iPoint pos = MapToWorld(path[i].x, path[i].y);
		app->render->DrawRectangle({ pos.x, pos.y, 32, 32 }, 0, 50, 0, 50);
	}
}

bool Map::IsWalkable(int x, int y) const
{
	bool isWalkable = false;
	//afegir limits del mapa
	if (x >= 0 && y >= 0 && x <= 600 && y <= 32) {
		
		//gets the second layer
		ListItem<MapLayer*>* mapLayerItem;
		mapLayerItem = mapData.layers.start;
		mapLayerItem = mapLayerItem->next;

		//identify if its collider or not
		int gid = mapLayerItem->data->Get(x, y);

		if (gid == 0) {
			isWalkable = true;
		}
	}

	return isWalkable;
}

void Map::ComputePath(int x, int y)
{
	path.Clear();
	iPoint goal = WorldToMap(x, y);

	path.PushBack(goal);
	int index = visited.find(goal);

	//Follow the breadcrumbs to get the full path
	while ((index >= 0) && (goal != breadcrumbs[index]))
	{
		goal = breadcrumbs[index];
		path.PushBack(goal);
		index = visited.find(goal);
	}
}

void Map::PropagateBFS()
{
	//Take the last frontier element
	iPoint curr;
	if (frontier.Pop(curr))
	{
		//4 neighbor tiles
		iPoint neighbors[4];
		neighbors[0].create(curr.x + 1, curr.y + 0);
		neighbors[1].create(curr.x + 0, curr.y + 1);
		neighbors[2].create(curr.x - 1, curr.y + 0);
		neighbors[3].create(curr.x + 0, curr.y - 1);

		for (uint i = 0; i < 4; ++i)
		{
			//If is walkable...
			if (IsWalkable(neighbors[i].x, neighbors[i].y))
			{
				//If the tile is not added in visited, add it
				if (visited.find(neighbors[i]) == -1)
				{
					frontier.Push(neighbors[i], 0);
					visited.add(neighbors[i]);
					breadcrumbs.add(curr);
				}
			}
		}
	}
}

iPoint Map::Pathfinding(iPoint initPoint, iPoint endPoint) {
	//if init or end are not walkable quit
	if ((!IsWalkable(initPoint.x, initPoint.y) || !IsWalkable(endPoint.x, endPoint.y)) || (initPoint == endPoint)) {
		return iPoint(-1, -1);
	}
	
	ResetPath(initPoint.x, initPoint.y);
	
	int i = 0;
	while (visited.find(endPoint) == -1) {
		PropagateBFS();
		i++;
		if (i > 1000) {
			return iPoint(-1, -1);
		}
	}

	iPoint endPoint2 = MapToWorld(endPoint.x, endPoint.y);
	ComputePath(endPoint2.x, endPoint2.y);
	
	if ((path.Count() - 2) <= 0) {
		return iPoint(-1, -1);
	}
	//return the position before the last (the next position the object has to move to)
	return path[path.Count() - 2];
}