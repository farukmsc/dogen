#!/bin/bash
#
# Copyright (C) 2012-2016 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be  useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#

#
# deps
#
dropbox="https://www.dropbox.com/s/axf22srjkiltvr7/"
version=8
package="dogen_deps_gcc_5.3_linux_amd64_v${version}.bz2"
input_location="${dropbox}/${package}"
output_location="/tmp/${package}"
extract_dir="/tmp/dogen_deps"
wget --no-check-certificate ${input_location} -O ${output_location}
mkdir ${extract_dir}
tar -xaf ${output_location} -C ${extract_dir}

#
# common repos
#
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

if [ "${WITH_CSHARP}" == "1" ]; then
    sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
    echo "deb http://download.mono-project.com/repo/debian wheezy main" | sudo tee /etc/apt/sources.list.d/mono-xamarin.list
    sudo apt-get update -qq

    sudo apt-get install mono-devel nuget
    mono --version
    xbuild /version
fi

#
# clang
#
if [ "$CXX" == "clang++" ]; then
    server="http://llvm.org/apt/precise/"
    sources="/etc/apt/sources.list"
    precise="llvm-toolchain-precise"
    sudo sh -c "echo 'deb ${server} ${precise}-3.7 main' >> ${sources}"
    sudo sh -c "echo 'deb ${server} ${precise} main' >> ${sources}"
    wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | sudo apt-key add -
    sudo apt-get update -qq

    sudo apt-get install --allow-unauthenticated -qq clang-3.7
    which clang-3.7
    export CXX="clang++-3.7" CC="clang-3.7"
fi

#
# g++
#
if [ "$CXX" = "g++" ]; then
    sudo apt-get install -qq g++-6
    export CXX="g++-6" CC="gcc-6" GCOV="gcov-6"
fi

#
# ninja
#
sudo apt-get install ninja-build

#
# cmake
#
cmake_name="cmake-3.4.1-Linux-x86_64"
cmake_tar="${cmake_name}.tar.gz"
cmake_input="https://cmake.org/files/v3.4/${cmake_tar}"
cmake_output="/tmp/${cmake_tar}"
wget --no-check-certificate ${cmake_input} -O ${cmake_output}
tar xf ${cmake_output} -C /tmp
sudo cp -r /tmp/${cmake_name}/* /usr

#
# coverage
#
sudo pip install cpp-coveralls
