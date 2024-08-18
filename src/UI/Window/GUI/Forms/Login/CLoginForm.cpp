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

	ImGui::GetWindowDrawList( )->AddText( wp + ImVec2( 100, 100 ), ImColor( 255, 255, 255, 255 ), "GAY" );

}

bool CLoginForm::Animate( ) {
	this->flAnimationTime += 1.0f * ImGui::GetIO( ).DeltaTime;

	return true;
}

void CLoginForm::Reset( ) {
	this->flAnimationTime = 0.0f;
	this->bAnimationCompleted = false;
}