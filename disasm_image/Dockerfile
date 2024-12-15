FROM ubuntu:22.04

COPY c_related_packages_list.txt /tmp/c_related_packages_list.txt

# Update and install packages from the list and git in one step
RUN apt-get update && \
    xargs -a /tmp/c_related_packages_list.txt apt-get install -y && \
    apt-get install -y git && \
    apt-get install binutils-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/c_related_packages_list.txt

RUN git clone https://github.com/null1024-ws/disasm.git /disasm

WORKDIR /disasm

RUN ./configure

RUN make clean
RUN make

# Adjust CMD to not use <path_to_test_file> directly
# CMD ["./disasm"]

