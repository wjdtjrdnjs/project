#include "new_map.h"
#include <unordered_map>
#include <iostream>

int get_bitmask(int x, int y, const MapData& map_data) {
    int mask = 0;
    int rows = (int)map_data.size();
    int cols = (int)map_data[0].size();

    if (y > 0 && map_data[y - 1][x] == 1) mask |= 1;
    if (x < cols - 1 && map_data[y][x + 1] == 1) mask |= 2;
    if (y < rows - 1 && map_data[y + 1][x] == 1) mask |= 4;
    if (x > 0 && map_data[y][x - 1] == 1) mask |= 8;

    return mask;
}

std::unordered_map<int, std::string> tileMap = {
    {0, "tile_0 (1).bmp"},
    {1, "tile_0 (2).bmp"},
    {2, "tile_0 (3).bmp"},
    {3, "tile_0 (4).bmp"},
    {4, "tile_0 (5).bmp"},
    {5, "tile_0 (6).bmp"},
    {6, "tile_0 (7).bmp"},
    {7, "tile_0 (8).bmp"},
    {8, "tile_0 (9).bmp"},
    {9,  "4_1.bmp"},
    {10, "5_1.bmp"},
    {11, "7_1.bmp"},
    {12, "8_1.bmp"}
};

std::string bitmask_to_tilefile(int bitmask) {
    if (tileMap.count(bitmask))
        return tileMap[bitmask];
    else
        return "unknown.bmp";
}

void create_map_image(const MapData& map_data, const std::string& tile_folder) {
    int rows = (int)map_data.size();
    int cols = (int)map_data[0].size();

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (map_data[y][x] == 0)
                std::cout << "[grass] ";
            else {
                int mask = get_bitmask(x, y, map_data);
                std::cout << "(mask:" << mask << ") [" << bitmask_to_tilefile(mask) << "] ";
            }
        }
        std::cout << "\n";
    }
}
