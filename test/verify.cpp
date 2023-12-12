#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/mman.h> // 用于内存映射
#include <fcntl.h>    // 用于文件控制
#include <unistd.h>

using namespace std;

uint64_t buffer[1024 * 20];
int main() {
    int fd = open("test.dat.rearg", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    for (int i = 0; i < 20; i++, cout << '\n')
        for (int j = 0; j < 1024; j++)
            cout << buffer[i*1024 + j] << ' ';

    return 0;
}