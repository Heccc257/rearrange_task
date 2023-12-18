#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/mman.h> // 用于内存映射
#include <fcntl.h>    // 用于文件控制
#include <unistd.h>

using namespace std;

void Rearrange(string raw_data_path, string musk_result_path, string rearg_result_path) {
    const size_t CHUNKSIZE = 8192;
    // if the last Chunk is incomplete, then leave it in its place.
    ifstream raw_data(raw_data_path, std::ios::binary);
    int raw_data_fd = open(raw_data_path.c_str(), O_RDONLY);
    if (!raw_data.is_open()) {
        std::cerr << "无法打开文件 " << raw_data_path << std::endl;
        return ;
    }
    raw_data.seekg(0, std::ios::end);
    size_t raw_data_size = raw_data.tellg();
    raw_data.seekg(0, std::ios::beg);
    size_t Chunk_nums = (raw_data_size + CHUNKSIZE - 1) / CHUNKSIZE;
    ifstream musk_data(musk_result_path, std::ios::in);
    if (!musk_data.is_open()) {
        std::cerr << "无法打开文件 " << musk_result_path << std::endl;
        return ;
    }
    
    fstream rearg_file(rearg_result_path, std::ios::binary | std::ios::out);
    int rearg_fd = open(rearg_result_path.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    std::cerr << "rearg file: " << rearg_result_path << '\n';
    ftruncate(rearg_fd, raw_data_size);
    if (rearg_fd == -1) {
        std::cerr << "无法打开rearg\n";
        return ;
    }
    size_t ChunkID;

    std::cerr << "here1\n";
    string line;
    vector<size_t> ids;
    vector<size_t> lstGroup;
    vector<size_t> orders(Chunk_nums);
    vector<size_t> reverse_orders(Chunk_nums);
    size_t tot = 0;
    cout << "Chunk nums: " << Chunk_nums << '\n';
    while (getline(musk_data, line)) {
        int number;
        stringstream numbers(line);
        ids.clear();
        while (numbers >> number) {
            reverse_orders[tot] = number;
            if (tot >= Chunk_nums || number >= Chunk_nums) {
                std::cerr << "error  " << Chunk_nums << " tot = " << tot << '\n';
            }
            orders[number] = tot++;
        }
    }
    std::cerr << "here2\n";
    for (auto id: lstGroup)
        orders[id] = tot++;
    
    // for (auto r: orders)
    //     std::cerr << r << '\n';
    // return ;
    const size_t batch_size = 100000;
    const size_t MAXMMAPSIZE = batch_size * CHUNKSIZE;
    char *buffer = new char[MAXMMAPSIZE];

    cout << "Chunk nums = " << Chunk_nums << '\n';
    size_t rawDataOff = 0;
    int idx = 0;
    for (int i = 0; i < Chunk_nums; i += batch_size) {
        std::cerr << "i = " << i << '\n';
        vector<int> pos;
        
        size_t mmap_size = min(MAXMMAPSIZE, raw_data_size - rawDataOff);
        void* file_memory = mmap(0, mmap_size, PROT_READ, MAP_SHARED, raw_data_fd, rawDataOff);
        char *data = reinterpret_cast<char*>(file_memory);

        for (size_t s = 0; s < mmap_size; s += CHUNKSIZE) {
            pos.push_back(orders[idx]);
            idx ++ ;
        }
        sort(pos.begin(), pos.end());

        // 不能初始化为0
        size_t lstOutOff = 1;

        for (auto p: pos) {
            size_t outputOff = p * CHUNKSIZE;
            size_t inputOff = CHUNKSIZE * (reverse_orders[p] - i);
            // if ((size_t)rearg_file.tellp() + CHUNKSIZE != outputOff || 1) {
            rearg_file.seekp(outputOff);
            // }
            lstOutOff = outputOff;
            rearg_file.write(data + inputOff, min(CHUNKSIZE, mmap_size - inputOff));
        }
        rearg_file.flush();
        
        munmap(file_memory, mmap_size);
        rawDataOff += mmap_size;
    }

    // close file
    close(raw_data_fd);
    close(rearg_fd);
    raw_data.close();
    musk_data.close();
    rearg_file.close();

    //
    delete []buffer;

    return ;
}
