/**
 * @file ControlTower.tsx
 * @brief Dashboard Principal orquestrado por Contextos e Hooks.
 * @author Engenheiro de Elite
 */

import React from 'react';
import { useMission } from '../contexts/MissionContext';
import DroneMonitor from './DroneMonitor';

const ControlTower: React.FC = () => {
    const { fleet, systemIntegrity, lastSync } = useMission();

    return (
        <div className="nexus-dashboard" style={{
            display: 'grid',
            gridTemplateAreas: '"header" "fleet" "footer"',
            gridTemplateRows: 'auto 1fr auto',
            gap: '20px',
            height: '100vh',
            padding: '20px'
        }}>
            <header style={{ gridArea: 'header', borderBottom: '1px solid var(--border-color)', paddingBottom: '20px' }}>
                <h1 style={{ letterSpacing: '4px' }}>SKYCARGO <span style={{ fontWeight: 300 }}>REACT ENGINE</span></h1>
                <div style={{ display: 'flex', gap: '20px', marginTop: '10px', fontSize: '0.8rem' }}>
                    <span>SISTEMA: <strong style={{ color: systemIntegrity === 100 ? 'var(--status-success)' : 'var(--status-alert)' }}>{systemIntegrity}% INTEGRITY</strong></span>
                    <span>LAST SYNC: {lastSync.toLocaleTimeString()}</span>
                </div>
            </header>

            <main style={{ gridArea: 'fleet', overflowY: 'auto' }}>
                <h2 style={{ color: 'var(--brand-accent)', marginBottom: '20px' }}>Active Fleet Radar</h2>
                <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(280px, 1fr))', gap: '20px' }}>
                    {fleet.map(drone => (
                        <DroneMonitor key={drone.id} drone={drone} />
                    ))}
                </div>
            </main>

            <footer style={{ gridArea: 'footer', borderTop: '1px solid var(--border-color)', paddingTop: '10px', textAlign: 'center', fontSize: '0.7rem', color: 'var(--text-muted)' }}>
                &copy; 2026 LogiSpeed Global. Automated React Engine v3.0 Validated.
            </footer>
        </div>
    );
};

export default ControlTower;
