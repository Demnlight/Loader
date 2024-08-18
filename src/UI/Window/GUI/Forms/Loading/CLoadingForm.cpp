#include "CLoadingForm.h"

#include <Dependencies/ImGui/imgui.h>
#include <Dependencies/ImGui/imgui_internal.h>

#include "../../ImGuiWrapper/CImGuiWrapper.h"

#include <Windows.h>

CLoadingForm::CLoadingForm( ) {
	this->Reset( );
}

void CLoadingForm::Render( ) {
	this->Animate( );

	ImVec2 wp = ImGui::GetWindowPos( );
	ImVec2 ws = ImGui::GetWindowSize( );

	g_ImGuiWrapper->Spinner( this->LoadingLabel.c_str( ), ImGui::GetWindowWidth( ) / 4 * ImGui::GetDPI( ), static_cast< int >( 4.0f * ImGui::GetDPI( ) ), ImColor( 255, 255, 255, 255 ), wp + ws / 2 );
}

bool CLoadingForm::Animate( ) {
	this->flAnimationTime += 1.0f * ImGui::GetIO( ).DeltaTime;

	return true;
}

void CLoadingForm::Reset( ) {
	this->flAnimationTime = 0.0f;
	this->bAnimationCompleted = false;
}