#pragma once
#include <vector>
#include <string>

using MapData = std::vector<std::vector<int>>;

int get_bitmask(int x, int y, const MapData& map_data);

std::string bitmask_to_tilefile(int bitmask);

void create_map_image(const MapData& map_data, const std::string& tile_folder);
