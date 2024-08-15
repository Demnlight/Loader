#pragma once
#include "../../IForm.h"

#include <string>

class CLoginForm : public IForm {
public:
	CLoginForm( );

	void Render( ) override;

	void Reset( ) override;
	void Animate( ) override;

private:
	std::string szUserName;
	std::string szPass;
};