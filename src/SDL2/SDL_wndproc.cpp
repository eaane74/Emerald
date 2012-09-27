#include <SDL2/SDL.h>

#include "../system.h"
#include "../input.h"

Keys Convert_SDL_Keysym_to_Key( SDL_Keysym sym );
extern bool isRunning;

void wndproc( const SDL_Event& ev )
{
	sys::Event evnt;

	switch( ev.type )
	{
		case SDL_QUIT:
			//sys::debug_print( "SDL_QUIT event detected" );
			isRunning = false;
			break;
		case SDL_KEYUP:
			evnt.type = sys::Event::KEYUP;
			evnt.data1 = Convert_SDL_Keysym_to_Key( ev.key.keysym ).val;

			// add event only if key is valid
			if( evnt.data1 )
				sys::push_event( evnt );

			break;
		case SDL_KEYDOWN:
			evnt.type = sys::Event::KEYDOWN;
			evnt.data1 = Convert_SDL_Keysym_to_Key( ev.key.keysym ).val;

			// add event only if key is valid
			if( evnt.data1 )
				sys::push_event( evnt );

			break;
		case SDL_WINDOWEVENT:
		{
			switch( ev.window.event )
			{
				case SDL_WINDOWEVENT_CLOSE:
					sys::quit();
					break;
				default: break;
			}
			break;
		}
		default: break;
	}
}

Keys Convert_SDL_Keysym_to_Key( SDL_Keysym sym )
{
	Keys k;
	k.val = 0;

	if( !( sym.scancode & ( 1 << 30 ) ) )
	{
		// it is an ascii valued key
		k.val = sym.sym;
	}
	else
	{
		switch( sym.sym )
		{
			case SDLK_UP:
				k.val = Keys::K_Up;
				break;
			case SDLK_DOWN:
				k.val = Keys::K_Down;
				break;
			case SDLK_LEFT:
				k.val = Keys::K_Left;
				break;
			case SDLK_RIGHT:
				k.val = Keys::K_Right;
				break;
			case SDLK_F1:
				k.val = Keys::K_F1;
				break;
			case SDLK_F2:
				k.val = Keys::K_F2;
				break;
			case SDLK_F3:
				k.val = Keys::K_F3;
				break;
			case SDLK_F4:
				k.val = Keys::K_F4;
				break;
			case SDLK_F5:
				k.val = Keys::K_F5;
				break;
			case SDLK_F6:
				k.val = Keys::K_F7;
				break;
			case SDLK_F8:
				k.val = Keys::K_F8;
				break;
			case SDLK_F9:
				k.val = Keys::K_F9;
				break;
			case SDLK_F10:
				k.val = Keys::K_F10;
				break;
			case SDLK_F11:
				k.val = Keys::K_F11;
				break;
			case SDLK_F12:
				k.val = Keys::K_F12;
				break;
			default:
				k.val = Keys::K_None;
				break;
		}
	}

	return k;
}