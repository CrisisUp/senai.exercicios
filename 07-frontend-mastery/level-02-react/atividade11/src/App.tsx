/**
 * @file App.tsx
 * @brief Orquestrador de Dados e Comandos do SkyCargo.
 * @author Engenheiro de Elite
 */

import './styles/theme.css';
import type { IDrone } from './types/index';
import DroneMonitor from './components/DroneMonitor';

function App() {
  // 1. Massa de Dados Táticos (SSOT)
  const frota: IDrone[] = [
    { id: "ALPHA-707", modelo: "Interceptor v3", status: "OPERACIONAL", altitude: 150, velocidade: 85 },
    { id: "BETA-404", modelo: "Cargo Lifter", status: "ALERTA", altitude: 12, velocidade: 0 },
    { id: "GAMMA-909", modelo: "Stealth Scout", status: "EM ROTA", altitude: 300, velocidade: 110 }
  ];

  // 2. Handler de Comando (Será passado via Props)
  const processarComando = (droneId: string, action: string) => {
    console.log(`\x1b[1;33m[NEXUS-HQ]\x1b[0m Comando '${action}' enviado para o drone ${droneId}.`);
    alert(`Comando '${action}' enviado para ${droneId}. Verifique os logs no Nexus Vault.`);
  };

  return (
    <div className="nexus-app" style={{ padding: '30px' }}>
      <header style={{ marginBottom: '40px', borderLeft: '4px solid var(--brand-primary)', paddingLeft: '20px' }}>
        <h1>SKYCARGO <span style={{ fontWeight: 300 }}>PROPS COMMAND</span></h1>
        <p style={{ color: 'var(--text-secondary)' }}>Status da Rede: <span style={{ color: 'var(--status-success)' }}>ESTÁVEL</span></p>
      </header>

      <main>
        <div style={{ display: 'flex', flexWrap: 'wrap', gap: '30px' }}>
          {frota.map(drone => (
            <DroneMonitor 
                key={drone.id} 
                drone={drone} 
                onCommand={processarComando} 
            />
          ))}
        </div>
      </main>

      <footer style={{ marginTop: '80px', color: 'var(--text-muted)', fontSize: '0.8rem' }}>
        &copy; 2026 LogiSpeed Global - Engenharia de Componentes Tipada.
      </footer>
    </div>
  );
}

export default App;
