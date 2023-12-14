#include <bits/stdc++.h>

using namespace std;

const int ChunkSize = 8192;
char buffer[ChunkSize];
string hash_file(string file_name) {
    ifstream file(file_name, std::ios::binary);
    uint64_t XOR = 0, SUM = 0;
    uint64_t tem;
    while (1) {
        file.read(buffer, ChunkSize);
        if (file.gcount() < ChunkSize) break;
        for (int i = 0; i < ChunkSize; i += 8) {
            tem = *reinterpret_cast<uint64_t*>(buffer + i);
            XOR ^= tem;
            SUM += tem;
        }
    }
    ostringstream oss;
    oss << XOR << SUM;
    file.close();
    return oss.str();
}