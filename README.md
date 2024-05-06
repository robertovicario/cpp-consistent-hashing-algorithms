# cpp-consistent-hashing-algorithms

## Overview

This project collects C++ implementations of the most prominent consistent hashing algorithms for non-peer-to-peer contexts.

### Algorithms

- **Jump** by [Lamping et al.](https://arxiv.org/pdf/1406.2294.pdf) (2014)
- **Anchor** by [Mendelson et al.](https://arxiv.org/pdf/1812.09674.pdf) (2020)
- **Dx** by [Dong et al.](https://arxiv.org/pdf/2107.07930.pdf) (2021)
- **Power** by [Leu et al.](https://arxiv.org/pdf/2307.12448.pdf) (2023)
- **Memento** by [Coluzzi et al.](https://arxiv.org/pdf/2306.09783.pdf) (2023)

You can find new implementations in related branches:

- Ring [Karger et al.](https://dl.acm.org/doi/pdf/10.1145/258533.258660) (1997)
- Maglev [Eisenbud et al.](https://www.usenix.org/sites/default/files/nsdi16-paper-eisenbud-update.pdf) (2016)

### Benchmarks

- **Balance**: The ability of the algorithm to spread the keys evenly across the cluster nodes.
- **Initialization Time**: The time the algorithm requires to initialize its internal structure.
- **Lookup Time**: The time the algorithm needs to find the node a given key belongs to.
- **Memory Usage**: The amount of memory the algorithm uses to store its internal structure.
- **Monotonicity**: The ability of the algorithm to move the minimum amount of resources when the cluster scales.
- **Resize Balance**: The ability of the algorithm to keep its balance after adding or removing nodes.
- **Resize Time**: The time the algorithm requires to reorganize its internal structure after adding or removing nodes.

### Configuration

The format of the configuration file is described in detail in the [`configs/template.yaml`](configs/template.yaml) file. The tool will use the [`configs/default.yaml`](configs/default.yaml) file that represents the default configuration if no configuration file is provided.

## Instructions

Clone the repository and navigate to the cloned repository:

```sh
git clone https://github.com/robertovicario/cpp-consistent-hashing-algorithms.git
cd cpp-consistent-hashing-Algorithms
```

Run repository setup:

- vcpkg:
    ```sh
    # Ensure scripts has executable permissions:
    # chmod +x repo.sh
    ./repo.sh
    ```
- CMake:
    ```sh
    # Ensure scripts has executable permissions:
    # chmod +x cmake.sh
    ./cmake.sh
    ```

Build the project with Ninja:

```sh
cd build
ninja
```

Start the framework:

- Default configuration:
    ```sh
    ./main
    ```
- Custom configuration:
    ```sh
    ./main <your_config>.yaml
    ```

## Contributing

### Adding New Algorithms

1. Insert the algorithm name into any configuration file located in `configs/`.
2. Implement your algorithm in `Algorithms/your_algo/`. Keep in mind that the system employs C++ templates to integrate the algorithms into the loop.
3. Integrate a new execution routine into `Main.cpp`. Append a new `else if` branch and incorporate your engine using:
    ```cpp
    execute<YourEngine>("your_algo", handler, yaml);
    ```

### Adding New Benchmarks

1. Insert the benchmark name into any configuration file located in `configs/`.
2. Implement the benchmark in `Benchmarks/`. Create a function named `computeYourBenchmark` within it, accepting parameters `string algorithm` and `uint32_t initNodes`. Note that the system utilizes C++ templates for benchmark integration into the loop.
3. Integrate a new benchmark routine into `Benchmarks/Routine.hpp`. Append a new `else if` branch and incorporate your engine using:
    ```cpp
    printInfo(k, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
    results[k] = computeYourBenchmark<Engine>(algorithm, initNodes);
    ```

## Licence

This project is distributed under [GNU General Public License version 3](https://opensource.org/license/gpl-3-0). You can find the complete text of the license in the project repository.

> [!IMPORTANT]
> 
> ### Credits
>
> - **java-consistent-hashing-algorithms**:
>   - **Author**: [SUPSI-DTI-ISIN](https://github.com/SUPSI-DTI-ISIN)
>   - **License**: [GNU General Public License version 3](https://opensource.org/license/gpl-3-0)
>   - **Source**: [GitHub Repository](https://github.com/SUPSI-DTI-ISIN/java-consistent-hashing-algorithms.git)
> - **cpp-anchorhash**:
>   - **Author**: [anchorhash](https://github.com/anchorhash)
>   - **License**: [The MIT License](https://opensource.org/license/mit)
>   - **Source**: [GitHub Repository](https://github.com/anchorhash/cpp-anchorhash.git)
> - **DxHash**:
>   - **Author**: [ChaosD](https://github.com/ChaosD)
>   - **License**: none
>   - **Source**: [GitHub Repository](https://github.com/ChaosD/DxHash.git)

## Contacts

- Amos Brocco: amos.brocco@supsi.ch
- Roberto Vicario: roberto.vicario@student.supsi.ch
