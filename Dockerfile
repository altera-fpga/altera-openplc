# ##################################################################################
# Copyright (C) 2025 Altera Corporation
# SPDX-License-Identifier: GPL-3.0-or-later
# ##################################################################################

FROM debian:bullseye-20240722

ARG OPENPLC_REV=01770ddd8ce88045ec5a95fa17f3ccae4d9bf2c0
ARG RUCKIG_REV=801c5f6bab618388f4383d4da3be49022bcba692

RUN apt update && apt install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    python3 \
    python3-venv \
    sqlite3

RUN mkdir /docker_persistent

VOLUME /docker_persistent

# OpenPLC v3
RUN git clone https://github.com/thiagoralves/OpenPLC_v3.git workdir && \
    cd /workdir && \
    git checkout $OPENPLC_REV

RUN mkdir /workdir/patches

# Ruckig
RUN git clone https://github.com/pantor/ruckig.git /ruckig
WORKDIR /ruckig
RUN git checkout $RUCKIG_REV
RUN mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make install

# Fix headers
RUN mkdir /usr/local/include/nlohmann && cp /ruckig/third_party/nlohmann/json.hpp /usr/local/include/nlohmann

# RTMotion
COPY libs/plcopen-motion/. /rtmotion/
WORKDIR /rtmotion
RUN mkdir build && cd build && cmake .. && make install
RUN cp -R /rtmotion/openplc/src/* /workdir/webserver/
RUN cp /rtmotion/openplc/patches/* /workdir/patches/

# Hardware
COPY hardware_support/agilex_doc.cpp /workdir/webserver/core/hardware_layers/
COPY hardware_support/patches/* /workdir/patches/

# Build OpenPLCv3
WORKDIR /workdir
RUN git apply patches/*.patch
RUN ./install.sh docker

RUN touch /docker_persistent/mbconfig.cfg \
    && touch /docker_persistent/persistent.file \
    && mkdir /docker_persistent/st_files \
    && cp /workdir/webserver/openplc.db /docker_persistent/openplc.db \
    && mv /workdir/webserver/openplc.db /workdir/webserver/openplc_default.db \
    && cp /workdir/webserver/dnp3.cfg /docker_persistent/dnp3.cfg \
    && mv /workdir/webserver/dnp3.cfg /workdir/webserver/dnp3_default.cfg \
    && cp /workdir/webserver/st_files/* /docker_persistent/st_files/ \
    && mv /workdir/webserver/st_files /workdir/webserver/st_files_default \
    && cp /workdir/webserver/active_program /docker_persistent/active_program \
    && mv /workdir/webserver/active_program /workdir/webserver/active_program_default \
    && ln -s /docker_persistent/mbconfig.cfg /workdir/webserver/mbconfig.cfg \
    && ln -s /docker_persistent/persistent.file /workdir/webserver/persistent.file \
    && ln -s /docker_persistent/openplc.db /workdir/webserver/openplc.db \
    && ln -s /docker_persistent/dnp3.cfg /workdir/webserver/dnp3.cfg \
    && ln -s /docker_persistent/st_files /workdir/webserver/st_files \
    && ln -s /docker_persistent/active_program /workdir/webserver/active_program

ENTRYPOINT ["./start_openplc.sh"]
