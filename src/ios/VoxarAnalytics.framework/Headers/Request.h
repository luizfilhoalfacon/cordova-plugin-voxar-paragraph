
#ifndef Request_h
#define Request_h

#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
//#ifdef _WIN32
#include <unistd.h> /* read, write, close */
//#endif
#include <string.h> /* memcpy, memset */

#include <vector>
#include <string>

#ifdef __APPLE__            //same as linux
#include <sys/socket.h> /* socket, connect */
#include <netdb.h> /* struct hostent, gethostbyname */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#elif _WIN32
//#include <winsock2.h>
//#include <ws2tcpip.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include "LibConfig.h"

#else

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif



namespace vxa
{
#if defined _WIN32
    void VXA_LIBRARY_POLICY error(const char *msg);
    bool VXA_LIBRARY_POLICY httpPOST(std::string& , int portno, std::string& path, const char *params);
#else
    void error(const char *msg);
    bool httpPOST(std::string& , int portno, std::string& path, const char *params);
#endif
}


#endif
