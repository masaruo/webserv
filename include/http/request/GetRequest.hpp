#include "ARequest.hpp"
#include "GetResponse.hpp"

class GetRequest : public ARequest
{
private:

public:
	GetRequest();
	GetRequest(RequestLine const &line, HttpHeader const &header);
	~GetRequest();
	GetRequest(GetRequest const &rhs);
	GetRequest &operator=(GetRequest const &rhs);
	GetResponse	*createResponse(int sockfd) const;
	std::string	get_path(void) const;
};
