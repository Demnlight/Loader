#include "CLoginForm.h"

#include <Dependencies/ImGui/imgui.h>
#include <Dependencies/ImGui/imgui_internal.h>
#include <Dependencies/ImGui/imgui_stdlib.h>

#include <Windows.h>

CLoginForm::CLoginForm( ) {
	this->Reset( );
}

void CLoginForm::Render( ) {
	ImVec2 wp = ImGui::GetWindowPos( );
	ImVec2 ws = ImGui::GetWindowSize( );

	ImGui::SetCursorPos( ImVec2( ws.x - ( 12 + 3 ) * ImGui::GetDPI( ), 3 * ImGui::GetDPI( ) ) );
	if ( ImGui::Button( ( "X" ), ImVec2( 12 * ImGui::GetDPI( ), 14 * ImGui::GetDPI( ) ) ) ) {
		PostMessage( GetActiveWindow( ), WM_CLOSE, 0, 0 );
	};

	int offset = static_cast<int>( 70.0f * ImGui::GetDPI( ) );
	ImRect m_rLogoZone = ImRect( ImVec2( wp.x + offset, wp.y + 0 ), ImVec2( wp.x + ws.x - offset, wp.y + 65 * ImGui::GetDPI( ) ) );

	ImGui::PushFont( ImGui::GetIO().Fonts->Fonts[ 1 ] );
	ImGui::RenderTextClipped( m_rLogoZone.Min, m_rLogoZone.Max, ( "Laconism" ), 0, 0, ImVec2( 0.5f, 0.5f ) );
	ImGui::PopFont( );

	ImGui::SetNextWindowPos( ImVec2( m_rLogoZone.Min.x - 20 * ImGui::GetDPI( ), m_rLogoZone.Max.y ) );
	ImGui::BeginChild( ( "Child" ), ImVec2( m_rLogoZone.Max.x - m_rLogoZone.Min.x + 40 * ImGui::GetDPI( ), 119 * ImGui::GetDPI( ) ), false );

	ImGui::Dummy( ImVec2( 0, 1 * ImGui::GetDPI( ) ) );

	ImGui::InputText( ( "Username" ), &this->szUserName );
	ImGui::InputText( ( "Password" ), &this->szPass, ImGuiInputTextFlags_Password );

	ImGui::SetCursorPos( ImVec2( 8, 90 * ImGui::GetDPI( ) ) );

	ImVec2 m_vecButtonSize = ImVec2( ( ws.x - ( offset - 20 * ImGui::GetDPI( ) ) * 2 - ImGui::GetStyle( ).ItemSpacing.x * 3 ) / 2, 20 * ImGui::GetDPI( ) );

	if ( ImGui::Button( ( "Forgot Pas" ), m_vecButtonSize ) ) {
	}

	ImGui::SameLine( );

	if ( ImGui::Button( ( "Login" ), m_vecButtonSize ) ) {
		//CFormManager::Instance( ).SetCurrentForm( Forms_t::LOADING );
	}

	ImGui::EndChild( );
}

void CLoginForm::Reset( ) {
	this->flAnimationTime = 0.0f;
	this->bAnimationCompleted = false;
}