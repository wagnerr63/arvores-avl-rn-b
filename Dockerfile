FROM ubuntu:latest

WORKDIR /usr/src/app

COPY . .

RUN apt-get update
RUN apt-get install build-essential -y && \
    apt-get install manpages-dev -y && \
    apt-get clean