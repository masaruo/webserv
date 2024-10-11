#include "Date.hpp"
#include <ctime>

std::string	Date::time(void)
{
	time_t		timestamp = std::time(NULL);
	struct tm	datetime = *std::gmtime(&timestamp);

	char	output[50];
	std::size_t	written_size = strftime(output, 50, "%a, %d %b %Y %H:%M:%S", &datetime);
	std::string date(output);
	date.resize(written_size);
	date.append(" GMT");

	return (date);
}
