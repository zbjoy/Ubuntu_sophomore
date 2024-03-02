#ifndef SREVER_H
#define SERVER_H

int initListenFd(unsigned short port);

int epoll_run(unsigned short port);

#endif
