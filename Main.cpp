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
        string arg1 = "default.yaml";
        string arg2;

        if (argc == 2) {
            arg1 = argv[1];
        } else if (argc == 3) {
            arg1 = argv[1];
            arg2 = argv[2];
        }

        /*
         * Loading the YAML file.
         */
        string pathYaml = "../configs/" + arg1;
        YAML::Node yaml = YAML::LoadFile(pathYaml);

        /*
         * Creating the CSV file.
         */
        auto pathCsv = yaml["common"]["output-folder"].as<string>("/tmp");
        pathCsv += "/results.csv";

        /*
         * [!WARNING]
         * This line could be removed only if change the standard of the 'output-folder' from '/dir' to 'dir/'.
         */
        pathCsv = pathCsv.substr(1);
        auto* handler = new HandlerImpl(pathCsv);

        cout << "# [SYS] ----- ****************************" << endl;
        cout << "# [SYS] ----- ***** STARTING ROUTINE *****" << endl;
        cout << "# [SYS] ----- ****************************" << endl;
        cout << "#" << endl;

        /*
         * Starting the benchmark routine.
         */
        bool flag = false;
        for (auto i : yaml["algorithms"]) {
            auto algorithm = i["name"].as<string>();
            if (!arg2.empty() && algorithm != arg2) {
                flag = true;
                continue;
            }

            if (algorithm == "anchor") {
                /*
                 * ANCHOR
                 */
                auto capacity = i["args"]["capacity"].as<int>(10);
                execute<AnchorEngine>(*handler, yaml, "anchor", capacity);
            } else if (algorithm == "dx") {
                /*
                 * DX
                 */
                auto capacity = i["args"]["capacity"].as<int>(10);
                execute<DxEngine>(*handler, yaml, "dx", capacity);
            } else if (algorithm == "jump") {
                /*
                 * JUMP
                 */
                execute<JumpEngine>(*handler, yaml, "jump");
            } else if (algorithm == "maglev") {
                /*
                 * MAGLEV
                 */
                auto permutations = i["args"]["permutations"].as<int>(128);
                // execute<MaglevEngine>(handler, yaml, "maglev", permutations);
            } else if (algorithm == "memento") {
                /*
                 * MEMENTO
                 */
                execute<MementoEngine<boost::unordered_flat_map>>(*handler, yaml, "memento");
            } else if (algorithm == "multi-probe") {
                /*
                 * MULTIPROBE
                 */
                auto probes = i["args"]["probes"].as<int>(21);
                // execute<MultiprobeEngine>(handler, yaml, "multi-probe", probes);
            } else if (algorithm == "power") {
                /*
                 * POWER
                 */
                execute<PowerEngine>(*handler, yaml, "power");
            } else if (algorithm == "rendezvous") {
                /*
                 * RENDEZVOUS
                 */
                // execute<RendezvousEngine>(handler, yaml, "rendezvous");
            } else if (algorithm == "ring") {
                /*
                 * RING
                 */
                auto virtualNodes = i["args"]["virtualNodes"].as<int>(1000);
                // execute<RingEngine>(handler, yaml, "ring", virtualNodes);
            }
        }

        if (flag) {
            cout << "#" << endl;
        }

        delete handler;
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
