# 🚀 Guia de Operação: 13-Frontend-Angular

Este documento descreve os procedimentos necessários para inicializar e executar
o ecossistema Nexus OS em ambiente Angular v21.

---

## 🛠️ Pré-requisitos de Engenharia

- **Node.js:** v22 ou superior (LTS recomendada).
- **NPM:** Gerenciador de pacotes integrado ao Node.
- **Angular CLI:** `npx @angular/cli` (para execução sem instalação global).

---

## 🏗️ Sequência de Boot (Primeira Execução)

Se esta é a primeira vez que você roda este módulo após um clone do repositório,
siga estes passos:

1. **Acesse o diretório do módulo:**

    ```bash
    cd 13-frontend-angular
    ```

2. **Instale as dependências (Build Artifacts):**

    ```bash
    npm install
    ```

---

## ⚡ Execução do Sistema (Modo Dev)

Para colocar a interface no ar e habilitar o **Hot Reload** (atualização instantânea ao salvar):

1. **Inicie o servidor de desenvolvimento:**

    ```bash
    npm start
    ```

    *Nota: Este comando mapeia internamente para `ng serve` utilizando o motor de renderização ultra-rápido baseado em Vite/esbuild.*

2. **Acesse o terminal de comando no navegador:**

    - **URL:** `http://localhost:4200`

---

## 📂 Estratégia de Navegação

O sistema utiliza **Roteamento Funcional Standalone**. Para alternar entre as
atividades, utilize a barra de endereços:

- `http://localhost:4200/atividade01` -> Tríade Fundamental
- `http://localhost:4200/atividade02` -> Inventário Digital
- `http://localhost:4200/atividade03` -> Monitor de Autonomia
- `http://localhost:4200/atividade04` -> Console de Operações (Home)

---

## 🛡️ Comandos de Elite (CLI)

- **Gerar novo componente:** `npx ng generate component pages/nome-da-atividade`
- **Executar testes unitários:** `npm test`
- **Build de produção:** `npm run build`

---

## *Manual de Operações atualizado em 30 de Abril de 2026.*
