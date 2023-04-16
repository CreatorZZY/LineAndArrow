FROM ubuntu:22.04

RUN sed -i s/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g /etc/apt/sources.list; \
    apt-get update -y; \
    apt-get install -y cmake gcc g++ libcairo2-dev python3 python3-pip python3-flask python3-flask-cors;

WORKDIR /srv/app

COPY ./src ./src
COPY ./include ./include
COPY ./CMakeLists.txt ./CMakeLists.txt
COPY ./LICENSE ./LICENSE

RUN mkdir build; cd build; \
    cmake -DCMAKE_CXX_COMPILER=g++-11 -DCMAKE_C_COMPILER=gcc-11 ..; \
    make -j;

EXPOSE 80

CMD python3 -u src/server.py --port 80 -e ./build/bin/LineAndArrow
