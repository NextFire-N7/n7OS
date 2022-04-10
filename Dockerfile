FROM debian:stable-slim

RUN apt update && \
    apt install -y --no-install-recommends build-essential && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /projet
