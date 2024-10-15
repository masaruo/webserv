FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y

RUN apt-get install -y \
    clang \
    nginx \
    net-tools \
    iproute2 \
    dnsutils \
    curl \
    wget \
    iputils-ping \
    iptables \
    nmap \
    tcpdump \
    telnet \
    git \
    make \
    gdb \
    build-essential \
    cmake \
    tar \
    unzip \
    zip \
    pkg-config \
    libc++-dev \
    libc++abi-dev \
    libstdc++-12-dev \
    rr \
    tree \
    lsof \
    vim \
    valgrind \
    man-db \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

COPY ../nginx/gdbinit /root/.config/gdb/gdbinit

WORKDIR /webserv

# Keep the container running
CMD ["/bin/bash", "-c", "while sleep 1000; do :; done"]
