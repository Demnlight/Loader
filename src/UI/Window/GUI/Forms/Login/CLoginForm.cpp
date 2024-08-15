#include "CLoginForm.h"

#include <Dependencies/ImGui/imgui.h>
#include <Dependencies/ImGui/imgui_internal.h>
#include <Dependencies/ImGui/imgui_stdlib.h>

#include <Windows.h>

CLoginForm::CLoginForm( ) {
	this->Reset( );
}

void CLoginForm::Render( ) {
	this->Animate( );

	ImVec2 wp = ImGui::GetWindowPos( );
	ImVec2 ws = ImGui::GetWindowSize( );

}

void CLoginForm::Animate( ) {
	this->flAnimationTime += 1.0f * ImGui::GetIO( ).DeltaTime;
}

void CLoginForm::Reset( ) {
	this->flAnimationTime = 0.0f;
	this->bAnimationCompleted = false;
}