/**
 * @file App.tsx
 * @brief Orquestrador de Componentes do SkyCargo Control Tower.
 * @author Engenheiro de Elite
 */

import './styles/theme.css';
import DroneCard from './components/DroneCard';

function App() {
  return (
    <div className="nexus-app" style={{ minHeight: '100vh', padding: '20px' }}>
      <header style={{ marginBottom: '40px', borderBottom: '1px solid var(--border-color)', paddingBottom: '20px' }}>
        <h1>SKYCARGO <span style={{ fontWeight: 300 }}>REACT ENGINE</span></h1>
        <p style={{ color: 'var(--text-secondary)' }}>LogiSpeed Global Ops - Nível 12 (Componentização)</p>
      </header>

      <main>
        <section>
          <h2 style={{ marginBottom: '20px', color: 'var(--brand-accent)' }}>Frota em Operação</h2>
          
          <div style={{ display: 'flex', flexWrap: 'wrap', gap: '20px' }}>
            {/* Instanciando o "Lego" de interface múltiplas vezes */}
            <DroneCard id="ALPHA-707" altitude={150} velocidade={85} status="OPERACIONAL" />
            <DroneCard id="BETA-404" altitude={12} velocidade={0} status="ALERTA" />
            <DroneCard id="GAMMA-909" altitude={300} velocidade={110} status="EM ROTA" />
            <DroneCard id="SIGMA-001" altitude={0} velocidade={0} status="OFFLINE" />
          </div>
        </section>
      </main>

      <footer style={{ marginTop: '60px', textAlign: 'center', color: 'var(--text-muted)', fontSize: '0.8rem' }}>
        &copy; 2026 LogiSpeed Global - Arquitetura de Componentes Validada.
      </footer>
    </div>
  );
}

export default App;
