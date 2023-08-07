GS_MGMT_IMAGE_REPO ?= ghcr.io/oopt-goldstone/mgmt
GS_MGMT_VERSION ?= v0.8.0

.PHONY: manifests

ifndef X1
$(error $X1 is not defined)
endif

GS_MGMT_BASE ?= $(X1)/packages/base/any/mgmt/builds/manifests

manifests:
	rm -rf manifests && mkdir manifests
	for file in $(wildcard $(TEMPLATE_DIR)/*.yaml);\
	do\
	    sed -e s!IMAGE_TAG!$(IMAGE_TAG)!g -e s!MGMT_IMAGE_REPO!$(GS_MGMT_IMAGE_REPO)!g $$file > manifests/$$(basename $$file);\
	done
	cp -r $(GS_MGMT_BASE) manifests/base
