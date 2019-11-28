cmake_minimum_required(VERSION 3.15)

PROJECT(CeleroProject)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

	EXTERNALPROJECT_ADD(
		rapidjson
		GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG "master"
		SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rapidjson"
		UPDATE_COMMAND  "git clone"
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
	)
