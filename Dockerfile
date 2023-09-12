FROM  devkitpro/devkita64:latest  as  builder

# install dependencies
RUN   apt-get  update       \
  &&  apt-get  install  -y  \
    python3                 \
    python3-pip             \
  &&  pip3  install  keystone-engine  \
;

WORKDIR  /app/

ENTRYPOINT  make
