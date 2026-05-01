/**
 * @file Atividade09.tsx
 * @author Cristiano
 * @date 2026
 */
import React, { useState, useEffect, useRef } from 'react';
import styles from './Atividade09.module.css';

/**
 * @brief Componente de Alerta (Modularizado)
 * Demonstra o uso da tag nativa <dialog> e refs em React.
 */
interface AlertModalProps {
  isOpen: boolean;
  onClose: () => void;
  message: string;
}

const AlertModal: React.FC<AlertModalProps> = ({ isOpen, onClose, message }) => {
  const dialogRef = useRef<HTMLDialogElement>(null);

  useEffect(() => {
    if (isOpen) {
      dialogRef.current?.showModal();
    } else {
      dialogRef.current?.close();
    }
  }, [isOpen]);

  return (
    <dialog 
      ref={dialogRef} 
      className={styles.modal}
      onCancel={onClose} // Trata a tecla ESC nativamente
    >
      <div className={styles.modalContent}>
        <h2>🚨 ALERTA DE EMERGÊNCIA</h2>
        <p>{message}</p>
        <div className={styles.modalActions}>
          <button onClick={onClose} className={styles.btnConfirm}>CONFIRMAR CIÊNCIA [ESC]</button>
        </div>
      </div>
    </dialog>
  );
};

const Atividade09: React.FC = () => {
  const [isAlertOpen, setIsAlertOpen] = useState(false);
  const [logMessages, setLogMessages] = useState<string[]>(["Sistema inicializado..."]);

  /**
   * @section Eventos de Teclado (Requisito de Elite)
   */
  useEffect(() => {
    const handleKeyDown = (e: KeyboardEvent) => {
      // Tecla 'A' para abrir alerta
      if (e.key.toLowerCase() === 'a') {
        setIsAlertOpen(true);
      }
      // Tecla 'L' para gerar log rápido
      if (e.key.toLowerCase() === 'l') {
        setLogMessages(prev => [`[${new Date().toLocaleTimeString()}] Log de campo disparado via atalho.`, ...prev]);
      }
    };

    window.addEventListener('keydown', handleKeyDown);
    return () => window.removeEventListener('keydown', handleKeyDown);
  }, []);

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Console de Missão - Controle de Camadas</h1>
        <p>Atalhos: [A] Alerta | [L] Log Rápido | [ESC] Fechar</p>
      </header>

      <main className={styles.main}>
        <div className={styles.workspace}>
          <div className={styles.baseLayer}>
            <h3>MAPA TÁTICO (CAMADA BASE)</h3>
            <div className={styles.mapPlaceholder}>
              <div className={styles.droneMarker}>DR-09</div>
            </div>
          </div>

          {/* Botão Fixo (Requisito de Elite) */}
          <button 
            className={styles.floatingBtn}
            onClick={() => setIsAlertOpen(true)}
          >
            DISPARAR ALERTA
          </button>
        </div>

        <section className={styles.logPanel}>
          <h3>LOG DE OPERAÇÕES</h3>
          <ul>
            {logMessages.map((msg, i) => <li key={i}>{msg}</li>)}
          </ul>
        </section>
      </main>

      <AlertModal 
        isOpen={isAlertOpen} 
        onClose={() => setIsAlertOpen(false)}
        message="Risco de colisão detectado no setor 7G! Manobra evasiva recomendada."
      />

      <footer className={styles.theoryBox}>
        <h4>Nota Técnica: Camadas, Atalhos e Ref</h4>
        <p>
          Esta atividade introduz a manipulação de camadas via <strong>Z-index</strong> e <strong>position: fixed</strong>. 
          Utilizamos o hook <code>useRef</code> para interagir diretamente com a API nativa da tag <code>&lt;dialog&gt;</code>, 
          permitindo que o React controle elementos que possuem comportamento imperativo no navegador. 
          O uso de <code>window.addEventListener</code> no useEffect garante que o sistema reaja globalmente a comandos de teclado.
        </p>
      </footer>
    </div>
  );
};

export default Atividade09;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
