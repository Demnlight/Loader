#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "IForm.h"

class IFormFabric {
public:
	void Create( FORMS_ID key, std::shared_ptr<IForm> form ) {
		if ( aForms.find( key ) == aForms.end( ) ) {
			aForms[ key ] = form;
		}
	}

protected:
	std::unordered_map<FORMS_ID, std::shared_ptr<IForm>> aForms;
};

class IFormManager : public IFormFabric {
public:
	virtual IForm* GetCurrentForm( ) = 0;
protected:
};

class CFormManager : public IFormManager {
public:
	CFormManager( );

	IForm* GetCurrentForm( ) override;

private:
	FORMS_ID eCurrentForm = FORMS_ID::LOGIN;
};