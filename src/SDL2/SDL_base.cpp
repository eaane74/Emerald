#include "../system.h"
#include "../globals.h"

#include <SDL2/SDL.h>
#include <cstdarg>

#ifdef _DEBUG
	#include <windows.h>
#endif

#define SCREEN_WIDTH		Globals::Default_Window_Width
#define SCREEN_HEIGHT		Globals::Default_Window_Height

extern void wndproc( const SDL_Event& ev );

SDL_Window* main_window = nullptr;
SDL_Renderer* main_renderer = nullptr;
bool isRunning = false;

bool sys::init( void )
{
	static bool initialized = false;

	if( initialized ) return true;

	#ifdef _DEBUG
		// Initialize the debug console. ( windows only )
		//FreeConsole();
		AllocConsole();

		freopen( "conout$", "w", stdout );
		freopen( "conout$", "w", stderr );
		freopen( "conin$", "r", stdin );

		HWND debug_console = GetConsoleWindow();
		MoveWindow( debug_console, 1, 1, 640, 480, TRUE );

		fprintf( stdout, "\n*****************************\n" 
				 		 "* Debug Console initialized *\n"
				 		 "*****************************\n" );
		fflush( stdout );
	#endif

	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		error( "Could not initialize SDL2\n" );
		return false;
	}

	// take out the garbage if any
	SDL_ClearError();

	main_window = SDL_CreateWindow( "Hello world!", SDL_WINDOWPOS_CENTERED, 
									SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, 
									SCREEN_HEIGHT, SDL_WINDOW_HIDDEN );
	if( !main_window )
	{
		error( "Could not create main window" );
		return false;
	}

	// This stuff is just used for debugging purposes
	int w, h, x, y;
	const char* title;

	SDL_GetWindowSize( main_window, &w, &h);
	SDL_GetWindowPosition( main_window, &x, &y);
	title = SDL_GetWindowTitle( main_window );

	debug_print( "Main window created! %s\t%dx%d @ %dx%d", title, w, h, x, y );

	main_renderer = SDL_CreateRenderer( main_window, -1, SDL_RENDERER_ACCELERATED | 
										SDL_RENDERER_TARGETTEXTURE );
	if ( !main_renderer )
	{
		error( "Could not create main renderer" );
		return false;
	}

	SDL_ShowWindow( main_window );

	// This stuff is just used for debugging purposes
	SDL_RendererInfo rend_info;
	SDL_GetRendererInfo( main_renderer, &rend_info );

	if ( rend_info.flags & SDL_RENDERER_ACCELERATED )
		debug_print( "Hardware acceleration available!" );
	else
		debug_print( "No hardware acceleration!" );

	if ( rend_info.flags & SDL_RENDERER_TARGETTEXTURE )
		debug_print( "Rendering surface available!" );
	else
		debug_print( "No rendering surface available!" );

	debug_print( "Main renderer created: %s\n\tmax texture width: %d\n\t"
				 "max texture height: %d", rend_info.name, rend_info.max_texture_width,
				 rend_info.max_texture_height );

	SDL_SetRenderDrawColor( main_renderer, 0, 0, 255, 0 );

	//SDL_FlushEvents( SDL_FIRSTEVENT, SDL_LASTEVENT );		
	isRunning = true;
	return true;
}

void sys::quit()
{
	SDL_Event ev;
	SDL_memset( &ev, 0, sizeof( SDL_Event ) );

	ev.type = SDL_QUIT;
	int status = SDL_PushEvent( &ev );

	if( status == 0 )
	{
		print( "QUIT events are being filtered!!!" );
		return;
	}

	if( status == -1 )
	{
		error( "Event queue may be full, flushing..." );
		SDL_FlushEvents( SDL_FIRSTEVENT, SDL_LASTEVENT );

		if( SDL_PushEvent( &ev ) == -1 )
		{
			error( "Unknown event error!" );
			return;
		}
	}
}

void sys::shutdown()
{
	if( main_renderer )
	{
		SDL_DestroyRenderer( main_renderer );
		main_renderer = nullptr;
	}

	if( main_window )
	{
		SDL_DestroyWindow( main_window );
		main_window = nullptr;
	}

	SDL_Quit();
}

void sys::flush_events( void )
{
	SDL_Event ev;

	while( SDL_PollEvent( nullptr ) )
	{
		if( SDL_WaitEvent( &ev ) == 0 )
		{
			error( "SDL_WaitEvent returned an error" );
			break;
		}

		wndproc( ev );
	}
}

void sys::final_update( void )
{
	SDL_RenderClear( main_renderer );
	SDL_RenderPresent( main_renderer );
}

const char* sys::get_error()
{
	return SDL_GetError();
}

void sys::clear_error()
{
	return SDL_ClearError();
}

bool sys::is_running( void )
{
	return isRunning;
}