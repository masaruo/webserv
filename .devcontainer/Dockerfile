FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y \
    clang \
    net-tools \
    iproute2 \
    dnsutils \
    curl \
    iputils-ping \
    iptables \
    nmap \
    tcpdump \
    telnet \
    make \
    gdb \
    build-essential \
    pkg-config \
    libc++-dev \
    libc++abi-dev \
    libstdc++-12-dev \
    tree \
    lsof \
    vim \
    valgrind \
    man-db \
    siege \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /webserv

# Keep the container running
CMD ["/bin/bash", "-c", "while sleep 1000; do :; done"]
