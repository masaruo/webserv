#pragma once
#include "AResponseBuilder.hpp"
#include "CgiSocket.hpp"

class CgiBuilder : public AResponseBuilder
{
private:
	CgiSocket	*socket_;
	std::string	script_path_;

	virtual void buildStatusLine();
	virtual void buildHeader();
	virtual void buildBody();

	void		parseCgiOutput(std::string const &cgi_output);
public:
	explicit CgiBuilder(CgiSocket *socket);
	~CgiBuilder();

	CgiBuilder &setScriptPath(std::string const &script_path);
private:
	CgiBuilder();
	CgiBuilder(CgiBuilder const &rhs);
	CgiBuilder &operator=(CgiBuilder const &rhs);
};
