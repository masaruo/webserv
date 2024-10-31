#pragma once
#include "ASocket.class.hpp"

class CgiSocket : public ASocket
{
private:
	CgiSocket();
	CgiSocket(CgiSocket const &rhs);
	CgiSocket &operator=(CgiSocket const &rhs);
public:
	std::string	request_body_;//todo private
	std::string	response_body_;//todo private
	explicit CgiSocket(int sock_parent);
	~CgiSocket();
	void	setSockaddr();
};
