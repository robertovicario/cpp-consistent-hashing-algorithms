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

        /*
         * ![WARNING]
         * This line could be removed only if change the standard of the 'output-folder' from '/dir' to 'dir/'.
         */
        pathCsv = pathCsv.substr(1);

        HandlerImpl handler = HandlerImpl(pathCsv);

        cout << "# [SYS] ----- ****************************" << endl;
        cout << "# [SYS] ----- ***** STARTING ROUTINE *****" << endl;
        cout << "# [SYS] ----- ****************************" << endl;
        cout << "#" << endl;

        /*
         * Starting the benchmark routine.
         */
        for (auto i: yaml["algorithms"]) {
            auto algorithm = i["name"].as<string>();
            if (algorithm == "anchor") {
                /*
                 * ANCHOR
                 */
                auto capacity = i["args"]["capacity"].as<int>(10);
                execute<AnchorEngine>("anchor", handler, yaml, capacity);
            } else if (algorithm == "dx") {
                /*
                 * DX
                 */
                auto capacity = i["args"]["capacity"].as<int>(10);
                execute<DxEngine>("dx", handler, yaml, capacity);
            } else if (algorithm == "jump") {
                /*
                 * JUMP
                 */
                execute<JumpEngine>("jump", handler, yaml);
            } else if (algorithm == "maglev") {
                /*
                 * MAGLEV
                 */
                 // auto permutations = i["args"]["permutations"].as<int>(128);
                 // execute<MaglevEngine>("maglev", handler, yaml, permutations);
            } else if (algorithm == "memento") {
                execute<MementoEngine<boost::unordered_flat_map>>("memento", handler, yaml);
            } else if (algorithm == "multi-probe") {
                /*
                 * MULTIPROBE
                 */
                // auto probes = i["args"]["probes"].as<int>(21);
                // execute<MultiProbeEngine>("multi-probe", handler, yaml, probes);
            } else if (algorithm == "power") {
                /*
                 * POWER
                 */
                execute<PowerEngine>("power", handler, yaml);
            } else if (algorithm == "rendezvous") {
                /*
                 * RENDEZVOUS
                 */
                // execute<RendezvousEngine>("rendezvous", handler, yaml);
            } else if (algorithm == "ring") {
                /*
                 * RING
                 */
                // auto virtualNodes = i["args"]["virtualNodes"].as<int>(1000);
                // execute<RingEngine>("ring", handler, yaml, virtualNodes);
            }
        }
    } catch (const YAML::Exception &e) {
        cout << "# [ERR] ----- Exception: " << e.what() << endl;
        return 1;
    } catch (const exception &e) {
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
