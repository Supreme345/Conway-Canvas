#pragma once

#include<vector>
#include<SDL2/SDL.h>
class LifeGrid
{
	public:
		LifeGrid(int w,int h);
		void initialise_random();
		int count_alive_cells();
		void update();
		void draw(SDL_Renderer* renderer);
		void clear_grid();
		void set_cell(int row,int col,int state);

	private:
		int width,height;
		std::vector<std::vector<int>> grid;
		std::vector<std::vector<int>> next_grid;
		int count_neighbors(int x,int y);
};


