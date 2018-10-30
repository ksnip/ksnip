#!/bin/bash

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    sudo add-apt-repository ppa:beineri/opt-qt562-trusty -y
    sudo apt-get update -qq
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    docker pull ubuntu:17.10
    docker run --name build-container -dit ubuntu:17.10 bash
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker pull opensuse:42.2
    docker run --name build-container -dit opensuse:42.2 bash
fi
