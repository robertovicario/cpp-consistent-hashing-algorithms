/**
 * @author Roberto Vicario
 */

#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

class HandlerImpl {
private:
    ofstream file;
    string pathCsv;

public:
    HandlerImpl(const string& pathCsv) : pathCsv(pathCsv) {
        /*
         * Configuring the system.
         */
        cout << "# [SYS] ----- ******************************" << endl;
        cout << "# [SYS] ----- ***** CONFIGURING SYSTEM *****" << endl;
        cout << "# [SYS] ----- ******************************" << endl;
        cout << "#" << endl;

        string dir = pathCsv.substr(0, pathCsv.find_last_of("/\\"));
        struct stat info;

        if (stat(dir.c_str(), &info) != 0) {
            if (mkdir(dir.c_str(), 0777) != 0) {
                cout << "# [ERR] ----- Unable to configure the directory." << endl;
                exit(1);
            }
        } else if (!(info.st_mode & S_IFDIR)) {
            cout << "# [ERR] ----- Unable to configure the directory." << endl;
            exit(1);
        }

        cout << "# [SYS] ----- Directory configured successfully." << endl;
        cout << "#" << endl;

        /*
         * Creating the CSV file.
         */
        cout << "# [SYS] ----- Creating CSV file..." << endl;

        string filename = pathCsv;
        int count = 0;
        while (ifstream(filename)) {
            count++;
            size_t extensionIndex = pathCsv.find_last_of(".");
            filename = pathCsv.substr(0, extensionIndex) + "-" + to_string(count) + pathCsv.substr(extensionIndex);
        }

        file.open(filename, ios::out | ios::app);
        if (file.is_open()) {
            file << "algorithm,benchmark,hash_function,init_nodes,iterations,mean,var,stddev\n";
            cout << "# [SYS] ----- CSV file created successfully: " << filename << endl;
            cout << "#" << endl;
        } else {
            cout << "# [ERR] ----- Unable to create CSV file." << endl;
            exit(1);
        }
    }

    void updateData(const string& algorithm, const string& benchmark, const string& hashFunction, int initNodes, int iterationsRun, double mean, double var, double stddev) {
        /*
         * Updating the new data to the CSV file.
         */
        cout << "# [SYS] ----- Updating CSV file..." << endl;

        if (!file.is_open()) {
            file.open(pathCsv, ios::out | ios::app);
            if (!file.is_open()) {
                cout << "# [ERR] ----- Unable to update data." << endl;
                exit(1);
            }
        }

        file << algorithm << "," << benchmark << "," << hashFunction << "," << initNodes << "," << iterationsRun << "," << mean << "," << var << "," << stddev << "\n";
        cout << "# [SYS] ----- Data updated successfully." << endl;
        file.flush();
    }

    ~HandlerImpl() {
        if (file.is_open()) {
            file.close();
        }
    }
};
