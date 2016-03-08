#!/bin/bash

gmp_tarball_url='http://ftp.gnu.org/gnu/gmp/gmp-4.3.2.tar.gz'
gwenhywfar_tarball_url='http://www2.aquamaniac.de/sites/download/download.php?package=01&release=78&file=01&dummy=gwenhywfar-4.13.1.tar.gz'
aqbanking_tarball_url='http://www.aquamaniac.de/sites/download/download.php?package=03&release=118&file=01&dummy=aqbanking-5.5.1.tar.gz'



#echo "Serving files from /tmp on $PORT"
cd /tmp
#python -m SimpleHTTPServer $PORT &

#cd $temp_dir
#echo "Temp dir: $temp_dir"

echo "Downloading $gmp_tarball_url"
curl -L $gmp_tarball_url | tar xzv

echo "Downloading $gwenhywfar_tarball_url"
curl -L $gwenhywfar_tarball_url | tar xzv

echo "Downloading $aqbanking_tarball_url"
curl -L $aqbanking_tarball_url | tar xzv

cd /tmp/gmp-4.3.2
./configure --prefix=/tmp/gmp
make
make install


cd /tmp/gwenhywfar-4.13.1
./configure --prefix=/tmp/gwenhywfar --with-guis=
make
make install


cd /tmp/aqbanking-5.5.1
./configure --prefix=/tmp/aqbanking --with-gwen-dir=/tmp/gwenhywfar CPPFLAGS="-I/tmp/gmp/include"
make
make install
