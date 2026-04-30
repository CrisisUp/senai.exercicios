import React, { useState } from 'react';
import styles from './Atividade15.module.css';

/**
 * @interface DroneData
 * @brief Estrutura de dados recebida do servidor remoto (Simulado).
 */
interface DroneData {
  id: number;
  name: string;
  email: string; // Usaremos email como 'Callsign do Operador' para o exemplo
  company: { name: string }; // 'Modelo do Drone'
}

const Atividade15: React.FC = () => {
  const [drones, setDrones] = useState<DroneData[]>([]);
  const [isLoading, setIsLoading] = useState<boolean>(false);
  const [error, setError] = useState<string | null>(null);

  /**
   * @section Comunicação de Rede (Fetch API & Async/Await)
   * Requisito de Elite: Tratamento de erro e feedback visual.
   */
  const fetchNexusData = async () => {
    setIsLoading(true);
    setError(null);
    setDrones([]); // Limpa lista anterior

    try {
      // Simulação de latência de rede industrial (2 segundos)
      await new Promise(resolve => setTimeout(resolve, 2000));

      const response = await fetch('https://jsonplaceholder.typicode.com/users');
      
      if (!response.ok) {
        throw new Error(`Falha na conexão: Código HTTP ${response.status}`);
      }

      const data: DroneData[] = await response.json();
      setDrones(data.slice(0, 5)); // Pegamos apenas os 5 primeiros drones

    } catch (err) {
      setError(err instanceof Error ? err.message : 'Erro desconhecido no Sat-Link.');
    } finally {
      setIsLoading(false);
    }
  };

  return (
    <div className={styles.container}>
      <header className={styles.header}>
        <h1>Monitoramento Global Nexus - Link Satelital</h1>
        <p>Sincronize os dados da frota remota em tempo real.</p>
      </header>

      <main className={styles.main}>
        <div className={styles.actionBar}>
          <button 
            onClick={fetchNexusData} 
            className={styles.btnFetch}
            disabled={isLoading}
          >
            {isLoading ? 'ESTABELECENDO LINK...' : 'REQUISITAR DADOS DO NEXUS'}
          </button>
        </div>

        {/* ÁREA DE RESULTADOS */}
        <section className={styles.dataArea}>
          {/* Skeleton Loaders (Requisito de Elite) */}
          {isLoading && Array.from({ length: 5 }).map((_, i) => (
            <div key={i} className={styles.skeletonCard}>
              <div className={styles.skeletonTitle}></div>
              <div className={styles.skeletonText}></div>
              <div className={styles.skeletonTextShort}></div>
            </div>
          ))}

          {/* Mensagem de Erro (Try/Catch) */}
          {error && (
            <div className={styles.errorBox}>
              <span className={styles.errorIcon}>⚠️</span>
              <h3>ERRO DE COMUNICAÇÃO</h3>
              <p>{error}</p>
            </div>
          )}

          {/* Dados Carregados (Fade-In) */}
          {!isLoading && !error && drones.map(drone => (
            <article key={drone.id} className={styles.droneCard}>
              <div className={styles.cardHeader}>
                <span className={styles.droneId}>UNIDADE: #{drone.id}</span>
                <span className={styles.statusOn}>LINK ATIVO</span>
              </div>
              <h3>{drone.company.name}</h3>
              <div className={styles.operator}>
                <label>OPERADOR RESPONSÁVEL:</label>
                <span>{drone.name.toUpperCase()}</span>
              </div>
              <p className={styles.callsign}>CALLSIGN: {drone.email}</p>
            </article>
          ))}

          {!isLoading && !error && drones.length === 0 && (
            <p className={styles.empty}>LINK SATELITAL EM STANDBY. REQUISITE DADOS PARA INICIAR.</p>
          )}
        </section>

        <footer className={styles.theoryBox}>
          <h4>Nota do Arquiteto: Fetch & Estados de Rede</h4>
          <p>
            Em React, gerenciamos o <strong>Estado de Carregamento (Loading State)</strong> para nunca deixar o operador 
            no escuro. O uso de <code>async/await</code> torna o código de rede linear e legível, enquanto o 
            <code>try/catch</code> garante que falhas de infraestrutura não quebrem a interface, 
            permitindo um tratamento de erro gracioso.
          </p>
        </footer>
      </main>
    </div>
  );
};

export default Atividade15;
