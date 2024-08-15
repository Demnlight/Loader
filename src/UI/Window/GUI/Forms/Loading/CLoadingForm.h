#pragma once
#include "../../IForm.h"

#include <string>

class CLoadingForm : public IForm {
public:
	CLoadingForm(  );

	void Render( ) override;

	void Reset( ) override;
	void Animate( ) override;

private:

	std::string LoadingLabel = "";
};