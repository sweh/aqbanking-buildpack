# norootforbuild
# neededforbuild gettext gettext-devel gcc openssl-devel openssl


%define name gwenhywfar
%define version 4.13.0
%define rpm_cxxflags \"-O2 -march=i486 -mcpu=i586\"
%define rpm_cflags \"-O2 -march=i486 -mcpu=i586\"

%define dist    Ubuntu
%define disttag ubuntu
%define distver 

# Note: There is not yet a special symbol for the rpm release
# version. We set it to one here.
%define release 1.%{disttag}%{distver}


Summary: A multi-platform helper library for other libraries
Name: %{name}
Version: %{version}
Release: %{release}
Source: http://download.sourceforge.net/gwenhywfar/%{name}-%{version}.tar.gz
Group: System Environment/Libraries
License: LGPL
Packager: Martin Preuss <martin@libchipcard.de>
URL: http://sourceforge.net/projects/gwenhywfar
BuildRoot: %{_tmppath}/%{name}-%{version}-root
BuildRequires: openssl-devel gettext
Prereq: /sbin/ldconfig

%description
This is Gwenhywfar, a multi-platform helper library for networking and
security applications and libraries. It is heavily used by libchipcard
www.libchipcard.de and AqBanking/AqHBCI, the German online banking 
libraries.

%package devel
Summary: Gwenhywfar development kit
Group: Development/Libraries
Requires: %{name} = %{version}-%{release}
%description devel
This package contains gwenhywfar-config and header files for writing and
compiling programs using Gwenhywfar.


%prep
%setup -q

%build
%configure --disable-static --with-openssl-libs=%{_libdir}
make

%install
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%files
%defattr(-,root,root)
%doc AUTHORS README COPYING ChangeLog
%{_libdir}/*.so.*
%{_libdir}/%{name}
%{_datadir}/locale/*/LC_MESSAGES/gwenhywfar.mo
%{_bindir}/gct-tool
%{_datadir}/gwenhywfar/*.crt

%files devel
%defattr(-,root,root)
%{_bindir}/gwenhywfar-config
%{_bindir}/xmlmerge
%{_bindir}/mklistdoc
%{_bindir}/typemaker
%{_includedir}/gwenhywfar3
%{_libdir}/*.so
%{_libdir}/*.la
#%{_libdir}/*.a
%{_datadir}/aclocal/gwenhywfar.m4
%{_libdir}/pkgconfig/gwenhywfar.pc

%changelog
