#include "ClientSocket.class.hpp"
#include "ListenSocket.class.hpp"
#include "SocketHolder.class.hpp"
// #include "epoller.class.hpp"
#include <string>
#include <iostream>

int main(void)
{
  SocketHolder  holder;
  ListenSocket  *port80 = new ListenSocket(8888);

  holder.addSocket(port80);
  while (true)
  {
    holder.addSocket(new ClientSocket(port80->getFd()));
  }
  // holder.addSocket(new ListenSocket(80));
  return (0);
}
