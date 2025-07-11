#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

bool isPortOpen(const string& ip, int port, int timeout = 1) {
    int sockfd;
    struct sockaddr_in target;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return false;

    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &target.sin_addr);

    // Set timeout
    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    int result = connect(sockfd, (struct sockaddr*)&target, sizeof(target));
    close(sockfd);

    return result == 0;
}

int main() {
    string targetIP;
    int startPort, endPort;

    cout << "🛡️  Simple TCP Port Scanner\n";
    cout << "Enter target IP address: ";
    cin >> targetIP;
    cout << "Enter start port: ";
    cin >> startPort;
    cout << "Enter end port: ";
    cin >> endPort;

    cout << "\n🔍 Scanning " << targetIP << " from port " << startPort << " to " << endPort << "...\n";

    for (int port = startPort; port <= endPort; ++port) {
        if (isPortOpen(targetIP, port)) {
            cout << "✅ Port " << port << " is OPEN\n";
        } else {
            cout << "❌ Port " << port << " is CLOSED\n";
        }
    }

    return 0;
}



