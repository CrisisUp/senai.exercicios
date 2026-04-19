# ==============================================================================
# MAKEFILE - Automação de Compilação (SENAI Exercícios)
# ==============================================================================
# Este Makefile compila todos os arquivos .cpp encontrados no projeto,
# mantendo os executáveis nas mesmas pastas dos códigos-fonte.
# ==============================================================================

# Configurações do Compilador
CXX      := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -fcolor-diagnostics -fansi-escape-codes

# Alvo padrão: Compila tudo
all:
	@echo "🚀 Iniciando compilação em lote..."
	@find . -name "*.cpp" | while read -r file; do \
		echo "🔨 Compilando: $$file"; \
		$(CXX) $(CXXFLAGS) "$$file" -o "$${file%.cpp}"; \
	done
	@echo "✅ Todos os arquivos foram processados com sucesso!"

# Limpa executáveis e pastas de debug (dSYM)
clean:
	@echo "🧹 Iniciando limpeza profunda..."
	@# Remove executáveis baseados nos arquivos .cpp existentes
	@find . -name "*.cpp" | while read -r file; do \
		rm -f "$${file%.cpp}"; \
	done
	@# Remove pastas de debug do macOS (.dSYM)
	@find . -name "*.dSYM" -exec rm -rf {} +
	@echo "✨ Ambiente limpo!"

# Ajuda simplificada
help:
	@echo "Uso do Makefile:"
	@echo "  make        - Compila recursivamente todos os arquivos .cpp"
	@echo "  make clean  - Remove todos os executáveis e arquivos de debug"
	@echo "  make help   - Mostra esta mensagem"

.PHONY: all clean help
