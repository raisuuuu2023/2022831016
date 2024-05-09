all:
  g++ -I src/include -L src/lib -o task101 task101.cpp -lmingw32 -lSDL2main -lSDL2
  g++ -I src/include -L src/lib -o task102 task102.cpp -lmingw32 -lSDL2main -lSDL2
  g++ -I src/include -L src/lib -o task103 task103.cpp -lmingw32 -lSDL2main -lSDL2