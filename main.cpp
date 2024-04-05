/**
 * @author Roberto Vicario
 */

#include <iostream>
#include <yaml-cpp/yaml.h>

#include "algorithms/anchor/anchorengine.h"
#include "algorithms/dx/DxEngine.h"
#include "algorithms/jump/jumpengine.h"
#include "algorithms/memento/mementoengine.h"
#include "algorithms/power/powerengine.h"
#include "benchmarks/Routine.h"
#include "utils/AlgorithmsASCII.h"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        /**
         * Handling terminal usage.
         */
        string configName = (argc == 2) ? argv[1] : "default.yaml";

        /**
         * Loading YAML file.
         */
        string fileName = "../configs/" + configName;
        YAML::Node yaml = YAML::LoadFile(fileName);

        /**
         * Starting benchmark routine.
         */
        cout << "# [SYS] ----- ****************************" << endl;
        cout << "# [SYS] ----- ***** STARTING ROUTINE *****" << endl;
        cout << "# [SYS] ----- ****************************" << endl;
        cout << "#" << endl;
        cout << "#" << endl;

        for (const auto &iter: yaml["algorithms"]) {
            auto algorithm = iter["name"].as<string>();
            if (algorithm == "anchor") {
                /**
                 * ANCHOR
                 */
                printAnchor();
                execute<AnchorEngine>(yaml, "anchor", 1000000, 1000000, 20000, 1000000);
            } else if (algorithm == "dx") {
                /**
                 * DX
                 */
                printDx();
                execute<DxEngine>(yaml, "dx", 1000000, 1000000, 20000, 1000000);
            } else if (algorithm == "jump") {
                /**
                 * JUMP
                 */
                printJump();
                execute<JumpEngine>(yaml, "jump", 1000000, 1000000, 20000, 1000000);
            } else if (algorithm == "maglev") {
                /**
                 * MAGLEV
                 */
                // printMaglev();
            } else if (algorithm == "memento") {
                /**
                 * MEMENTO
                 */
                printMemento();
                execute<MementoEngine<boost::unordered_flat_map>>(yaml, "memento", 1000000, 1000000, 20000, 1000000);
            } else if (algorithm == "multi-probe") {
                /**
                 * MULTIPROBE
                 */
                // printMultiprobe();
            } else if (algorithm == "power") {
                /**
                 * POWER
                 */
                printPower();
                execute<PowerEngine>(yaml, "power", 1000000, 1000000, 20000, 1000000);
            } else if (algorithm == "rendezvous") {
                /**
                 * RENDEZVOUS
                 */
                // printRendezvous();
            } else if (algorithm == "ring") {
                /**
                 * RING
                 */
                // printRing();
            }
        }
    } catch (const YAML::Exception& e) {
        cerr << "# [ERR] ----- YAML Exception: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "# [ERR] ----- Exception: " << e.what() << endl;
        return 1;
    }

    /**
     * Closing benchmark routine.
     */
    cout << "# [SYS] ----- *****************************" << endl;
    cout << "# [SYS] ----- ***** ROUTINE COMPLETED *****" << endl;
    cout << "# [SYS] ----- *****************************" << endl;

    return 0;
}
