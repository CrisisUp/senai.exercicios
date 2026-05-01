/**
 * @file Atividade07.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState, useMemo } from 'react';
import styles from './Atividade07.module.css';

interface Drone {
  id: string;
  name: string;
  status: 'OPERATIONAL' | 'WARNING' | 'IN_ROUTE';
  load: number;
}

// Dados brutos da frota (Simulando uma API) - Movido para fora para evitar recriação
const fullFleet: Drone[] = [
  { id: 'DR-10', name: 'Eagle Eye', status: 'OPERATIONAL', load: 45 },
  { id: 'DR-22', name: 'Storm Breaker', status: 'WARNING', load: 88 },
  { id: 'DR-35', name: 'Night Hawk', status: 'IN_ROUTE', load: 12 },
  { id: 'DR-49', name: 'Cloud Racer', status: 'OPERATIONAL', load: 30 },
  { id: 'DR-51', name: 'Iron Wing', status: 'WARNING', load: 95 },
];

const Atividade07: React.FC = () => {
  // Estado para o filtro selecionado
  const [filter, setFilter] = useState<string>('ALL');

  /**
   * @brief Lógica de Filtro (Requisito de Elite)
   * O uso de useMemo garante que o filtro só rode se o 'filter' ou 'fullFleet' mudarem.
   */
  const filteredFleet = useMemo(() => {
    if (filter === 'ALL') return fullFleet;
    return fullFleet.filter(drone => drone.status === filter);
  }, [filter]);

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Terminal Tático - Visão de Frota</h1>
        <p>Ajuste os filtros para focar em unidades críticas.</p>
      </header>

      <main className={styles.main}>
        {/* Painel de Controle (Filtros) */}
        <section className={styles.filterBar}>
          <label htmlFor="status-filter">FILTRAR POR STATUS:</label>
          <select 
            id="status-filter" 
            value={filter} 
            onChange={(e) => setFilter(e.target.value)}
            className={styles.select}
          >
            <option value="ALL">EXIBIR TODOS</option>
            <option value="OPERATIONAL">OPERACIONAIS</option>
            <option value="WARNING">ALERTAS CRÍTICOS</option>
            <option value="IN_ROUTE">EM ROTA</option>
          </select>
        </section>

        {/* Grade de Drones (Visão Tática) */}
        <section className={styles.grid}>
          {filteredFleet.map(drone => (
            <div key={drone.id} className={`${styles.card} ${styles[drone.status]}`}>
              <div className={styles.cardGlass}>
                <span className={styles.droneId}>{drone.id}</span>
                <h3>{drone.name}</h3>
                <div className={styles.statusInfo}>
                  <span className={styles.indicator}></span>
                  {drone.status.replace('_', ' ')}
                </div>
                <div className={styles.loadArea}>
                  <label>Carga:</label>
                  <span>{drone.load}%</span>
                  <div className={styles.loadBar}>
                    <div className={styles.loadFill} style={{ width: `${drone.load}%` }}></div>
                  </div>
                </div>
              </div>
            </div>
          ))}
          {filteredFleet.length === 0 && (
            <p className={styles.emptyMsg}>Nenhuma unidade encontrada com este filtro.</p>
          )}
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota Técnica: O Poder do .filter()</h4>
          <p>
            No React, o filtro é puramente reativo. Ao mudar o valor do <code>select</code>, 
            o estado <code>filter</code> é alterado, disparando uma nova execução do método 
            <code>.filter()</code>. As cores são geradas via <strong>HSL</strong> e <strong>RGBA</strong>, 
            permitindo efeitos de transparência e brilho consistentes.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade07;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
