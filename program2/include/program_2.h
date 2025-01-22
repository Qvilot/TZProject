#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
#include <cctype>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include "lib.h"


void handle_client(int client_socket);

