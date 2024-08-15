#pragma once
#include <Dependencies/ImGui/imgui.h>

class IWindowDecorator {
public:
	virtual void SetupImGui( ) = 0;
protected:
	struct DecoratorData_t {
		ImGuiIO* io = nullptr;
	} DecoratorData;
};