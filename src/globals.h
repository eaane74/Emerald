#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "Interfaces.h"

class Globals
{
public:
static const int Default_Window_Width 	= 640;
static const int Default_Window_Height 	= 480;
static const int Max_Output_String		= 2048;
static const int Max_Events				= 256;
static const int Event_Mask				= Max_Events - 1;

static ISystem* g_Sys;
static IApplication* g_App;

private:
	// These stay unimplemented!
	Globals( void );
	Globals( const Globals& );
	Globals& operator=( const Globals& );
	~Globals( void );
};

#endif