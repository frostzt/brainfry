FROM ubuntu:22.04
RUN apt-get update && apt-get install -y \
    build-essential cmake clang clangd iproute2 iputils-ping \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /workspace
