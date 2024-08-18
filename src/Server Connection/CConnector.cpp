#include "CConnector.h"
#include <ws2tcpip.h>

bool CConnector::Connect( std::string address, int port ) {
	SOCKADDR_IN addr{ };
	PVOID buffer = nullptr;

	addr.sin_addr.S_un.S_addr = inet_addr( address.c_str( ) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );

	bool bConnected = connect( this->Socket, ( SOCKADDR* )&addr, sizeof( addr ) ) != SOCKET_ERROR;

	int nIteration = 0;
	while ( !bConnected ) {
		if ( nIteration >= 5 )
			return false;

		Sleep( 1000 );
		bConnected = connect( this->Socket, ( SOCKADDR* )&addr, sizeof( addr ) ) != SOCKET_ERROR;
		++nIteration;
	}

	return true;
}