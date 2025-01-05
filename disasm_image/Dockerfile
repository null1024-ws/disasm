# Use 32-bit Ubuntu 20.04 as the base image
FROM i386/ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Update and install essential packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        git \
        ca-certificates \
        binutils-dev \
        cmake \
        gcc \
        g++ \
        libc6:i386 \
        libc6-dbg:i386 \
        libc6-dev:i386 \
        gdb \
        python3 \
        wget \
        vim \
        file \
        make && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Clone the repository
RUN git clone https://github.com/null1024-ws/disasm.git /disasm

# Install GEF
RUN bash -c "$(wget https://gef.blah.cat/sh -O -)"
ENV LC_CTYPE=C.UTF-8

# Set the working directory
WORKDIR /disasm

# Configure and build the project in one step
# RUN CFLAGS="-g -O0" bash -c "git pull && ./configure --enable-debug && make clean && make"
RUN CFLAGS="-g -O3" bash -c "git pull && ./configure && make clean && make"

# Default command to start the container
CMD ["bash"]

