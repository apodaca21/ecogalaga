cmake_minimum_required(VERSION 3.16)
project(SFML)

set(CMAKE_CXX_STANDARD 17)

# Ruta a las librerías de SFML
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

# Buscar las librerías de SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Archivos fuente
set(SOURCES
        main.cpp
        Game.cpp
        Player.cpp
        Enemy.cpp
        Bullet.cpp
)

# Crear el ejecutable
add_executable(SFML ${SOURCES})

# Enlazar SFML al ejecutable
target_link_libraries(SFML sfml-graphics sfml-audio)

# Copiar recursos automáticamente al directorio de compilación
file(COPY ${CMAKE_SOURCE_DIR}/fondojuegoespacio.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/fondoparajuego.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/personajeverde.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/enemigorojo.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/botellamala.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/GAMEOVER.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/sonidodisparo.ogg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/sonidofondo.ogg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/sonidogameover.ogg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Roboto-Regular.ttf DESTINATION ${CMAKE_BINARY_DIR})
