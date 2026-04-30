/**
 * @file App.tsx
 * @brief Orquestrador Principal de Reatividade.
 */

import './styles/theme.css';
import DroneCommander from './components/DroneCommander';

function App() {
  return (
    <div className="nexus-app" style={{ minHeight: '100vh', display: 'flex', justifyContent: 'center', alignItems: 'center', padding: '20px' }}>
      <main style={{ maxWidth: '800px', width: '100%' }}>
        <header style={{ textAlign: 'center', marginBottom: '40px' }}>
            <h1 style={{ letterSpacing: '4px' }}>SKYCARGO <span style={{ fontWeight: 300 }}>OPERATIONS</span></h1>
            <p style={{ color: 'var(--text-secondary)', marginTop: '10px' }}>Engine Status: <span style={{ color: 'var(--status-success)' }}>REACTIVE / USESTATE</span></p>
        </header>

        <DroneCommander />

        <footer style={{ marginTop: '50px', textAlign: 'center', fontSize: '0.8rem', color: 'var(--text-muted)' }}>
            &copy; 2026 LogiSpeed Global. Virtual DOM Synchronization: ACTIVE.
        </footer>
      </main>
    </div>
  );
}

export default App;
