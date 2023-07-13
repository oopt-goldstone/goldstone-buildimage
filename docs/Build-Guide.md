# Goldstone NOS build guide

##  Description

Following are the instructions on how to build an ONIE compatible network operating system (NOS) installer image of Goldstone NOS

Goldstone project has following repositories which needs to be built -

- Goldstone-management
- usonic
- oopt-tai-implementations
- Goldstone-buildimage

Following repositories are used as submodules in the above repositories -

- OpenNetworkLinux
- oopt-tai

###  Build-Server Requirements

Any server can be a build image server as long as it has:

- Multiple cores to increase build speed
- 8GB+ RAM 
- 200G+ of free disk space
- KVM Virtualization Support
- Ubuntu 20.04
- Docker version >= 20.10.12
  - Enable an execution of different multi-architecture containers by QEMU and binfmt_misc
    - You can do this by running `docker run --rm --privileged multiarch/qemu-user-static --reset -p`
    - See https://github.com/multiarch/qemu-user-static for details

### Prerequisites

Packages that needs to be installed on the build server for building Goldstone NOS

- ca-certificates curl gnupg

- docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin 

- git make  dpkg-dev python-is-python3


### goldstone-mgmt
To compile goldstone-mgmt follow the below steps
```
$ git clone git@github.com:oopt-goldstone/goldstone-mgmt.git
$ cd goldstone-mgmt
$ git checkout master
$ git submodule update --init --recursive
$ make all
```

###  usonic
Usonic builds all the container images required to run the SONiC components in Goldstone NOS
```
$ git clone git@github.com:oopt-goldstone/usonic.git
$ cd usonic
$ git checkout 201904
$ git submodule update --init --recursive sm/sonic-py-swsssdk sm/sonic-sairedis sm/sonic-swss sm/sonic-swss-common sm/sonic-utilities sm/sonic-frr sm/sonic-dbsyncd
$ git submodule update --init sm/sonic-buildimage
$ make all
```

###  oopt-tai-implementations
```
$ git clone git@github.com:Telecominfraproject/oopt-tai-implementations.git
$ cd oopt-tai-implementations/
$ git checkout feature
$ git submodule update --init
$ cd tai_mux/
$ make builder 
$ make dco
```

### Goldstone-buildimage
Goldstone-buildimage will generate the NOS image that can be installed on the device. Goldstone-mgmt, usonic and oopt-tai-implementations repositories must be compiled before building the Goldstone NOS image.

**Note: Incremental build doesn't work well with goldstone-buildimage, so always clone a fresh repository and do a clean build.**
```
$ git clone git@github.com:oopt-goldstone/goldstone-buildimage.git
$ cd goldstone-buildimage
$ git checkout master
$ git submodule update --init
$ make builder
$ make docker
```

## Installing image

After sucessfuly building Goldstone NOS,  image is available in the goldstone-buildimage repository in folder :
```
$ find RELEASE
RELEASE
RELEASE/buster
RELEASE/buster/arm64
RELEASE/buster/arm64/goldstone-v0.8.0_ONL-OS10_2022-11-13.0547-02419c5_ARM64.swi.md5sum
RELEASE/buster/arm64/goldstone-v0.8.0_2022-11-13.0547-02419c5_ARM64_INSTALLER
RELEASE/buster/arm64/goldstone-v0.8.0_ONL-OS10_2022-11-13.0547-02419c5_ARM64.swi
RELEASE/buster/arm64/goldstone-v0.8.0_2022-11-13.0547-02419c5_ARM64_INSTALLER.md5sum
RELEASE/buster/amd64
RELEASE/buster/amd64/goldstone-v0.8.0_ONL-OS10_2022-11-13.0547-02419c5_AMD64.swi
RELEASE/buster/amd64/goldstone-v0.8.0_ONL-OS10_2022-11-13.0547-02419c5_AMD64.swi.md5sum
RELEASE/buster/amd64/goldstone-v0.8.0_2022-11-13.0547-02419c5_AMD64_INSTALLER
RELEASE/buster/amd64/goldstone-v0.8.0_2022-11-13.0547-02419c5_AMD64_INSTALLER.md5sum
```

- Reboot the device and select the ONIE install option
- Transfer the INSTALLER file from build server to the device.
- Use below command to install the image -
  `onie-install-nos goldstone-v0.8.0_2022-11-13.0547-02419c5_AMD64_INSTALLER`
