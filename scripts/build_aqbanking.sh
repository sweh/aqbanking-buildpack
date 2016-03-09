#!/bin/bash

XMLSEC1_VERSION="1.2.20"
GMP_VERSION="4.3.2"
GWENHYWFAR_VERSION="4.13.1"
AQBANKING_VERSION="5.5.1"

xmlsec1_tarball_url="http://www.aleksey.com/xmlsec/download/xmlsec1-$XMLSEC1_VERSION.tar.gz"
gmp_tarball_url="http://ftp.gnu.org/gnu/gmp/gmp-$GMP_VERSION.tar.gz"
gwenhywfar_tarball_url="http://www2.aquamaniac.de/sites/download/download.php?package=01&release=78&file=01&dummy=gwenhywfar-$GWENHYWFAR_VERSION.tar.gz"
aqbanking_tarball_url="http://www.aquamaniac.de/sites/download/download.php?package=03&release=118&file=01&dummy=aqbanking-$AQBANKING_VERSION.tar.gz"

mkdir -p /app/download
mkdir -p /app/.aqbanking-buildpack

echo "Serving files from /app/download on $PORT"
cd /app/download
python -m SimpleHTTPServer $PORT &

cd /tmp

echo "Downloading $xmlsec1_tarball_url"
curl -L $xmlsec1_tarball_url | tar xzv

echo "Downloading $gmp_tarball_url"
curl -L $gmp_tarball_url | tar xzv

echo "Downloading $gwenhywfar_tarball_url"
curl -L $gwenhywfar_tarball_url | tar xzv

echo "Downloading $aqbanking_tarball_url"
curl -L $aqbanking_tarball_url | tar xzv


cd "/tmp/xmlsec1-$XMLSEC1_VERSION"
./configure --prefix=/app/.aqbanking-buildpack/xmlsec1
make
make install

cd "/tmp/gmp-$GMP_VERSION"
./configure --prefix=/app/.aqbanking-buildpack/gmp
make
make install

cd "/tmp/gwenhywfar-$GWENHYWFAR_VERSION"
./configure --prefix=/app/.aqbanking-buildpack/gwenhywfar --with-guis=
make
make install

cd "/tmp/aqbanking-$AQBANKING_VERSION"
XMLSEC_CFLAGS="$(/bin/bash /app/.aqbanking-buildpack/xmlsec1/bin/xmlsec1-config --cflags)" XMLSEC_LIBS="$(/bin/bash /app/.aqbanking-buildpack/xmlsec1/bin/xmlsec1-config --libs)" ./configure --prefix=/app/.aqbanking-buildpack/aqbanking --with-gwen-dir=/app/.aqbanking-buildpack/gwenhywfar gmp_libs="-L/app/.aqbanking-buildpack/gmp/lib -lgmp" CPPFLAGS="-I/app/.aqbanking-buildpack/gmp/include"
make
make install

cd /app/
tar -czf "aqbanking-$AQBANKING_VERSION.tar.gz" .aqbanking-buildpack
mv "aqbanking-$AQBANKING_VERSION.tar.gz" download

while true
do
    sleep 1
    echo "."
done
