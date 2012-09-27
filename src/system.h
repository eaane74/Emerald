#ifndef SYSTEM_H_
#define SYSTEM_H_

namespace sys
{
	/*
	 *	Initiallization and shutdown functions should only be
	 *	called once per program lifetime.
	 *	The quit function forces a system quit.
	 */
	bool init( void );
	void shutdown( void );
	void quit( void );
	void final_update( void );

	void flush_events( void );

	/*
	 *	System specific error handling
	 */
	const char* get_error( void );
	void clear_error( void );

	int error( const char* error, ... );
	int debug_print( const char* msg, ... );
	int print( const char* msg, ... );

	bool is_running( void );

	/*
	 *	Cross platform event stuff.
	 *	These functions should only be called in one .cpp file
	 */
	struct Event
	{
		enum Event_type
		{ 
			NONE,
			KEYUP,
			KEYDOWN,
			MOUSE,
			JOY
		} type;

		int data1;
		int data2;
		int data3;
	};

	void push_event( const Event& ev );
	int poll_event( Event& pev );
}

#endif
