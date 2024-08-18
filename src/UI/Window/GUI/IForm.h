#pragma once

enum FORMS_ID : int {
	LOGIN,
	LOADING,
	CONNECTING,
};

class IFormAnimation {
public:
	virtual void Reset( ) = 0;
	virtual bool Animate( ) = 0;
protected:
	float flAnimationTime = 0.0f;
	bool bAnimationCompleted = false;
};

class IForm : public IFormAnimation {
public:
	virtual void Render( ) = 0;
};