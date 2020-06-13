# Dockerfile
# https://github.com/fcwu/docker-ubuntu-vnc-desktop
FROM dorowu/ubuntu-desktop-lxde-vnc

RUN sudo sed -i 's|http://tw.|http://de.|g' /etc/apt/sources.list
RUN sudo apt update
RUN sudo apt -y install dirmngr

RUN sudo add-apt-repository -y ppa:peek-developers/stable

RUN sudo apt -y upgrade
RUN sudo apt -y install less mc htop git qtcreator qt5-default g++ qttools5-dev build-essential qtdeclarative5-dev libqt5svg5-dev qttools5-dev-tools libqt5xmlpatterns5-dev libqt5websockets5-dev libqt5x11extras5-dev vim peek xscreensaver synaptic

# install smartgit
RUN cd /tmp && wget https://www.syntevo.com/downloads/smartgit/smartgit-20_1_2.deb && sudo dpkg -i smartgit-20_1_2.deb || sudo apt install -fy

