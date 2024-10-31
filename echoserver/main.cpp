#include "ISocket.hpp"
#include "MSocket.hpp"
#include "ListenImpl.hpp"
#include "ClientImpl.hpp"
#include <vector>
#include <sys/epoll.h>
#include <algorithm>
#include <string>

int main(void)
{
    std::vector<ISocket*> holder;
    
    // リスニングソケット作成
    holder.push_back(new MSocket<ListenImpl>(new ListenImpl(8888)));
    
    // epoll作成
    int epfd = epoll_create1(0);
    if (epfd == -1) {
        return 1;
    }
    
    // リスニングソケットをepollに登録
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.ptr = holder[0];
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, holder[0]->getFd(), &ev) == -1) {
        return 1;
    }
    
    // イベントループ
    while (1) {
        struct epoll_event events[10];
        int nfds = epoll_wait(epfd, events, 10, -1);
        
        for (int i = 0; i < nfds; i++) {
            ISocket* current = static_cast<ISocket*>(events[i].data.ptr);
            
            if (current == holder[0]) {  // リスニングソケット
                // 新規クライアント接続
                ISocket* client = new MSocket<ClientImpl>(new ClientImpl(holder[0]->getFd()));
                holder.push_back(client);
                
                // クライアントをepollに登録
                ev.events = EPOLLIN;
                ev.data.ptr = client;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client->getFd(), &ev);
            } else {  // クライアントソケット
                // char buf[1024];
				std::string buf(1024, '\0');
                ssize_t n = recv(current->getFd(), &buf[0], sizeof(buf), 0);
                buf.resize(n);
				buf.append("****");
                if (n <= 0) {
                    // 切断処理
                    epoll_ctl(epfd, EPOLL_CTL_DEL, current->getFd(), NULL);
                    std::vector<ISocket*>::iterator it = 
                        std::find(holder.begin(), holder.end(), current);
                    if (it != holder.end()) {
                        holder.erase(it);
                    }
                    delete current;
                    continue;
                }
                
                // エコー送信
                send(current->getFd(), &buf[0], sizeof(buf), 0);
            }
        }
    }
    
    // クリーンアップ
    close(epfd);
    for (size_t i = 0; i < holder.size(); ++i) {
        delete holder[i];
    }
    return 0;
}
