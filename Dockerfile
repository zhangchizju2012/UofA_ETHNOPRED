FROM ubuntu:15.10
RUN rm /bin/sh && ln -s /bin/bash /bin/sh
RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y libssl-dev
RUN apt-get install -y g++
RUN apt-get install -y libcpprest-dev
RUN apt-get install -y libcpprest-doc
RUN apt-get install -y libboost-all-dev
RUN apt-get install -y gdb
