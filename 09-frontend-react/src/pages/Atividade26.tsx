/**
 * @file Atividade26.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState } from 'react';
import styles from './Atividade26.module.css';

interface Package {
  id: string;
  label: string;
  location: 'inventory' | 'hangar1' | 'hangar2';
}

/**
 * @page Atividade26
 * @brief Logística Visual: Mastering Drag and Drop API no React.
 */
const Atividade26: React.FC = () => {
  const [packages, setPackages] = useState<Package[]>([
    { id: 'PKG-707', label: 'Telemetria Alpha', location: 'inventory' },
    { id: 'PKG-808', label: 'Sensores Beta', location: 'inventory' },
    { id: 'PKG-909', label: 'Motores Gamma', location: 'inventory' },
  ]);

  const [lastLog, setLastLog] = useState('SISTEMA DE DESPACHO PRONTO PARA OPERAÇÃO');
  const [activeHangar, setActiveHangar] = useState<string | null>(null);

  // --- EVENTOS DE DRAG (ARRASTE) ---
  const handleDragStart = (e: React.DragEvent, id: string) => {
    e.dataTransfer.setData('packageId', id);
    e.dataTransfer.effectAllowed = 'move';
    // Adiciona classe visual via classe condicional no render
  };

  // --- EVENTOS DE DROP (SOLTAR) ---
  const handleDragOver = (e: React.DragEvent, hangarId: string) => {
    e.preventDefault(); // Obrigatório para permitir o DROP
    setActiveHangar(hangarId);
  };

  const handleDragLeave = () => {
    setActiveHangar(null);
  };

  const handleDrop = (e: React.DragEvent, targetLocation: Package['location']) => {
    e.preventDefault();
    setActiveHangar(null);

    const packageId = e.dataTransfer.getData('packageId');
    
    setPackages(prev => prev.map(pkg => 
      pkg.id === packageId ? { ...pkg, location: targetLocation } : pkg
    ));

    const locationName = targetLocation === 'inventory' ? 'INVENTÁRIO' : targetLocation.toUpperCase();
    setLastLog(`SUCESSO: ${packageId} DESPACHADO PARA ${locationName}`);
  };

  const renderPackages = (location: Package['location']) => {
    return packages
      .filter(pkg => pkg.location === location)
      .map(pkg => (
        <div 
          key={pkg.id}
          id={pkg.id}
          className={styles.package}
          draggable
          onDragStart={(e) => handleDragStart(e, pkg.id)}
        >
          <span className={styles.packageIcon}>📦</span>
          <span className={styles.packageLabel}>{pkg.label} ({pkg.id})</span>
        </div>
      ));
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Logística Visual SkyCargo</h1>
        <p>Despacho de Ativos via Drag and Drop API nativa.</p>
      </header>

      <main className={styles.logisticsGrid}>
        {/* Inventário */}
        <section 
          className={styles.inventoryArea}
          onDragOver={(e) => handleDragOver(e, 'inventory')}
          onDragLeave={handleDragLeave}
          onDrop={(e) => handleDrop(e, 'inventory')}
        >
          <h2>Inventário de Cargas</h2>
          {renderPackages('inventory')}
        </section>

        {/* Hangares de Destino */}
        <div className={styles.hangarArea}>
          <section 
            className={`${styles.hangar} ${activeHangar === 'hangar1' ? styles.hangarActive : ''}`}
            onDragOver={(e) => handleDragOver(e, 'hangar1')}
            onDragLeave={handleDragLeave}
            onDrop={(e) => handleDrop(e, 'hangar1')}
          >
            <h3>Hangar 01</h3>
            {renderPackages('hangar1')}
          </section>

          <section 
            className={`${styles.hangar} ${activeHangar === 'hangar2' ? styles.hangarActive : ''}`}
            onDragOver={(e) => handleDragOver(e, 'hangar2')}
            onDragLeave={handleDragLeave}
            onDrop={(e) => handleDrop(e, 'hangar2')}
          >
            <h3>Hangar 02</h3>
            {renderPackages('hangar2')}
          </section>
        </div>
      </main>

      <div className={styles.logArea}>
        {lastLog}
      </div>

      <footer className={styles.theoryBox}>
        <h4>Nota do Engenheiro: Drag and Drop Declarativo</h4>
        <p>
          Embora estejamos usando a <strong>Drag and Drop API nativa</strong> (eventos como <code>onDragStart</code> e <code>onDrop</code>), 
          no React não manipulamos o DOM diretamente (como o <code>appendChild</code> da trilha original). 
          <br /><br />
          Em vez disso, usamos o <strong>Estado Reativo</strong>: o arraste captura o ID e o "soltar" atualiza a localização no objeto da carga. 
          O React então re-renderiza a interface, movendo o componente para o hangar correspondente de forma declarativa e segura.
        </p>
      </footer>
    </div>
  );
};

export default Atividade26;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
