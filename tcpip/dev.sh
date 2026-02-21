#!/bin/bash

set -e

PROJECT_DIR=$(pwd)
CONTAINER_NAME="tun-dev-session"
IMAGE_NAME="tun-dev:latest"

# Check if Dockerfile exists, if not create it
if [ ! -f "Dockerfile" ]; then
    echo "Creating Dockerfile..."
    cat > Dockerfile << 'EOF'
FROM ubuntu:22.04
RUN apt-get update && apt-get install -y \
    build-essential \
    iproute2 \
    iputils-ping \
    cmake \
    gdb \
    git \
    vim \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /workspace
EOF
fi

# Build image if it doesn't exist
if ! docker image inspect $IMAGE_NAME >/dev/null 2>&1; then
    echo "Building Docker image..."
    docker build -t $IMAGE_NAME .
fi

# Run container
echo "Starting dev container..."
docker run -it --rm \
    --cap-add=NET_ADMIN \
    --device=/dev/net/tun \
    -v "$PROJECT_DIR:/workspace" \
    -w /workspace \
    --name $CONTAINER_NAME \
    $IMAGE_NAME bash -c "
        echo '=== TUN/TAP Dev Environment ==='
        echo 'ip addr add 10.0.0.1/24 dev tun0'
        echo 'ip link set tun0 up'
        echo 'ping -c 1 10.0.0.2'
        exec bash
    "
