#include "../include/Game.h"

Game::Game() :
    m_gameIsRunning{ false },
    gWindow{NULL},
    gScreenSurface{NULL},
    gXOut{NULL},
	m_factoryTest{true},
	factory{new BrickFactory}
{

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}
}
    
Game::~Game()
{
}
    
void Game::run()
{
    m_gameIsRunning = true;
    while (m_gameIsRunning)
    {
        update();
    }
}

void Game::endGame()
{
	//Deallocate surface
	SDL_FreeSurface( gXOut );
	gXOut = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void Game::update()
{
   //Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
        }
		if(m_factoryTest)
		{
			m_bricks.push_back(factory->CreateLego());
			m_bricks.push_back(factory->CreateClay());
			m_bricks.push_back(factory->CreateLime());
			m_bricks.push_back(factory->CreateAsh());

			for(int i = 0; i < m_bricks.size(); i++)
			{
				m_bricks[i]->draw();
			}
			
			m_factoryTest = false;
		}
		
		//Apply the image
		SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
	
		//Update the surface
		SDL_UpdateWindowSurface( gWindow );
	}
	endGame();
}

