#include "port.class.hpp"
#include "socket.class.hpp"
#include <string>
#include <iostream>

int main(void)
{
	Port port(80);

  while (true)
  {
	Socket	fd(port);

	fd.recv();
  fd.updateBuf("this is return msg\n");
	fd.send();
  }
  return (0);
}
