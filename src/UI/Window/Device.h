#pragma once
#include <d3d9.h>

class IDevice {
public:
	virtual bool CreateDeviceD3D( HWND hWnd ) = 0;
	virtual void CleanupDeviceD3D( ) = 0;
protected:
	struct DeviceData_t {
		LPDIRECT3D9 D3D;
		LPDIRECT3DDEVICE9 Device;
		D3DPRESENT_PARAMETERS PresentParams;

		void ResetDevice( );
	} DeviceData;
};