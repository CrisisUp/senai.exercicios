/**
 * @file sw.js
 * @brief Service Worker para modo offline do Nexus Terminal.
 */

const CACHE_NAME = 'nexus-v3-cache';
const ASSETS = [
    './',
    './index.html',
    './style.css',
    './script.js'
];

self.addEventListener('install', (event) => {
    event.waitUntil(
        caches.open(CACHE_NAME).then((cache) => {
            return cache.addAll(ASSETS);
        })
    );
});

self.addEventListener('fetch', (event) => {
    event.respondWith(
        caches.match(event.request).then((response) => {
            return response || fetch(event.request);
        })
    );
});
