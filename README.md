# Fast Preference Learning README

## Introduction

This work is based on Olivier Sobrie's work on preference learning algorithms (python code : <https://github.com/oso/pymcda>, thesis: <https://tel.archives-ouvertes.fr/tel-01370555/document>).

The  objective of this repository is to translate the previous code (py-mcda) in C++ and set up the parallelisation tools needed to process a greater amount of entrypoints.

The README contains information on how to run the application and help future developpers to set their environment.

The full description and documentation of the project can be found at <https://mostah.github.io/fastPL/>.

---

## Repository structure  

* [include](<https://github.com/Mostah/fastPL/tree/master/include>) : Header files

* [src](<https://github.com/Mostah/fastPL/tree/master/src>) : Sources files

* [test](<https://github.com/Mostah/fastPL/tree/master/test>) : Test files

* [extsrc](<https://github.com/Mostah/fastPL/tree/master/extsrc>) : External sources and dependencies

* [data](<https://github.com/Mostah/fastPL/tree/master/data>) : Data (datasets and models) repository

* [doc](<https://github.com/Mostah/fastPL/tree/master/doc>) : Doxygen documentation repository

* [.circleci](<https://github.com/Mostah/fastPL/tree/master/.circleci>) : CircleCi pipelines configuration

---

## Run project in Docker (Recommended)

### Build Docker image

First thing first, build the docker image

```bash
docker build . -t fastpl
```

Currently, the built of all dependencies requires ~1h

### Run the main app in Docker

The following command will show the run config options (helper):

```bash
docker run fastpl ./Main -h
```

To run the app with on a specific dataset:

```bash
docker run fastpl ./Main -d $dataset_path -o $output_path
```

At the end of the algorithm, the model will be stored in the `$output_path`

### Run the tests in Docker

Run all tests:

```bash
docker run fastpl ./Test
```

Run specified tests:

```bash
docker run fastpl ./Test --gtest_filter=TestGeneralName.TestPreciseName   # One specific Test
docker run fastpl ./Test --gtest_filter=TestGeneralName.*                 # All tests of Name1 = GeneralName 
```

### Check the logs

Get the fastpl docker container id by running `docker ps`

```bash
docker run -it $container_id /bin/bash 
cd /home/fastpl/logs
```

---

## Run project locally

The following requires CMake to be installed in your machine.

From the root of the project directory:

### Download dependencies

```bash
git submodule init
git submodule update
```

### Build C++ files

```bash
mkdir build && cd build
cmake .. -DBUILD_DEPS:BOOL=ON -DUSE_SCIP=OFF && make
```

Currently, the built of all dependencies requires ~1h

### Run the main app locally

From the `build` directory:

The following command will show the run config options (helper):

```bash
./Main -h
```

To run the app on a specified dataset:

```bash
./Main -d $dataset_path -o $output_path
```

At the end of the algorithm, the model will be stored in the `$output_path`

### Run the tests locally

From the `build` directory:

Run all tests:

```bash
./Test
```

Run specified tests:

```bash
./Test --gtest_filter=TestGeneralName.TestPreciseName   # One specific Test
./Test --gtest_filter=TestGeneralName.*                 # All tests of Name1 = GeneralName 
```

---

## Application configuration

The application configuration can be found at: [app-config](<https://github.com/Mostah/fastPL/tree/master/app-config.yaml>)

The application configuration holds the general config of the learning algorithms.

### Parameters

* `log_level`: log filter, values in `INFO`, `ERROR`, `DEBUG`
* `log_file`: path of the logfile
* `data_dir`: data directory path. When changed, the args -d and -o passed along with ./Main program is set relatively to the data directory path configured here
* `model_batch_size`: model population size used in the metaheuristic
* `max_iterations`: max iteration of the metaheuristic before terminating the application

---

## CircleCi pipelines

CircleCi pipelines configuration can be found at: [.circleci](<https://github.com/Mostah/fastPL/tree/master/.circleci>)

### pipelines

* Build: Try to build all the project
* Tests (requires build): Try to pass all the tests
* Doc generation (requires build): Try to generate the documentation

## Documentation

The documentation of this project is generated by doxygen. In order to generate locally or update the online documentation, the following modules must be installed: `doxygen`, `doxygen-doc`, `doxygen-gui`, `graphviz`.

The documentation configuration and files can be found at: [doc](<https://github.com/Mostah/fastPL/tree/master/doc>)

### Update online documentation

The online documentation is currently host on GitHub Pages: <https://mostah.github.io/fastPL/>.

The GitHub Page displays static html files from a specified branch. The files used by GitHub Pages to display the latest documentation are set on the `gh-pages` branch and must not be changed manually.

The following script updates the `gh-pages` branch by generating the documentation from the latest `master` commit.

From root directory:

```bash
sh doc_generation.sh
```

### Generate documentation locally

From `/doc` directory:

```bash
cmake . && doxygen Doxyfile.Doxigen
```

Open the documentation on your browser, from `/doc/html` directory:

```bash
open index.html
```
---

## Profiling

Profiling requires the app to be run on a Docker container. The following assumes the fastpl app has already been built by docker.

### Profiling with GPROF

#### Running the docker container and ssh into it

```bash
docker run -it fastpl /bin/bash
```

#### Executing the program we want to profile

```bash
./$PROGRAM
```

#### Creating the profiling data as a callgraph image (Recommended)

```bash
gprof $PROGRAM | python3 gprof2dot/gprof2dot.py | dot -Tpng -o analysis.png
```

#### Creating the profiling data as a text file

```bash
gprof $PROGRAM > analysis.txt
```

#### copy the analysis from the docker container into your machine

Keep this terminal open, and open a new one

Get the $ID of the fastpl container running with `docker ps`

```bash
docker cp $ID:/home/fastPL/build/analysis.{txt or png} $YOUR_PATH
```

The profiling data should now be in $YOUR_PATH in your machine.

@page readme FastPL README
