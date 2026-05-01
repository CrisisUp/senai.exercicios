/**
 * @date 2026
 */
/**
 * @file App.tsx
 * @brief Orquestrador Master com Estado Global (Context API).
 * @author Engenheiro de Elite
 */

import './styles/theme.css';
import { ThemeProvider } from './contexts/ThemeContext';
import ThemeSwitcher from './components/ThemeSwitcher';

const InfoPanel: React.FC = () => {
    return (
        <div style={{ padding: '20px', background: 'var(--bg-card)', borderRadius: 'var(--border-radius)' }}>
            <h3>Status do Vault</h3>
            <p style={{ color: 'var(--text-secondary)', marginTop: '10px' }}>
                Os estilos deste card estão reagindo ao contexto global.
            </p>
        </div>
    );
};

function App() {
  return (
    <ThemeProvider>
        {/* Agora tudo aqui dentro pode acessar o ThemeContext */}
        <div className="nexus-app" style={{ padding: '40px' }}>
            <header style={{ marginBottom: '40px' }}>
                <h1 style={{ letterSpacing: '2px' }}>SKYCARGO <span style={{ fontWeight: 300 }}>GLOBAL CONTEXT</span></h1>
                <p style={{ color: 'var(--text-secondary)' }}>LogiSpeed Fleet Management - Nível 17</p>
            </header>

            <main>
                <ThemeSwitcher />
                <InfoPanel />
            </main>

            <footer style={{ marginTop: '80px', color: 'var(--text-muted)', fontSize: '0.8rem', textAlign: 'center' }}>
                &copy; 2026 LogiSpeed Global. Context Provider Architecture: VALIDATED.
            </footer>
        </div>
    </ThemeProvider>
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
