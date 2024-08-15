#include "WndProc.h"

#include <Dependencies/ImGui/backends/imgui_impl_win32.h>
#include <Dependencies/ImGui/backends/imgui_impl_dx9.h>

#include <Dependencies/ImGui/imgui_internal.h>

void CWindow::Create( ) {
	ImGui::CreateContext( );

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow( );
	GetWindowRect( hDesktop, &desktop );

	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof( WNDCLASSEX );
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA( 0 );
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "Laconism";
	windowClass.hIconSm = 0;

	RegisterClassEx( &windowClass );

	this->Data.hwnd = ::CreateWindowExA( WS_EX_APPWINDOW, windowClass.lpszClassName, this->Data.szName.c_str( ), WS_POPUP,
		desktop.right / 2 - this->Data.vSize.x / 2,
		desktop.bottom / 2 - this->Data.vSize.y / 2,
		this->Data.vSize.x, this->Data.vSize.y, NULL, NULL, windowClass.hInstance, NULL );

	SetWindowLongPtr( this->Data.hwnd, GWLP_USERDATA, ( LONG_PTR )this );

	ImGui::SetDPI( ImGui_ImplWin32_GetDpiScaleForHwnd( this->Data.hwnd ) );

	this->Data.vSize *= ImGui::GetDPI( );
	SetWindowPos( this->Data.hwnd, 0, 0, 0, this->Data.vSize.x, this->Data.vSize.y, SWP_NOMOVE );

	if ( !CreateDeviceD3D( this->Data.hwnd ) ) {
		CleanupDeviceD3D( );
		::UnregisterClass( windowClass.lpszClassName, windowClass.hInstance );
		throw std::exception( "Failed to init D3DDevice" );
		return;
	}
}

void CWindow::Handler( ) {
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	while ( msg.message != WM_QUIT ) {
		if ( int result = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );

			if ( result == 0 )
				break;
			continue;
		}

		ImGui_ImplDX9_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );
		{
			this->pGUI->Render( );
		}
		ImGui::EndFrame( );

		DeviceData.Device->SetRenderState( D3DRS_ZENABLE, FALSE );
		DeviceData.Device->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		DeviceData.Device->SetRenderState( D3DRS_SCISSORTESTENABLE, FALSE );

		if ( DeviceData.Device->BeginScene( ) >= 0 ) {
			ImGui::Render( );
			ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
			DeviceData.Device->EndScene( );
		}

		DeviceData.Device->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 0, 0, 0, 255 ), 1.0f, 0 );

		if ( DeviceData.Device->BeginScene( ) >= 0 ) {
			ImGui::Render( );
			ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
			DeviceData.Device->EndScene( );
		}

		const auto result = DeviceData.Device->Present( 0, 0, 0, 0 );

		// Handle loss of D3D9 device
		if ( result == D3DERR_DEVICELOST && DeviceData.Device->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET )
			DeviceData.ResetDevice( );
	}
}

void CWindow::SetupImGui( ) {
	this->DecoratorData.io = &ImGui::GetIO( );
	this->DecoratorData.io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	this->DecoratorData.io->IniFilename = nullptr;

	if ( this->pGUI ) {
		this->pGUI->InitColors( );
		this->pGUI->InitFonts( );
	}

	ImGui_ImplWin32_Init( this->Data.hwnd );
	ImGui_ImplDX9_Init( DeviceData.Device );
}

void CWindow::Show( ) {
	::ShowWindow( this->Data.hwnd, SW_SHOWDEFAULT );
	::UpdateWindow( this->Data.hwnd );
}

void CWindow::Hide( ) {
	::ShowWindow( this->Data.hwnd, SW_HIDE );
	::UpdateWindow( this->Data.hwnd );
}

void CWindow::Destroy( ) {
	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );

	CleanupDeviceD3D( );
	::DestroyWindow( this->Data.hwnd );
	::UnregisterClass( this->Data.szName.c_str( ), GetModuleHandle( NULL ) );
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT WINAPI CWindow::WindowProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	if ( ImGui_ImplWin32_WndProcHandler( hWnd, msg, wParam, lParam ) )
		return true;

	switch ( msg ) {
	case WM_SIZE:
		if ( DeviceData.D3D != NULL && wParam != SIZE_MINIMIZED ) {
			DeviceData.PresentParams.BackBufferWidth = LOWORD( lParam );
			DeviceData.PresentParams.BackBufferHeight = HIWORD( lParam );
			DeviceData.ResetDevice( );
		}
		return 0;
	case WM_SYSCOMMAND:
		if ( ( wParam & 0xfff0 ) == SC_KEYMENU ) // Disable ALT application menu
			return 0;
		break;

	case WM_CLOSE:
		::PostQuitMessage( 0 );
		return 0;
		break;

	case WM_DESTROY:
		::PostQuitMessage( 0 );
		return 0;
		break;
	case WM_LBUTTONDOWN:
	{
		this->Data.vPosition = MAKEPOINTS( lParam ); // set click points
	}return 0;

	case WM_MOUSEMOVE:
	{
		if ( wParam == MK_LBUTTON ) {
			const auto points = MAKEPOINTS( lParam );
			auto rect = ::RECT{ };

			GetWindowRect( this->Data.hwnd, &rect );

			rect.left += points.x - this->Data.vPosition.x;
			rect.top += points.y - this->Data.vPosition.y;

			if ( this->Data.vPosition.x >= 0 &&
				this->Data.vPosition.x <= 200 &&
				this->Data.vPosition.y >= 0 && this->Data.vPosition.y <= 19 )
				SetWindowPos(
					this->Data.hwnd,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}

	}return 0;
	}
	return ::DefWindowProc( hWnd, msg, wParam, lParam );
}

bool CWindow::CreateDeviceD3D( HWND hWnd ) {
	if ( ( DeviceData.D3D = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL )
		return false;

	ZeroMemory( &DeviceData.PresentParams, sizeof( DeviceData.PresentParams ) );
	DeviceData.PresentParams.Windowed = TRUE;
	DeviceData.PresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	DeviceData.PresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
	DeviceData.PresentParams.EnableAutoDepthStencil = TRUE;
	DeviceData.PresentParams.AutoDepthStencilFormat = D3DFMT_D16;
	DeviceData.PresentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	if ( DeviceData.D3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &DeviceData.PresentParams, &DeviceData.Device ) < 0 )
		return false;

	return true;
}

void CWindow::CleanupDeviceD3D( ) {
	if ( DeviceData.Device ) { DeviceData.Device->Release( ); DeviceData.Device = NULL; }
	if ( DeviceData.D3D ) { DeviceData.D3D->Release( ); DeviceData.D3D = NULL; }
}

void CWindow::DeviceData_t::ResetDevice( ) {
	ImGui_ImplDX9_InvalidateDeviceObjects( );
	HRESULT hr = Device->Reset( &PresentParams );
	if ( hr == D3DERR_INVALIDCALL )
		IM_ASSERT( 0 );

	ImGui_ImplDX9_CreateDeviceObjects( );
}

void CWindow::SetupGUI( IGUI* source ) {
	if ( source ) {
		this->pGUI = source;
		this->pGUI->RenderData.vWindowSize = ImVec2( static_cast< float >( this->Data.vSize.x ), static_cast< float >( this->Data.vSize.y ) );
	}
};