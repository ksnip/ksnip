#!/bin/bash

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    sudo add-apt-repository ppa:beineri/opt-qt562-trusty -y
    sudo apt-get update -qq
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    docker pull ubuntu:17.10
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker pull opensuse:42.2
fi
