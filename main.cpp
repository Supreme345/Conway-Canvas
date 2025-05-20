#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<SDL2/SDL.h>
#include "life_grid.h"
#define WIDTH 100
#define HEIGHT  150
#define CELL_SIZE 10
using namespace std;

int main()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "SDL Initialization Failed : " << SDL_GetError() << endl;
		return 1;
	}

	window = SDL_CreateWindow("Conway's Game of Life",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,800,SDL_WINDOW_SHOWN);

	if(!window)
	{
		cout << "Window Creation Failed : " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}
	renderer = SDL_CreateRenderer(window,-1,0);

	if(!renderer)
	{
		cout << "Renderer Creation Failed : " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	LifeGrid grid(WIDTH,HEIGHT);

	char choice;
	bool correctInput = false;
	bool paused = false,next_gen = false,isDrawMode = false;

	cout << "========================================================" << endl;
	cout << "	Welcome to Conway Canvas" << endl;
	cout << "========================================================" << endl;

	do
	{
		cout << "Choose starting mode : "<< endl;
		cout << " '1' Random Initialization " << endl;
		cout << " '2' Draw your own Pattern " << endl;
		cout << "Enter your choice (1 or 2): ";
		cin  >> choice;
		cout << endl;

		if( choice == '1')
		{
			grid.initialise_random();
			cout << "Random Pattern generated." << endl;
			correctInput = true;
		}

		else if( choice == '2')
		{
			grid.clear_grid();
			isDrawMode = true;
			paused = true;
			cout << "You can now draw your own patterns." << endl;
			correctInput = true;
		}

		else
		{
			correctInput = false;
			cout << "Invalid Input . Enter only valid input (1/2) " << endl;
		}
	}while(!correctInput);

	unsigned long generation = 0;

	bool gameStatus = true;
	SDL_Event event;

	cout << "\n----------------------Controls------------------------" << endl;
	cout << "  p :  Pause and Enter Draw Mode " << endl;
	cout << "  r :  Resume Automatic Simulation" << endl;
	cout << "  n :  Advance to Next Generation (only in Pause Mode)" << endl;
	cout << "  c : Clear Grid and Draw New Pattern " << endl;
	cout << "Close the window to quit the Game " << endl;
	cout << "\n-----------------------------------------------------" << endl;

	while(gameStatus)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				cout << "\n========================================================" << endl;
				cout << "    Thank you for playing Conway Canvas!" << endl;
				cout << "    Total Generations: " << generation << endl;
                        	cout << "    Alive Cells: " << grid.count_alive_cells()<<endl;
				cout << "=========================================================" << endl;

				gameStatus = false;
			}

			else if(event.type == SDL_KEYDOWN)// Handle keyboard input for game controls
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_p:// Pause game and enableand enable draw mode
					{
						paused = true;
						cout << "\nPaused - Draw Mode ON (left click = alive , right click = dead)" << endl;
						break;
					}

					case SDLK_r:// Resume simulation
					{
						paused = false;
						cout << "\nResumed" << endl;
						break;
					}

					case SDLK_n://Advance one generation if paused
					{
						if(paused)
						{
							next_gen = true;
							cout << "\nStep Forward" << endl;
						}

						else
						{
							cout << "\nYou must pause the game first (press 'p') before stepping with 'n'." << endl;
						}
						break;
					}

					case SDLK_c://Clear grid and reset for drawing
					{
						paused = true;
						grid.clear_grid();
						isDrawMode = true;
						generation = 0;
						cout << "\nCleared - Ready to make your own patterns! " << endl;
						break;
					}

				}
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN && paused)
			{
				int x_pos = event.button.x / CELL_SIZE;//convert pixel x to grid column
				int y_pos = event.button.y / CELL_SIZE;//convert pixel y to grid row

				switch(event.button.button)//Handle mouse button clicks to set cell state
				{
					case SDL_BUTTON_LEFT://Left-click to set cell as alive
					{
						grid.set_cell(y_pos,x_pos,1);
						cout << "Alive cell placed at grid position (row - "<< y_pos << " , col - " << x_pos << " )." << endl;
						break;
					}

					case SDL_BUTTON_RIGHT://Right-click to set cell as dead
					{
						grid.set_cell(y_pos,x_pos,0);
						cout << "Dead cell placed at grid position (row - " << y_pos << " , col - " << x_pos << " )." << endl;
						break;
					}
				}
			}

		}
		if(!paused || next_gen)
                {
			grid.update();
			++generation;
                        next_gen = false;
                        usleep(100000);//100 ms delay

		}

		grid.draw(renderer);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
