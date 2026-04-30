import React from 'react';
import { DroneUnit } from '../hooks/useDroneNetwork';
import styles from '../pages/Atividade16.module.css';

interface Props {
  drone: DroneUnit;
}

/**
 * @component DroneCardModular
 * @brief Componente especializado na visualização (Camada de UI).
 * Mirror da ui.js na trilha Trilogia.
 */
export const DroneCardModular: React.FC<Props> = ({ drone }) => {
  return (
    <div className={`${styles.card} ${styles[drone.status]}`}>
      <div className={styles.cardHeader}>
        <span className={styles.unitCode}>NODE-0{drone.id}</span>
        <span className={styles.statusLabel}>{drone.status}</span>
      </div>
      <h3 className={styles.modelName}>{drone.name}</h3>
      <p className={styles.operator}>Operador: @{drone.username}</p>
    </div>
  );
};
