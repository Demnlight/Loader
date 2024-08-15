#pragma once
#include <memory>

class Vector2 {
public:
	Vector2( ) {
		this->x = 0;
		this->y = 0;
	}

	explicit Vector2( int value ) {
		this->x = value;
		this->y = value;
	}

	explicit Vector2( int _x, int _y ) {
		this->x = _x;
		this->y = _y;
	}

	Vector2( Vector2&& vec ) noexcept {
		this->x = std::move( vec.x );
		this->y = std::move( vec.y );
	}

	Vector2( Vector2& vec ) {
		this->x = vec.x;
		this->y = vec.y;
	};

	Vector2& operator=( const Vector2& other ) {
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	Vector2& operator+( const Vector2& other ) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vector2& operator-( const Vector2& other ) {
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vector2& operator*( const Vector2& other ) {
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	Vector2& operator*( const float& val ) {
		float newX = static_cast< float >( this->x ) * val;
		float newY = static_cast< float >( this->y ) * val;
		this->x = static_cast< int >( newX );
		this->y = static_cast< int >( newY );
		return *this;
	}

	Vector2& operator*=( const Vector2& other ) {
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	Vector2& operator*=( const float& val ) {
		float newX = static_cast< float >( this->x ) * val;
		float newY = static_cast< float >( this->y ) * val;
		this->x = static_cast< int >( newX );
		this->y = static_cast< int >( newY );
		return *this;
	}

	Vector2& operator/( const Vector2& other ) {
		this->x /= other.x;
		this->y /= other.y;
		return *this;
	}

	Vector2& operator/( const int& val ) {
		this->x /= val;
		this->y /= val;
		return *this;
	}

	~Vector2( ) = default;

public:
	int x;
	int y;
};