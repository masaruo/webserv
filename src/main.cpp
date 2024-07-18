#include <socket.class.hpp>
#include <string>
#include <iostream>

int main(void)
{
	char buf[1000];

	Socket  sock(80);	
  while (true)
  {
		int fd = sock.getAcceptedFD();
		recv(fd, buf, 999, 0);
		std::string bufstr(buf);
		std::cout << bufstr << std::endl;
		std::string	outstr("out message hello world¥n");
		send(fd, outstr.c_str(), outstr.length(), 0);
  }
  return (0);
}
