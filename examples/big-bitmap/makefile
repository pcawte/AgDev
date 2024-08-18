# ----------------------------
# Makefile Options
# ----------------------------

NAME = big-bitmap
DESCRIPTION = "Big Bitmap Demo"
COMPRESSED = NO
LDHAS_ARG_PROCESSING = 0

BSSHEAP_LOW = 060000
BSSHEAP_HIGH = 09FFFF

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

IMAGES = $(call NATIVEPATH,$(SRCDIR)/img/*.rgba)
IMAGES_DEST = $(call NATIVEPATH,$(BINDIR)/img)

DEPS = $(IMAGES)

#Unsure why the copy of this in makefile.mk doesn't cover this already...
ifeq ($(OS),Windows_NT)
COPYDIR ?= ( xcopy $1 $2 /S /Q /Y /I /K 1>nul 2>nul || call )
else
COPYDIR ?= cp -r $1 $2
endif

# ----------------------------

include $(shell cedev-config --makefile)

#copy images to /bin
$(IMAGES): 
	$(Q)$(call NATIVEMKDR,$(IMAGES_DEST))
	$(Q)$(call COPYDIR,$(IMAGES),$(IMAGES_DEST))
	
	