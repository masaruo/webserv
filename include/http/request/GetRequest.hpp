#include "ARequest.hpp"

class GetRequest : public ARequest
{
private:
	GetRequest();//=delete
	bool	is_autoIndex(std::string const &path) const;
public:
	explicit	GetRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config);
	~GetRequest();
	GetRequest(GetRequest const &rhs);
	GetRequest	&operator=(GetRequest const &rhs);
	Response	generateResponse(void) const;
};
