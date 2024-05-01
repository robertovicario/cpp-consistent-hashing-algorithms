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
    string path;

public:
    HandlerImpl(const string& path) : file(), path(path) {
        /**
         * Configuring the system.
         */
        cout << "# [SYS] ----- ******************************" << endl;
        cout << "# [SYS] ----- ***** CONFIGURING SYSTEM *****" << endl;
        cout << "# [SYS] ----- ******************************" << endl;
        cout << "#" << endl;

        int pos = 0;
        string dir;

        while ((pos = path.find_first_of("/\\", pos + 1)) != string::npos) {
            dir = path.substr(0, pos);
            struct stat info;

            /**
             * Checking the system.
            */
            cout << "# [SYS] ----- Configuring the system ..." << endl;

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

        /**
         * Creating the CSV file.
         */
        cout << "# [SYS] ----- Creating the CSV file ..." << endl;

        file.open(path, ios::out | ios::app);
        if (file.is_open()) {
            file << "algorithm,benchmark,hash_function,init_nodes,iterations,mean,var,stddev\n";
            cout << "# [SYS] ----- CSV file created successfully." << endl;
            cout << "#" << endl;
        } else {
            cout << "# [ERR] ----- Unable to create CSV file." << endl;
            exit(1);
        }

        /**
         * Saving the stream.
         */
        file.flush();
        file.close();
    }

    void updateData(const string& algorithm, const string& benchmark, const string& hash_function, int init_nodes, int iterations, double mean, double variance, double standardDeviation) {
        /**
         * Updating new data to the CSV file.
        */
        cout << "# [SYS] ----- Updating new data to the CSV file ..." << endl;

        if (file.is_open()) {
            file << algorithm << "," << benchmark << "," << hash_function << "," << init_nodes << "," << iterations << "," << mean << "," << variance << "," << standardDeviation << "\n";
            cout << "# [SYS] ----- Data updated successfully." << endl;
        } else {
            cout << "# [ERR] ----- Unable to update data to CSV file." << endl;
        }

        cout << "#" << endl;

        /**
         * Saving the stream.
         */
        file.flush();
        file.close();
    }
};
