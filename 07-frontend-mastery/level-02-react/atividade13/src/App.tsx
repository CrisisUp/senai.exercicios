/**
 * @file App.tsx
 * @brief Orquestrador Principal com Sincronização Automática.
 */

import './styles/theme.css';
import LiveTelemetry from './components/LiveTelemetry';

function App() {
  return (
    <div className="nexus-app" style={{ minHeight: '100vh', display: 'flex', justifyContent: 'center', alignItems: 'center', padding: '20px' }}>
      <main style={{ maxWidth: '600px', width: '100%' }}>
        <header style={{ textAlign: 'center', marginBottom: '40px' }}>
            <h1 style={{ letterSpacing: '4px' }}>SKYCARGO <span style={{ fontWeight: 300 }}>MONITOR</span></h1>
            <p style={{ color: 'var(--text-secondary)', marginTop: '10px' }}>Nexus Sync Engine: <span style={{ color: 'var(--status-success)' }}>ESTABLISHED</span></p>
        </header>

        <LiveTelemetry />

        <footer style={{ marginTop: '50px', textAlign: 'center', fontSize: '0.8rem', color: 'var(--text-muted)' }}>
            &copy; 2026 LogiSpeed Global. Automated Polling: ON.
        </footer>
      </main>
    </div>
  );
}

export default App;
