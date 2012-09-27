#include "../system.h"
#include "../input.h"
#include "../globals.h"

int main(int argc, char *argv[])
{
	if( !Globals::g_Sys->Initialize() ) return -1;

	while( Globals::g_Sys->isRunning() ) 
	{
		Globals::g_Sys->Process();

		sys::Event ev;
		while( sys::poll_event( ev ) )
		{
			if( ev.type == sys::Event::KEYUP )
			{
				if( ev.data1 == Keys::K_Escape )
					Globals::g_Sys->Quit();
				break;
			}
		}

		Globals::g_Sys->Update();
	}
	
	Globals::g_Sys->Shutdown();
	
	return 0;
}