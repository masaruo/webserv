#include "ARequest.hpp"

class GetRequest : public ARequest
{
private:

public:
	GetRequest();
	GetRequest(std::string const &raw_request);
	~GetRequest();
	GetRequest(GetRequest const &rhs);
	GetRequest &operator=(GetRequest const &rhs);
	void	createMockResponse(int sockfd);
	AResponse	*createResponse(int sockfd) const;
	std::string	get_path(void) const;
};
