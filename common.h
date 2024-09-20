//#************************************************************************
//#*
//#* Copyright (C) 2024 Damian-Software
//#* All rights reserved.
//#*
//#* Author: Damián Zelený
//#* Contact: Damian-Software (dzeleny@recvsoftware.com)
//#*
//#************************************************************************
//#
#pragma once
#ifndef COMMON_H
#define COMMON_H
//-------------------------------------------------------------------------
#include <algorithm>				// for std::max()
#include <arpa/inet.h>				// for inet_addr() and inet_ntoa()
#include <atomic>					// for spinlock
#include <chrono>					// for std::chrono::seconds()
#include <cmath>					// for INFINITY
#include <cstdlib>					// for std::rand() a std::srand()
#include <cstring>					// for memcpy()
#include <ctime>					// for localtime
#include <fstream>					// for ofstream
#include <iostream>					// for std::cout ans std::endl ...
#include <limits.h>					// for std::numeric_limits
#include <mutex>					// for std::mutex
#include <netinet/in.h>				// for socketaddr_in
#include <random>					// for random generate random number
#include <stdint.h>					// for int64_t
#include <string.h>					// for std::string
#include <sys/select.h>				// for select()
#include <sys/socket.h>				// for socket()
#include <sys/time.h>				// for timeval
#include <sys/types.h>				// for fd_set
#include <thread>					// for std::thread
#include <unistd.h>					// for close()
#include <vector>					// for std::vector
#include <csignal>					// for signal
#include <memory>					// for std::atexit(cleanup);
//-------------------------------------------------------------------------
#include <functional>				// for std::function
#include <sys/epoll.h>				// for epoll_create1(), epoll_ctl(), struct epoll_event
#include <stdio.h>					// for fprintf()
#include <stdlib.h>
#include <errno.h>
#include <unordered_map>
#include <fcntl.h>
#include <pthread.h>



#include <netdb.h>
#include <ifaddrs.h>

#endif // !COMMON_H











