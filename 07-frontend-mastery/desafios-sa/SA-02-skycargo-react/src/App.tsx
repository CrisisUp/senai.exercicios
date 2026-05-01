/**
 * @author Cristiano
 * @date 2026
 */
/**
 * @file App.tsx
 * @brief Orquestrador Final do SkyCargo React Engine (SA-02).
 */

import './styles/theme.css';
import { MissionProvider } from './contexts/MissionContext';
import ControlTower from './components/ControlTower';

function App() {
  return (
    <MissionProvider>
        <ControlTower />
    </MissionProvider>
  );
}

export default App;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
