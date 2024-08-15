#pragma once
#include <Windows.h>
#include "CWindow.h"

static LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	CWindow* pWindow = ( CWindow* )GetWindowLongPtr( hWnd, GWLP_USERDATA );
	
	if ( pWindow )
		return pWindow->WindowProc( hWnd, msg, wParam, lParam );
	else
		return ::DefWindowProc( hWnd, msg, wParam, lParam );
}