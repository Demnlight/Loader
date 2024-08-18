#include "CConnectingForm.h"

#include <Dependencies/ImGui/imgui.h>
#include <Dependencies/ImGui/imgui_internal.h>

#include "../../ImGuiWrapper/CImGuiWrapper.h"
#include <src/Server Connection/CConnector.h>

#include <Windows.h>

void ConnectorThread( CConnectingForm* source ) {

	source->SetStatus( ConnectingStatus_t::CONNECTING );

	if ( g_Connector->Connect( "127.0.0.1", 443 ) ) {
		source->SetStatus( ConnectingStatus_t::CONNECTED );
		source->SetLabel( "Connected" );

	} else {
		source->SetStatus( ConnectingStatus_t::FAILED );
		source->SetLabel( "Failed to connect" );
	}
}

CConnectingForm::CConnectingForm( IFormManager* source ) {
	this->FormManager = source;

	this->Reset( );
	this->ConnectionThread = std::thread( ConnectorThread, this );
}

void CConnectingForm::Render( ) {
	if ( !this->Animate( ) ) {
		this->FormManager->SetCurrentForm( FORMS_ID::LOGIN );
		return;
	}

	ImVec2 wp = ImGui::GetWindowPos( );
	ImVec2 ws = ImGui::GetWindowSize( );

	g_ImGuiWrapper->Spinner( this->LoadingLabel.c_str( ), ImGui::GetWindowWidth( ) / 4 * ImGui::GetDPI( ), static_cast< int >( 4.0f * ImGui::GetDPI( ) ), ImColor( 255, 255, 255, 255 ), wp + ws / 2 );
}

bool CConnectingForm::Animate( ) {
	if ( this->eStatus == ConnectingStatus_t::CONNECTED && abs( this->flLastConnectedTime - this->flAnimationTime) > 1.0f ) {
		this->FreeConnectionThread( );
		return false;
	}

	this->flAnimationTime += 1.0f * ImGui::GetIO( ).DeltaTime;

	if ( this->eStatus == ConnectingStatus_t::CONNECTING ) {
		if ( strcmp( this->LoadingLabel.c_str( ), "Connecting" ) >= 0 ) {
			switch ( static_cast< int >( this->flAnimationTime ) % 3 ) {
			case 0: this->LoadingLabel = "Connecting."; break;
			case 1: this->LoadingLabel = "Connecting.."; break;
			case 2: this->LoadingLabel = "Connecting..."; break;
			default: break;
			}
		}
	}

	return true;
}

void CConnectingForm::Reset( ) {
	this->flAnimationTime = 0.0f;
	this->bAnimationCompleted = false;
}