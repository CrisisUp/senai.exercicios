/**
 * @file App.tsx
 * @brief Orquestrador Final do SkyCargo Global Nexus (SA-03).
 */

import React from 'react';
import './styles/theme.css';
import { QueryClient, QueryClientProvider } from '@tanstack/react-query';
import { NexusProvider, useNexus } from './contexts/NexusContext';
import NexusRadar from './components/NexusRadar';
import NexusVault from './components/NexusVault';

const queryClient = new QueryClient();

const DashboardContent: React.FC = () => {
    const { missionStatus, networkIntegrity, lastNexusSync } = useNexus();

    return (
        <div style={{
            display: 'grid',
            gridTemplateAreas: '"header header" "radar vault" "footer footer"',
            gridTemplateColumns: '1fr 350px',
            gridTemplateRows: 'auto 1fr auto',
            gap: '20px',
            minHeight: '100vh',
            padding: '20px'
        }}>
            <header style={{ gridArea: 'header', display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
                <div>
                    <h1 style={{ letterSpacing: '5px' }}>SKYCARGO <span style={{ fontWeight: 300 }}>GLOBAL NEXUS</span></h1>
                    <p style={{ color: 'var(--text-secondary)' }}>LogiSpeed Unified Operations v2.0</p>
                </div>
                <div style={{ textAlign: 'right', fontLines: 'monospace' }}>
                    <p>STATUS: <strong style={{ color: 'var(--status-success)' }}>{missionStatus}</strong></p>
                    <p>INTEGRIDADE: <strong>{networkIntegrity}%</strong></p>
                    <small style={{ color: 'var(--text-muted)' }}>SYNC: {lastNexusSync.toLocaleTimeString()}</small>
                </div>
            </header>

            <main style={{ gridArea: 'radar' }}>
                <NexusRadar />
            </main>

            <aside style={{ gridArea: 'vault' }}>
                <NexusVault />
            </aside>

            <footer style={{ gridArea: 'footer', borderTop: '1px solid var(--border-color)', paddingTop: '10px', textAlign: 'center', fontSize: '0.7rem', color: 'var(--text-muted)' }}>
                &copy; 2026 LogiSpeed Global. Full-Stack Confluence: C++ -> Rust -> SQL -> React.
            </footer>
        </div>
    );
};

function App() {
  return (
    <QueryClientProvider client={queryClient}>
        <NexusProvider>
            <DashboardContent />
        </NexusProvider>
    </QueryClientProvider>
  );
}

export default App;
