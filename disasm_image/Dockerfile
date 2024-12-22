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
        make && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Clone the repository
RUN git clone https://github.com/null1024-ws/disasm.git /disasm

# Set the working directory
WORKDIR /disasm

# Configure and build the project in one step
RUN ./configure && make clean && make

# Default command to start the container
CMD ["bash"]

