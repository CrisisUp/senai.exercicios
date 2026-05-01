/**
 * @file App.tsx
 * @brief Implementação/Componente App.tsx
 * @author Cristiano
 * @date 2026
 */
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';
import Home from './pages/Home';
import Atividade01 from './pages/Atividade01';
import Atividade02 from './pages/Atividade02';
import Atividade03 from './pages/Atividade03';
import Atividade04 from './pages/Atividade04';
import Atividade05 from './pages/Atividade05';
import Atividade06 from './pages/Atividade06';
import Atividade07 from './pages/Atividade07';
import Atividade08 from './pages/Atividade08';
import Atividade09 from './pages/Atividade09';
import Atividade10 from './pages/Atividade10';
import Atividade11 from './pages/Atividade11';
import Atividade12 from './pages/Atividade12';
import Atividade13 from './pages/Atividade13';
import Atividade14 from './pages/Atividade14';
import Atividade15 from './pages/Atividade15';
import Atividade16 from './pages/Atividade16';
import Atividade17 from './pages/Atividade17';
import Atividade18 from './pages/Atividade18';
import Atividade19 from './pages/Atividade19';
import Atividade20 from './pages/Atividade20';
import Atividade21 from './pages/Atividade21';
import Atividade22 from './pages/Atividade22';
import Atividade23 from './pages/Atividade23';
import Atividade24 from './pages/Atividade24';
import Atividade25 from './pages/Atividade25';
import Atividade26 from './pages/Atividade26';
import Atividade27 from './pages/Atividade27';
import Atividade28 from './pages/Atividade28';
import Atividade29 from './pages/Atividade29';
import Atividade30 from './pages/Atividade30';

function App() {
  return (
    <Router>
      <div className="app-container">
        <header className="main-header">
          <nav>
            <Link to="/">Nexus Home</Link>
          </nav>
        </header>

        <main>
          <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/atividade01" element={<Atividade01 />} />
            <Route path="/atividade02" element={<Atividade02 />} />
            <Route path="/atividade03" element={<Atividade03 />} />
            <Route path="/atividade04" element={<Atividade04 />} />
            <Route path="/atividade05" element={<Atividade05 />} />
            <Route path="/atividade06" element={<Atividade06 />} />
            <Route path="/atividade07" element={<Atividade07 />} />
            <Route path="/atividade08" element={<Atividade08 />} />
            <Route path="/atividade09" element={<Atividade09 />} />
            <Route path="/atividade10" element={<Atividade10 />} />
            <Route path="/atividade11" element={<Atividade11 />} />
            <Route path="/atividade12" element={<Atividade12 />} />
            <Route path="/atividade13" element={<Atividade13 />} />
            <Route path="/atividade14" element={<Atividade14 />} />
            <Route path="/atividade15" element={<Atividade15 />} />
            <Route path="/atividade16" element={<Atividade16 />} />
            <Route path="/atividade17" element={<Atividade17 />} />
            <Route path="/atividade18" element={<Atividade18 />} />
            <Route path="/atividade19" element={<Atividade19 />} />
            <Route path="/atividade20" element={<Atividade20 />} />
            <Route path="/atividade21" element={<Atividade21 />} />
            <Route path="/atividade22" element={<Atividade22 />} />
            <Route path="/atividade23" element={<Atividade23 />} />
            <Route path="/atividade24" element={<Atividade24 />} />
            <Route path="/atividade25" element={<Atividade25 />} />
            <Route path="/atividade26" element={<Atividade26 />} />
            <Route path="/atividade27" element={<Atividade27 />} />
            <Route path="/atividade28" element={<Atividade28 />} />
            <Route path="/atividade29" element={<Atividade29 />} />
            <Route path="/atividade30" element={<Atividade30 />} />
          </Routes>
        </main>
      </div>
    </Router>
  );
}

export default App;

/* @section ArchitectureMap
 * Descrição técnica da estrutura e fluxo de dados.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
