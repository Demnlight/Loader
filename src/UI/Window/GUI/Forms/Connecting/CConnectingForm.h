#pragma once
#include "../../IForm.h"
#include "../../CFormManager.h"

#include <string>
#include <thread>

enum class ConnectingStatus_t : int {
	CONNECTING,
	FAILED,
	CONNECTED
};

class CConnectingForm : public IForm {
public:
	CConnectingForm( IFormManager* source );

	void Render( ) override;

	void Reset( ) override;
	bool Animate( ) override;

	void SetLabel( std::string source ) {
		this->LoadingLabel = source;
	}

	void SetStatus( ConnectingStatus_t source ) {
		if ( source == ConnectingStatus_t::CONNECTED )
			this->flLastConnectedTime = this->flAnimationTime;

		this->eStatus = source;
	}

	void FreeConnectionThread( ) {
		if ( this->ConnectionThread.joinable( ) )
			this->ConnectionThread.join( );
	}

private:

	std::string LoadingLabel = "Connecting";
	
	ConnectingStatus_t eStatus;

	float flLastConnectedTime = 0.0f;

	std::thread ConnectionThread;

	IFormManager* FormManager = nullptr;
};