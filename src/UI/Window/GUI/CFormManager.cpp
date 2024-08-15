#include "CFormManager.h"

#include "Forms/Login/CLoginForm.h"
#include "Forms/Loading/CLoadingForm.h"
#include "Forms/Connecting/CConnectingForm.h"

#include <memory>

CFormManager::CFormManager( ) {
	this->Create( FORMS_ID::LOGIN, std::make_shared<CLoginForm>( ) );
	this->Create( FORMS_ID::LOADING, std::make_shared<CLoadingForm>( ) );
	this->Create( FORMS_ID::CONNECTING, std::make_shared<CConnectingForm>( ) );

}


IForm* CFormManager::GetCurrentForm( ) {
	return this->aForms[ eCurrentForm ].get( );
}