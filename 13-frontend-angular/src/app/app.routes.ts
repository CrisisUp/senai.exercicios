/**
 * @file app.routes.ts
 * @brief Definição de Rotas do Ecossistema Nexus - Desafio Final de Elite.
 * @author Cristiano
 * @date 2026
 */
import { Routes } from '@angular/router';
import { Atividade01Component } from './pages/atividade01/atividade01.component';
import { Atividade02Component } from './pages/atividade02/atividade02.component';
import { Atividade03Component } from './pages/atividade03/atividade03.component';
import { Atividade04Component } from './pages/atividade04/atividade04.component';
import { Atividade05Component } from './pages/atividade05/atividade05.component';
import { Atividade06Component } from './pages/atividade06/atividade06.component';
import { Atividade07Component } from './pages/atividade07/atividade07.component';
import { Atividade08Component } from './pages/atividade08/atividade08.component';
import { Atividade09Component } from './pages/atividade09/atividade09.component';
import { Atividade10Component } from './pages/atividade10/atividade10.component';
import { Atividade11Component } from './pages/atividade11/atividade11.component';
import { Atividade12Component } from './pages/atividade12/atividade12.component';
import { Atividade13Component } from './pages/atividade13/atividade13.component';
import { Atividade14Component } from './pages/atividade14/atividade14.component';
import { Atividade15Component } from './pages/atividade15/atividade15.component';
import { Atividade16Component } from './pages/atividade16/atividade16.component';
import { Atividade17Component } from './pages/atividade17/atividade17.component';
import { RestrictedZoneComponent } from './pages/atividade17/components/restricted-zone/restricted-zone.component';
import { securityGuard } from './pages/atividade17/guards/security.guard';
import { Atividade18Component } from './pages/atividade18/atividade18.component';
import { Atividade19Component } from './pages/atividade19/atividade19.component';
import { Atividade20Component } from './pages/atividade20/atividade20.component';
import { Atividade21Component } from './pages/atividade21/atividade21.component';
import { Atividade22Component } from './pages/atividade22/atividade22.component';
import { Atividade23Component } from './pages/atividade23/atividade23.component';
import { Atividade24Component } from './pages/atividade24/atividade24.component';
import { Atividade25Component } from './pages/atividade25/atividade25.component';
import { Atividade26Component } from './pages/atividade26/atividade26.component';
import { Atividade27Component } from './pages/atividade27/atividade27.component';
import { Atividade28Component } from './pages/atividade28/atividade28.component';
import { Atividade29Component } from './pages/atividade29/atividade29.component';
import { Atividade30Component } from './pages/atividade30/atividade30.component';
import { Atividade31Component } from './pages/atividade31/atividade31.component';
import { Atividade32Component } from './pages/atividade32/atividade32.component';
import { Atividade33Component } from './pages/atividade33/atividade33.component';
import { Atividade34Component } from './pages/atividade34/atividade34.component';
import { Atividade35Component } from './pages/atividade35/atividade35.component';
import { Atividade36Component } from './pages/atividade36/atividade36.component';

export const routes: Routes = [
  { path: 'atividade01', component: Atividade01Component },
  { path: 'atividade02', component: Atividade02Component },
  { path: 'atividade03', component: Atividade03Component },
  { path: 'atividade04', component: Atividade04Component },
  { path: 'atividade05', component: Atividade05Component },
  { path: 'atividade06', component: Atividade06Component },
  { path: 'atividade07', component: Atividade07Component },
  { path: 'atividade08', component: Atividade08Component },
  { path: 'atividade09', component: Atividade09Component },
  { path: 'atividade10', component: Atividade10Component },
  { path: 'atividade11', component: Atividade11Component },
  { path: 'atividade12', component: Atividade12Component },
  { path: 'atividade13', component: Atividade13Component },
  { path: 'atividade14', component: Atividade14Component },
  { path: 'atividade15', component: Atividade15Component },
  { path: 'atividade16', component: Atividade16Component },
  { 
    path: 'atividade17', 
    component: Atividade17Component,
    children: [
      { 
        path: 'restricted', 
        component: RestrictedZoneComponent,
        canActivate: [securityGuard] 
      }
    ]
  },
  { path: 'atividade18', component: Atividade18Component },
  { path: 'atividade19', component: Atividade19Component },
  { path: 'atividade20', component: Atividade20Component },
  { path: 'atividade21', component: Atividade21Component },
  { path: 'atividade22', component: Atividade22Component },
  { path: 'atividade23', component: Atividade23Component },
  { path: 'atividade24', component: Atividade24Component },
  { path: 'atividade25', component: Atividade25Component },
  { path: 'atividade26', component: Atividade26Component },
  { path: 'atividade27', component: Atividade27Component },
  { path: 'atividade28', component: Atividade28Component },
  { path: 'atividade29', component: Atividade29Component },
  { path: 'atividade30', component: Atividade30Component },
  { path: 'atividade31', component: Atividade31Component },
  { path: 'atividade32', component: Atividade32Component },
  { path: 'atividade33', component: Atividade33Component },
  { path: 'atividade34', component: Atividade34Component },
  { path: 'atividade35', component: Atividade35Component },
  { path: 'atividade36', component: Atividade36Component },
  { path: '', redirectTo: 'atividade36', pathMatch: 'full' }
];

/* @section ArchitectureMap
 * O roteador atinge o marco final: O Nexus Prime Core.
 * Orquestração Enterprise total integrando todas as camadas de maestria.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
