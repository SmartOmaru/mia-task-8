FROM gcc:latest

WORKDIR /app

COPY ../main.cpp .

RUN g++ -o battle main.cpp

CMD ["./battle"]
