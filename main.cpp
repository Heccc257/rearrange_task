#include <bits/stdc++.h>

#include "rearrange.h"

using namespace std;

void ReadConfig(const string& configFilePath, map<string, string>& config) {
    ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        cerr << "Error: Unable to open config file " << configFilePath << endl;
        exit(1);
    }

    string line;
    while (getline(configFile, line)) {
        istringstream iss(line);
        string key, value;
        if (getline(iss, key, '=')) {
            // Trim spaces from the key
            key.erase(key.find_last_not_of(" \t") + 1);
            key.erase(0, key.find_first_not_of(" \t"));

            // Trim spaces from the value
            if (getline(iss, value)) {
                value.erase(value.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
            }

            config[key] = value;
        }
    }
    configFile.close();
}

vector<vector<int> > clusters;
int main(int argc, char* argv[]) {

    map<string, string> config;
    string configFilePath = "config.txt"; // Default config file path
    string data_name;
    // Check if a config file path is provided as a command-line argument
    if (argc == 2) {
        // configFilePath = argv[1];
        data_name = argv[1];
    } else {
        cerr << "Usage: " << argv[0] << " [data name]" << endl;
        return 1;
    }
    // Read parameters from the config file
    ReadConfig(configFilePath, config);

    string raw_data_path = config["raw_data_dir"] + "/" + data_name;
    string hash_data_path = config["hash_result_dir"] + "/" + data_name +  ".hash";
    string musk_result_path = config["musk_result_dir"] + "/" + data_name +  ".musk";
    string rearg_result_path = config["musk_result_dir"] + "/" + data_name +  ".rearg";
    ifstream inputFile(hash_data_path, std::ios::binary);

    cout << "data name: " << data_name << '\n';

    int M;
    inputFile.read(reinterpret_cast<char*>(&M), sizeof(int));
    cout << "length: " << M << '\n';

    Rearrange(raw_data_path, musk_result_path, rearg_result_path);

    return 0;
}