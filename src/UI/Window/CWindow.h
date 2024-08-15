#pragma once
#include <string>
#include <Windows.h>

#include <Dependencies/Vector/Vector.h>

#include "Decorator.h"
#include "Device.h"

class WindowData_t {
public:
	WindowData_t( ) { };

	WindowData_t( 
		 std::string szName,
		 Vector2 vSize ) {

		this->szName = std::move( szName );
		this->vSize = std::move( vSize );
	};

	std::string szName;
	Vector2 vSize;
};

class IWindow {
public:
	virtual void Create( ) = 0;
	virtual void Destroy( ) = 0;

	virtual void Show() = 0;
	virtual void Hide() = 0;

	virtual void Handler() = 0;
protected:
	WindowData_t Data;
};

class CWindow : IWindow, IWindowDecorator, IDevice {
public:
	CWindow( ) = delete;

	CWindow(WindowData_t&& Data) {
		this->Data.szName = std::move( Data.szName );
		this->Data.vSize = std::move( Data.vSize );
	};

	~CWindow() {

	};

	CWindow(CWindow const&) = delete;
	CWindow(CWindow&&) = delete;
	CWindow operator=(CWindow const&) = delete;
	CWindow operator=(CWindow&&) = delete;

	void Create( ) override;
	void Destroy() override;

	void Show() override;
	void Hide() override;

	void Handler() override;

	bool CreateDeviceD3D( HWND hWnd ) override;
	void CleanupDeviceD3D( ) override;

	void SetupImGui( ) override;

	static LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
private:
};