#include "port.class.hpp"
#include "socket.class.hpp"
#include "epoller.class.hpp"
#include <string>
#include <iostream>

int main(void)
{
	Port port(8888);
  Socket listening(port);
  Epoller epoll(5, -1);
  // epoll.epollAdd(c1.clone());
  epoll.epollAdd(listening);
    epoll.epollLoop();
  return (0);
}
