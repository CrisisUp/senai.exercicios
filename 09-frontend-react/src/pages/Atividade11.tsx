import React, { useState } from 'react';
import styles from './Atividade11.module.css';

/**
 * @section Sub-Componente Modular (O Padrão Arquiteto)
 * Em React, em vez de querySelectorAll, criamos moldes (componentes) 
 * que gerenciam sua própria lógica de exibição.
 */
interface ModuleProps {
  title: string;
  icon: string;
  isSelected: boolean;
  onSelect: () => void;
  children: React.ReactNode;
}

const ControlModule: React.FC<ModuleProps> = ({ title, icon, isSelected, onSelect, children }) => {
  return (
    <article 
      className={`${styles.module} ${isSelected ? styles.selected : ''}`}
      onClick={onSelect}
    >
      <header className={styles.moduleHeader}>
        <span className={styles.icon}>{icon}</span>
        <h3>{title}</h3>
      </header>
      <div className={styles.moduleContent}>
        {children}
      </div>
    </article>
  );
};

const Atividade11: React.FC = () => {
  // Estado para gerenciar qual módulo está em foco
  const [activeModule, setActiveModule] = useState<string | null>(null);

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Nexus Arquiteto - Dashboard Modular</h1>
        <p>Selecione um módulo para focar nos sistemas de telemetria.</p>
      </header>

      <main className={styles.moduleGrid}>
        <ControlModule 
          title="BATERIA" 
          icon="🔋" 
          isSelected={activeModule === 'bat'} 
          onSelect={() => setActiveModule('bat')}
        >
          <div className={styles.stat}>Status: 98% (Carregando)</div>
          <p>Células de energia estáveis.</p>
        </ControlModule>

        <ControlModule 
          title="RADAR TÁTICO" 
          icon="📡" 
          isSelected={activeModule === 'radar'} 
          onSelect={() => setActiveModule('radar')}
        >
          <div className={styles.stat}>Contatos: 12 detectados</div>
          <p>Varredura de 360° ativa.</p>
        </ControlModule>

        <ControlModule 
          title="CLIMA LOCAL" 
          icon="🌤️" 
          isSelected={activeModule === 'weather'} 
          onSelect={() => setActiveModule('weather')}
        >
          <div className={styles.stat}>Vento: 12 km/h (Norte)</div>
          <p>Condições ideais para voo.</p>
        </ControlModule>

        <ControlModule 
          title="LOGS DE VOO" 
          icon="📜" 
          isSelected={activeModule === 'logs'} 
          onSelect={() => setActiveModule('logs')}
        >
          <div className={styles.stat}>Eventos: 45 arquivados</div>
          <p>Persistência garantida via HD.</p>
        </ControlModule>
      </main>

      <footer className={styles.theoryBox}>
        <h4>Nota do Arquiteto: Flex-Wrap & Reuso</h4>
        <p>
          No nível anterior, operávamos via IDs. Como Arquitetos, trabalhamos com <strong>Componentes</strong>. 
          O layout utiliza <code>flex-wrap: wrap</code>, garantindo que se você adicionar 10 módulos, eles 
          se organizem automaticamente sem esmagar a interface. No React, a lógica de "destaque" não busca 
          elementos no DOM; ela apenas reage ao estado <code>activeModule</code>.
        </p>
      </footer>
    </div>
  );
};

export default Atividade11;
