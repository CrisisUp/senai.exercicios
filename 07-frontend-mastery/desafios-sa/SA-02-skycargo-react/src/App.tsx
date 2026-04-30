/**
 * @file App.tsx
 * @brief Orquestrador Final do SkyCargo React Engine (SA-02).
 */

import './styles/theme.css';
import { MissionProvider } from './contexts/MissionContext';
import ControlTower from './components/ControlTower';

function App() {
  return (
    <MissionProvider>
        <ControlTower />
    </MissionProvider>
  );
}

export default App;
