import React, { useState } from 'react';
import styles from './Atividade06.module.css';

interface Drone {
  id: string;
  model: string;
  battery: number;
  status: 'READY' | 'FLYING' | 'MAINTENANCE';
}

const Atividade06: React.FC = () => {
  // Estado inicial da Frota (Array de Objetos)
  const [fleet, setFleet] = useState<Drone[]>([
    { id: "S-001", model: "Interceptor", battery: 95, status: 'READY' },
    { id: "S-002", model: "Cargo Hauler", battery: 40, status: 'FLYING' },
    { id: "S-003", model: "Explorer v2", battery: 15, status: 'MAINTENANCE' },
  ]);

  // Função para simular atualização de frota (Adicionar novo drone)
  const addDrone = () => {
    const newId = `S-00${fleet.length + 1}`;
    const newDrone: Drone = {
      id: newId,
      model: "Standard Unit",
      battery: 100,
      status: 'READY'
    };
    setFleet([...fleet, newDrone]);
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Central de Monitoramento Global</h1>
        <p>Controle de Frota LogiSpeed - Nível 06</p>
      </header>

      <main className={styles.main}>
        <div className={styles.actionBar}>
          <button onClick={addDrone} className={styles.btnAdd}>ADICIONAR UNIDADE (+)</button>
          <span className={styles.fleetCount}>Total de Unidades: {fleet.length}</span>
        </div>

        <section className={styles.tableContainer}>
          <table className={styles.fleetTable}>
            <thead>
              <tr>
                <th>ID</th>
                <th>MODELO</th>
                <th>BATERIA</th>
                <th>STATUS OPERACIONAL</th>
              </tr>
            </thead>
            <tbody>
              {fleet.map((drone) => (
                <tr key={drone.id} className={styles.droneRow}>
                  <td className={styles.idCell}>{drone.id}</td>
                  <td>{drone.model}</td>
                  <td>
                    <div className={styles.batteryCell}>
                      <div className={styles.batteryMinibar}>
                        <div 
                          className={styles.fill} 
                          style={{ 
                            width: `${drone.battery}%`,
                            backgroundColor: drone.battery < 20 ? '#ff0055' : '#39ff14'
                          }}
                        ></div>
                      </div>
                      <span>{drone.battery}%</span>
                    </div>
                  </td>
                  <td className={`${styles.statusCell} ${styles[drone.status]}`}>
                    {drone.status}
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
          {/* Refatoração Semântica: React map em tabelas deve retornar <tr> diretamente para manter a estrutura */}
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota Técnica: Arrays & Renderização Dinâmica</h4>
          <p>
            No React, não usamos <code>forEach</code> para manipular o DOM manualmente. 
            Utilizamos o método <code>.map()</code> para transformar cada objeto do array <strong>fleet</strong> em uma linha da tabela (JSX). 
            A "Key" é fundamental para que o React saiba qual item atualizar sem redesenhar a frota inteira.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade06;
