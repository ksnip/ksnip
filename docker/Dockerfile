# Dockerfile
# https://github.com/fcwu/docker-ubuntu-vnc-desktop
FROM dorowu/ubuntu-desktop-lxde-vnc

RUN sudo sed -i 's|http://tw.|http://de.|g' /etc/apt/sources.list && \
    sudo apt update && \
    sudo apt -y upgrade
RUN sudo apt -y install dirmngr cmake less mc htop git qtcreator qt5-default g++ qttools5-dev \
    build-essential qtdeclarative5-dev libqt5svg5-dev qttools5-dev-tools libqt5xmlpatterns5-dev \
    libqt5websockets5-dev libqt5x11extras5-dev vim xscreensaver synaptic libglvnd-dev libx11-dev \
    libxcb-render0-dev libxcb-shape0-dev libxcb-xfixes0-dev libxcb1-dev

# install smartgit
RUN cd /tmp && wget https://www.syntevo.com/downloads/smartgit/smartgit-20_1_2.deb && sudo dpkg -i smartgit-20_1_2.deb || sudo apt install -fy

# cleanup
RUN sudo apt-get clean && sudo rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN mkdir /code && cd /code && \
    git clone git://github.com/ksnip/kColorPicker && \
    git clone git://github.com/ksnip/kImageAnnotator && \
    git clone git://github.com/KDE/extra-cmake-modules

COPY build-deps.sh /code
RUN /code/build-deps.sh
RUN chown 1000:1000 /code -R
