/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file main.tsx
 * @brief Ponto de entrada com integração do TanStack Query.
 */

import React from 'react'
import ReactDOM from 'react-dom/client'
import { QueryClient, QueryClientProvider } from '@tanstack/react-query'
import App from './App'

// 1. Criamos o cliente mestre de cache
const queryClient = new QueryClient({
  defaultOptions: {
    queries: {
      staleTime: 1000 * 60 * 5, // Dados são considerados frescos por 5 minutos
      gcTime: 1000 * 60 * 30,    // Mantém no cache por 30 minutos (antigo cacheTime)
      retry: 2,                  // Tenta novamente 2 vezes em caso de falha de rede
      refetchOnWindowFocus: true // Re-sincroniza ao voltar para a aba do navegador
    }
  }
})

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <QueryClientProvider client={queryClient}>
      <App />
    </QueryClientProvider>
  </React.StrictMode>,
)

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
