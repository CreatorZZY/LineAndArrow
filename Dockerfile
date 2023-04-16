FROM ubuntu:22.04

RUN sed -i s/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g /etc/apt/sources.list; \
    apt-get update -y; \
    apt-get install -y cmake gcc-10 g++-10 libcairo2-dev python3 python3-pip; \
    pip3 install flask flask_cors;

WORKDIR /srv/app

COPY ./src ./src
COPY ./lib ./lib
COPY ./include ./include
COPY ./CMakeLists.txt ./CMakeLists.txt
COPY ./LICENSE ./LICENSE

RUN mkdir build; cd build; \
    cmake -DCMAKE_CXX_COMPILER=g++-10 -DCMAKE_C_COMPILER=gcc-10 ..; \
    make -j;

EXPOSE 80

CMD python3 -u src/server.py --port 80 -e ./build/bin/LineAndArrow
