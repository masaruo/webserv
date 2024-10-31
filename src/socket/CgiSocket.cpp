#include "CgiSocket.hpp"

CgiSocket::CgiSocket(int parent_socket)
:ASocket(ASocket::IDLE, parent_socket)
{
	return ;
}

CgiSocket::~CgiSocket()
{
	return ;
}

void	CgiSocket::setSockaddr()
{
	return ;

	//todo cleanup
}
