FROM ubuntu:20.04

MAINTAINER georgezhao 2018221138@email.szu.edu.cn

RUN apt-get update -y
RUN apt-get install -y cmake
RUN apt-get install -y git
RUN apt-get install -y gcc-10
RUN apt-get install -y g++-10
RUN apt-get install -y python3
RUN apt-get install -y python3-pip
RUN apt-get install -y libcairo2-dev

RUN pip3 install flask
RUN pip3 install flask_cors

WORKDIR /root
RUN git clone https://github.com/CreatorZZY/LineAndArrow.git
WORKDIR /root/LineAndArrow
RUN mkdir build
WORKDIR /root/LineAndArrow/build
RUN cmake -DCMAKE_CXX_COMPILER=g++-10 -DCMAKE_C_COMPILER=gcc-10 ..
RUN make -j

WORKDIR /root/LineAndArrow

EXPOSE 80

CMD python3 -u /root/LineAndArrow/src/server.py --port 80 -e /root/LineAndArrow/build/bin/LineAndArrow
