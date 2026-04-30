/**
 * @file sw.js
 * @brief Service Worker do Nexus: Gestão de Cache e Modo Offline.
 */

const CACHE_NAME = 'nexus-vault-v1';
const ASSETS = [
    './',
    './index.html',
    './style.css',
    './script.js'
];

// 1. INSTALAÇÃO: Salva os arquivos no disco local
self.addEventListener('install', (event) => {
    event.waitUntil(
        caches.open(CACHE_NAME).then((cache) => {
            console.log('[SW] Cache aberto. Guardando ativos industriais.');
            return cache.addAll(ASSETS);
        })
    );
});

// 2. ATIVAÇÃO: Limpa versões antigas de cache
self.addEventListener('activate', (event) => {
    console.log('[SW] Worker ativado e pronto.');
});

// 3. ESTRATÉGIA DE FETCH: Cache First
self.addEventListener('fetch', (event) => {
    event.respondWith(
        caches.match(event.request).then((response) => {
            // Retorna do cache se existir, senão vai para a rede
            return response || fetch(event.request);
        })
    );
});
