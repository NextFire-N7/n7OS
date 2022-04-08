FROM debian:stable-slim

RUN apt update && apt install -y build-essential

WORKDIR /projet
