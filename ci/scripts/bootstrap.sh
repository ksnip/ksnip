#!/bin/bash

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    docker pull ubuntu:17.10
    docker run --name build-container -v `pwd`:`pwd` -w `pwd` -dit ubuntu:17.10 bash
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    docker pull ubuntu:17.10
    docker run --name build-container -v `pwd`:`pwd` -w `pwd` -dit ubuntu:17.10 bash
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker pull opensuse:42.2
    docker run --name build-container -v `pwd`:`pwd` -w `pwd` -dit opensuse:42.2 bash
fi
