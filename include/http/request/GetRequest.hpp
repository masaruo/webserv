#include "ARequest.hpp"
#include "define.hpp"
#include "GetResponse.hpp"

class GetRequest : public ARequest
{
private:
	ft::str_map	query_;
	ft::str_map	parseQuery(std::string const &uri);
	GetRequest();//=delete
public:
	explicit GetRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config);
	~GetRequest();
	GetRequest(GetRequest const &rhs);
	GetRequest &operator=(GetRequest const &rhs);
	GetResponse	*createResponse(void) const;
};
