FROM gcc:latest

# Installation des dépendances
RUN apt-get update && apt-get install -y \
    libsdl2-dev \
    libsdl2-image-dev \
    libc6-dev \
    build-essential

# Copie du code source
COPY . /smolRPG
WORKDIR /smolRPG

# Compilation du code
RUN gcc -o main ./src/main.c ./src/game.c ./src/character.c ./src/characterMovement.c ./src/obstacle.c  ./src/spell.c ./src/fight.c ./src/drawBackground.c ./src/fightDraw.c  ./src/functions.c -I ./header -I /usr/include/SDL2 -I /usr/include/SDL2_image -L /usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image

# Commande par défaut pour l'exécution
CMD ["./main"]
