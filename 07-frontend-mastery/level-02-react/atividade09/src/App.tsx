/**
 * @file App.tsx
 * @brief Componente Principal do SkyCargo React Engine.
 * @author Engenheiro de Elite
 */

import './styles/theme.css';

function App() {
  return (
    <div className="nexus-app">
      <header className="header module-box" style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', padding: '20px', borderBottom: '1px solid var(--border-color)' }}>
        <h1>SKYCARGO <span style={{ fontWeight: 300 }}>REACT CORE</span></h1>
        <div className="status-badge status-online">ENGINE: ACTIVE</div>
      </header>

      <main style={{ padding: '40px', textAlign: 'center' }}>
        <h2 style={{ color: 'var(--brand-accent)' }}>Bem-vindo ao Pilar 2: React Elite</h2>
        <p style={{ marginTop: '20px', color: 'var(--text-secondary)' }}>
          O scaffolding industrial via Vite foi concluído com sucesso.
          Pronto para iniciar a componentização de missão crítica.
        </p>
      </main>

      <footer style={{ padding: '20px', textAlign: 'center', fontSize: '0.8rem', color: 'var(--text-muted)' }}>
        &copy; 2026 LogiSpeed Global - V-3.0.0-REACT
      </footer>
    </div>
  );
}

export default App;
