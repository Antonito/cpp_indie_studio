COLOR_SUPPORTED=	1

ifeq ($(COLOR_SUPPORTED), 0)
# Colors definitions
CLEAR=

# Bold High Intens
BLACK=
RED=
GREEN=
YELLOW=
BLUE=
PURPLE=
CYAN=
WHITE=

# Regular
BLACK_R=
RED_R=
GREEN_R=
YELLOW_R=
BLUE_R=
PURPLE_R=
CYAN_R=
WHITE_R=

# Bold
BLACK_B=
RED_B=
GREEN_B=
YELLOW_B=
BLUE_B=
PURPLE_B=
CYAN_B=
WHITE_B=

# High Intens
BLACK_H=
RED_H=
GREEN_H=
YELLOW_H=
BLUE_H=
PURPLE_H=
CYAN_H=
WHITE_H=

# Underline
BLACK_U=
RED_U=
GREEN_U=
YELLOW_U=
BLUE_U=
PURPLE_U=
CYAN_U=
WHITE_U=

# Background
BLACK_BG=
RED_BG=
GREEN_BG=
YELLOW_BG=
BLUE_BG=
PURPLE_BG=
CYAN_BG=
WHITE_BG=

# High Intens Background
BLACK_BG_H=		\e[0;100m
RED_BG_H=		\e[0;101m
GREEN_BG_H=		\e[0;102m
YELLOW_BG_H=	\e[0;103m
BLUE_BG_H=		\e[0;104m
PURPLE_BG_H=	\e[0;105m
CYAN_BG_H=		\e[0;106m
WHITE_BG_H=		\e[0;107m
else
# Colors definitions
CLEAR=			\e[0m

# Bold High Intens
BLACK=			\e[1;90m
RED=			\e[1;91m
GREEN=			\e[1;92m
YELLOW=			\e[1;93m
BLUE=			\e[1;94m
PURPLE=			\e[1;95m
CYAN=			\e[1;96m
WHITE=			\e[1;97m

# Regular
BLACK_R=		\e[0;30m
RED_R=			\e[0;31m
GREEN_R=		\e[0;32m
YELLOW_R=		\e[0;33m
BLUE_R=			\e[0;34m
PURPLE_R=		\e[0;35m
CYAN_R=			\e[0;36m
WHITE_R=		\e[0;37m

# Bold
BLACK_B=		\e[1;30m
RED_B=			\e[1;31m
GREEN_B=		\e[1;32m
YELLOW_B=		\e[1;33m
BLUE_B=			\e[1;34m
PURPLE_B=		\e[1;35m
CYAN_B=			\e[1;36m
WHITE_B=		\e[1;37m

# High Intens
BLACK_H=		\e[0;90m
RED_H=			\e[0;91m
GREEN_H=		\e[0;92m
YELLOW_H=		\e[0;93m
BLUE_H=			\e[0;94m
PURPLE_H=		\e[0;95m
CYAN_H=			\e[0;96m
WHITE_H=		\e[0;97m

# Underline
BLACK_U=		\e[4;30m
RED_U=			\e[4;31m
GREEN_U=		\e[4;32m
YELLOW_U=		\e[4;33m
BLUE_U=			\e[4;34m
PURPLE_U=		\e[4;35m
CYAN_U=			\e[4;36m
WHITE_U=		\e[4;37m

# Background
BLACK_BG=		\e[40m
RED_BG=			\e[41m
GREEN_BG=		\e[42m
YELLOW_BG=		\e[43m
BLUE_BG=		\e[44m
PURPLE_BG=		\e[45m
CYAN_BG=		\e[46m
WHITE_BG=		\e[47m

# High Intens Background
BLACK_BG_H=		\e[0;100m
RED_BG_H=		\e[0;101m
GREEN_BG_H=		\e[0;102m
YELLOW_BG_H=	\e[0;103m
BLUE_BG_H=		\e[0;104m
PURPLE_BG_H=	\e[0;105m
CYAN_BG_H=		\e[0;106m
WHITE_BG_H=		\e[0;107m
endif
