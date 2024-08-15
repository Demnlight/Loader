#pragma once
#include <memory>

#include <Dependencies/ImGui/imgui.h>
#include <Dependencies/ImGui/imgui_internal.h>

class IImGuiWrapper {
public:
	virtual void Spinner( const char* label, float radius, int thickness, const ImU32& color, ImVec2 pos ) = 0;
	virtual void InputText( ) = 0;
};

class CImGuiWrapper : IImGuiWrapper {
public:
	void Spinner( const char* label, float radius, int thickness, const ImU32& color, ImVec2 pos ) override;
	void InputText( ) override;

};

inline std::unique_ptr<CImGuiWrapper> g_ImGuiWrapper = std::make_unique<CImGuiWrapper>( );