#pragma once

#include"tile.h"

#include<SDL.h>
#include<string>
#include<fstream>
#include<Sstream>

class Map
{
public:
	Map() {};
	~Map() {};

	bool load(const std::string& path)
	{
		std::ifstream file(path);
		if (!file.good())
			return false;

		TileMap tile_map_temp;

		int idx_x = -1, idx_y = -1;

		std::string str_line;
		while (std::getline(file, str_line))
		{
			str_line = trim_str(str_line);
			if (str_line.empty())//不是空行时
				continue;

			idx_x = -1;
			idx_y++;
			tile_map_temp.emplace_back();//追加一行

			std::string str_tile;
			std::stringstream str_stream(str_line);
			while (std::getline(str_stream, str_tile, ','))
			{
				idx_x++;
				tile_map_temp[idx_y].emplace_back();//不断增加列
				Tile& tile = tile_map_temp[idx_y].back();
				load_tile_from_string(tile, str_tile);
			}
		}
		file.close();

		if (tile_map_temp.empty() || tile_map_temp[0].empty())
			return false;

		tile_map = tile_map_temp;

		return true;
	}

	size_t get_width() const
	{
		if (tile_map.empty())
			return 0; 

		return tile_map[0].size();
	}

private:
	TileMap tile_map;
	SDL_Point idx_home = {0};

private:

	std::string trim_str(const std::string& str)
	{
		size_t begin_idx = str.find_first_not_of(" \t");
		if (begin_idx == std::string::npos)
			return "";
		size_t end_idx = str.find_last_not_of(" \t");
		size_t idx_range = end_idx - begin_idx + 1;

		return str.substr(begin_idx, idx_range);
	}

	void load_tile_from_string(Tile& tile, const std::string& str)
	{
		std::string str_tidy = trim_str(str);

		std::string str_value;
		std::vector<int> values;
		std::stringstream str_stream(str_tidy);

		while (std::getline(str_stream, str_value, '\\'))
		{
			int value;
			try
			{
				value = std::stoi(str_value);
			}
			catch (const std::invalid_argument&)
			{
				value = -1;
			}
			values.push_back(value);

		}

		tile.terrain = (values.size() < 1 || values[0] < 0) ? 0 : values[0];
		tile.decoration = (values.size() < 2) ? -1 : values[1];
		tile.direction = (Tile::Direction)((values.size() < 3 || values[2] < 0) ? 0 : values[2]);
		tile.special_flag = (values.size() <= 3) ? -1 : values[3];
	}

	void generate_map_cache()
	{
		for (int y = 0; ; y++)
		{

		}
	}

};