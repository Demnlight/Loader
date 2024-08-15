#include "CLoadingForm.h"

#include <Dependencies/ImGui/imgui.h>
#include <Dependencies/ImGui/imgui_internal.h>

#include <Windows.h>

CLoadingForm::CLoadingForm( ) {
	this->Reset( );
}

void CLoadingForm::Render( ) {
	
}

void CLoadingForm::Reset( ) {
	this->flAnimationTime = 0.0f;
	this->bAnimationCompleted = false;
}