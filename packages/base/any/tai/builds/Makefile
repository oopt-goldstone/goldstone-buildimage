IMAGE_REPO=docker.io/microsonic
IMAGE_NAME ?= tai
TAG=latest

ANY_DIR ?= $(X1)/packages/base/any/tai/builds
DOCKER_FILE ?= $(ANY_DIR)/Dockerfile

ifndef ARCH
$(error $$ARCH is not defined)
endif

ifndef TAI_LIBS
$(error $$TAI_LIBS is not defined)
endif

LIB_DIR ?= lib
LIBS := $(addprefix $(LIB_DIR)/,$(TAI_LIBS))

LIB_REPO ?= ghcr.io/oopt-goldstone

define download_library
docker run --rm --platform linux/$(ARCH) -v $(abspath $(LIB_DIR)):/data -w /data $(LIB_REPO)/$(1) sh -c 'cp /root/* /data/'
sudo chown -R `id -u`:`id -g` $(LIB_DIR)
endef

all: $(LIBS) tai-$(ARCH).tar

tai-$(ARCH).tar: FORCE
	docker pull --platform=linux/$(ARCH) $(IMAGE_REPO)/$(IMAGE_NAME):$(TAG)
	DOCKER_BUILDKIT=1 docker build --build-arg BASE=$(IMAGE_REPO)/$(IMAGE_NAME):$(TAG) --platform linux/$(ARCH) -t $(IMAGE_NAME)-$(ARCH):$(TAG) -f $(DOCKER_FILE) .
	docker save $(IMAGE_NAME)-$(ARCH):$(TAG) > $@

FORCE:
