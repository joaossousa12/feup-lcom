# name of the program (Minix service)
PROG = proj

.PATH: ${.CURDIR}/devices/timer
.PATH: ${.CURDIR}/devices/video
.PATH: ${.CURDIR}/devices/keyboard
.PATH: ${.CURDIR}/devices/mouse
.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/sprites
.PATH: ${.CURDIR}/game
#complete

# source code files to be compiled
SRCS = proj.c timer.c utils.c keyboard.c KBC.c mouse.c video.c menu.c instructions.c game.c sprites.c KBC_mouse.c # complete

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic 

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>