#include "ARequest.hpp"

class Get : public ARequest
{
private:

public:
	Get();
	Get(std::string const &raw_request);
	~Get();
	Get(Get const &rhs);
	Get &operator=(Get const &rhs);
	void	createMockResponse(int sockfd);
};
