#pragma once
#include <vector>
#include <Dependencies/ImGui/imgui.h>

class IGUIRender {
public:
	virtual void Render( ) = 0;
	virtual void SetDPIScale( float& source ) = 0;

	struct GUIRenderData_t {
		std::vector<ImFont*> aFontsPointers;

		float flDPIScale = 1.0f;
	} RenderData;
};

class IGUIData {
public:
	virtual void InitFonts( ) = 0;
	virtual void InitColors( ) = 0;
};

class IGUI : public IGUIRender, public IGUIData {
public:

protected:

};

class CGUI : public IGUI {
public:
	void Render( ) override;
	void SetDPIScale( float& source ) override;
	
	void InitFonts( ) override;
	void InitColors( ) override;
};

class IGUIManager {
public:
	virtual void SetupGUI( IGUI* source ) = 0;
protected:
	IGUI* pGUI = nullptr;
};