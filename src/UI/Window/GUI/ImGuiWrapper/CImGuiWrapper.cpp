#include "CImGuiWrapper.h"

void CImGuiWrapper::Spinner( const char* label, float radius, int thickness, const ImU32& color, ImVec2 pos ) {
	ImGuiWindow* window = ImGui::GetCurrentWindow( );
	if ( window->SkipItems )
		return;

	ImVec2 hue_wheel_center( pos );
	const ImGuiID id = window->GetID( label );

	const ImRect bb( ImVec2( hue_wheel_center.x - radius, hue_wheel_center.y - radius ), ImVec2( hue_wheel_center.x + radius, hue_wheel_center.y + radius ) );
	ImGui::ItemSize( bb );
	if ( !ImGui::ItemAdd( bb, id ) )
		return;

	const ImU32 hue_wheel[ 6 + 1 ] = { ImColor( 99, 91, 189, 255 ), ImColor( 167, 100, 167, 255 ), ImColor( 220, 106, 115, 255 ), ImColor( 220, 106, 115, 255 ), ImColor( 167, 100, 167, 255 ), ImColor( 99, 91, 189, 255 ), ImColor( 99, 91, 189, 255 ) };
	const ImU32 col_white = ImColor( 255, 255, 255, 255 );
	const float aeps = 0.5f / ( radius / 2.f );
	const int segmentation = ImMax( 4, 512 );

	for ( int i = 0; i < 6; i++ ) {
		const float a0 = ( i ) / 6.0f * 2.0f * IM_PI - aeps;
		const float a1 = ( i + 1.0f ) / 6.0f * 2.0f * IM_PI + aeps;
		const int buff_start_idx = window->DrawList->VtxBuffer.Size;
		window->DrawList->PathArcTo( hue_wheel_center, radius, a0, a1, segmentation );
		window->DrawList->PathStroke( col_white, 0, static_cast< float >( thickness - 1 ) );
		const int buff_end_idx = window->DrawList->VtxBuffer.Size;

		ImVec2 gradient_p0( hue_wheel_center.x + ImCos( a0 ) * radius, hue_wheel_center.y + ImSin( a0 ) * radius );
		ImVec2 gradient_p1( hue_wheel_center.x + ImCos( a1 ) * radius, hue_wheel_center.y + ImSin( a1 ) * radius );
		ImGui::ShadeVertsLinearColorGradientKeepAlpha( window->DrawList, buff_start_idx, buff_end_idx, gradient_p0, gradient_p1, hue_wheel[ i ], hue_wheel[ i + 1 ] );
	}

	static float position = 0.f;
	position = ImLerp( position, IM_PI * 1.7f, 1.25f * ImGui::GetIO( ).DeltaTime );

	window->DrawList->PathClear( );
	window->DrawList->PathArcTo( hue_wheel_center, radius, IM_PI * 2.5f + ( position * 2.5f ), IM_PI * ( 3.35f + 0.45F ) + ( position * 2.6f ), 40 );
	window->DrawList->PathStroke( ImColor( 20, 20, 20, 255 ), 0, static_cast< float >( thickness + 1 ) );

	ImGui::PushStyleColor( ImGuiCol_Text, ImVec4( 200 / 255.f, 200 / 255.f, 200 / 255.f, 1.0f ) );
	ImGui::RenderTextClipped( bb.Min, bb.Max, label, 0, 0, ImVec2( 0.5f, 0.5f ) );
	ImGui::PopStyleColor( );

	//Reset anim
	if ( position >= IM_PI * 1.5f )
		position = -0.16f;
}

void CImGuiWrapper::InputText( ) {
}