/**
 * @date 2026
 */
/**
 * @file TacticalDashboard.tsx
 * @brief Dashboard com Cálculos Pesados Otimizados via useMemo e useCallback.
 * @author Engenheiro de Elite
 */

import React, { useState, useMemo, useCallback } from 'react';
import RadarDisplay from './RadarDisplay';

const TacticalDashboard: React.FC = () => {
    const [droneId, setDroneId] = useState<string>('ALPHA-01');
    const [inputVal, setInputVal] = useState<string>(''); // Simula digitação do operador
    const [carga, setCarga] = useState<number>(500);

    /**
     * @brief Simulação de um cálculo matemático pesado.
     * Sem useMemo, este loop rodaria a cada letra digitada no input!
     */
    const autonomiaCalculada = useMemo(() => {
        console.log("\x1b[1;33m[CPU]\x1b[0m Executando cálculo pesado de autonomia...");
        let res = 0;
        for (let i = 0; i < 10000000; i++) { res += Math.sqrt(i); } // Simulação de carga
        return (res / 1000000 + (1000 - carga)).toFixed(2);
    }, [carga]); // Só recalcula se a 'carga' mudar

    /**
     * @brief Handler de reset memorizado.
     * useCallback garante que a referência da função seja a mesma entre renders,
     * impedindo que o RadarDisplay (React.memo) seja redesenhado à toa.
     */
    const handleResetRadar = useCallback(() => {
        console.log("\x1b[1;36m[SYSTEM]\x1b[0m Radar resetado via callback memorizado.");
        setDroneId('STANDBY');
    }, []); 

    return (
        <section style={{
            background: 'var(--bg-surface)',
            border: '1px solid var(--border-color)',
            padding: '30px',
            borderRadius: 'var(--border-radius)',
            maxWidth: '600px',
            margin: '0 auto'
        }}>
            <h2 style={{ color: 'var(--brand-accent)', marginBottom: '20px' }}>MISSION CONTROL ENGINE</h2>

            <div style={{ marginBottom: '20px' }}>
                <label>ID DO ALVO: </label>
                <input 
                    value={droneId} 
                    onChange={e => setDroneId(e.target.value)}
                    style={{ background: 'var(--bg-card)', color: 'white', padding: '5px' }}
                />
            </div>

            <div style={{ marginBottom: '20px' }}>
                <label>NOTAS DO OPERADOR (Teste de Performance): </label>
                <input 
                    value={inputVal} 
                    onChange={e => setInputVal(e.target.value)}
                    placeholder="Digite para testar a fluidez..."
                    style={{ width: '100%', padding: '10px', marginTop: '10px' }}
                />
                <p style={{ fontSize: '0.7rem', color: 'var(--text-muted)', marginTop: '5px' }}>
                    Note no console que digitar aqui NÃO dispara o cálculo pesado ou o redesenho do radar.
                </p>
            </div>

            <hr style={{ borderColor: 'var(--border-color)', margin: '20px 0' }} />

            <div style={{ textAlign: 'center' }}>
                <p>AUTONOMIA CALCULADA: <strong>{autonomiaCalculada} km</strong></p>
                <button 
                    onClick={() => setCarga(prev => prev + 100)}
                    style={{ marginTop: '10px', cursor: 'pointer' }}
                >
                    AUMENTAR CARGA (+100kg)
                </button>
            </div>

            <RadarDisplay droneId={droneId} onReset={handleResetRadar} />
        </section>
    );
};

export default TacticalDashboard;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
