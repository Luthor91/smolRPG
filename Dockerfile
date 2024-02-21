FROM gcc:latest

# Prevent dialog prompts
ENV DEBIAN_FRONTEND=noninteractive

ENV XDG_RUNTIME_DIR=/tmp/runtime-root

RUN apt-get update && apt-get install -y \
    libsdl2-dev \
    libsdl2-image-dev \
    libc6-dev \
    build-essential

COPY . /smolRPG
WORKDIR /smolRPG

RUN gcc -o main ./src/main.c ./src/game.c ./src/character.c ./src/characterMovement.c ./src/obstacle.c  ./src/spell.c ./src/fight.c ./src/drawBackground.c ./src/fightDraw.c  ./src/functions.c -I ./header -I /usr/include/SDL2 -I /usr/include/SDL2_image -L /usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image

CMD ["./main"]
