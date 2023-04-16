FROM ubuntu:22.04


ENV export LANG="C.UTF-8" \
    LANGUAGE="en_US:en" \
    LC_CTYPE="C.UTF-8" \
    LC_NUMERIC="C.UTF-8" \
    LC_TIME="C.UTF-8" \
    LC_COLLATE="C.UTF-8" \
    LC_MONETARY="C.UTF-8" \
    LC_MESSAGES="C.UTF-8" \
    LC_PAPER="C.UTF-8" \
    LC_NAME="C.UTF-8" \
    LC_ADDRESS="C.UTF-8" \
    LC_TELEPHONE="C.UTF-8" \
    LC_MEASUREMENT="C.UTF-8" \
    LC_IDENTIFICATION="C.UTF-8" \
    LC_ALL=""

RUN sed -i "s/#force_color_prompt=yes/force_color_prompt=yes/g" /root/.bashrc; \
    echo -e "APT::Install-Suggests \"0\";\nAPT::Install-Recommends \"0\";" > /etc/apt/apt.conf.d/01norecommend; \
    sed -i s/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g /etc/apt/sources.list; \
    apt-get update -y; \
    apt-get install -y cmake gcc g++ libcairo2-dev python3 python3-flask python3-flask-cors;

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
