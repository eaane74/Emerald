#ifndef INTERFACES_H
#define INTERFACES_H

class ISystem
{
public:
        ISystem( void ) {}
virtual ~ISystem( void ) {}

virtual int Initialize( void )              = 0;
virtual void Quit( void )                   = 0;
virtual void Shutdown( void )               = 0;
virtual void Process( void )                = 0;
virtual void Update( void )                 = 0;

virtual bool isInitialized( void ) const    = 0;
virtual bool isRunning( void ) const        = 0;

virtual int Print( const char* fmt, ... )   = 0;
virtual int Error( const char* fmt, ... )   = 0;
virtual int Debug( const char* fmt, ... )   = 0;
};

class IApplication
{
public:
        IApplication( void ) {}
virtual ~IApplication( void ) {}

virtual int Initialize( void )              = 0;
virtual void ShutDown( void )               = 0;
virtual void Process( void )                = 0;
virtual void Update( void )                 = 0;

virtual void OnKeyup( int key )             = 0;
virtual void OnKeydown( int key )           = 0;

virtual bool isInitialized( void ) const    = 0;

    /* data */
};

#endif