FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
ENV VCPKG_ROOT=/opt/vcpkg
ENV PATH="$VCPKG_ROOT:$PATH"

WORKDIR /workspace/yasf

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    clang-format \
    clang-tidy \
    clangd \
    cmake \
    cppcheck \
    curl \
    g++-14 \
    gcc-14 \
    git \
    libgl1 \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libglx-mesa0 \
    libudev-dev \
    libx11-6 \
    libx11-dev \
    libxcursor-dev \
    libxcursor1 \
    libxi-dev \
    libxi6 \
    libxinerama1 \
    libxrandr-dev \
    libxrandr2 \
    lldb \
    pkg-config \
    python3 \
    python3-pip \
    tar \
    unzip \
    zip \
    && rm -rf /var/lib/apt/lists/*

RUN  update-alternatives --install \
    /usr/bin/gcc gcc /usr/bin/gcc-14 180 \
    && update-alternatives --install \
    /usr/bin/g++ g++ /usr/bin/g++-14 180

