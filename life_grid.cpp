#include "life_grid.h"
#include<unistd.h>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<SDL2/SDL.h>

#define WIDTH 100
#define HEIGHT 150
#define CELL_SIZE 10

using std::vector;

LifeGrid::LifeGrid(int w,int h):width(w),height(h)
{
	grid.resize(height,vector<int>(width,0));
	next_grid.resize(height,vector<int>(width,0));
}

void LifeGrid::initialise_random()
{
	unsigned int seed=time(0);
	srand(seed);
	int initial_cells=(width*height)/4;

	while(initial_cells--)
	{
		int row=rand() % height;
		int col=rand() % width;
		grid[row][col] = 1;//make the cell alive
	}
}

int LifeGrid::count_alive_cells()
{
	int row,col,alive_cells=0;
	for(row = 0; row < height; row++)
	{
		for(col = 0; col < width; col++)
		{
			if(grid[row][col] == 1)
				alive_cells++;
		}
	}
	return alive_cells;
}

int LifeGrid::count_neighbors(int row,int col)
{
	int count=0;
	for(int r = -1; r <= 1; r++)
	{
		for(int c = -1 ; c <= 1; c++)
		{
			if( r == 0 && c == 0)
				continue;
			int nr = (r + row + height) % height;//to wrap around edges
			int nc = (c + col + width) % width;//and to stay in bound
			count += grid[nr][nc];
		}
	}
	return count;
}

void LifeGrid::update()
{
	int row,col;
	for(row = 0; row < height; row++)
	{
		for(col = 0; col < width; col++)
		{
			int alive_neighbors = count_neighbors(row,col);
			if(grid[row][col]==1)
			{
				next_grid[row][col]=(alive_neighbors == 2) || (alive_neighbors == 3) ? 1 : 0;
			}
			else
			{
				next_grid[row][col]=(alive_neighbors == 3) ? 1 : 0;
			}
		}
	}
	grid.swap(next_grid);
}


void LifeGrid::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer,0,0,0,255);//black - background
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);//white - alive cells

	for(int row = 0; row < height ; row++)
	{
		for(int col = 0; col < width; col++)
		{
			//Render alive cells by converting grid coordinates to pixel positions (each cell is 10x10 pixels)
			if(grid[row][col] == 1)
			{
				SDL_Rect rect;
				rect.x = col * CELL_SIZE ;
				rect.y = row * CELL_SIZE;
				rect.w = CELL_SIZE;
				rect.h = CELL_SIZE;

				SDL_RenderFillRect(renderer,&rect);
			}
		}
	}

	SDL_RenderPresent(renderer);
}

void LifeGrid::clear_grid()
{
	int row,col;
	for(row = 0; row < height ; row++)
	{
		for(col = 0; col < width ; col++)
		{
			grid[row][col] = 0;
		}
	}
}

void LifeGrid::set_cell(int row,int col,int state)
{
	if(row >= 0 && row < height && col >= 0 && col < width)
		grid[row][col] = state;
}
