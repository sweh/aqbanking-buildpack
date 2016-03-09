# add dependent libraries to library path
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/.aqbanking-buildpack/gmp/lib/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/.aqbanking-buildpack/gwenhywfar/lib/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/.aqbanking-buildpack/xmlsec1/lib/

# add aqbanking libraries to library path
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/.aqbanking-buildpack/aqbanking/lib/

# add aqbanking binaries to the path
PATH=$PATH:$HOME/.aqbanking-buildpack/aqbanking/bin/
