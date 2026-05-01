/**
 * @file Atividade12.tsx
 * @author Cristiano
 * @date 2026
 */
import React from 'react';
import styles from './Atividade12.module.css';

/**
 * @interface DroneSpecs
 * @brief Definição rigorosa do objeto de dados do drone (Arquiteto Standard).
 */
interface DroneSpecs {
  id: string;
  model: string;
  payloadCapacity: number; // kg
  autonomy: number; // horas
  year: number;
  status: 'ACTIVE' | 'OFFLINE';
}

/**
 * @brief Componente DroneCard
 * Demonstra a passagem de objetos complexos via Props e estilização tátil.
 */
const DroneCard: React.FC<{ drone: DroneSpecs }> = ({ drone }) => {
  return (
    <article className={styles.card}>
      <div className={styles.cardHeader}>
        <span className={styles.droneId}>{drone.id}</span>
        <span className={`${styles.badge} ${styles[drone.status]}`}>{drone.status}</span>
      </div>
      
      <h3 className={styles.modelName}>{drone.model}</h3>
      
      <dl className={styles.specsList}>
        <div className={styles.specItem}>
          <dt>CAPACIDADE:</dt>
          <dd>{drone.payloadCapacity} kg</dd>
        </div>
        <div className={styles.specItem}>
          <dt>AUTONOMIA:</dt>
          <dd>{drone.autonomy} h</dd>
        </div>
        <div className={styles.specItem}>
          <dt>ANO FABRIC.:</dt>
          <dd>{drone.year}</dd>
        </div>
      </dl>
      
      <footer className={styles.cardFooter}>
        <button className={styles.btnDetail}>VER TELEMETRIA COMPLETA</button>
      </footer>
    </article>
  );
};

const Atividade12: React.FC = () => {
  // Array de Objetos Complexos (Dados Multidimensionais)
  const fleet: DroneSpecs[] = [
    { id: 'ALPHA-01', model: 'SkyCarrier v4', payloadCapacity: 150, autonomy: 12, year: 2025, status: 'ACTIVE' },
    { id: 'BRAVO-07', model: 'ThunderBolt X', payloadCapacity: 80, autonomy: 18, year: 2026, status: 'ACTIVE' },
    { id: 'CHARLIE-12', model: 'SilentShadow', payloadCapacity: 20, autonomy: 24, year: 2024, status: 'OFFLINE' },
  ];

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Arquitetura de Dados - Especificações de Frota</h1>
        <p>Monitoramento detalhado de parâmetros multidimensionais.</p>
      </header>

      <main className={styles.grid}>
        {fleet.map(drone => (
          <DroneCard key={drone.id} drone={drone} />
        ))}
      </main>

      <footer className={styles.theoryBox}>
        <h4>Nota do Arquiteto: Objetos & Transformações</h4>
        <p>
          Nesta atividade, evoluímos de variáveis simples para <strong>Objetos Estruturados</strong>. 
          O CSS utiliza a propriedade <code>transform</code> para criar um efeito de escala (pop-out) e deslocamento (lift) 
          sem impactar o fluxo do DOM, garantindo uma performance suave (60 FPS) durante a interação do operador.
        </p>
      </footer>
    </div>
  );
};

export default Atividade12;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
