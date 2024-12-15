# disasm Project in Docker

This repository provides a `Dockerfile` to build and run the `disasm` C project in a containerized environment.

## Usage

```bash
# Step 1: Clone the repository
git clone https://github.com/null1024-ws/disasm.git
cd disasm_image

# Step 2: Build the Docker image
docker build -t disasm-project .

# Step 3: Run the Docker container
docker run -it --name disasm-container disasm-project /bin/bash

# Step 4: Run the disasm tool inside the container
cd /disasm
./disasm /path/to/test/file.o

# Optional: Use digraphs/istats for enhanced disassembly
./disasm -P digraphs/istats /path/to/test/file.o

# Step 5: Exit the container
exit

```
## Debug log
Please feel free to visit this [link](https://hackmd.io/uAkgHz1RRNOi_soqLLLG4w). 
