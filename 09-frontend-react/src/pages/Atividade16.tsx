import React from 'react';
import { useDroneNetwork } from '../hooks/useDroneNetwork';
import { DroneCardModular } from '../components/DroneCardModular';
import styles from './Atividade16.module.css';

/**
 * @page Atividade16
 * @brief Maestro do Sistema (Camada de Orquestração).
 * Mirror da main.js na trilha Trilogia.
 */
const Atividade16: React.FC = () => {
  const { data, loading, error, connectToNexus } = useDroneNetwork();

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Nexus Arquiteto - Separação de Preocupações</h1>
        <p>Arquitetura escalável: Hooks (Lógica) + Componentes (UI).</p>
      </header>

      <main className={styles.main}>
        <section className={styles.controlArea}>
          <button 
            className={styles.btnAction} 
            onClick={connectToNexus}
            disabled={loading}
          >
            {loading ? 'MODULOS CARREGANDO...' : 'SINCRONIZAR MÓDULOS'}
          </button>
        </section>

        {loading && <div className={styles.loading}>[ SISTEMA ] CARREGANDO DEPENDÊNCIAS...</div>}
        
        {error && <div className={styles.error}>[ FALHA ] {error}</div>}

        <section className={styles.grid}>
          {!loading && !error && data.map(drone => (
            <DroneCardModular key={drone.id} drone={drone} />
          ))}
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota do Arquiteto: Módulos e Clean Code</h4>
          <p>
            No React, a modularização é nativa. Nesta atividade, separamos o sistema em 3 peças:
            <br />
            1. <strong>useDroneNetwork (Hook)</strong>: Encapsula toda a complexidade de rede (o antigo api.js).
            <br />
            2. <strong>DroneCardModular (Componente)</strong>: Especialista em exibir o dado (o antigo ui.js).
            <br />
            3. <strong>Atividade16 (Página)</strong>: Atua como o maestro que conecta a lógica à visão (o antigo main.js).
            <br /><br />
            Isso garante que um bug na lógica de rede não exija mexer no código de design, facilitando a manutenção industrial.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade16;
