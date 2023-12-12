#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/mman.h> // 用于内存映射
#include <fcntl.h>    // 用于文件控制
#include <unistd.h>

using namespace std;


uint64_t buffer[1024];
int main() {
    int fd = open("test.dat", O_WRONLY | O_CREAT);

    if (fd == -1) {
        std::cerr << "can't open file\n";
        return 0;
    }
    
    for (int i = 0; i < 1024; i++)
        buffer[i] = 1ll * rand() * rand();
    
    for (int i = 0; i < 10; i++) {
        buffer[i*10] = 1ll * rand() * rand();
        write(fd, buffer, sizeof(buffer));
    }
    for (int i = 0; i < 10; i++) {
        memset(buffer, 0, sizeof(buffer));
        for (int j = 0; j < 1024; j++)
            buffer[j] = 1ll * rand() * rand();
        
        buffer[i] = 1;
        write(fd, buffer, sizeof(buffer));
        for (int j = 0; j < 1024; j++)
            cout << buffer[j] << ' ';
        cout << '\n';
    }

    return 0;
}