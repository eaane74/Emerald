#include "Interfaces.h"
#include "system.h"
#include "globals.h"

#include <cstdarg>
#include <cstdio>

#define MAX_OUTPUT_STRING 	Globals::Max_Output_String

class CSystem : public ISystem
{
public:
		CSystem( void );
virtual ~CSystem( void );

	int Initialize( void );
	void Shutdown( void );
	void Quit( void );
	void Process( void ); 
	void Update( void );

	bool isInitialized( void ) const { return m_isInitialized; }
	bool isRunning( void ) const { return sys::is_running(); }

	int Print( const char* fmt, ... );
	int Error( const char* fmt, ... );
	int Debug( const char* fmt, ... );

private:
	bool m_isInitialized;
};

CSystem _sys;
ISystem* Globals::g_Sys = &_sys;

CSystem::CSystem( void ) : m_isInitialized( false )
{
	//ctor
}

CSystem::~CSystem( void )
{
	//dtor
}

int CSystem::Initialize( void )
{
	if( m_isInitialized == true ) return true;

	m_isInitialized = sys::init();

	return m_isInitialized;
}

void CSystem::Shutdown( void )
{
	if( m_isInitialized == false ) return;

	sys::shutdown();
	m_isInitialized = false;
}

void CSystem::Quit( void )
{
	return sys::quit();
}

void CSystem::Process( void )
{
	sys::flush_events();
}

void CSystem::Update( void )
{
	sys::final_update();
}

int CSystem::Print( const char* fmt, ... )
{
	va_list ap;
	char buffer[MAX_OUTPUT_STRING];

	va_start( ap, fmt );
		int len = std::vsnprintf( buffer, MAX_OUTPUT_STRING - 1, fmt, ap );
	va_end( ap );

	return ( len + sys::print( "%s", buffer ) );
}

int CSystem::Debug( const char* fmt, ... )
{
	int len = 0;
#ifdef _DEBUG
	va_list ap;
	char buffer[MAX_OUTPUT_STRING];

	va_start( ap, fmt );
		len = std::vsnprintf( buffer, MAX_OUTPUT_STRING - 1, fmt, ap );
	va_end( ap );

	sys::print( "%s", buffer );
#endif
	return len;
}

int CSystem::Error( const char* fmt, ... )
{
	int len = 0;

	va_list ap;
	char buffer[MAX_OUTPUT_STRING];

	va_start( ap, fmt );
		len = std::vsnprintf( buffer, MAX_OUTPUT_STRING - 1, fmt, ap );
	va_end( ap );

	return ( len + sys::error( "%s", buffer ) );
}

int sys::error( const char *error, ... )
{
	// wtf?
	if( !error ) return -1;

	char buffer[MAX_OUTPUT_STRING];

	va_list ap;
	va_start( ap, error );
		int len = vsnprintf( buffer, MAX_OUTPUT_STRING - 1, error, ap );
	va_end( ap );

	fprintf( stderr, "ERROR: %s\n", buffer );

	const char* err = sys::get_error();

	// See if the system detected an error
	if ( err )
		fprintf( stderr, "%s\n", err );

	// flush stderr to force a write
	fflush( stderr );

	// clear out the garbage if any
	sys::clear_error();

	return len;
}

int sys::debug_print( const char *msg, ... )
{
	int len = 0;
#ifdef _DEBUG
	// wtf?
	if( !msg ) return -1;

	char buffer[MAX_OUTPUT_STRING];

	va_list ap;
	va_start( ap, msg );
		len = vsnprintf( &buffer[0], MAX_OUTPUT_STRING, msg, ap );
	va_end( ap );

	// output to stdout and flush to force a write
	fprintf( stdout, "DEBUG:\t%s\n", buffer );
	fflush( stdout );
#endif
	return len;
}

int sys::print( const char *msg, ... )
{
	int len = 0;

	// wtf?
	if( !msg ) return -1;

	char buffer[MAX_OUTPUT_STRING];

	va_list ap;
	va_start( ap, msg );
		len = vsnprintf( &buffer[0], MAX_OUTPUT_STRING, msg, ap );
	va_end( ap );

	// output to stdout and flush to force a write
	fprintf( stdout, "%s\n", buffer );
	fflush( stdout );

	return len;
}

/*
 *	Event handling stuff
 */
 #define MAX_EVENTS 			Globals::Max_Events
 #define EVENT_MASK				Globals::Event_Mask

sys::Event gEvents[MAX_EVENTS];
int gHead = 0;
int gTail = 0;

void sys::push_event( const Event &ev )
{
	gEvents[gHead] = ev;
	gHead = ( ( ++gHead ) & EVENT_MASK );
}

int sys::poll_event( Event& ev )
{
	gTail = ( ( ++gTail ) & EVENT_MASK );
	ev = gEvents[gTail];

	return gHead != gTail;
}