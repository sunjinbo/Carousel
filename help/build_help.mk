# ============================================================================
#  Name	 : build_help.mk
#  Part of  : Carousel
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : Carousel
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : Carousel_0xe3732b5d.hlp
Carousel_0xe3732b5d.hlp : Carousel.xml Carousel.cshlp Custom.xml
	cshlpcmp.bat Carousel.cshlp
ifeq (WINSCW,$(findstring WINSCW, $(PLATFORM)))
	md $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy Carousel_0xe3732b5d.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del Carousel_0xe3732b5d.hlp
	del Carousel_0xe3732b5d.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo Carousel_0xe3732b5d.hlp

FINAL : do_nothing
