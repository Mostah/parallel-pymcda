FROM ubuntu:groovy

#test 
# install c++ tools
RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install build-essential cmake git graphviz python3 doxygen gnuplot

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . /home/fastPL
WORKDIR /home/fastPL/

# install & configure submodules 
RUN git submodule init && git submodule update

# build c++ programs
RUN mkdir -p /home/fastPL/build
WORKDIR /home/fastPL/build/
RUN cmake .. && make

# To visualize profiling data
RUN git clone https://github.com/jrfonseca/gprof2dot.git

CMD ["./Main -h"]