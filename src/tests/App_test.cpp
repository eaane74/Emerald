#include "App_test.h"

CApp_test::CApp_test( void ) : m_isInitialized( false )
{
	//ctor
}

CApp_test::~CApp_test( void )
{
	//dtor
}

int CApp_test::Initialize( void )
{
	m_isInitialized = true;

	return 1;
}

void CApp_test::Shutdown( void )
{
	m_isInitialized = false;
}

void CApp_test::Process( void )
{
}

void CApp_test::Update( void )
{
}

void CApp_test::OnKeyup( int key )
{
}

void CApp_test::OnKeydown( int key )
{
}