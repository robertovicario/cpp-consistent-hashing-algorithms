/**
 * @author Roberto Vicario
 */

#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

using namespace std;

class HandlerImpl {
private:
    ofstream file;
    string pathCsv;

public:
    HandlerImpl(const string& path) {
        /*
         * Building the constructor.
         */
        this->pathCsv = path;

        /*
         * Configuring the system.
         */
        cout << "# [SYS] ----- ******************************" << endl;
        cout << "# [SYS] ----- ***** CONFIGURING SYSTEM *****" << endl;
        cout << "# [SYS] ----- ******************************" << endl;
        cout << "#" << endl;

        int pos = 0;
        string dir;

        while ((pos = pathCsv.find_first_of("/\\", pos + 1)) != string::npos) {
            dir = pathCsv.substr(0, pos);
            struct stat info;

            cout << "# [SYS] ----- Configuring ..." << endl;
            if (stat(dir.c_str(), &info) != 0) {
                if (mkdir(dir.c_str(), 0777) != 0) {
                    cout << "# [SYS] ----- Unable to configure the system." << endl;
                    exit(1);
                }
            } else if (!(info.st_mode & S_IFDIR)) {
                cout << "# [ERR] ----- Unable to configure the system." << endl;
                exit(1);
            }
        }

        cout << "# [SYS] ----- System configured successfully." << endl;
        cout << "#" << endl;

        /*
         * Creating the CSV file.
         */
        cout << "# [SYS] ----- Creating ..." << endl;

        int count = 0;
        string filename = pathCsv;
        while (ifstream(filename)) {
            count++;
            size_t extensionIndex = path.find_last_of(".");
            filename = pathCsv.substr(0, extensionIndex) + "-" + to_string(count) + pathCsv.substr(extensionIndex);
        }

        file.open(filename, ios::out | ios::app);
        if (file.is_open()) {
            file << "algorithm,benchmark,hash_function,init_nodes,iterations,mean,var,stddev\n";
            cout << "# [SYS] ----- CSV file created successfully." << endl;
            cout << "#" << endl;
        } else {
            cout << "# [ERR] ----- Unable to create CSV file." << endl;
            exit(1);
        }

        /*
         * Flushing and closing the stream.
         */
        file.flush();
        file.close();
    }

    void updateData(const string& algorithm, const string& benchmark, const string& hashFunction, int initNodes, int iterationsRun, double mean, double var, double stddev) {
        /*
         * Updating the new data to the CSV file.
         */
        cout << "# [SYS] ----- Updating ..." << endl;

        file.open(pathCsv, ios::out | ios::app);
        if (file.is_open()) {
            file << algorithm << "," << benchmark << "," << hashFunction << "," << initNodes << "," << iterationsRun << "," << mean << "," << var << "," << stddev << "\n";
            cout << "# [SYS] ----- Data updated successfully." << endl;
        } else {
            cout << "# [ERR] ----- Unable to update data to CSV file." << endl;
        }

        cout << "#" << endl;

        /*
         * Flushing and closing the stream.
         */
        file.flush();
        file.close();
    }
};
