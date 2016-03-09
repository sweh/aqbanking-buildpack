===========================
Heroku Buildpack: aqbanking
===========================

Buildpack vendoring aqbanking (http://www.aquamaniac.de/sites/aqbanking/index.php)
inside a dyno.

.. image:: https://img.shields.io/badge/license-MIT-blue.svg
   :target: https://github.com/sweh/aqbanking-buildpack/blob/master/LICENSE.txt
   :alt: License

Motivation
==========

I built a web application that displays banking account transactions.
Aqbanking helps me to retrieve those transactions from my bank
programmatically.

Versions
========

xmlsec1: 1.2.20
gmp: 4.3.2
gwenhywfar: 4.13.1
aqbanking: 5.5.1

Setup
=====

Simply add this buildpack to your configured buildpacks::

    $ heroku buildpacks:add https://github.com/sweh/aqbanking-buildpack.git
