#!/bin/bash

xmlsec1_tarball_url='http://www.aleksey.com/xmlsec/download/xmlsec1-1.2.20.tar.gz'
gmp_tarball_url='http://ftp.gnu.org/gnu/gmp/gmp-4.3.2.tar.gz'
gwenhywfar_tarball_url='http://www2.aquamaniac.de/sites/download/download.php?package=01&release=78&file=01&dummy=gwenhywfar-4.13.1.tar.gz'
aqbanking_tarball_url='http://www.aquamaniac.de/sites/download/download.php?package=03&release=118&file=01&dummy=aqbanking-5.5.1.tar.gz'



echo "Serving files from /app on $PORT"
cd /app
python -m SimpleHTTPServer $PORT &

mkdir -p /app/.aqbanking-buildpack
cd /tmp
#cd $temp_dir
#echo "Temp dir: $temp_dir"

echo "Downloading $xmlsec1_tarball_url"
curl -L $xmlsec1_tarball_url | tar xzv

echo "Downloading $gmp_tarball_url"
curl -L $gmp_tarball_url | tar xzv

echo "Downloading $gwenhywfar_tarball_url"
curl -L $gwenhywfar_tarball_url | tar xzv

echo "Downloading $aqbanking_tarball_url"
curl -L $aqbanking_tarball_url | tar xzv


cd /tmp/xmlsec1-1.2.20
./configure --prefix=/app/.aqbanking-buildpack/xmlsec1
make
make install

cd /tmp/gmp-4.3.2
./configure --prefix=/app/.aqbanking-buildpack/gmp
make
make install

cd /tmp/gwenhywfar-4.13.1
./configure --prefix=/app/.aqbanking-buildpack/gwenhywfar --with-guis=
make
make install

cd /tmp/aqbanking-5.5.1
XMLSEC_CFLAGS="$(/bin/bash /app/.aqbanking-buildpack/xmlsec1/bin/xmlsec1-config --cflags)" XMLSEC_LIBS="$(/bin/bash /app/.aqbanking-buildpack/xmlsec1/bin/xmlsec1-config --libs)" ./configure --prefix=/app/.aqbanking-buildpack/aqbanking --with-gwen-dir=/app/.aqbanking-buildpack/gwenhywfar gmp_libs="-L/app/.aqbanking-buildpack/gmp/lib -lgmp" CPPFLAGS="-I/app/.aqbanking-buildpack/gmp/include"
make
make install

cd /app/
tar -czf aqbanking.tar.gz .aqbanking-buildpack

while true
do
    sleep 1
    echo "."
done
