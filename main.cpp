#include <bits/stdc++.h>

#include "rearrange.h"
#include "file_hash.h"

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
    string cluster_result_path = config["cluster_result_dir"] + "/" + data_name +  ".cluster";
    string rearg_result_path = config["cluster_result_dir"] + "/" + data_name +  ".rearg";

    cout << "cluster result path: " << cluster_result_path << '\n';
    cout << "rearg result path: " << rearg_result_path << '\n';
    cout << "data name: " << data_name << '\n';

    Rearrange(raw_data_path, cluster_result_path, rearg_result_path);
    string hash_raw = hash_file(raw_data_path);
    cout << "raw file hash: " << hash_raw << '\n';
    string hash_rearg = hash_file(rearg_result_path);
    cout << "rearg file hash: " << hash_rearg << '\n';
    cout << "\n";
    if (hash_raw != hash_rearg) {
        cerr << "not match\n";
        system("pause");
    }
    return 0;
}