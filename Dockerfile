# development enviroment
FROM alpine:3.16 AS development
WORKDIR /src
COPY . .
# speed up apk downloading (for China mainland)
RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.ustc.edu.cn/g' /etc/apk/repositories
RUN apk update && apk upgrade
RUN apk add --no-cache openssl gcc g++ make cmake python3 bam icu-dev zlib-dev
RUN mkdir build; cd build; cmake .. -DCMAKE_BUILD_TYPE=Release -DGEOLOCATION=OFF; make -j$(nproc)

# production enviroment (alpine
FROM alpine:3.16 AS production
WORKDIR /infdust_srv/
# speed up apk downloading (for China mainland)
RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.ustc.edu.cn/g' /etc/apk/repositories
RUN apk update && apk upgrade
RUN apk add --no-cache openssl libstdc++ icu
COPY --from=development /src/build /infdust_srv
COPY --from=development /src/autoexec.cfg /infdust_srv/
EXPOSE 8303/udp
ENTRYPOINT ["./Infclass-Server"]
