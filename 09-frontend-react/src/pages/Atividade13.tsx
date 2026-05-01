/**
 * @file Atividade13.tsx
 * @brief Implementação/Componente Atividade13.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState, useMemo } from 'react';
import styles from './Atividade13.module.css';

interface Drone {
  id: string;
  name: string;
  status: 'operational' | 'alert' | 'maintenance';
}

const fleet: Drone[] = [
  { id: 'DR-701', name: 'SkyScout Alpha', status: 'operational' },
  { id: 'DR-702', name: 'Eagle Eye Beta', status: 'alert' },
  { id: 'DR-703', name: 'Storm Runner', status: 'operational' },
  { id: 'DR-704', name: 'Cloud Ghost', status: 'maintenance' },
  { id: 'DR-705', name: 'Iron Wing', status: 'operational' },
  { id: 'DR-706', name: 'Silent Strike', status: 'alert' },
];

const Atividade13: React.FC = () => {
  const [searchTerm, setSearchTerm] = useState('');
  const [auditLog, setAuditLog] = useState<string[]>([]);

  // Busca Tática Dinâmica (Memoizada)
  const filteredFleet = useMemo(() => {
    return fleet.filter(drone => 
      drone.name.toLowerCase().includes(searchTerm.toLowerCase()) || 
      drone.id.toLowerCase().includes(searchTerm.toLowerCase())
    );
  }, [searchTerm]);

  /**
   * @section Delegação de Eventos (Padrão Arquiteto)
   * No React, eventos em listas já são otimizados pelo Synthetic Event System.
   * Usaremos um handler único para capturar interações via Data Attributes.
   */
  const handleFleetInteraction = (e: React.MouseEvent<HTMLDivElement>) => {
    const target = e.target as HTMLElement;
    // Busca o elemento mais próximo que contenha o data-id (subindo na árvore)
    const card = target.closest('[data-id]');
    
    if (card) {
      const id = card.getAttribute('data-id');
      const status = card.getAttribute('data-status');
      
      const logEntry = `[${new Date().toLocaleTimeString()}] INTERAÇÃO: Drone ${id} selecionado. Status: ${status}`;
      setAuditLog(prev => [logEntry, ...prev.slice(0, 4)]);
    }
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Monitoramento Tático de Alta Densidade</h1>
        <div className={styles.searchBar}>
          <span className={styles.icon}>🔍</span>
          <input 
            type="text" 
            placeholder="BUSCAR DRONE POR ID OU NOME..." 
            value={searchTerm}
            onChange={(e) => setSearchTerm(e.target.value)}
            className={styles.searchInput}
          />
        </div>
      </header>

      <main className={styles.main}>
        {/* Container Pai com Event Delegation */}
        <section 
          className={styles.fleetGrid}
          onClick={handleFleetInteraction}
        >
          {filteredFleet.map(drone => (
            <div 
              key={drone.id} 
              className={styles.droneCard}
              data-id={drone.id}      // Data Attribute (Requisito de Elite)
              data-status={drone.status} // Data Attribute (Requisito de Elite)
            >
              <div className={styles.cardHeader}>
                <span className={styles.droneId}>{drone.id}</span>
                <span className={styles.statusDot}></span>
              </div>
              <h3>{drone.name}</h3>
              <button className={styles.btnAction}>ACESSAR SISTEMAS</button>
            </div>
          ))}
          {filteredFleet.length === 0 && (
            <p className={styles.empty}>NENHUMA UNIDADE DETECTADA.</p>
          )}
        </section>

        <aside className={styles.auditPanel}>
          <h3>LOG DE AUDITORIA</h3>
          <ul className={styles.logList}>
            {auditLog.map((log, i) => <li key={i}>{log}</li>)}
          </ul>
        </aside>
      </main>

      <footer className={styles.theoryBox}>
        <h4>Nota Técnica: Delegação & Metadados</h4>
        <p>
          Embora o React gerencie eventos internamente de forma eficiente, a técnica de <strong>Event Delegation</strong> 
          (captura no pai) é vital para reduzir o consumo de memória em listas massivas. O uso de <strong>Data Attributes</strong> 
          garante que os metadados do domínio (ID, Status) fiquem acoplados ao elemento visual, facilitando a extração 
          de dados em manipuladores globais.
        </p>
      </footer>
    </div>
  );
};

export default Atividade13;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
