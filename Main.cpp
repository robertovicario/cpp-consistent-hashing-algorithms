/**
 * @author Roberto Vicario
 */

#include <iostream>
#include <yaml-cpp/yaml.h>

#include "Algorithms/anchor/AnchorEngine.hpp"
#include "Algorithms/dx/DxEngine.hpp"
#include "Algorithms/jump/JumpEngine.hpp"
#include "Algorithms/memento/MementoEngine.hpp"
#include "Algorithms/power/PowerEngine.hpp"
#include "Benchmarks/Routine.hpp"
#include "Handler/HandlerImpl.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        /*
         * Handling the terminal usage.
         */
        string configName = (argc == 2) ? argv[1] : "default.yaml";

        /*
         * Loading the YAML file.
         */
        string pathYaml = "../configs/" + configName;
        YAML::Node yaml = YAML::LoadFile(pathYaml);

        /*
         * Creating the CSV file.
         */
        auto pathCsv = yaml["common"]["output-folder"].as<string>();
        pathCsv += "/results.csv";
        pathCsv = pathCsv.substr(1);

        HandlerImpl handler = HandlerImpl(pathCsv);

        cout << "# [SYS] ----- ****************************" << endl;
        cout << "# [SYS] ----- ***** STARTING ROUTINE *****" << endl;
        cout << "# [SYS] ----- ****************************" << endl;
        cout << "#" << endl;

        /*
         * Starting the benchmark routine.
         */
        for (auto i : yaml["algorithms"]) {
            auto algorithm = i["name"].as<string>();
            if (algorithm == "anchor") {
                /*
                 * ANCHOR
                 */
                // execute<AnchorEngine>("anchor", handler, yaml);
            } else if (algorithm == "dx") {
                /*
                 * DX
                 */
                execute<DxEngine>("dx", handler, yaml);
            } else if (algorithm == "jump") {
                /*
                 * JUMP
                 */
                // execute<JumpEngine>("jump", handler, yaml);
            } else if (algorithm == "memento") {
                /*
                 * MEMENTO
                 */
                // execute<MementoEngine<boost::unordered_flat_map>>("memento", handler, yaml);
            } else if (algorithm == "power") {
                /*
                 * POWER
                 */
                // execute<PowerEngine>("power", handler, yaml);
            }
        }
    } catch (const YAML::Exception& e) {
        cout << "# [ERR] ----- Exception: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cout << "# [ERR] ----- Exception: " << e.what() << endl;
        return 1;
    }

    /*
     * Closing the benchmark routine.
     */
    cout << "# [SYS] ----- *****************************" << endl;
    cout << "# [SYS] ----- ***** ROUTINE COMPLETED *****" << endl;
    cout << "# [SYS] ----- *****************************" << endl;

    return 0;
}
