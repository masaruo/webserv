#include "port.class.hpp"
#include "socket.class.hpp"
#include <string>
#include <iostream>

int main(void)
{
	Port port(80);
	Socket	fd(port);

  while (true)
  {

	fd.recv();
  fd.updateBuf("this is return msg\n");
	fd.send();
  }
  return (0);
}
