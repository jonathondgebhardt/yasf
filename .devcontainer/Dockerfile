FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
ENV VCPKG_ROOT=/opt/vcpkg

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

# Install vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT \
    && $VCPKG_ROOT/bootstrap-vcpkg.sh

# Make vcpkg available globally
ENV PATH="$VCPKG_ROOT:$PATH"
