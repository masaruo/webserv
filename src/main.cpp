#include "ClientSocket.class.hpp"
#include "ListenSocket.class.hpp"
#include "SocketHolder.class.hpp"
#include "epoller.class.hpp"
#include <string>
#include <iostream>

int main(void)
{
  Epoller poller(1, 1000);

  poller.epollAdd(new ListenSocket(7777));
  poller.epollAdd(new ListenSocket(8888));

  poller.epollLoop();


  return (0);
}
