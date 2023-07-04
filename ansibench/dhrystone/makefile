# DEFAULT BENCHMARK CONFIGURATION
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
n           = 10000000
time        = TIME			# use UNIX time function - okay for single-user machine
hz          = 100

# ----------------------------
# Makefile Options
# ----------------------------

NAME = dhrystone
DESCRIPTION = "Ag C Toolchain Demo"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz -D$(time) -DDHRY_HZ=$(hz)
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
