ifndef ARCH
$(error $$ARCH not set)
endif

ifneq ($(BOOTMODE), INSTALLED)
$(error $$BOOTMODE is not INSTALLED but $BOOTMOT)
endif

# Hardcoded to match ONL File naming conventions.
include $(X1)/make/versions/version-goldstone.mk
INSTALLER_NAME=$(FNAME_PRODUCT_VERSION)_$(FNAME_BUILD_ID)_$(UARCH)_INSTALLER

MKINSTALLER_OPTS := \
  --arch $(ARCH) \
  --boot-config boot-config \
  --swi goldstone-swi:$(ARCH) \
  --add-file zerotouch.json \
  --onl-version "$(VERSION_STRING)" \
  # THIS LINE INTENTIONALLY LEFT BLANK

ifeq ($(ARCH_BOOT),uboot)
    MKINSTALLER_OPTS += --fit x1-loader-fit:$(ARCH) x1-loader-fit.itb
else ifeq ($(ARCH_BOOT),grub)
    MKINSTALLER_OPTS += --initrd x1-loader-initrd:$(ARCH) x1-loader-initrd-$(ARCH).cpio.gz
else
    $(error ARCH_BOOT=$(ARCH_BOOT) not recognized.)
endif

__installer:
	-rm -f *md5sum *_INSTALLER
	$(ONLPM) --copy-file x1-loader-initrd:$(ARCH) zerotouch.json .
	$(X1)/tools/mkinstaller.py $(MKINSTALLER_OPTS) --out $(INSTALLER_NAME)
	md5sum "$(INSTALLER_NAME)" | awk '{ print $$1 }' > "$(INSTALLER_NAME).md5sum"

clean:
	rm -rf $(WORK_DIR)
