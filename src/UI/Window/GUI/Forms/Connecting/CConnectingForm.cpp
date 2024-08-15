#include "CConnectingForm.h"

#include <Dependencies/ImGui/imgui.h>
#include <Dependencies/ImGui/imgui_internal.h>

#include "../../ImGuiWrapper/CImGuiWrapper.h"

#include <Windows.h>

CConnectingForm::CConnectingForm( ) {
	this->Reset( );
}

void CConnectingForm::Render( ) {
	this->Animate( );

	ImVec2 wp = ImGui::GetWindowPos( );
	ImVec2 ws = ImGui::GetWindowSize( );

	g_ImGuiWrapper->Spinner( this->LoadingLabel.c_str( ), ImGui::GetWindowWidth( ) / 4 * ImGui::GetDPI( ), static_cast< int >( 4.0f * ImGui::GetDPI( ) ), ImColor( 255, 255, 255, 255 ), wp + ws / 2 );
}

void CConnectingForm::Animate( ) {
	this->flAnimationTime += 1.0f * ImGui::GetIO( ).DeltaTime;

	if ( strcmp( this->LoadingLabel.c_str( ), "Connecting" ) >= 0 ) {
		switch ( static_cast< int >( this->flAnimationTime ) % 3 ) {
		case 0: this->LoadingLabel = "Connecting."; break;
		case 1: this->LoadingLabel = "Connecting.."; break;
		case 2: this->LoadingLabel = "Connecting..."; break;
		default: break;
		}
	}
}

void CConnectingForm::Reset( ) {
	this->flAnimationTime = 0.0f;
	this->bAnimationCompleted = false;
}