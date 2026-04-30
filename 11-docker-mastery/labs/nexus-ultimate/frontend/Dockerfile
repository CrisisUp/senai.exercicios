# ESTÁGIO 1: Build (Simulado)
FROM alpine AS builder
WORKDIR /build
COPY index.html .
RUN echo "<!-- Versão de Produção -->" >> index.html

# ESTÁGIO 2: Produção (Nginx)
FROM nginx:alpine
WORKDIR /usr/share/nginx/html
COPY --from=builder /build/index.html .
EXPOSE 80
