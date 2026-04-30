import React, { useEffect } from 'react';
import styles from './Atividade01.module.css';

const Atividade01: React.FC = () => {
  useEffect(() => {
    // Lógica portada do script.js original
    console.log("%c[SYSTEM] Nexus OS v1.0.0 Online (Ported to React)", "color: #00f2ff; font-weight: bold; font-size: 20px;");
    console.log("Sequência de boot concluída. Componente React renderizado.");
    
    // Alert comentado para não atrapalhar o fluxo do desenvolvedor no Hot Reload, 
    // mas mantido como referência técnica da atividade original.
    // alert("Sinal de vida detectado: Nexus OS pronto para operar.");
  }, []);

  return (
    <div className={styles.container}>
      <h1>Nexus OS - Terminal de Comando</h1>
      <p>Iniciando sequência de boot da Tríade Fundamental (Versão React)...</p>
    </div>
  );
};

export default Atividade01;
