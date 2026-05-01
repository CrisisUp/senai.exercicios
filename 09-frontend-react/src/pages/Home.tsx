/**
 * @file Home.tsx
 * @brief Implementação/Componente Home.tsx
 * @author Cristiano
 * @date 2026
 */
import { Link } from 'react-router-dom';

const Home = () => {
  return (
    <div className="home-container">
      <h1>🎓 Trilha React Elite</h1>
      <p>Selecione uma atividade para iniciar a migração do Nexus OS:</p>
      <nav className="activity-menu">
        <ul>
          <li>
            <Link to="/atividade01">Atividade 01: Fundação React</Link>
          </li>
          <li>
            <Link to="/atividade02">Atividade 02: O Inventário Reativo</Link>
          </li>
          <li>
            <Link to="/atividade03">Atividade 03: Geometria & Cálculo de Autonomia</Link>
          </li>
          <li>
            <Link to="/atividade04">Atividade 04: Controles de Missão (Eventos)</Link>
          </li>
          <li>
            <Link to="/atividade05">Atividade 05: Inteligência Adaptativa (Condicionais)</Link>
          </li>
          <li>
            <Link to="/atividade06">Atividade 06: Gestão de Frota (Arrays & Tabelas)</Link>
          </li>
          <li>
            <Link to="/atividade07">Atividade 07: Visão Tática (Filtros & Cores)</Link>
          </li>
          <li>
            <Link to="/atividade08">Atividade 08: Sistemas Vivos (Animações & Intervalos)</Link>
          </li>
          <li>
            <Link to="/atividade09">Atividade 09: Camadas e Atalhos (Dialog & Keyboard)</Link>
          </li>
          <li>
            <Link to="/atividade10">Atividade 10: Persistência de Missão (LocalStorage)</Link>
          </li>
          <li>
            <Link to="/atividade11">Atividade 11: Arquitetura Modular (Componentes & Flex-Wrap)</Link>
          </li>
          <li>
            <Link to="/atividade12">Atividade 12: Dados Multidimensionais (Objetos & Transform)</Link>
          </li>
          <li>
            <Link to="/atividade13">Atividade 13: Eficiência e Busca (Event Delegation & Data)</Link>
          </li>
          <li>
            <Link to="/atividade14">Atividade 14: Grade de Comando (CSS Grid & Batch Rendering)</Link>
          </li>
          <li>
            <Link to="/atividade15">Atividade 15: Conexão Global (Fetch API & Async)</Link>
          </li>
          <li>
            <Link to="/atividade16">Atividade 16: Arquitetura de Módulos (Hooks & SoC)</Link>
          </li>
          <li>
            <Link to="/atividade17">Atividade 17: Processamento de Dados (Regex & Dates)</Link>
          </li>
          <li>
            <Link to="/atividade18">Atividade 18: A Sincronia de Dubai (Promises & Skeleton)</Link>
          </li>
          <li>
            <Link to="/atividade19">Atividade 19: O Nexus Vivo (Async/Await & APIs)</Link>
          </li>
          <li>
            <Link to="/atividade20">Atividade 20: Encapsulamento de Elite (React Components)</Link>
          </li>
          <li>
            <Link to="/atividade21">Atividade 21: Gráficos Táticos (HTML5 Canvas)</Link>
          </li>
          <li>
            <Link to="/atividade22">Atividade 22: Movimento de Precisão (RequestAnimationFrame)</Link>
          </li>
          <li>
            <Link to="/atividade23">Atividade 23: Sinais Sonoros (Web Audio API)</Link>
          </li>
          <li>
            <Link to="/atividade24">Atividade 24: Processamento Paralelo (Web Workers)</Link>
          </li>
          <li>
            <Link to="/atividade25">Atividade 25: Consciência Espacial (Geolocation API)</Link>
          </li>
          <li>
            <Link to="/atividade26">Atividade 26: Logística Visual (Drag and Drop API)</Link>
          </li>
          <li>
            <Link to="/atividade27">Atividade 27: Visão Tática (MediaDevices API)</Link>
          </li>
          <li>
            <Link to="/atividade28">Atividade 28: Alertas Externos (Notification & Vibration API)</Link>
          </li>
          <li>
            <Link to="/atividade29">Atividade 29: Sobrevivência Digital (Service Workers & Offline)</Link>
          </li>
          <li>
            <Link to="/atividade30">Atividade 30: O Link Bi-direcional (WebSockets API)</Link>
          </li>
        </ul>
      </nav>
    </div>
  );
};

export default Home;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
