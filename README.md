# cpp-consistent-hashing-algorithms

## Overview

C++ implementations of the most popular and best performing consistent hashing algorithms for non-peer-to-peer contexts.

### Abstract

Within the scope of a research project, conducted under the guidance of Massimo Coluzzi, a framework in Java was developed for benchmarking state-of-the-art consistent hashing algorithms. In order to explore the performance of these algorithms using different languages, I was tasked with creating a version in C++. This version currently encompasses only a partial selection of the technologies considered in the ISIN framework. However, the tool has been designed adaptively to easily implement new algorithms and benchmarks. The software remains consistent with the behavior of its Java counterpart. It is designed to operate via a command-line interface and to save benchmark results in a CSV file, utilizing YAML files for parameter configuration.

## Algorithms

These algorithms play a crucial role in distributed systems and represent some of
the most famous methods in state-of-the-art of consistent hashing:

- **Jump** by [Lamping et al.](https://arxiv.org/pdf/1406.2294.pdf) (2014)

- **Anchor** by [Mendelson et al.](https://arxiv.org/pdf/1812.09674.pdf) (2020)

- **Dx** by [Dong et al.](https://arxiv.org/pdf/2107.07930.pdf) (2021)

- **Power** by [Leu et al.](https://arxiv.org/pdf/2307.12448.pdf) (2023)

- **Memento** by [Coluzzi et al.](https://arxiv.org/pdf/2306.09783.pdf) (2023)

Some engines are not yet implemented in this project but are already configured for execution in the benchmark routine:

- **Ring** by [Karger et al.](https://dl.acm.org/doi/pdf/10.1145/258533.258660) (1997)

- **Rendezvous** by [Thaler et al.](https://d1wqtxts1xzle7.cloudfront.net/96307627/HRW98-libre.pdf?1671926741=&response-content-disposition=inline%3B+filename%3DUsing_name_based_mappings_to_increase_hi.pdf&Expires=1722682933&Signature=KP~csPgAHOx1QdFc48jOrZfYACTMopMFA28GHrrYQyaCG8Nw6f7IF2YukI2TUtniWTBny91j3hCaOPORnepii8xX-x~hXmNzDo8Pl1CvLqJRW12R6Vs0l-8c5eDagrCocrJ99NhEY-6JnxK6YVZwahZC-1~Src95qhbEh26Pf6EZ1KlU-vP2UZV-nRi8ScXIx3OOmzBW0G-szp92d0ctryZVevPL6Qc2gURfhMdVozFiI0yNZXu3U3IK6XgzNgq4323gwM7nMlscYxQ6Xefikqq~HjCtAkxrPaZnmYA4h5nj9qLvCj4zvChm492AYJzRpWNnewph-s3XLpkALFVDCA&Key-Pair-Id=APKAJLOHF5GGSLRBV4ZA) (1998)

- **Multi-probe** by [Appleton et al.](https://arxiv.org/pdf/1505.00062) (2015)

- **Maglev** by [Eisenbud et al.](https://www.usenix.org/sites/default/files/nsdi16-paper-eisenbud-update.pdf) (2016)

## Benchmarks

As outlined in _"A survey and comparison of consistent hashing algorithms" by Coluzzi et al. (2023)_, here is a concise overview of the benchmarks utilized:

- **Balance:** The ability of the algorithm to spread the keys evenly across the cluster nodes.

- **Initialization Time:** The time the algorithm requires to initialize its internal structure.

- **Lookup Time:** The time the algorithm needs to find the node a given key belongs to.

- **Memory Usage:** The amount of memory the algorithm uses to store its internal structure.

- **Monotonicity:** The ability of the algorithm to move the minimum amount of resources when the cluster scales.

- **Resize Balance:** The ability of the algorithm to keep its balance after adding or removing nodes.

- **Resize Time:** The time the algorithm requires to reorganize its internal structure after adding or removing nodes.

## Configuration

The format of the configuration file is described in detail in the [`configs/template.yaml`](configs/template.yaml) file. The tool will use the [`configs/default.yaml`](configs/default.yaml) file that represents the default configuration if no configuration file is provided.

## Control Flow

Figure 1 shows a UML sequence diagram to explain how the benchmark routine procedure works.

<table>
    <tr>
        <td><img src="https://raw.githubusercontent.com/robertovicario/cpp-consistent-hashing-algorithms/main/docs/Control_Flow.png" alt="Control_Flow" width=512></td>
    </tr>
    <tr>
        <td align="center">Figure 1: Exploring the control flow of the benchmark routine.</td>
    </tr>
</table>

## Instructions

1. Clone the repository and navigate to the cloned repository:

    ```sh
    git clone https://github.com/robertovicario/cpp-consistent-hashing-algorithms.git
    cd cpp-consistent-hashing-algorithms
    ```

2. Run repository setup:

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

3. Build the project with Ninja:

    ```sh
    cd build
    ninja
    ```

4. Start the framework:

   - Default configuration:
   
       ```sh
       ./main
       ```
   - Custom configuration:
   
       ```sh
       ./main <your_config>.yaml
       ```

5. Navigate to `build/tmp/` and check the `results.csv` file.

## Contributing

### Adding New Algorithms

1. Insert the algorithm name into any configuration file located in `configs/`.
2. Implement your algorithm in `Algorithms/your_algo/`. Keep in mind that the system employs C++ templates to integrate the algorithms into the loop.
3. Integrate a new execution routine into `Main.cpp`. Append a new `else if` branch and incorporate your engine using:
    
    ```cpp
    execute<YourEngine>(handler, yaml, "your_algo");
    ```
   
   If your engine requires additional parameters, include them as follows:

    ```cpp
    execute<YourEngine>(handler, yaml, "your_algo", param1, param2, ..., paramN);
    ```

### Adding New Benchmarks

1. Insert the benchmark name into any configuration file located in `configs/`.
2. Implement the benchmark in `Benchmarks/`. Note that the system utilizes C++ templates for benchmark integration into the loop.
3. Integrate a new benchmark routine into `Benchmarks/Routine.hpp`. Append a new `else if` branch and incorporate your engine using:
    
   ```cpp
    printInfo(l, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
    results[l] = computeYourBenchmark<Engine>(yaml, algorithm, initNodes, args...); 
    ```

## Testing

### Single Algorithm Routine

Differently by the framework in Java, it was implemented a functionality to run the benchmark routine for a single algorithm. This is the command to start the framework:

```sh
./main <your_config>.yaml <algorithm_name>
```

## Licence

This project is distributed under [GNU General Public License version 3](https://opensource.org/license/gpl-3-0). You can find the complete text of the license in the project repository.

> [!IMPORTANT]
> 
> ### Credits
>
> - **java-consistent-hashing-algorithms:**
>   - **Author:** [SUPSI-DTI-ISIN](https://github.com/SUPSI-DTI-ISIN)
>   - **License:** [GNU General Public License version 3](https://opensource.org/license/gpl-3-0)
>   - **Source:** [GitHub Repository](https://github.com/SUPSI-DTI-ISIN/java-consistent-hashing-algorithms.git)
> - **cpp-anchorhash:**
>   - **Author:** [anchorhash](https://github.com/anchorhash)
>   - **License:** [The MIT License](https://opensource.org/license/mit)
>   - **Source:** [GitHub Repository](https://github.com/anchorhash/cpp-anchorhash.git)
> - **DxHash:**
>   - **Author:** [ChaosD](https://github.com/ChaosD)
>   - **License:** none
>   - **Source:** [GitHub Repository](https://github.com/ChaosD/DxHash.git)

## Contacts

- **Supervisor:** Amos Brocco: @slashdotted
- **Student:** Roberto Vicario: @robertovicario
