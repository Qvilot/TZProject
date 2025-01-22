#pragma once
#include <iostream>
#include <thread>
#include <algorithm>
#include <chrono>
#include <cctype>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <sys/socket.h>
#include <netinet/in.h>
#include "lib.h"


class SharedBuffer {
    public:
    void put (const std::string& data);
    std::string get();
    bool isEmpty();

    private:
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<std::string> q;
};

    void thread1_function (SharedBuffer &buffer);
    void thread2_function (SharedBuffer &buffer, const std::string &serverIP, int serverPort);



