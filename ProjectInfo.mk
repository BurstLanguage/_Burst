#
# BurstLanguage/ProjectInfo.mk
# Defines general information about the project.
#
NAME := "Burst"
OWNER := "Brynden 'Gigabyte Giant' Bielefeld"
LICENSE := "MIT"
REPOSITORY := "https://github.com/Gigabyte-Giant/Burst.git"

VERSION_MAJOR := "0"
VERSION_MINOR := "0"
VERSION_ITERATION := "0"
VERSION_STRING := "v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_ITERATION}"

dump_project_info:
	@echo "${NAME} ${VERSION_STRING}"
	@echo "${LICENSE} license"