/**
 * @file Atividade02.tsx
 * @brief Implementação/Componente Atividade02.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState } from 'react';
import styles from './Atividade02.module.css';

interface Drone {
  id: string;
  name: string;
  status: 'active' | 'warning';
}

const Atividade02: React.FC = () => {
  // JS (Atitude): Declarando constantes e estados
  const systemVersion = "v2.0.0-react";
  const [operatorName] = useState<string>("Cristiano");

  const drones: Drone[] = [
    { id: "D-001", name: "SkyHawk Zero", status: 'active' },
    { id: "D-002", name: "StormRunner", status: 'warning' },
    { id: "D-003", name: "ThunderBolt", status: 'active' },
  ];

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Inventário de Frota - Nexus React</h1>
        <p>Operador: <strong>{operatorName}</strong> | Versão: {systemVersion}</p>
      </header>

      <section className={styles.inventory}>
        <h2>Status dos Drones em Tempo Real</h2>
        <ul className={styles.droneList}>
          {drones.map((drone) => (
            <li 
              key={drone.id} 
              className={`${styles.droneItem} ${drone.status === 'warning' ? styles.warning : styles.active}`}
              id={drone.status === 'warning' ? 'drone-warning' : undefined}
            >
              <span className={styles.droneId}>[{drone.id}]</span>
              <span className={styles.droneName}>{drone.name}</span>
              <span className={styles.statusBadge}>
                {drone.status === 'active' ? '● OPERACIONAL' : '▲ FALHA DE SISTEMA'}
              </span>
            </li>
          ))}
        </ul>
      </section>
    </div>
  );
};

export default Atividade02;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
