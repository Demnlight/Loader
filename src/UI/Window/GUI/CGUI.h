#pragma once
#include <vector>
#include <Dependencies/ImGui/imgui.h>

#include "CFormManager.h"

class IGUIRender {
public:
	virtual void Render( ) = 0;

public:
	struct GUIRenderData_t {
		ImVec2 vWindowSize;
	} RenderData;

	CFormManager FormManager;
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
	
	void InitFonts( ) override;
	void InitColors( ) override;
};

class IGUIManager {
public:
	virtual void SetupGUI( IGUI* source ) = 0;
protected:
	IGUI* pGUI = nullptr;
};