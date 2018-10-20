#!/bin/bash

if [[ "${BUILD_TYPE}" == "AppImage"  || "${BUILD_TYPE}" == "deb" ]]; then
    sudo add-apt-repository ppa:beineri/opt-qt562-trusty -y
    sudo apt-get update -qq
fi