USONIC_IMAGES ?= docker.io/nlpldev/usonic-cli:latest ghcr.io/oopt-goldstone/usonic-debug:202205 docker.io/bitnami/kubectl:latest
BCMD_IMAGE ?= bcmd:latest

.PHONY: bcmd

all: usonic-amd64.tar 

usonic-amd64.tar: Makefile bcmd
	for image in $(USONIC_IMAGES);\
	do \
	    docker pull $$image; \
	done
	docker save $(USONIC_IMAGES) $(BCMD_IMAGE) > $@

bcmd:
	cd bcmd && DOCKER_BUILDKIT=1 docker build --progress plain -t $(BCMD_IMAGE) .
