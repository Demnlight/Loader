#include <src/UI/Window/CWindow.h>

int APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, PSTR Line, int Show ) {

	std::unique_ptr<CWindow> pWindow = std::make_unique<CWindow>( WindowData_t(
		"Laconism",
		Vector2( 200, 200 )
	) );

	pWindow->Create( );
	pWindow->SetupImGui( );

	pWindow->Show( );
	pWindow->Handler( );

	pWindow->Destroy( );
	return 0;
}