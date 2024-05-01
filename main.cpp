/**
 * @author Roberto Vicario
 */

#include <iostream>
#include <yaml-cpp/yaml.h>

#include "Algorithms/dx/DxEngine.h"
#include "Benchmarks/Routine.h"
#include "Handler/HandlerImpl.h"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        /**
         * Handling the terminal usage.
         */
        string configName = (argc == 2) ? argv[1] : "default.yaml";

        /**
         * Loading the YAML file.
         */
        string pathYaml = "../configs/" + configName;
        YAML::Node yaml = YAML::LoadFile(pathYaml);

        /**
         * Creating the CSV file.
         */
        auto pathCSV = yaml["common"]["output-folder"].as<string>();
        HandlerImpl handler(pathCSV + "results.csv");

        cout << "# [SYS] ----- ****************************" << endl;
        cout << "# [SYS] ----- ***** STARTING ROUTINE *****" << endl;
        cout << "# [SYS] ----- ****************************" << endl;
        cout << "#" << endl;

        /**
         * Starting the benchmark routine.
         */
        /*
        for (auto i : yaml["algorithms"]) {
            auto algorithm = i["name"].as<string>();
        }
        */

        execute<DxEngine>(handler, yaml);
    } catch (const YAML::Exception& e) {
        cout << "# [ERR] ----- Exception: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cout << "# [ERR] ----- Exception: " << e.what() << endl;
        return 1;
    }

    /**
     * Closing the benchmark routine.
     */
    cout << "# [SYS] ----- *****************************" << endl;
    cout << "# [SYS] ----- ***** ROUTINE COMPLETED *****" << endl;
    cout << "# [SYS] ----- *****************************" << endl;

    return 0;
}
