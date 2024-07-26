#include "ClientSocket.class.hpp"
#include "ListenSocket.class.hpp"
#include "SocketHolder.class.hpp"
#include "epoller.class.hpp"
#include <string>
#include <iostream>

int main(void)
{
  // SocketHolder  holder;
  // ListenSocket  *port8888 = new ListenSocket(8888);
  // ListenSocket  *port7777 = new ListenSocket(7777);

  // holder.addSocket(port8888);
  // holder.addSocket(port7777);
  // while (true)
  // {
  //   holder.addSocket(new ClientSocket(port8888->getFd()));
  //   holder.addSocket(new ClientSocket(port7777->getFd()));
  // }
  // holder.addSocket(new ListenSocket(80));

  Epoller poller(1, -1);

  poller.epollAdd(new ListenSocket(8888));
  poller.epollAdd(new ListenSocket(7777));

  poller.epollLoop();


  return (0);
}
