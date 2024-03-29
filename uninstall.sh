#!/bin/bash

cd "$(dirname "$0")" || exit 1
source "lib/verbose.sh"
source "lib/installer.sh"

echo "* unloading current driver module"
modprobe -r hid_vader3 || true

echo "* looking for registered instances"
echo "found ${#INSTALLED[@]} registered instance(s) on your system"

for instance in "${INSTALLED[@]}"
do
    echo "* $instance"

    set -e

    echo "  * uninstalling and removing $instance from DKMS"
    dkms remove "${V[*]}" "hid-vader3/${instance}" --all

    echo "  * removing $instance folder from /usr/src"
    rm --recursive "${V[@]}" "/usr/src/hid-vader3-$instance/"
done
