FROM cyberbotics/webots:R2025a-ubuntu22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y xvfb \
  screen \
  python3-pip \
  cmake \
  libboost-system-dev \
  libboost-thread-dev \
  protobuf-compiler

RUN mkdir /app

WORKDIR /app

ADD . /app

RUN make

EXPOSE 20011 30011 30012 10300 10301 10302 5900 5555 1234

CMD [ "/bin/bash", "-c", "webots --stream --batch --stdout --stderr --minimize worlds/Match3v3.wbt"  ]
