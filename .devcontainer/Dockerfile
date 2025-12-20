FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
ENV VCPKG_ROOT=/opt/vcpkg
ENV PATH="$VCPKG_ROOT:$PATH"

WORKDIR /workspace/yasf

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    curl \
    python3 \
    python3-pip \
    clang \
    clangd \
    clang-tidy \
    clang-format \
    lldb \
    zip \
    unzip \
    tar \
    pkg-config \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*

