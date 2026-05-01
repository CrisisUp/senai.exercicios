/**
 * @file Atividade20.tsx
 * @author Cristiano
 * @date 2026
 */
import React from 'react';
import { NexusDroneCard } from '../components/NexusDroneCard';
import styles from './Atividade20.module.css';

/**
 * @page Atividade20
 * @brief Encapsulamento de Elite: A força dos Componentes React.
 * Substitui o conceito de Web Components (Shadow DOM) por Componentes Funcionais + CSS Modules.
 */
const Atividade20: React.FC = () => {
  const frota = [
    { id: 1, name: "Nexus-Alpha-1", status: "ONLINE" as const, battery: 95 },
    { id: 2, name: "Nexus-Beta-2", status: "OFFLINE" as const, battery: 15 },
    { id: 3, name: "Nexus-Gamma-3", status: "MAINTENANCE" as const, battery: 45 },
    { id: 4, name: "Nexus-Delta-4", status: "ONLINE" as const, battery: 80 }
  ];

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Encapsulamento de Elite</h1>
        <p>Módulos isolados e reutilizáveis (O fim do Style Leak).</p>
      </header>

      <main>
        <section className={styles.grid}>
          {frota.map(drone => (
            <NexusDroneCard 
              key={drone.id}
              name={drone.name}
              status={drone.status}
              battery={drone.battery}
            />
          ))}
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota do Mestre Arquiteto: O Poder do Encapsulamento</h4>
          <p>
            Enquanto no Vanilla JS usamos <strong>Web Components</strong> e <strong>Shadow DOM</strong> para evitar que o CSS vaze, 
            no React atingimos a mesma maestria através de <strong>Componentes Funcionais</strong> e <strong>CSS Modules</strong>.
            <br /><br />
            Cada <code>NexusDroneCard</code> é um universo isolado. Alterar o estilo de um botão dentro dele 
            não afeta nenhum outro botão do sistema. Isso garante a escalabilidade industrial do SkyCargo Nexus.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade20;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
