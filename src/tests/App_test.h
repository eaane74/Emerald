#ifndef APP_TEST_H
#define APP_TEST_H

#include "../Interfaces.h"

class CApp_test : public IApplication
{
public:
	CApp_test( void );
	~CApp_test( void );

	int Initialize( void );
	void Shutdown( void );
	void Process( void );
	void Update( void );

	void OnKeyup( int key );
	void OnKeydown( int key );

	bool isInitialized( void ) const { return m_isInitialized; }

private:
	bool m_isInitialized;
};

#endif