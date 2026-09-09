FROM  devkitpro/devkita64:latest  AS  builder

# install dependencies
RUN   apt-get  update       \
  &&  apt-get  install  -y  \
    python3                 \
    python3-pip             \
    python3-venv;

RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"
RUN pip3 install keystone-engine

WORKDIR  /app/

ENTRYPOINT  make
