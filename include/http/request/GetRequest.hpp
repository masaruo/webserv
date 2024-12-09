#include "ARequest.hpp"

class GetRequest : public ARequest
{
private:
	std::string	setLocalPath(void) const;
	void		assertAutoIndex(std::string const &path, std::string const &pathWithRoot) const;
	std::string	getIndexFileName(std::string const &path) const;
	GetRequest();//=delete
public:
	explicit	GetRequest(RequestLine const &line, RequestHeader const &header, config::Config const &config, Server &server);
	~GetRequest();
	GetRequest(GetRequest const &rhs);
	GetRequest	&operator=(GetRequest const &rhs);
	void		generateResponseData(void);
};
