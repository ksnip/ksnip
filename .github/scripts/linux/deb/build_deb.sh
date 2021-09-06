#!/bin/bash

cd ksnip-*
debuild -us -uc

mv ksnip_*.deb ksnip-${VERSION}.deb
