cmake_minimum_required(VERSION 2.6)

# Add all source files
file( GLOB sources src/*.cpp )
file( GLOB headers src/*.hpp src/*.h )

#Prevent Visual Studio to add its annoying /Debug /Release folders
if( MSVC )
		## Set the directory where the binaries will be stored  
		include_directories( ${CMAKE_SOURCE_DIR}/dependencies/include/ )
		link_directories( ${CMAKE_SOURCE_DIR}/dependencies/lib/ )
		
		set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin )
		
        # Replace the /MDd and /MD flags with respectively /MTd and /MT
        # Prevent Visual to switch to "debug mode" when Boost libraries are the release ones
		set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
        set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
        set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
        foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
                string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
                set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
                set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
                set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
        endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
		
		# copy WIN32 DLLs 
		file(COPY ${CMAKE_SOURCE_DIR}/dependencies/dll/SDL.dll 
		${CMAKE_SOURCE_DIR}/dependencies/dll/sdl_image.dll
		${CMAKE_SOURCE_DIR}/dependencies/dll/libjpeg-8.dll
		${CMAKE_SOURCE_DIR}/dependencies/dll/zlib1.dll
		${CMAKE_SOURCE_DIR}/dependencies/dll/libpng15-15.dll
		${CMAKE_SOURCE_DIR}/dependencies/dll/SDL_ttf.dll
		${CMAKE_SOURCE_DIR}/dependencies/dll/libfreetype-6.dll
		${CMAKE_SOURCE_DIR}/dependencies/dll/SDL_gfx.dll
		${CMAKE_SOURCE_DIR}/dependencies/dll/SDL_mixer.dll
		${CMAKE_SOURCE_DIR}/dependencies/dll/msvcp100d.dll
		${CMAKE_SOURCE_DIR}/dependencies/dll/msvcr100d.dll
		DESTINATION ${CMAKE_SOURCE_DIR}/bin)
endif()

add_executable(HeavyTrain ${sources} ${headers} )

if( MSVC )
	target_link_libraries(HeavyTrain SDLmain)
	target_link_libraries(HeavyTrain tinyxml)
	target_link_libraries(HeavyTrain tinyxmlSTL)
	target_link_libraries(HeavyTrain optimized box2D debug box2Dd)
else()
	target_link_libraries(HeavyTrain Box2D)
	target_link_libraries(HeavyTrain tinyxml)
endif()

target_link_libraries(HeavyTrain SDL)
target_link_libraries(HeavyTrain SDL_image)
target_link_libraries(HeavyTrain SDL_ttf)
target_link_libraries(HeavyTrain SDL_gfx)
target_link_libraries(HeavyTrain SDL_mixer)