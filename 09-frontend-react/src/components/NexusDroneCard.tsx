import React from 'react';
import styles from './NexusDroneCard.module.css';

interface NexusDroneCardProps {
  name: string;
  status: 'ONLINE' | 'OFFLINE' | 'MAINTENANCE';
  battery: number;
}

/**
 * @component NexusDroneCard
 * @brief Componente encapsulado (Mestre Arquiteto).
 * Demonstra isolamento de estilo e lógica via CSS Modules.
 */
export const NexusDroneCard: React.FC<NexusDroneCardProps> = ({ name, status, battery }) => {
  const getStatusClass = () => {
    switch (status) {
      case 'ONLINE': return styles.online;
      case 'OFFLINE': return styles.offline;
      case 'MAINTENANCE': return styles.maint;
      default: return '';
    }
  };

  return (
    <div className={styles.nexusCard}>
      <div className={styles.cardHeader}>
        <h3>{name}</h3>
        <span className={`${styles.statusBadge} ${getStatusClass()}`}>
          {status}
        </span>
      </div>

      <div className={styles.batteryArea}>
        <div className={styles.batteryLabel}>
          <span>Bateria</span>
          <span>{battery}%</span>
        </div>
        <div className={styles.batteryBar}>
          <div 
            className={`${styles.batteryFill} ${battery < 20 ? styles.lowBattery : ''}`} 
            style={{ width: `${battery}%` }}
          ></div>
        </div>
      </div>

      <button className={styles.actionBtn}>
        DETALHES DA MISSÃO
      </button>
    </div>
  );
};
