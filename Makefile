 #* =====================================================================================
 #*       Filename:  Makefile
 #*    Description:  Болванка для с++ проектов
 #*        Version:  2.293 20250321090020
 #*        Created:  2012.06.08  /  18:00:00
 #*       Revision:  2025.03.21/09:00:09
 #*       Compiler:  gcc 12.2.0 deb
 #*         Author:  mb14
 #*        Company:
 #* =====================================================================================
CPUS := $(shell grep -c ^processor /proc/cpuinfo)
MAKEFLAGS += --jobs=$(CPUS)

#MAKEFLAGS+=-j3
CPP  = g++
CC   = gcc

UNAME := $(shell uname)

PRIMARY_TARGET = main.exe

WINDRES = windres.exe
RES_SOURCE_PATH = $(HOME)/Documents/src/resources
RES_SOURCE_FILES = test_zip.txt $(RES_SOURCE_PATH)/GRAF_id_788.png
RESFILE = resourse.zip
ZIPRESSCOMMAND = zip -9
#zip -9 zetblog.zip -r zetblog -x "*.git*" -x "*.venv*" -z
  #-9 - задаёт степень сжатия, 9 - самое сильное и самое медленное; zetblog.zip - имя архива который надо создать; -r - флаг рекурсивного обхода; zetblog - диреткория, которую будем архивировать; -x - не добавлять в архив файлы и директории, которые попадают под указанную маску; -z - этот флаг означает что мы хотим ввести комментарий для архива, комментарий будет считан из stdin, для завершения ввода нужно ввести строку содержащую одну точку и больше ничего.

RM = rm -fv
.PHONY: all all-before all-after clean clean-custom
source_dirs := . src
search_wildcards := $(addsuffix /*.cpp,$(source_dirs))
VPATH := $(source_dirs)
INCS = -I"C:/mingw/include"
CFLAGS = $(INCS)

ifeq ($(UNAME), Linux)
CXXINCS = -I"./include" $(addprefix -I,$(source_dirs)) -I"/usr/include/pcre" -I$(HOME)/Documents/.service/include
LIBS_PATH = -L"." -L"./lib" -L$(HOME)/Documents/.service/lib
LIBS = -lminizip -lpcre -lcurl -lpthread
else
CXXINCS = -I"./include" $(addprefix -I,$(source_dirs)) -I$(HOME)/Documents/.service/include
LIBS_PATH = -L"." -L"./lib" -L$(HOME)/Documents/.service/lib
LIBS = -lmingw32 -lws2_32 -lminizip -lcurl -lpcre -lpthread
endif
#winmm.lib(libwinmm.a) for PlaySound -L"C:/MinGW/i686-w64-mingw32/lib/" -lwinmm -lgdiplus -lboost_regex -lboost_thread -lboost_system XXX sinomimi bibliotek boost pod msys2 -lboost_thread-mt -lboost_system-mt

#-Wextra -Wpedantic -Werror    -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo
#-Wfatal-errors -- sobirat tolko do pervoi oshibki, ot mnogostranichih logov oshibok
#-D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fsanitize=leak -fsanitize=pointer-subtract -fsanitize=pointer-compare -fno-omit-frame-pointer -fstack-protector-all -fstack-clash-protection -fcf-protection
DEBUG_RELEASE_VAR = -g -Wall -Wextra -Wpedantic -DDEBUG_LEVEL=0
CXXFLAGS = $(CXXINCS) $(DEBUG_RELEASE_VAR) -pipe -std=c++20
#enabled with the -MD -pipe.// -MD add *.d files  # -mwindows For WinMain app, -mconsole For console app, SET_MAXIMUM_CCP_VERSION -std=c++98 -std=c++0x -std=c++11 -std=c++14 -std=c++17

release_dir = release
debug_dir = debug
source_files := $(wildcard $(search_wildcards))
object_files := $(notdir $(patsubst %.cpp,%.o,$(source_files)))
object_filesd := $(addprefix $(debug_dir)/, $(object_files))
clean_files := $(PRIMARY_TARGET) *.o *.obj *.d *.log ./$(debug_dir)/*.* ./$(release_dir)/*.* $(RESFILE)

all: all-before ${PRIMARY_TARGET} all-after

clean: clean-custom
	${RM} $(clean_files)

release: DEBUG_RELEASE_VAR = -O3
release: $(PRIMARY_TARGET)

$(RESFILE): $(RES_SOURCE_FILES)
	$(ZIPRESSCOMMAND) $(RESFILE) $(RES_SOURCE_FILES)

$(PRIMARY_TARGET): $(object_files)# $(RESFILE)
	$(CPP) -o $@ $(object_files) $(LIBS_PATH) $(LIBS) $(HOME)/Documents/.service/lib/libmb14shared.so #-lmb14static
	#cat $(RESFILE) >> $@
	echo -e "\a"

%.o: %.cpp
	$(CPP) $(CXXFLAGS) -c $<

all-before:
	@echo source_dirs - $(source_dirs)
	@echo include_dirs - $(CXXINCS)
	@echo libs_dirs - $(LIBS_PATH)
	@echo search_wildcards - $(search_wildcards)
	@echo wildcard - $(wildcard $(search_wildcards))
	@echo CXXFLAGS - $(CXXFLAGS)
	@echo object_files - $(object_files)
	@echo notdir - $(notdir $(patsubst %.cpp, %.o, $(search_wildcards)))
	@echo clean_files - $(clean_files)
	@echo RES_SOURCE_PATH - $(RES_SOURCE_PATH)
	@echo MAKEFLAGS - $(MAKEFLAGS)
	@echo cpus - $(CPUS)

include $(wildcard *.d) 

