import { useState, useCallback } from 'react';

export interface DroneUnit {
  id: number;
  name: string;
  username: string;
  status: 'ONLINE' | 'STANDBY';
}

interface ExternalUser {
  id: number;
  username: string;
  company: {
    name: string;
  };
}

/**
 * @hook useDroneNetwork
 * @brief Hook customizado para gerenciar a lógica de rede (Camada de Dados).
 * Mirror da api.js na trilha Trilogia.
 */
export const useDroneNetwork = () => {
  const [data, setData] = useState<DroneUnit[]>([]);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const connectToNexus = useCallback(async () => {
    setLoading(true);
    setError(null);
    try {
      const response = await fetch('https://jsonplaceholder.typicode.com/users');
      if (!response.ok) throw new Error('Falha na autenticação do Sat-Link.');
      
      const rawData = await response.json() as ExternalUser[];
      const formattedData: DroneUnit[] = rawData.slice(0, 4).map((u) => ({
        id: u.id,
        name: u.company.name,
        username: u.username,
        status: Math.random() > 0.3 ? 'ONLINE' : 'STANDBY'
      }));
      
      setData(formattedData);
    } catch (err) {
      setError(err instanceof Error ? err.message : 'Erro crítico de rede.');
    } finally {
      setLoading(false);
    }
  }, []);

  return { data, loading, error, connectToNexus };
};
