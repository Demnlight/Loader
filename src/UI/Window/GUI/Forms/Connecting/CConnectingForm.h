#pragma once
#include "../../IForm.h"

#include <string>

class CConnectingForm : public IForm {
public:
	CConnectingForm( );

	void Render( ) override;

	void Reset( ) override;
	void Animate( ) override;

private:

	std::string LoadingLabel = "Connecting";
};