COLOR_OFF     := $(shell tput sgr0)

COLOR_BLACK   := $(shell tput setaf 0)
COLOR_RED     := $(shell tput setaf 1)
COLOR_GREEN   := $(shell tput setaf 2)
COLOR_YELLOW  := $(shell tput setaf 3)
COLOR_BLUE    := $(shell tput setaf 4)
COLOR_MAGENTA := $(shell tput setaf 5)
COLOR_CYAN    := $(shell tput setaf 6)
COLOR_WHITE   := $(shell tput setaf 7)

COLOR_LIGHT_BLUE := $(shell tput setaf 014)

COLOR_BOLD    := $(shell tput bold)

STATUS_OK := $(shell tput cub 999)$(shell tput cuf 80)$(shell tput bold)[$(shell tput setaf 2)OK$(shell tput sgr0)]\n
