/**
 * @file App.tsx
 * @brief Orquestrador de Frota Dinâmica.
 */

import './styles/theme.css';
import FleetManager from './components/FleetManager';

function App() {
  return (
    <div className="nexus-app" style={{ minHeight: '100vh', padding: '20px' }}>
      <header style={{ marginBottom: '40px', borderLeft: '4px solid var(--brand-accent)', paddingLeft: '20px' }}>
        <h1>SKYCARGO <span style={{ fontWeight: 300 }}>FLEET ENGINE</span></h1>
        <p style={{ color: 'var(--text-secondary)' }}>Operações Globais: <span style={{ color: 'var(--status-success)' }}>ACTIVE / RECONCILING</span></p>
      </header>

      <main>
        <FleetManager />
      </main>

      <footer style={{ marginTop: '80px', textAlign: 'center', fontSize: '0.8rem', color: 'var(--text-muted)' }}>
        &copy; 2026 LogiSpeed Global. Dynamic List Reconciliation: VALIDATED.
      </footer>
    </div>
  );
}

export default App;
