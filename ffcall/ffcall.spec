%define	name	ffcall
%define	version	1.9
%define	release	1
%define	serial	1

Summary:	Libraries that can be used to build foreign function call interfaces.
Name:		%{name}
Version:	%{version}
Release:	%{release}
Serial:		%{serial}
Copyright:	GPL
Group:		Development/Libraries
Vendor:		The GNUstep Project
URL:		ftp://ftp.santafe.edu/pub/gnu/
Source:		%{name}-%{version}.tar.gz
BuildRoot:	/var/tmp/%{name}-%{version}
Packager:	Adam Fedor <fedor@gnu.org>

%description
This is a collection of four libraries which can be used to build
foreign function call interfaces in embedded interpreters.

The four packages are:

    avcall - calling C functions with variable arguments

    vacall - C functions accepting variable argument prototypes

    trampoline - closures as first-class C functions

    callback - closures with variable arguments as first-class C functions
               (a reentrant combination of vacall and trampoline)

%prep
%setup -q

%build
CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=$RPM_BUILD_ROOT/usr

make

%install
if [ -d $RPM_BUILD_ROOT ]; then rm -r $RPM_BUILD_ROOT; fi
mkdir -p $RPM_BUILD_ROOT
make prefix=$RPM_BUILD_ROOT/usr install

%post	-p /sbin/ldconfig
%postun	-p /sbin/ldconfig

%clean
if [ -d $RPM_BUILD_ROOT ]; then rm -r $RPM_BUILD_ROOT; fi

%files
%defattr(-,root,root)
%doc COPYING NEWS README PLATFORMS
/usr/include/*
/usr/lib/*
/usr/man/*
/usr/share/*

%changelog

