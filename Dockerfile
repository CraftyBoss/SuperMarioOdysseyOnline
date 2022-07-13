FROM  ubuntu:20.04  as  builder

# install dependencies
RUN   apt-get  update       \
  &&  apt-get  install  -y  \
    curl                    \
    apt-transport-https     \
    python3                 \
    python3-pip             \
  &&  pip  install  keystone-engine  \
;

# install devkitpro
RUN   ln  -s  /proc/self/mounts  /etc/mtab  \
  &&  mkdir  /devkitpro/  \
  &&  echo "deb [signed-by=/devkitpro/pub.gpg] https://apt.devkitpro.org stable main" >/etc/apt/sources.list.d/devkitpro.list  \
  &&  curl --fail  -o /devkitpro/pub.gpg  https://apt.devkitpro.org/devkitpro-pub.gpg  \
  &&  apt-get update  \
  &&  DEBIAN_FRONTEND=noninteractive  apt-get  install  -y  devkitpro-pacman  \
  &&  dkp-pacman  --noconfirm  -S switch-dev  \
;

WORKDIR  /app/

ENV  DEVKITPRO  /opt/devkitpro
ENTRYPOINT  make
