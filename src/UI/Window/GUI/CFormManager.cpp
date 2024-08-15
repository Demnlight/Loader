#include "CFormManager.h"

#include "Forms/Login/CLoginForm.h"
#include "Forms/Loading/CLoadingForm.h"

#include <memory>

CFormManager::CFormManager( ) {
	this->Create( FORMS_ID::LOGIN, std::make_shared<CLoginForm>( ) );
	this->Create( FORMS_ID::LOADING, std::make_shared<CLoadingForm>( ) );

}


IForm* CFormManager::GetCurrentForm( ) {
	return this->aForms[ eCurrentForm ].get( );
}