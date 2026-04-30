# 🏛️ Dockerfile: Ecossistema de Engenharia de Elite (SENAI)
FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

# 1. Instalar dependências de sistema
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    build-essential cmake ninja-build pkg-config \
    doxygen graphviz \
    python3 python3-pip \
    sqlite3 libsqlite3-dev \
    curl unzip zip \
    highlight

# 2. Instalar AWS CLI v2
RUN curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip" \
    && unzip awscliv2.zip && ./aws/install && rm -rf awscliv2.zip aws/

# 3. Instalar Rust Toolchain
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# 4. Configurar Vcpkg
ENV VCPKG_ROOT=/opt/vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git ${VCPKG_ROOT} \
    && ${VCPKG_ROOT}/bootstrap-vcpkg.sh

# 5. Workspace Setup
WORKDIR /workspaces/senai.exercicios
