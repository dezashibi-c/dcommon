# ***************************************************************************************
#    Project: dcommon -> https://github.com/dezashibi-c/dcommon
#    File: Makefile
#    Date: 2024-09-08
#    Author: Navid Dezashibi
#    Contact: navid@dezashibi.com
#    Website: https://www.dezashibi.com | https://github.com/dezashibi
#    License:
#     Please refer to the LICENSE file, repository or website for more information about
#     the licensing of this work. If you have any questions or concerns,
#     please feel free to contact me at the email address provided above.
# ***************************************************************************************
#    Description: Please refer to readme file
# ***************************************************************************************

# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -O0 -Wall -Wextra -pedantic

# Platform Specific Settings
ifeq ($(OS),Windows_NT)
	TARGET_EXT = .exe
	CFLAGS +=
	VALGRIND =
else
	TARGET_EXT = .out
	CFLAGS += -lpthread
	VALGRIND = valgrind
endif

SRCDIR = examples

# Source files
SRCS = $(wildcard $(SRCDIR)/*.c)
TARGETS = $(patsubst $(SRCDIR)/%.c,$(SRCDIR)/%$(TARGET_EXT),$(SRCS))

BUILDCMD = $(CC) $(CFLAGS)

# Default target (debug build)
all: $(TARGETS)

test: $(TARGETS)
	@for target in $(TARGETS); do \
		echo "========================================="; \
		echo " Running $$target"; \
		echo "========================================="; \
		./$$target || exit 1; \
	done

memtest: $(TARGETS)
ifeq ($(VALGRIND),)
	@echo "Valgrind is not available on Windows, try using WSL or a VM or an actual Linux machine"
else 
	@for target in $(TARGETS); do \
		echo "========================================="; \
		echo " valgrind $$target"; \
		echo "========================================="; \
		$(VALGRIND) ./$$target || exit 1; \
	done
endif

$(SRCDIR)/%$(TARGET_EXT): $(SRCDIR)/%.c
	$(BUILDCMD) $< -o $@

clean:
	rm -rf $(TARGETS) $(SRCDIR)/*.pdb $(SRCDIR)/*.o $(SRCDIR)/*.obj output.txt $(SRCDIR)/output.txt dthreads.zip $(SRCDIR)/*.dSYM