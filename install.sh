#!/bin/bash -e

cd "$(dirname "$0")" || exit 1
source "lib/verbose.sh"
source "lib/installer.sh"

if [[ ! -d /sys/devices/virtual/misc/uhid ]]; then

    >&2 echo "WARNING: kernel uhid module not found, controller firmware 5.x will not be supported"

fi

if [[ -z "${INSTALLED[*]}" ]]; then

    set -e

    echo "* creating dkms.conf"
    sed 's/"@DO_NOT_CHANGE@"/"'"${VERSION}"'"/g' <hid-vader3/dkms.conf.in >hid-vader3/dkms.conf

    # TODO: Works around https://github.com/dell/dkms/issues/177 for DKMS 3
    echo "* adding hid-vader3-${VERSION} folder to /usr/src"
    mkdir -p "/usr/src/hid-vader3-${VERSION}"
    cp --recursive "${V[@]}" hid-vader3/. "/usr/src/hid-vader3-${VERSION}/."

    echo "* installing module (using DKMS)"
    dkms install "${V[*]}" "hid-vader3/${VERSION}" --force || cat_dkms_make_log

else

    echo "already installed!"

fi
