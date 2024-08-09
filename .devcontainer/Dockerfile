# FROM ubuntu:latest

# ENV DEBIAN_FRONTEND=noninteractive

# # RUN apt update && apt upgrade -y 
# # RUN apt install -y net-tools iproute2 dnsutils curl wget iputils-ping iptables nmap tcpdump telnet 
# # RUN apt install -y git make gdb lldb build-essential cmake tar unzip zip pkg-config libc++-dev libc++abi-dev libstdc++-12-dev
# #netcat cannot install

# # RUN mkdir /webserv

# WORKDIR /webserv

# CMD ["/bin/bash", "-c", "while sleep 1000; do :; done"]

FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
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
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /webserv

# Keep the container running
CMD ["/bin/bash", "-c", "while sleep 1000; do :; done"]
