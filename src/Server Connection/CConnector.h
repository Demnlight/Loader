#pragma once
#include <string>
#include <memory>

#include <winsock2.h>
#include <stdexcept>
#pragma comment(lib, "WS2_32.lib")

class CConnector {
public:
	CConnector( ) {
		WSADATA WSAData;
		if ( WSAStartup( MAKEWORD( 2, 0 ), &WSAData ) ) {
			throw std::runtime_error( "Failed to startup" );
			return;
		}

		this->Socket = socket( AF_INET, SOCK_STREAM, 0 );

		if ( !this->Socket ) {
			throw std::runtime_error( "Failed to get socket" );
			return;
		}
	}
	~CConnector( ) {
		int iResult = shutdown( this->Socket, SD_SEND );
		closesocket( this->Socket );
		WSACleanup( );
	}

	bool Connect( std::string address, int port );

private:
	SOCKET Socket = 0;
};

inline std::unique_ptr<CConnector> g_Connector = std::make_unique<CConnector>( );