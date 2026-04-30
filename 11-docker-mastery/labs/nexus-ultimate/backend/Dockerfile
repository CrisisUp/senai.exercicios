FROM alpine
RUN apk add --no-cache curl && adduser -D nexus_user
WORKDIR /app
COPY api.txt .
RUN chown nexus_user:nexus_user api.txt
USER nexus_user
# Simula uma API
CMD ["sh", "-c", "echo 'API Rodando...' && sleep 3600"]
HEALTHCHECK --interval=10s --timeout=3s --retries=3 \
  CMD curl -f http://localhost:8080 || exit 1
